#ifndef THEATRE_ADMIN_TDLOGIN_H
#define THEATRE_ADMIN_TDLOGIN_H

#include <QtWidgets/QDialog>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

class TDLogin : public QDialog {
	QLineEdit *e_login, *e_password;
	QPushButton *b_acc, *b_rej;

public:
	TDLogin(QString mess = "", QWidget *parent = 0);

	static QJsonObject getCredentials(QString mess = "", QWidget *parent = 0);
};


#endif //THEATRE_ADMIN_TDLOGIN_H
