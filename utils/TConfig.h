#ifndef THEATRE_ADMIN_TCONFIG_H
#define THEATRE_ADMIN_TCONFIG_H

#include <QtCore/QJsonValue>
#include <QtCore/QJsonObject>

class TConfig {
	QJsonObject obj;
	const QString fileName = "config.json";

public:
	TConfig();

	void reload();

	void save();

	~TConfig();

	QJsonValue get(QString key, QJsonValue def = QJsonValue()) const;

	QString getS(QString key, QString def = "") const;

	bool has(QString key) const;

	void set(QString key, QJsonValue val);

	void rem(QString key);
};


#endif //THEATRE_ADMIN_TCONFIG_H
