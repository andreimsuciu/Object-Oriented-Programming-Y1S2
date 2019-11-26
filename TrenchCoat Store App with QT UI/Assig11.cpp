#include "Assig11.h"


Assig11::Assig11(ControllerCSV &ctrl,QWidget *parent): QMainWindow(parent), ctrl{ctrl}
{
	ui.setupUi(this);
	this->populateList();
	this->ui.coatListWidget->setStyleSheet("background-color: qlineargradient(x1: 0.5, y1: 0.5 x2: 0.5, y2: 1, stop: 0 #6666FF, stop: 0.7 #99CCFF );");
	this->ui.coatListWidget->setCurrentIndex(this->ui.coatListWidget->model()->index(0,0));
	connect(this->ui.add_button, &QPushButton::clicked, this, &Assig11::addToAdminList);
	connect(this->ui.remove_button, &QPushButton::clicked, this, &Assig11::removeFromAdminList);
	connect(this->ui.update_button, &QPushButton::clicked, this, &Assig11::updateAdminList);
	connect(this->ui.sortRadioButton, &QRadioButton::clicked, this, &Assig11::sort);
	connect(this->ui.shuffleRadioButton, &QRadioButton::clicked, this, &Assig11::shuffle);
}

void Assig11::populateList() {
	std::vector<TrenchCoat>* coat_vector = new std::vector<TrenchCoat>;
	coat_vector = this->ctrl.getAll();
	for (int i = 0; i < coat_vector->size(); i++) {
		new QListWidgetItem(QString::fromUtf8(coat_vector->at(i).trenchCoatToString().c_str()), this->ui.coatListWidget);
	}
	delete coat_vector;
}

void Assig11::removeFromAdminList()
{
	const QString coat = this->ui.coatListWidget->currentItem()->text();
	std::string coat_str = coat.toUtf8().constData();

	std::string colour;
	std::string size;
	int fields = 0, pos = 0, pos2=0;
	for (const char &c : coat_str) {
		if (fields == 2) {
			break;
		}
		if (c == ' ') {
			if (fields == 0) {
				size = coat_str.substr(0, pos);
				pos++;
				pos2 = pos;
			}
			else
				colour = coat_str.substr(pos2, pos-pos2);
			fields++;
		}
		else {
			pos++;
		}
	}
	try {
		this->ctrl.removeCoat(stoi(size), colour);
		this->ui.coatListWidget->clear();
		this->populateList();

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

void Assig11::addToAdminList() {
	const QString sizeEdit = this->ui.sizeEdit->text();
	const QString colourEdit = this->ui.colourEdit->text();
	const QString priceEdit = this->ui.priceEdit->text();
	const QString quantityEdit = this->ui.quantityEdit->text();
	const QString linkEdit = this->ui.linkEdit->text();

	std::string sizeEdit_str = sizeEdit.toUtf8().constData();
	std::string colourEdit_str = colourEdit.toUtf8().constData();
	std::string priceEdit_str = priceEdit.toUtf8().constData();
	std::string quantityEdit_str = quantityEdit.toUtf8().constData();
	std::string linkEdit_str = linkEdit.toUtf8().constData();
	
	bool allFieldsCompleted = true;
	if (sizeEdit_str == "")
		allFieldsCompleted = false;
	else if (colourEdit_str == "")
		allFieldsCompleted = false;
	else if (priceEdit_str == "")
		allFieldsCompleted = false;
	else if (quantityEdit_str == "")
		allFieldsCompleted = false;
	else if (linkEdit_str == "")
		allFieldsCompleted = false;

	if (allFieldsCompleted == false) {
		QLabel *crucialError = new QLabel{ QString::fromUtf8("All fields should be completed!") };
		QFont boldIt = crucialError->font();
		boldIt.setPointSize(30);
		boldIt.setBold(true);
		crucialError->setFont(boldIt);

		crucialError->show();
	}
	else {
		try {
			this->ctrl.addCoat(stoi(sizeEdit_str), colourEdit_str, stoi(priceEdit_str), stoi(quantityEdit_str), linkEdit_str);
			this->ui.coatListWidget->clear();
			this->populateList();
			
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
void Assig11::sort() {
	this->ctrl.sortL();
	this->ui.coatListWidget->clear();
	this->populateList();
}

void Assig11::shuffle() {
	this->ctrl.shuffle();
	this->ui.coatListWidget->clear();
	this->populateList();
}

void Assig11::updateAdminList() {
	const QString sizeEdit = this->ui.sizeEdit->text();
	const QString colourEdit = this->ui.colourEdit->text();
	const QString priceEdit = this->ui.priceEdit->text();
	const QString quantityEdit = this->ui.quantityEdit->text();
	const QString linkEdit = this->ui.linkEdit->text();

	std::string sizeEdit_str = sizeEdit.toUtf8().constData();
	std::string colourEdit_str = colourEdit.toUtf8().constData();
	std::string priceEdit_str = priceEdit.toUtf8().constData();
	std::string quantityEdit_str = quantityEdit.toUtf8().constData();
	std::string linkEdit_str = linkEdit.toUtf8().constData();

	bool allFieldsCompleted = true;
	if (sizeEdit_str == "")
		allFieldsCompleted = false;
	else if (colourEdit_str == "")
		allFieldsCompleted = false;
	else if (priceEdit_str == "")
		allFieldsCompleted = false;
	else if (quantityEdit_str == "")
		allFieldsCompleted = false;
	else if (linkEdit_str == "")
		allFieldsCompleted = false;

	if (allFieldsCompleted == false) {
		QLabel *crucialError = new QLabel{ QString::fromUtf8("All fields should be completed!") };
		QFont boldIt = crucialError->font();
		boldIt.setPointSize(30);
		boldIt.setBold(true);
		crucialError->setFont(boldIt);

		crucialError->show();
	}
	else {
		try {
			this->ctrl.updateCoat(stoi(sizeEdit_str), colourEdit_str, stoi(priceEdit_str), stoi(quantityEdit_str), linkEdit_str);
			this->ui.coatListWidget->clear();
			this->populateList();

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
