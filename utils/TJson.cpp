#include "TJson.h"

QString TJson::printO(QJsonObject o, int offset) {
	QString r;
	r += printK(offset, "{\n");
	offset += 1;

	for (QString k : o.keys()) {
		QJsonValue v = o[k];

		r += printK(offset, k) + ": " + printV(v, offset) + ",\n";
	}

	if (r.size() > 3)
		r = r.remove(r.size() - 2, 1);

	r += printK(offset - 1, "}");
	return r;
}

QString TJson::printS(QString s) {
	return "\"" + s.replace('\n', ' ') + "\"";
}

QString TJson::printI(int i) {
	return QString::number(i);
}

QString TJson::printA(QJsonArray a, int offset) {
	QString r;
	r += "\n";
	r += printK(offset, "[\n");
	offset += 1;

	for (QJsonValue v : a) {
		r += printV(v, offset);
		r += ",\n";

	}

	if (r.size() > 3)
		r = r.remove(r.size() - 2, 1);

	r += printK(offset - 1, "]");
	return r;
}

QString TJson::printV(QJsonValue v, int offset) {
	if (v.isObject()) {
		return printO(v.toObject(), offset);

	} else if (v.isArray()) {
		return printA(v.toArray(), offset);

	} else if (v.isString()) {
		return printS(v.toString());

	} else if (v.isDouble()) {
		return printI(v.toInt());

	}

	return "Undefined";
}

QString TJson::printK(int offset, QString k) {
	if (k.contains(QRegExp("[\\{,\\},\\[,\\]]")))
		return QString().fill(' ', offset * 4) + k;
	else
		return QString().fill(' ', offset * 4) + "\"" + k + "\"";
}

TJsonHighlighter::TJsonHighlighter(QTextDocument *d) : QSyntaxHighlighter(d) {

}

void TJsonHighlighter::highlightBlock(const QString &text) {
	enum {
		NormalState = -1, InKey, InStr, InNum
	};

	int state = previousBlockState();
	int start = 0;

	if (en)
		for (int i = 0; i < text.length(); ++i) {
			if (state == InKey) {
				if (text.mid(i, 2) == "\":") {
					state = NormalState;
					setFormat(start, i - start + 1, QColor::fromRgb(117, 135, 166));
				}

			} else if (state == InStr) {
				if (QRegExp("\",|\"").exactMatch(text.mid(i, 3))) {
					state = NormalState;
					setFormat(start, i - start + 1, QColor::fromRgb(106, 135, 89));
				}

			} else if (state == InNum) {
				if (!QRegExp("\\+|-|\\d").exactMatch(text.mid(i, 1))) {
					state = NormalState;
					setFormat(start, i - start + 1, QColor::fromRgb(207, 106, 76));
				}

			} else {
				if (text.mid(i - 2, 3) == ": \"") {
					start = i;
					state = InStr;

				} else if (text.mid(i, 1) == "\"") {
					start = i;
					state = InKey;

				} else if (QRegExp("\\+|-|\\d").exactMatch(text.mid(i, 1))) {
					start = i;
					state = InNum;
				}
			}
		}

	if (state == InNum)
		setFormat(start, text.length() - start, QColor::fromRgb(207, 106, 76));


	if (state == InStr || state == InKey)
		setFormat(start, text.length() - start, Qt::green);

	setCurrentBlockState(state);
}

void TJsonHighlighter::setEnabled(bool state) {
	en = state;
}
