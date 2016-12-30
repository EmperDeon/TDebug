#include "TDebug.h"

TDebug::TDebug() {
	QVBoxLayout *l = new QVBoxLayout;

	// Utils
	QGroupBox *b1 = new QGroupBox("Utils");
	QHBoxLayout *l1 = new QHBoxLayout;


	QPushButton *b_clear = new QPushButton("Clear token");
	connect(b_clear, &QPushButton::clicked, this, &TDebug::clearToken);
	l1->addWidget(b_clear);

	b1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	b1->setLayout(l1);
	l->addWidget(b1);
	// Utils

	// Requests
	QGroupBox *b2 = new QGroupBox("Requests");
	QVBoxLayout *l2 = new QVBoxLayout;


	b2->setLayout(l2);
	l->addWidget(b2);
	// Requests

	resize(500, 600);
	setLayout(l);
}

void TDebug::clearToken() {

}
