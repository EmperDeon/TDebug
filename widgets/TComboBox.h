#ifndef THEATRE_DEBUG_TCOMBOBOX_H
#define THEATRE_DEBUG_TCOMBOBOX_H

#include <QtCore/QtCore>
#include <QtWidgets/QtWidgets>
#include "utils/TConfig.h"

class TComboBox : public QComboBox {

	QString name;

public:
	TComboBox(QString n);

	void reload();

	QString getCurrent();

	QString getFieldName() const;
};


#endif //THEATRE_DEBUG_TCOMBOBOX_H
