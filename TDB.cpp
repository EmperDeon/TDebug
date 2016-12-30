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

QJsonValue TDB::request(QString path, QMap<QString, QString> params) {
	qDebug() << "Request:" << path << ", params:" << params;

	checkAndRefreshToken();
	params.insert("token", token);

	QJsonValue r = GET(path, params);
	hasErrors();

	return r;
}

QJsonValue TDB::GET(QString path, QMap<QString, QString> params) {
//	QUrl c("https://laravel-theatre.herokuapp.com/api/" + path);
	QUrl c("http://laravel.dev/api/" + path);

	QUrlQuery q;
	for (QString k : params.keys())
		q.addQueryItem(k, params[k]);

	c.setQuery(q);
//qDebug() << c;

	QNetworkReply *reply = manager.get(QNetworkRequest(c));
	QEventLoop wait;
	QObject::connect(&manager, SIGNAL(finished(QNetworkReply * )), &wait, SLOT(quit()));
	QTimer::singleShot(10000, &wait, SLOT(quit()));
	wait.exec();
	lastReply = QJsonDocument::fromJson(reply->readAll()).object();
	reply->deleteLater();

	return lastReply["response"];
}

QJsonObject TDB::lastError() {
	return QJsonObject{{"error",   lastReply["error"]},
	                   {"message", lastReply["message"]}};
}

void TDB::getToken() {
	QJsonObject cred = TDLogin::getCredentials();
	if (cred.isEmpty()) {
		exit(0); // TODO: prettify

	} else {
		conf.set("login", cred["login"]);

		QString o = GET("auth/new", QMap<QString, QString>{
				{"login",    cred["login"].toString()},
				{"password", cred["password"].toString()}
		}).toString();

		if (hasErrors()) {
			getToken();

		} else {
			token = o;
			conf.set("token", token);

		}
	}
}

void TDB::checkAndRefreshToken() {
	GET("auth/check", {{"token", token}}).toString();

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

		// TODO: move this to windows
//		if (err == "no_access") {
//			mess = QObject::tr("Недостаточно прав для этого действия");
//
//		} else
		if (err == "invalid_credentials") {
			mess = QObject::tr("Неправильный логин/пароль");

		} else if (err == "could_not_create_token") {
			mess = QObject::tr("Внутренняя ошибка сервера") + '\n' +
			       QObject::tr("Обратитесь к администратору с фотографией ошибки") + '\n' +
			       lastReply["message"].toString();

		}

		QMessageBox::critical(0, err, mess);
		return true;
	}

	return false;
}

void TDB::refreshToken() {
	QString o = GET("auth/ref", {{"token", token}}).toString();


	if (!hasErrors()) {
		token = o;
		conf.set("token", token);
	}
}

QStringList TDB::getPerms() {
	QStringList r;

	QJsonArray o = request("auth/perms").toArray();
	for (QJsonValue v : o)
		r << v.toString();

	return r;
}


