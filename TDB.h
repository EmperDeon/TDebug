#ifndef THEATRE_ADMIN_TDB_H
#define THEATRE_ADMIN_TDB_H

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonObject>
#include "TConfig.h"

class TDB {
	QNetworkAccessManager manager;
	QJsonObject lastReply;
	QString token;
	TConfig conf;

	QStringList roles;

	QJsonValue GET(QString path, QMap<QString, QString> params);

	void getToken();

	void refreshToken();

	void checkAndRefreshToken();

	bool hasErrors();

public:
	TDB();

	QJsonValue request(QString path, QMap<QString, QString> params = QMap<QString, QString>());

	QJsonObject lastError();

	QStringList getPerms();
};


#endif //THEATRE_ADMIN_TDB_H
