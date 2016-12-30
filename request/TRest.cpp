#include "TRest.h"

TRest::TRest() {
	QVBoxLayout *l = new QVBoxLayout;

	// Utils
	QGroupBox *b1 = new QGroupBox("Request");
	QHBoxLayout *l1 = new QHBoxLayout;

	l_url = new QLineEdit;

	b_send = new QPushButton("Send");
	b_send->setMaximumWidth(75);
	connect(l_url, &QLineEdit::returnPressed, this, &TRest::sendRequest);
	connect(b_send, &QPushButton::clicked, this, &TRest::sendRequest);

	l1->addWidget(l_url);
	l1->addWidget(b_send);

	b1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	b1->setLayout(l1);
	l->addWidget(b1);
	// Utils

	// Requests
	QGroupBox *b2 = new QGroupBox("Response");
	QVBoxLayout *l2 = new QVBoxLayout;

	t_res = new QTextEdit;

	l2->addWidget(t_res);

	b2->setLayout(l2);
	l->addWidget(b2);
	// Requests

	setLayout(l);
}

void TRest::sendRequest() {
	if (b_send->text() == "...")
		return;

	b_send->setText("...");

	QString url = l_url->text();
	QMap<QString, QString> par;

	processResponse(db.GET(url, par));

	b_send->setText("Send");
}

void TRest::processResponse(QString response) {
	t_res->setText(response);
}
