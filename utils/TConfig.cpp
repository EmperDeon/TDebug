#include <QtCore/QFile>
#include <QtCore/QJsonDocument>
#include "TConfig.h"

#define FILENAME "config.json"

QJsonObject TConfig::load() {
	QFile f(FILENAME);
	if (f.exists()) {
		f.open(QFile::ReadOnly);
		return QJsonDocument::fromJson(f.readAll()).object();

	}

	return QJsonObject();
}

void TConfig::save(QJsonObject obj) {
	QFile f(FILENAME);
	f.open(QFile::WriteOnly);
	f.write(QJsonDocument(obj).toJson());
	f.close();
}

QJsonValue TConfig::get(QString key, QJsonValue def) {
	QJsonObject obj = load();

	return obj.contains(key) ? obj.value(key) : def;
}

bool TConfig::has(QString key) {
	QJsonObject obj = load();

	return obj.contains(key);
}

void TConfig::set(QString key, QJsonValue val) {
	QJsonObject obj = load();

	obj.insert(key, val);

	save(obj);
}

QString TConfig::getS(QString key, QString def) {
	QJsonObject obj = load();

	return obj.contains(key) ? obj.value(key).toString(def) : def;
}

void TConfig::rem(QString key) {
	QJsonObject obj = load();

	obj.remove(key);

	save(obj);
}

