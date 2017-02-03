#include <QtCore/QFile>
#include <QtCore/QJsonDocument>
#include "TConfig.h"

TConfig::TConfig() {
	reload();
}

void TConfig::reload() {
	QFile f(fileName);
	if (f.exists()) {
		f.open(QFile::ReadOnly);
		obj = QJsonDocument::fromJson(f.readAll()).object();
		f.close();

	} else {
		obj = QJsonObject();

	}
}

void TConfig::save() {
	QFile f(fileName);
	f.open(QFile::WriteOnly);
	f.write(QJsonDocument(obj).toJson());
	f.close();
}

TConfig::~TConfig() {
	save();
}

QJsonValue TConfig::get(QString key, QJsonValue def) const {
	return obj.contains(key) ? obj.value(key) : def;
}

bool TConfig::has(QString key) const {
	return obj.contains(key);
}

void TConfig::set(QString key, QJsonValue val) {
	obj.insert(key, val);

	save();
}

QString TConfig::getS(QString key, QString def) const {
	return obj.contains(key) ? obj.value(key).toString(def) : def;
}

void TConfig::rem(QString key) {
	obj.remove(key);

	save();
}

