#ifndef THEATRE_DEBUG_TMAINWINDOW_H
#define THEATRE_DEBUG_TMAINWINDOW_H

#include <QMainWindow>
#include <request/TRest.h>

class TRest;

class TMainWindow : public QMainWindow {
	TRest *wgt;

public:
	TMainWindow();

	void constructMenu();

	QAction *getNewAction(QString name, std::function<void()> func) const;
};


#endif //THEATRE_DEBUG_TMAINWINDOW_H
