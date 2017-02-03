#include <utils/TDump.h>
#include <widgets/TComboDialog.h>
#include <widgets/TTextDialog.h>
#include <auth/TAuth.h>
#include "TMainWindow.h"

TMainWindow::TMainWindow() {
	wgt = new TRest;

	constructMenu();

	setCentralWidget(wgt);
	resize(500, 600);
}

void TMainWindow::constructMenu() {
	QMenuBar *menu = this->menuBar();

	QMenu *u = menu->addMenu("Utils");
	u->addAction(getNewAction("Dump source code", []() { (new TDump)->show(); }));

	QMenu *l = menu->addMenu("Lists");
	l->addAction(getNewAction("Edit 'Servers'", [=]() {
		TComboDialog::editList("servers");
		wgt->reloadLists();
	}));
	l->addAction(getNewAction("Edit 'Variables'", [=]() {
		TTextDialog::editList("vars");
		wgt->reloadLists();
	}));

	QMenu *a = menu->addMenu("Auth");
	a->addAction(getNewAction("Clear", []() { TAuth::clearToken(); }));
	a->addAction(getNewAction("Get new", []() { TAuth::getToken(); }));
}

QAction *TMainWindow::getNewAction(QString name, std::function<void()> func) const {
	QAction *a = new QAction(name);
	connect(a, &QAction::triggered, func);

	return a;
}
