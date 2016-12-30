#include <QtCore/QUrlQuery>
#include <QtCore/QEventLoop>
#include <QtCore/QTimer>
#include <QtCore/QJsonArray>
#include <QtCore/QJsonDocument>
#include <QtNetwork/QNetworkReply>
#include <QtWidgets/QMessageBox>
#include "TDLogin.h"
#include "TDB.h"

TDB::TDB() {
	token = conf.getS("token");
}


QString TDB::GET(QString path, QMap<QString, QString> params) {
	QUrl c(path);

	QUrlQuery q;
	for (QString k : params.keys())
		q.addQueryItem(k, params[k]);

	c.setQuery(q);

	QNetworkReply *reply = manager.get(QNetworkRequest(c));
	QEventLoop wait;
	QObject::connect(&manager, SIGNAL(finished(QNetworkReply * )), &wait, SLOT(quit()));
	QTimer::singleShot(10000, &wait, SLOT(quit()));
	wait.exec();
	QByteArray repl = reply->readAll();
	lastReply = QJsonDocument::fromJson(repl).object();
	reply->deleteLater();

	return QString::fromUtf8(repl);
}

void TDB::getToken() {
	QJsonObject cred = TDLogin::getCredentials();
	if (cred.isEmpty()) {
		exit(0); // TODO: prettify

	} else {
		conf.set("login", cred["login"]);
		GET("auth/new", QMap<QString, QString>{
				{"login",    cred["login"].toString()},
				{"password", cred["password"].toString()}
		});

		QString o = lastReply["response"].toString();

		if (hasErrors()) {
			getToken();

		} else {
			token = o;
			conf.set("token", token);

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
		conf.set("token", token);
	}
}


