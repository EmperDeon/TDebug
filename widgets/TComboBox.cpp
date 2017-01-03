#include "TComboBox.h"

TComboBox::TComboBox(QString n) : name(n) {
	reload();

	connect(this, &QComboBox::currentTextChanged, [=](QString s) {
		TConfig().set(getFieldName(), this->currentIndex());
	});
}

void TComboBox::reload() {
	if (name != "") {
		QJsonArray a = TConfig().get(name).toArray();

		for (QJsonValue v : a) {
			QJsonObject o = v.toObject();

			this->addItem(o["name"].toString(), o["str"].toString());
		}

		int active = TConfig().get(getFieldName()).toInt();
		this->setCurrentIndex(active);
	}
}

QString TComboBox::getFieldName() const {
	QString n = name;
	n[0] = toupper(n[0].toLatin1());

	return "last" + n;
}

QString TComboBox::getCurrent() {
	return currentData().toString();
}