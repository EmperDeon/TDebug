#ifndef THEATRE_DEBUG_TCOMBODIALOG_H
#define THEATRE_DEBUG_TCOMBODIALOG_H

#include <QtWidgets/QtWidgets>

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


#endif //THEATRE_DEBUG_TCOMBODIALOG_H
