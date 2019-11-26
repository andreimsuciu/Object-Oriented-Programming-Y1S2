#include "user.h"

user::user(ControllerCSV &ctrl, QWidget *parent) : QMainWindow(parent), ctrl{ ctrl }
{
	ui.setupUi(this);
	this->populateList();
	this->ui.sizeList->setEnabled(false);
	this->ui.coatList->setCurrentIndex(this->ui.coatList->model()->index(0, 0));
	this->ui.sizeList->setCurrentIndex(this->ui.sizeList->model()->index(0, 0));
	connect(this->ui.createListButton, &QPushButton::clicked, this, &user::create);
	connect(this->ui.addButton, &QPushButton::clicked, this, &user::addToList);
	connect(this->ui.nextButton, &QPushButton::clicked, this, &user::next);
}

void user::populateList() {
	std::vector<TrenchCoat>* coat_vector = new std::vector<TrenchCoat>;
	coat_vector = this->ctrl.getAll();
	for (int i = 0; i < coat_vector->size(); i++) {
		new QListWidgetItem(QString::fromUtf8(coat_vector->at(i).trenchCoatToString().c_str()), this->ui.coatList);
	}
	delete coat_vector;
}

void user::populateSizeList() {
	std::vector<TrenchCoat>* coat_vector = new std::vector<TrenchCoat>;
	coat_vector = this->ctrl.getSizeList();
	for (int i = 0; i < coat_vector->size(); i++) {
		new QListWidgetItem(QString::fromUtf8(coat_vector->at(i).trenchCoatToString().c_str()), this->ui.sizeList);
	}
	delete coat_vector;

}

void user::populateBasket() {
	std::vector<TrenchCoat>* coat_vector = new std::vector<TrenchCoat>;
	coat_vector = this->ctrl.getBasket();
	for (int i = 0; i < coat_vector->size(); i++) {
		new QListWidgetItem(QString::fromUtf8(coat_vector->at(i).trenchCoatToString().c_str()), this->ui.BaksetList);
	}
	delete coat_vector;
	int price = this->ctrl.getBasketPrice();
	std::string price_str = std::to_string(price);
	this->ui.priceEdit->setText(QString::fromUtf8(price_str.c_str()));
}

void user::create() {
	const QString sizeEdit = this->ui.sizeEdit->text();
	std::string sizeEdit_str = sizeEdit.toUtf8().constData();
	if (sizeEdit_str == "") {
		QLabel *crucialError = new QLabel{ QString::fromUtf8("Size cannot be empty!") };
		QFont boldIt = crucialError->font();
		boldIt.setPointSize(30);
		boldIt.setBold(true);
		crucialError->setFont(boldIt);

		crucialError->show();
	}
	else {
		try {
			this->ctrl.createSizeList(stoi(sizeEdit_str));
			this->ui.sizeList->clear();
			this->populateSizeList();

		}
		catch (ValidException &exception)
		{
			QLabel *crucialError = new QLabel{ QString::fromUtf8(exception.msg().c_str()) };
			QFont boldIt = crucialError->font();
			boldIt.setPointSize(30);
			boldIt.setBold(true);
			crucialError->setFont(boldIt);

			crucialError->show();
		}
		catch (RepoException &exception) {
			QLabel *crucialError = new QLabel{ QString::fromUtf8(exception.msg().c_str()) };
			QFont boldIt = crucialError->font();
			boldIt.setPointSize(30);
			boldIt.setBold(true);
			crucialError->setFont(boldIt);

			crucialError->show();
		}
	}
		
}

void user::addToList() {
	try {
		this->ctrl.addToBasket();
		this->ui.BaksetList->clear();
		this->populateBasket();
	}
	catch (RepoException &exception) {
		QLabel *crucialError = new QLabel{ QString::fromUtf8(exception.msg().c_str()) };
		QFont boldIt = crucialError->font();
		boldIt.setPointSize(30);
		boldIt.setBold(true);
		crucialError->setFont(boldIt);

		crucialError->show();
	}

}

void user::next() {
	try {
		TrenchCoat coat = this->ctrl.displayNextCoat();
		this->ui.sizeList->clear();
		new QListWidgetItem(QString::fromUtf8(coat.trenchCoatToString().c_str()), this->ui.sizeList);
	}
	catch (RepoException &exception) {
		QLabel *crucialError = new QLabel{ QString::fromUtf8(exception.msg().c_str()) };
		QFont boldIt = crucialError->font();
		boldIt.setPointSize(30);
		boldIt.setBold(true);
		crucialError->setFont(boldIt);

		crucialError->show();
	}
}