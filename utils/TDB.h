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

	void getToken();

	void refreshToken();

	void checkAndRefreshToken();

	bool hasErrors();

public:
	TDB();

	QString GET(QString path, QMap<QString, QString> params);
};


#endif //THEATRE_ADMIN_TDB_H
