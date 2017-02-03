//
// Created by ilya on 2/3/2017.
//

#include <QtCore/QJsonObject>
#include <auth/TDLogin.h>
#include <utils/TConfig.h>
#include <utils/TDB.h>
#include <QtCore/QJsonArray>
#include "TAuth.h"

void TAuth::getToken() {
	QJsonObject cred = TDLogin::getCredentials();
	qDebug() << cred;

	if (cred.isEmpty()) {
		exit(0); // TODO: prettify

	} else {
		TConfig().set("login", cred["login"]);
		TDB db;

		db.GET(getUrl() + "auth_api/new", {
				{"login",  cred["login"].toString()},
				{"pass",   cred["password"].toString()},
				{"method", "post"}
		});
		qDebug() << db.lastReply;

		QString o = db.lastReply["response"].toObject()["auth_token"].toString();

		if (db.hasErrors()) {
			getToken();

		} else {
			TConfig().set("token", o);

		}
	}
}

void TAuth::clearToken() {
	TConfig().rem("token");
}

QString TAuth::getUrl() {
	QJsonArray a = TConfig().get("servers").toArray();
	QString s = a[TConfig().get("lastServers").toInt()].toObject()["str"].toString();

	QString url = s + TConfig().get("lastUrl").toString();
	url = url.mid(0, url.indexOf('/', 8));

	return url + '/';
}
