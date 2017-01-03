#include <QtCore/QUrlQuery>
#include <QtCore/QEventLoop>
#include <QtCore/QTimer>
#include <QtCore/QJsonArray>
#include <QtCore/QJsonDocument>
#include <QtNetwork/QNetworkReply>
#include <QtWidgets/QMessageBox>
#include <QtCore/QMetaEnum>
#include "TDLogin.h"
#include "TDB.h"

TDB::TDB() {
	token = TConfig().getS("token");
}

TDBResponse TDB::request(QString path, QMap<QString, QString> params) {
	TDBResponse r;

	r.text = GET(path, params);
	r.code = getLastCode();
	r.time = getLastTime();

	return r;
}


QString TDB::GET(QString path, QMap<QString, QString> params) {
	QTime requestTime;
	requestTime.start();

	if (path.endsWith('/')) {
		path = path.remove(path.length() - 1, 1);
	}

	QUrl c(path);

	QUrlQuery q;
	for (QString k : params.keys())
		if (k != "" && params[k] != "")
			q.addQueryItem(k, params[k]);

	c.setQuery(q);

	QNetworkReply *reply = manager.get(QNetworkRequest(c));
	QEventLoop wait;
	connect(&manager, SIGNAL(finished(QNetworkReply * )), &wait, SLOT(quit()));
	QTimer::singleShot(30000, &wait, SLOT(quit()));
	wait.exec();
	QByteArray repl = reply->readAll();
	lastReply = QJsonDocument::fromJson(repl).object();
	reply->deleteLater();

	lastCode = reply->error();
	lastTime = requestTime.elapsed();

	return QString::fromUtf8(repl);
}

void TDB::getToken() {
	QJsonObject cred = TDLogin::getCredentials();
	if (cred.isEmpty()) {
		exit(0); // TODO: prettify

	} else {
		TConfig().set("login", cred["login"]);
		GET("auth/new", {
				{"login",    cred["login"].toString()},
				{"password", cred["password"].toString()}
		});

		QString o = lastReply["response"].toString();

		if (hasErrors()) {
			getToken();

		} else {
			token = o;
			TConfig().set("token", token);

		}
	}
}

void TDB::checkAndRefreshToken() {
	GET("auth/check", {{"token", token}});

	if (hasErrors()) {
		checkAndRefreshToken();

	}
}

bool TDB::hasErrors() {
	if (lastReply.contains("error")) {
		QString err = lastReply["error"].toString(), mess;
		qDebug() << "Error:" << err;

		if (err == "token_expired") {
			refreshToken();
			return true;
		}

		if (err == "no_token" || err == "token_invalid") {
			getToken();
			return true;
		}

		return true;
	}

	return false;
}

void TDB::refreshToken() {
	GET("auth/ref", {{"token", token}});
	QString o = lastReply["response"].toString();


	if (!hasErrors()) {
		token = o;
		TConfig().set("token", token);
	}
}

QString TDB::getLastTime() {
	QString r = QString::number(lastTime);

	if (r.size() > 3) {
		r = r.insert(r.size() - 3, '\'');

	}

	return r + " ms";
}

QString TDB::getLastCode() {
	QString r;

	if (lastCode == 0) {
		r = "200 OK";

	} else {
		QMetaObject obj = QNetworkReply::staticMetaObject;
		QMetaEnum en = obj.enumerator(obj.indexOfEnumerator("NetworkError"));
		r = QString::number(lastCode) + " - " + en.valueToKey(lastCode);

	}

	return r;
}


