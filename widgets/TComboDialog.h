#ifndef THEATRE_DEBUG_TCOMBODIALOG_H
#define THEATRE_DEBUG_TCOMBODIALOG_H

#include <QtWidgets/QtWidgets>

class TInputDialog;

class TComboDialog : public QDialog {
	QString name;
	QListWidget *list;

	QMap<QString, QString> map;

	void add();

	void rem();

public:
	TComboDialog(QString n);

	void save();

	static void editList(QString n);
};


class TInputDialog : QDialog {
	QLineEdit *l_par1, *l_par2;

public:
	TInputDialog();

	static QPair<QString, QString> getParams();
};


#endif //THEATRE_DEBUG_TCOMBODIALOG_H
