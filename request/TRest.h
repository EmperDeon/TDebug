#ifndef THEATRE_ADMIN_TDEBUG_H
#define THEATRE_ADMIN_TDEBUG_H
#include <QtWidgets/QtWidgets>
#include <widgets/TComboBox.h>
#include "utils/TDB.h"
#include "utils/TJson.h"
#include "request/TParams.h"
#include "TUrl.h"
#include "TResponse.h"

class TUrl;

class TParams;

class TResponse;

class TRest : public QWidget {
	TDB db;

	TUrl *w_request;
	TParams *w_params;
	TResponse *w_response;

public:
	TRest();

	void sendRequest();

	void reloadLists();

	void paramsToggle();
};


#endif //THEATRE_ADMIN_TDEBUG_H
