#ifndef THEATRE_DEBUG_TPARAMS_H
#define THEATRE_DEBUG_TPARAMS_H

#include <QtWidgets/QtWidgets>
#include <widgets/TComboBox.h>
#include "utils/TConfig.h"

class TParams : public QGroupBox {
Q_OBJECT

	QVBoxLayout *p_vl;

	TComboBox *p_method;
	QCheckBox *p_token;
	QList<QLineEdit *> l_keys, l_values;

Q_SIGNALS:
	void sendRequest();

protected:
	void addLine(QList<QWidget *> l = {}, QString key = "", QString val = "");

	void delLine();

	void checkLastLine();

	QHBoxLayout *getParamLine(QString key = "", QString val = "");

public:
	TParams();

	void fillFromJSON(QJsonArray arr);

	void toggle();

	QMap<QString, QString> getParams();
};


#endif //THEATRE_DEBUG_TPARAMS_H
