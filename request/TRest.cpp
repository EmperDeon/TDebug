#include <utils/TJson.h>
#include "TRest.h"

TRest::TRest() {
	QVBoxLayout *l = new QVBoxLayout;

	w_request = new TUrl;
	w_params = new TParams;
	w_response = new TResponse;

	// 'Enter' button
	connect(w_request, &TUrl::sendRequest, this, &TRest::sendRequest);
	connect(w_params, &TParams::sendRequest, this, &TRest::sendRequest);

	// 'Hide' button
	connect(w_request, &TUrl::toggleParams, this, &TRest::paramsToggle);

	bool params = TConfig::get("lastParamsActive", false).toBool();
	if (params)
		paramsToggle();

	l->addWidget(w_request);
	l->addWidget(w_params);
	l->addWidget(w_response);
	l->setSpacing(10);

	setLayout(l);
}

void TRest::sendRequest() {
	if (!w_request->tryLock())
		return;

	auto url = w_request->getUrl();
	auto par = w_params->getParams();

	w_response->processResponse(db.request(url, par));

	w_request->unlock();
}

void TRest::reloadLists() {
	w_request->reloadLists();
}

void TRest::paramsToggle() {
	w_params->toggle();
	w_request->toggleHideButton(w_params->isVisible());

	TConfig::set("lastParamsActive", w_params->isVisible());
}
