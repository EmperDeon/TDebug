#ifndef THEATRE_DEBUG_TPARAMS_H
#define THEATRE_DEBUG_TPARAMS_H

#include <QtWidgets/QtWidgets>
#include "utils/TConfig.h"

class TParams : public QGroupBox {
Q_OBJECT

	QVBoxLayout *p_vl;

	QCheckBox *p_token;
	QList<QLineEdit *> l_keys, l_values;

Q_SIGNALS:

	void sendRequest();

protected:
	void addLine(QList<QWidget *> l = {});

	void delLine();

	void checkLastLine();

	QHBoxLayout *getParamLine(QString key = "", QString val = "");

public:
	TParams();

	void fillFromUrl();

	void toggle();

	QMap<QString, QString> getParams();
};


#endif //THEATRE_DEBUG_TPARAMS_H
