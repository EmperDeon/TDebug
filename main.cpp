#include <QApplication>
#include "TMainWindow.h"

QString getStylesheet() {
	QFile f(":/style.qss");
	f.open(QFile::ReadOnly);
	return QString::fromUtf8(f.readAll());
}

int main(int argc, char **argv) {
	QApplication a(argc, argv);

	a.setStyleSheet(getStylesheet());

	TMainWindow *app = new TMainWindow();
	app->show();

	return a.exec();
}