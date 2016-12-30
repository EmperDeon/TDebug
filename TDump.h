#ifndef THEATRE_DEBUG_TDUMP_H
#define THEATRE_DEBUG_TDUMP_H

#include <QtCore/QtCore>

class TDump {

	QString dumpFile(QString fileName);

	QString dumpFolder(QString dirName);

	void dump();
};


#endif //THEATRE_DEBUG_TDUMP_H
