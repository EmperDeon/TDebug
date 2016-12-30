#include <QApplication>
#include "TDebug.h"

int main(int argc, char **argv) {
	QApplication a(argc, argv);

	TDebug *app = new TDebug();
	app->show();

	return a.exec();
}