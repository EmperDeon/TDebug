#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <TConfig.h>
#include "TDLogin.h"

TDLogin::TDLogin(QString mess, QWidget *parent) : QDialog(parent) {
	QFormLayout *l = new QFormLayout;
	QLabel *l_mess = new QLabel(mess == "" ? tr("Введите логин/пароль для входа:") : mess);

	l_mess->setAlignment(Qt::AlignCenter);

	e_login = new QLineEdit(TConfig().getS("login"));
	e_login->setAlignment(Qt::AlignCenter);
	e_login->setPlaceholderText(tr("Логин"));
	e_login->setTextMargins(5, 5, 5, 5);

	e_password = new QLineEdit;
	e_password->setAlignment(Qt::AlignCenter);
	e_password->setEchoMode(QLineEdit::Password);
	e_password->setPlaceholderText(tr("Пароль"));
	e_password->setTextMargins(5, 5, 5, 5);

	QHBoxLayout *hl = new QHBoxLayout;

	b_acc = new QPushButton(tr("ОК"));
	b_acc->setAutoDefault(true);

	b_rej = new QPushButton(tr("Отмена"));

	connect(b_acc, SIGNAL(clicked()), this, SLOT(accept()));
	connect(b_rej, SIGNAL(clicked()), this, SLOT(reject()));

	hl->addWidget(b_acc);
	hl->addWidget(b_rej);

	l->addRow(l_mess);
	l->addRow(e_login);
	l->addRow(e_password);
	l->addRow(hl);

	l->setAlignment(Qt::AlignCenter);

	setLayout(l);
	setMinimumWidth(320);
	setFixedHeight(sizeHint().height());
}

QJsonObject TDLogin::getCredentials(QString mess, QWidget *parent) {
	TDLogin dlg(mess, parent);

	int ret = dlg.exec();
	if (ret) {
		return QJsonObject{{"login",    dlg.e_login->text()},
		                   {"password", dlg.e_password->text()}};

	} else {
		return QJsonObject();

	}
}
