#include "TUrl.h"

TUrl::TUrl() : QGroupBox(tr("Запрос")) {
	QHBoxLayout *l = new QHBoxLayout;

	c_url = new TComboBox("servers");
	l_url = new QLineEdit(TConfig::get("lastUrl").toString());

	b_hide = new QPushButton;
	b_send = new QPushButton(tr("Send"));

	b_hide_up = QIcon(":/marker-inv-up.png");
	b_hide_dn = QIcon(":/marker-inv.png");

	c_url->setFixedSize(75, 30);
	b_send->setFixedSize(75, 30);
	b_hide->setIcon(b_hide_up);

	l_url->setMinimumHeight(30);

	connect(l_url, &QLineEdit::returnPressed, this, &TUrl::sendRequest);
	connect(l_url, &QLineEdit::textChanged, this, &TUrl::saveUrl);
	connect(b_hide, &QPushButton::clicked, this, &TUrl::toggleParams);
	connect(b_send, &QPushButton::clicked, this, &TUrl::sendRequest);

	l->addWidget(c_url);
	l->addWidget(l_url);
	l->addWidget(b_hide);
	l->addWidget(b_send);

	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	setLayout(l);

	QTimer::singleShot(10, [=]() { l_url->setFocus(); });
}

void TUrl::reloadLists() {

}

void TUrl::toggleHideButton(bool v) {
	b_hide->setIcon(v ? b_hide_dn : b_hide_up);
}

QString TUrl::getUrl() {
	return c_url->getCurrent() + l_url->text();
}

bool TUrl::tryLock() {
	if (b_send->text() == "...") {
		return false;

	} else {
		b_send->setText("...");
		return true;

	}
}

void TUrl::unlock() {
	b_send->setText(tr("Отправить"));
}

void TUrl::saveUrl() {
	TConfig::set("lastUrl", l_url->text());
}

