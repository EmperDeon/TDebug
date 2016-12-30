#ifndef THEATRE_ADMIN_TDEBUG_H
#define THEATRE_ADMIN_TDEBUG_H
#include <QtWidgets/QtWidgets>
#include "utils/TDB.h"
#include "utils/TJson.h"

class TJsonHighlighter;

class TRest : public QWidget {
	TDB db;

	QLineEdit *l_url;
	QPushButton *b_send;

	QTextEdit *t_res;
	TJsonHighlighter *t_hig;

public:
	TRest();

	void sendRequest();

	void processResponse(QString response);
};


#endif //THEATRE_ADMIN_TDEBUG_H
