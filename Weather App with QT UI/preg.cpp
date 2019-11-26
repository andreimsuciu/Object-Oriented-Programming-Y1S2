#include "preg.h"

preg::preg(Controller &ctrl, QWidget *parent) : QMainWindow(parent), ctrl{ctrl}
{
	ui.setupUi(this);
	this->populateList();
	this->ui.items->setCurrentIndex(this->ui.items->model()->index(0, 0));
	connect(this->ui.filterButton, &QPushButton::clicked, this, &preg::filter);
	connect(this->ui.hoursButton, &QPushButton::clicked, this, &preg::hours);
	connect(this->ui.sortButton, &QPushButton::clicked, this, &preg::sort);
	connect(this->ui.updateButton, &QPushButton::clicked, this, &preg::update);
}

void preg::populateList() {
	std::vector<Interval>* interval_vect = new std::vector<Interval>;
	interval_vect = this->ctrl.getAll();
	for (int i = 0; i < interval_vect->size(); i++) {
		new QListWidgetItem(QString::fromUtf8(interval_vect->at(i).intervalToString().c_str()), this->ui.items);
	}
	delete interval_vect;
	this->colorItems();
}

void preg::filter() {
	const QString filterData = this->ui.filterEdit->text();
	std::string filterData_str = filterData.toUtf8().constData();
	
	this->ui.filteredItems->clear();
	std::vector<Interval>* interval_vect = new std::vector<Interval>;
	interval_vect = this->ctrl.filter(stoi(filterData_str));
	for (int i = 0; i < interval_vect->size(); i++) {
		new QListWidgetItem(QString::fromUtf8(interval_vect->at(i).intervalToString().c_str()), this->ui.filteredItems);
	}
	delete interval_vect;
}

void preg::hours() {
	const QString hoursData = this->ui.hoursEdit->text();
	std::string hoursData_str = hoursData.toUtf8().constData();

	int hours=this->ctrl.hours(hoursData_str);
	std::string hours_str = std::to_string(hours);
	this->ui.hoursResultEdit->setText(QString::fromUtf8(hours_str.c_str()));
}

void preg::sort() {
	this->ctrl.sortTemp();
	this->ui.items->clear();
	this->populateList();
}

void preg::update() {
	int index = this->ui.items->currentRow();
	const QString updateData = this->ui.tempEdit->text();
	std::string updateData_str = updateData.toUtf8().constData();
	this->ctrl.update(stoi(updateData_str), index);
	this->ui.items->clear();
	this->populateList();
	this->ui.items->setCurrentIndex(this->ui.items->model()->index(0, 0));
}

void preg::colorItems()
{
	for (int i = 0; i < this->ui.items->count(); i++) {
		std::string desc=this->ctrl.askColor(i);
		if (desc == "sunny")
			this->ui.items->item(i)->setBackground(Qt::yellow);
		if (desc == "rainy")
			this->ui.items->item(i)->setBackground(Qt::blue);
		if (desc == "cloudy")
			this->ui.items->item(i)->setBackground(Qt::gray);
		if (desc == "foggy")
			this->ui.items->item(i)->setBackground(Qt::lightGray);
	}
}
