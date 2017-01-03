#include <utils/TDB.h>
#include "TResponse.h"

TResponse::TResponse() : QGroupBox(tr("Ответ")) {
	QVBoxLayout *l = new QVBoxLayout;
	QHBoxLayout *hl = new QHBoxLayout;

	QLabel *l_code = new QLabel(tr("Код ответа:"));
	QLabel *l_time = new QLabel(tr("за:"));
	t_code_s = new QLabel;
	t_code_e = new QLabel;
	t_time = new QLabel;

	t_res = new QTextEdit;
	t_hig = new TJsonHighlighter(t_res->document());

	t_hig->setEnabled(false);

	l_code->setProperty("responseStats", true);
	t_code_s->setProperty("responseStats", true);
	t_code_e->setProperty("responseStats", true);
	l_time->setProperty("responseStats", true);
	t_time->setProperty("responseStats", true);

	t_code_s->setStyleSheet("background: #4caf50;  padding: 5px 10px;  border-radius: 4px;");
	t_code_e->setStyleSheet("background: #af3733;  padding: 5px 10px;  border-radius: 4px;");
	t_code_s->setVisible(false);
	t_code_e->setVisible(false);

	hl->setSpacing(0);

	hl->addWidget(l_code);
	hl->addWidget(t_code_s);
	hl->addWidget(t_code_e);
	hl->addSpacerItem(new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Fixed));
	hl->addWidget(l_time);
	hl->addWidget(t_time);

	l->addLayout(hl);
	l->addWidget(t_res);
	setLayout(l);
}

void TResponse::processResponse(TDB &db, QString response) {
	QString code = db.getLastCode();
	t_code_s->setText(code);
	t_code_s->setVisible(code.startsWith("200"));
	t_code_e->setText(code);
	t_code_e->setVisible(!code.startsWith("200"));

	t_time->setText(db.getLastTime());

	if (response.startsWith('{')) {
		t_hig->setEnabled(true);
		QJsonObject o = QJsonDocument::fromJson(response.toUtf8()).object();
		t_res->setText(TJson::printO(o, 0));

	} else {
		t_hig->setEnabled(false);
		t_res->setText(response);

	}
}
