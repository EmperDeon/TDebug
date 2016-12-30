#ifndef THEATRE_ADMIN_TDEBUG_H
#define THEATRE_ADMIN_TDEBUG_H

#include <QtWidgets/QtWidgets>
#include "utils/TDB.h"

class TRest : public QWidget {
	TDB db;

	QLineEdit *l_url;
	QPushButton *b_send;

	QTextEdit *t_res;

public:
	TRest();

	void sendRequest();

	void processResponse(QString response);
};


#endif //THEATRE_ADMIN_TDEBUG_H
