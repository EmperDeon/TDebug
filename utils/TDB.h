#ifndef THEATRE_ADMIN_TDB_H
#define THEATRE_ADMIN_TDB_H
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonObject>
#include "TConfig.h"

struct TDBResponse {
	QString text, code, time;
};

class TDB : public QObject {
	QNetworkAccessManager manager;

	QJsonObject lastReply;
	int lastTime, lastCode;

	QString token;

	void getToken();

	void refreshToken();

	void checkAndRefreshToken();

	bool hasErrors();

public:
	TDB();

	TDBResponse request(QString path, QMap<QString, QString> params);

	QString GET(QString path, QMap<QString, QString> params);

	QString getLastTime();

	QString getLastCode();
};


#endif //THEATRE_ADMIN_TDB_H
