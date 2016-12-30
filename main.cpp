#include <QApplication>
#include "TMainWindow.h"

int main(int argc, char **argv) {
	QApplication a(argc, argv);

	TMainWindow *app = new TMainWindow();
	app->show();

	return a.exec();
}