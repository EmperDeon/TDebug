#ifndef THEATRE_DEBUG_TDUMP_H
#define THEATRE_DEBUG_TDUMP_H
#include <QtCore/QtCore>
#include <QtWidgets/QtWidgets>

class TDump : public QWidget {

	QString dumpFile(QString fileName);

	QString dumpFolder(QString dirName);

	void dump();

public:
	TDump();
};


#endif //THEATRE_DEBUG_TDUMP_H
