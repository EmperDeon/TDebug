#ifndef THEATRE_DEBUG_TTEXTDIALOG_H
#define THEATRE_DEBUG_TTEXTDIALOG_H

#include <QtWidgets/QtWidgets>

class TInputDialog;

class TTextDialog : public QDialog {
	QString name;
	QListWidget *list;

	QMap<QString, QString> map;

	void add();

	void rem();

public:
	TTextDialog(QString n);

	void save();

	static void editList(QString n);
};

#endif //THEATRE_DEBUG_TTEXTDIALOG_H
