#include <utils/TConfig.h>
#include "TComboDialog.h"

TComboDialog::TComboDialog(QString n) : name(n) {
	QVBoxLayout *l = new QVBoxLayout;


	// List
	QGroupBox *gr = new QGroupBox(tr("Редактирование списка"));

	QVBoxLayout *gl = new QVBoxLayout;
	QHBoxLayout *hl = new QHBoxLayout;

	QPushButton *b_add = new QPushButton("Добавить");
	QPushButton *b_rem = new QPushButton("Удалить");
	list = new QListWidget;

	connect(b_add, &QPushButton::clicked, this, &TComboDialog::add);
	connect(b_rem, &QPushButton::clicked, this, &TComboDialog::rem);

	hl->addWidget(b_add);
	hl->addWidget(b_rem);

	gl->addLayout(hl);
	gl->addWidget(list);

	gr->setLayout(gl);

	if (n != "") {
		QJsonArray a = TConfig().get(n).toArray();

		for (QJsonValue v : a) {
			QJsonObject o = v.toObject();

			map.insert(o["name"].toString(), o["str"].toString());
			list->addItem(o["name"].toString());
		}
	}
	// List


	QPushButton *b_save = new QPushButton(tr("Сохранить"));

	connect(b_save, &QPushButton::clicked, this, &TComboDialog::save);

	l->addWidget(gr);
	l->addWidget(b_save);

	setLayout(l);
}

void TComboDialog::save() {
	QJsonArray a;

	for (QString k : map.keys()) {
		a << QJsonObject{{"name", k},
		                 {"str",  map[k]}};
	}

	TConfig().set(name, a);

	this->accept();
}

void TComboDialog::editList(QString n) {
	TComboDialog *d = new TComboDialog(n);
	d->exec();
}

void TComboDialog::add() { // TODO: Create own dialog with 2 fields or add them to layout
	QString n = QInputDialog::getText(this, tr("Добавление строки"), tr("Название:"));
	QString l = QInputDialog::getText(this, tr("Добавление строки"), tr("Параметр:"));

	if (n != "" && l != "") {
		list->addItem(n);
		map.insert(n, l);
	}
}

void TComboDialog::rem() {
	auto selected = list->selectedItems();
	if (selected.size() == 0)
		return;

	QString curr = selected.value(0)->text();

	if (QMessageBox::question(this, tr("Удаление строки"),
	                          QString("%1 \n \"%2\"").arg(tr("Вы точно хотите удалить строку")).arg(curr)) ==
	    QMessageBox::Yes) {
		delete selected.value(0);

		map.remove(curr);
	}
}
