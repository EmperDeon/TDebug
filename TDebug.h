#ifndef THEATRE_ADMIN_TDEBUG_H
#define THEATRE_ADMIN_TDEBUG_H

#include <QtWidgets/QtWidgets>
#include "TDB.h"

class TDebug : public QWidget {
	TDB db;


public:
	TDebug();

	// Utils
	void clearToken();


};


#endif //THEATRE_ADMIN_TDEBUG_H
