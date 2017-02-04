#ifndef THEATRE_ADMIN_TCONFIG_H
#define THEATRE_ADMIN_TCONFIG_H

#include <QtCore/QJsonValue>
#include <QtCore/QJsonObject>

class TConfig {
public:
	static QJsonObject load();

	static void save(QJsonObject obj);

	static QJsonValue get(QString key, QJsonValue def = QJsonValue());

	static QString getS(QString key, QString def = "");

	static bool has(QString key);

	static void set(QString key, QJsonValue val);

	static void rem(QString key);
};


#endif //THEATRE_ADMIN_TCONFIG_H
