#include <utils/TConfig.h>
#include "TParams.h"

TParams::TParams() : QGroupBox(tr("Параметры")) {
	p_vl = new QVBoxLayout;

	QPushButton *b_fill = new QPushButton(tr("Заполнить из адреса"));
	p_token = new QCheckBox(tr("Токен"));

	p_token->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

	connect(b_fill, &QPushButton::clicked, this, &TParams::fillFromUrl);

	addLine({b_fill, p_token});
	addLine();

	setLayout(p_vl);
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
}

void TParams::fillFromUrl() {

}

void TParams::toggle() {
	bool v = !isVisible();

	setVisible(v);
}

void TParams::addLine(QList<QWidget *> l) {
	QHBoxLayout *th;

	if (l.count() == 0) {
		th = getParamLine();

	} else {
		th = new QHBoxLayout;

		for (QWidget *w : l)
			th->addWidget(w);
	}

	p_vl->addLayout(th);
}

QHBoxLayout *TParams::getParamLine(QString key, QString val) {
	QHBoxLayout *r = new QHBoxLayout;
	static int uuid = 0;

	QLineEdit *l_key = new QLineEdit(key);
	QLineEdit *l_val = new QLineEdit(val);
	QPushButton *b_del = new QPushButton(tr("-"));

	l_key->setPlaceholderText(tr("Ключ"));
	l_val->setPlaceholderText(tr("Значение"));
	b_del->setProperty("layoutIndex", uuid);

	r->setProperty("layoutIndex", uuid);

	l_key->setMinimumHeight(25);
	l_val->setMinimumHeight(25);
	b_del->setMinimumHeight(25);

	l_keys << l_key;
	l_values << l_val;

	r->addWidget(l_key);
	r->addWidget(l_val);
	r->addWidget(b_del);

	connect(l_key, &QLineEdit::returnPressed, this, &TParams::sendRequest);
	connect(l_val, &QLineEdit::returnPressed, this, &TParams::sendRequest);
	connect(l_key, &QLineEdit::textChanged, this, &TParams::checkLastLine);
	connect(l_val, &QLineEdit::textChanged, this, &TParams::checkLastLine);
	connect(b_del, &QPushButton::clicked, this, &TParams::delLine);

	uuid++;
	return r;
}

QMap<QString, QString> TParams::getParams() {
	QMap<QString, QString> r;

	if (p_token->isChecked())
		r["token"] = TConfig().get("token").toString();

	for (int i = 0; i < l_keys.size(); i++) {
		r.insert(l_keys[i]->text(), l_values[i]->text());
	}

	return r;
}

void TParams::delLine() {
	QObject *o = sender();

	for (int i = 0; i < p_vl->count(); i++) {
		QLayout *l = p_vl->itemAt(i)->layout();
		if (l->property("layoutIndex") == o->property("layoutIndex")) {
			l_keys.removeAll(dynamic_cast<QLineEdit *>(l->itemAt(0)->widget()));
			l_values.removeAll(dynamic_cast<QLineEdit *>(l->itemAt(1)->widget()));

			for (int j = 0; j < l->count(); j++) {
				l->itemAt(j)->widget()->deleteLater();
			}
			l->deleteLater();
		}
	}

	checkLastLine();
}

void TParams::checkLastLine() {
	int iL = l_keys.count() - 1;
	if (iL < 0 || l_keys[iL]->text() != "" || l_values[iL]->text() != "") {
		addLine();

	}
}
