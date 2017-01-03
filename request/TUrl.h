#ifndef THEATRE_DEBUG_TURL_H
#define THEATRE_DEBUG_TURL_H

#include <QtWidgets/QtWidgets>
#include <widgets/TComboBox.h>

class TUrl : public QGroupBox {
Q_OBJECT

	TComboBox *c_url;
	QLineEdit *l_url;
	QPushButton *b_hide, *b_send;
	QIcon b_hide_up, b_hide_dn;

Q_SIGNALS:

	void toggleParams();

	void sendRequest();


public:
	TUrl();

	void reloadLists();

	void toggleHideButton(bool v);

	bool tryLock();

	void unlock();

	QString getUrl();
};


#endif //THEATRE_DEBUG_TURL_H
