#include "TDump.h"

TDump::TDump() {

}

QString TDump::dumpFile(QString fileName) {
	QString r;

	r += fileName + "\n\n";

	QFile f(fileName);
	f.open(QFile::ReadOnly);
	r += QString::fromUtf8(f.readAll());
	f.close();

	r += "\n\n\n\n";

	return r.replace('\t', ' ');
}

QString TDump::dumpFolder(QString dirName) {
	QString r;
	for (QFileInfo f : QDir(dirName).entryInfoList({"*"}, QDir::AllEntries | QDir::NoDotAndDotDot)) {
		if (f.isDir()) {
			r += dumpFolder(dirName + '/' + f.fileName());
		} else {
			r += dumpFile(f.filePath());
		}
	}

	return r;
}

void TDump::dump() {

	QString out;

	out += dumpFolder("D:/Programming/Theatre_F");

	QFile f("out.txt");
	f.open(QFile::WriteOnly);
	f.write(out.toUtf8());
	f.close();


	qDebug() << "Success";
}