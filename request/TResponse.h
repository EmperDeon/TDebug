#ifndef THEATRE_DEBUG_TRESPONSE_H
#define THEATRE_DEBUG_TRESPONSE_H

#include <QtWidgets/QtWidgets>
#include <utils/TJson.h>
#include <utils/TDB.h>


class TJsonHighlighter;

class TResponse : public QGroupBox {
	QLabel *t_code_s, *t_code_e, *t_time;

	QTextEdit *t_res;
	TJsonHighlighter *t_hig;

public:
	TResponse();

	void processResponse(TDB &db, QString response);
};


#endif //THEATRE_DEBUG_TRESPONSE_H
