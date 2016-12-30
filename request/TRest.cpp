#include <utils/TJson.h>
#include "TRest.h"

TRest::TRest() {
	QVBoxLayout *l = new QVBoxLayout;

	// Utils
	QGroupBox *b1 = new QGroupBox("Request");
	QHBoxLayout *l1 = new QHBoxLayout;

	l_url = new QLineEdit("http://laravel.dev/api/updates/0");

	b_send = new QPushButton("Send");
	b_send->setFixedSize(75, 30);

	l_url->setMinimumHeight(30);

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
	t_res->setFont(QFont("Fantasque Sans Mono", 10));
	t_hig = new TJsonHighlighter(t_res->document());
	t_hig->setEnabled(false);


	l2->addWidget(t_res);

	b2->setLayout(l2);
	l->addWidget(b2);

	l->setSpacing(10);
	// Requests

	setLayout(l);
}//http://laravel-theatre.herokuapp.com/api/updates/0

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
	if (response.startsWith('{')) {
		t_hig->setEnabled(true);
		QJsonObject o = QJsonDocument::fromJson(response.toUtf8()).object();
		t_res->setText(TJson::printO(o, 0));

	} else {
		t_hig->setEnabled(false);
		t_res->setText(response);

	}
}

