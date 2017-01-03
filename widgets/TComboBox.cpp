#include "TComboBox.h"

TComboBox::TComboBox(QString n) : name(n) {
	reload();

	connect(this, &QComboBox::currentTextChanged, [=](QString s) {
		TConfig().set(name + "-active", this->currentIndex());
	});
}

void TComboBox::reload() {
	if (name != "") {
		QJsonArray a = TConfig().get(name).toArray();

		for (QJsonValue v : a) {
			QJsonObject o = v.toObject();

			this->addItem(o["name"].toString(), o["str"].toString());
		}

		int active = TConfig().get(name + "-active").toInt();
		this->setCurrentIndex(active);
	}
}

QString TComboBox::getCurrent() {
	return currentData().toString();
}