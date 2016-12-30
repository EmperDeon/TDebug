#ifndef THEATRE_DEBUG_TJSON_H
#define THEATRE_DEBUG_TJSON_H

#include <QtCore/QtCore>
#include <QtWidgets/QtWidgets>

class TJson {
public:
	static QString printO(QJsonObject o, int offset);

	static QString printS(QString s);

	static QString printI(int i);

	static QString printA(QJsonArray a, int offset);

	static QString printV(QJsonValue v, int offset);

	static QString printK(int offset, QString k);
};


class TJsonHighlighter : public QSyntaxHighlighter {
	bool en;

public:
	TJsonHighlighter(QTextDocument *d);

	void setEnabled(bool state);

protected:
	void highlightBlock(const QString &text) override;

};

#endif //THEATRE_DEBUG_TJSON_H
