#include <utils/TDump.h>
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
	u->addAction(getNewAction("Dump source code", [=]() { (new TDump)->show(); }));

}

QAction *TMainWindow::getNewAction(QString name, void (*func)()) const {
	QAction *a = new QAction(name);
	connect(a, &QAction::triggered, func);

	return a;
}
