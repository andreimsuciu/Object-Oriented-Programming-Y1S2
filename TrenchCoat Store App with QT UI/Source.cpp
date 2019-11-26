#include <iostream>
#include <sstream>


void Lab1112Gui::addEventToUsersList()
{
	/ QListWidgetItem currentEvent = new QListWidgetItem{};
	currentEvent = this->leftList->selectedItems()[0];
	this->rightList->addItem(currentEvent);

	? ? ? ? ?

		*/
		if (this->leftList->count() > 0)
		{
			const QString& currentEventQString = this->leftList->currentItem()->text();
			const std::string& currentEventSTDString = currentEventQString.toUtf8().constData();
			int position = 0;
			std::string titleOfEvent;
			for (const char& character : currentEventSTDString)
			{
				if (character == ' ')
				{
					titleOfEvent = currentEventSTDString.substr(0, position);
					break;
				}
				else
				{
					position++;
				}
			}
			try
			{
				this->controller.addElementToListUserController(titleOfEvent);
				this->leftList->clear();
				this->populateAdministratorList();
				this->rightList->clear();
				this->populateUserList();
			}
			catch (RepositoryException& e)
			{
				QLabel* errorMessage = new QLabel{ QString::fromUtf8(e.what().c_str()) };
				QFont errorMessageFont = errorMessage->font();
				errorMessageFont.setPointSize(30);
				errorMessageFont.setBold(true);
				errorMessage->setFont(errorMessageFont);
				QHBoxLayout* secondaryLayout = new QHBoxLayout{};
				errorMessage->adjustSize();
				errorMessage->setLayout(secondaryLayout);
				errorMessage->show();
			}
		}
}

void Lab1112Gui::removeEventFromUsersList()
{
	if (this->leftList->count() > 0)
	{
		const QString& currentEventQString = this->leftList->currentItem()->text();
		const std::string& currentEventSTDString = currentEventQString.toUtf8().constData();
		int position = 0;
		std::string titleOfEvent;
		for (const char& character : currentEventSTDString)
		{
			if (character == ' ')
			{
				titleOfEvent = currentEventSTDString.substr(0, position);
				break;
			}
			else
			{
				position++;
			}
		}
		try
		{
			this->controller.removeElementFromListUserController(titleOfEvent);
			this->leftList->clear();
			this->populateAdministratorList();
			this->rightList->clear();
			this->populateUserList();
		}
		catch (RepositoryException& e)
		{
			QLabel* errorMessage = new QLabel{ QString::fromUtf8(e.what().c_str()) };
			QFont errorMessageFont = errorMessage->font();
			errorMessageFont.setPointSize(30);
			errorMessageFont.setBold(true);
			errorMessage->setFont(errorMessageFont);
			QHBoxLayout* secondaryLayout = new QHBoxLayout{};
			errorMessage->adjustSize();
			errorMessage->setLayout(secondaryLayout);
			errorMessage->show();
		}
	}
}

void Lab1112Gui::sortedChronologically()
{
	const QString& monthQString = this->monthEdit->text();
	std::string month = monthQString.toUtf8().constData();
	bool validMonth = true;
	if (month != "" && month != "january" && month != "february" && month != "march" && month != "april" && month != "may" && month != "june"
		&& month != "july" && month != "august" && month != "september" && month != "october" && month != "november" && month != "december")
		validMonth = false;
	if (validMonth == true)
	{
		this->month = month;
		this->leftList->clear();
		this->populateAdministratorList();
		this->monthEdit->setText(QString::fromUtf8(""));
	}
	else
	{
		QLabel* errorMessage = new QLabel{ "UserInterfaceException: Please introduce a valid month!" };
		QFont errorMessageFont = errorMessage->font();
		errorMessageFont.setPointSize(30);
		errorMessageFont.setBold(true);
		errorMessage->setFont(errorMessageFont);
		QHBoxLayout* secondaryLayout = new QHBoxLayout{};
		errorMessage->adjustSize();
		errorMessage->setLayout(secondaryLayout);
		errorMessage->show();
	}
	this->monthEdit->setText(QString::fromUtf8(""));
}

void Lab1112Gui::openFile()
{
	this->controller.openFileListController();
}

void Lab1112Gui::processNextEvent()
{
	this->leftList->setCurrentRow(this->leftList->currentRow() + 1);
}

void Lab1112Gui::addEventToAdministratorList()
{
	const QString titleQString = this->titleEdit->text();
	const QString descriptionQString = this->descriptionEdit->text();
	const QString numberOfPeopleQString = this->numberOfPeopleEdit->text();
	const QString linkQString = this->linkEdit->text();
	const QString fullDateWithSpacesQString = this->calendar->selectedDate().toString("dd-MM-yyyy");
	const QString hourQString = this->hourEdit->text();
	const QString minuteQString = this->minuteEdit->text();

	bool allFieldsAreFilled = true;
	if (titleQString.isEmpty() == true)
	{
		allFieldsAreFilled = false;
	}
	else if (descriptionQString.isEmpty() == true)
	{
		allFieldsAreFilled = false;
	}
	else if (numberOfPeopleQString.isEmpty() == true)
	{
		allFieldsAreFilled = false;
	}
	else if (linkQString.isEmpty() == true)
	{
		allFieldsAreFilled = false;
	}
	else if (fullDateWithSpacesQString.isEmpty() == true)
	{
		allFieldsAreFilled = false;
	}
	else if (hourQString.isEmpty() == true)
	{
		allFieldsAreFilled = false;
	}
	else if (minuteQString.isEmpty() == true)
	{
		allFieldsAreFilled = false;
	}

	if (allFieldsAreFilled == true)
	{
		std::string title = titleQString.toUtf8().constData();
		std::string description = descriptionQString.toUtf8().constData();
		std::string numberOfPeople = numberOfPeopleQString.toUtf8().constData();
		std::string link = linkQString.toUtf8().constData();

		std::istringstream fullDate(fullDateWithSpacesQString.toUtf8().constData());
		std::string day;
		std::getline(fullDate, day, '-');
		std::string month;
		std::getline(fullDate, month, '-');
		std::string year;
		std::getline(fullDate, year, '-');

		std::string hour = hourQString.toUtf8().constData();
		std::string minute = minuteQString.toUtf8().constData();

		try
		{
			this->controller.addController(title, description, day, month, year, hour, minute, numberOfPeople, link);
			this->leftList->clear();
			this->populateAdministratorList();

		}
		catch (ValidatorException& v)
		{
			QLabel* errorMessage = new QLabel{ QString::fromUtf8(v.what().c_str()) };
			QFont errorMessageFont = errorMessage->font();
			errorMessageFont.setPointSize(30);
			errorMessageFont.setBold(true);
			errorMessage->setFont(errorMessageFont);
			QHBoxLayout* secondaryLayout = new QHBoxLayout{};
			errorMessage->adjustSize();
			errorMessage->setLayout(secondaryLayout);
			errorMessage->show();
		}
		catch (RepositoryException& r)
		{
			QLabel* errorMessage = new QLabel{ QString::fromUtf8(r.what().c_str()) };
			QFont errorMessageFont = errorMessage->font();
			errorMessageFont.setPointSize(30);
			errorMessageFont.setBold(true);
			errorMessage->setFont(errorMessageFont);
			QHBoxLayout* secondaryLayout = new QHBoxLayout{};
			errorMessage->adjustSize();
			errorMessage->setLayout(secondaryLayout);
			errorMessage->show();
		}
	}
	else
	{
		QLabel* errorMessage = new QLabel{ "UserInterfaceException: Please complete all the fields before adding!" };
		QFont errorMessageFont = errorMessage->font();
		errorMessageFont.setPointSize(30);
		errorMessageFont.setBold(true);
		errorMessage->setFont(errorMessageFont);
		QHBoxLayout* secondaryLayout = new QHBoxLayout{};
		errorMessage->adjustSize();
		errorMessage->setLayout(secondaryLayout);
		errorMessage->show();
	}
	this->titleEdit->setText(QString::fromUtf8(""));
	this->descriptionEdit->setText(QString::fromUtf8(""));
	this->numberOfPeopleEdit->setText(QString::fromUtf8(""));
	this->linkEdit->setText(QString::fromUtf8(""));
	this->hourEdit->setText(QString::fromUtf8(""));
	this->minuteEdit->setText(QString::fromUtf8(""));
}

void Lab1112Gui::removeEventFromAdministratorList()
{
	const QString& titleQString = this->titleEdit->text();
	const std::string& titleOfEvent = titleQString.toUtf8().constData();
	int position = 0;

	try
	{
		this->controller.removeController(titleOfEvent);
		this->leftList->clear();
		this->populateAdministratorList();
	}
	catch (ValidatorException& v)
	{
		QLabel* errorMessage = new QLabel{ QString::fromUtf8(v.what().c_str()) };
		QFont errorMessageFont = errorMessage->font();
		errorMessageFont.setPointSize(30);
		errorMessageFont.setBold(true);
		errorMessage->setFont(errorMessageFont);
		QHBoxLayout* secondaryLayout = new QHBoxLayout{};
		errorMessage->adjustSize();
		errorMessage->setLayout(secondaryLayout);
		errorMessage->show();
	}
	catch (RepositoryException& r)
	{
		QLabel* errorMessage = new QLabel{ QString::fromUtf8(r.what().c_str()) };
		QFont errorMessageFont = errorMessage->font();
		errorMessageFont.setPointSize(30);
		errorMessageFont.setBold(true);
		errorMessage->setFont(errorMessageFont);
		QHBoxLayout* secondaryLayout = new QHBoxLayout{};
		errorMessage->adjustSize();
		errorMessage->setLayout(secondaryLayout);
		errorMessage->show();
	}
	this->titleEdit->setText(QString::fromUtf8(""));
}

void Lab1112Gui::updateEventFromAdministratorList()
{
	if (this->leftList->count() > 0)
	{
		const QString titleQString = this->titleEdit->text();
		const QString newTitleQString = this->newTitleEdit->text();
		const QString descriptionQString = this->descriptionEdit->text();
		const QString numberOfPeopleQString = this->numberOfPeopleEdit->text();
		const QString linkQString = this->linkEdit->text();
		const QString fullDateWithSpacesQString = this->calendar->selectedDate().toString("dd-MM-yyyy");
		const QString hourQString = this->hourEdit->text();
		const QString minuteQString = this->minuteEdit->text();

		const std::string& titleOfEvent = titleQString.toUtf8().constData();


		if (descriptionQString.isEmpty() == false)
		{
			try
			{
				this->controller.updateController("description", titleOfEvent, descriptionQString.toUtf8().constData());
			}
			catch (ValidatorException& v)
			{
				QLabel* errorMessage = new QLabel{ QString::fromUtf8(v.what().c_str()) };
				QFont errorMessageFont = errorMessage->font();
				errorMessageFont.setPointSize(30);
				errorMessageFont.setBold(true);
				errorMessage->setFont(errorMessageFont);
				QHBoxLayout* secondaryLayout = new QHBoxLayout{};
				errorMessage->adjustSize();
				errorMessage->setLayout(secondaryLayout);
				errorMessage->show();
			}
			this->descriptionEdit->setText(QString::fromUtf8(""));
		}
		if (fullDateWithSpacesQString.isEmpty() == false)
		{
			std::istringstream fullDate(fullDateWithSpacesQString.toUtf8().constData());
			std::string day;
			std::getline(fullDate, day, '-');
			std::string month;
			std::getline(fullDate, month, '-');
			std::string year;
			std::getline(fullDate, year, '-');
			try
			{
				this->controller.updateController("day", titleOfEvent, day);
				this->controller.updateController("month", titleOfEvent, month);
				this->controller.updateController("year", titleOfEvent, year);
			}
			catch (ValidatorException& v)
			{
				QLabel* errorMessage = new QLabel{ QString::fromUtf8(v.what().c_str()) };
				QFont errorMessageFont = errorMessage->font();
				errorMessageFont.setPointSize(30);
				errorMessageFont.setBold(true);
				errorMessage->setFont(errorMessageFont);
				QHBoxLayout* secondaryLayout = new QHBoxLayout{};
				errorMessage->adjustSize();
				errorMessage->setLayout(secondaryLayout);
				errorMessage->show();
			}
		}
		if (numberOfPeopleQString.isEmpty() == false)
		{
			try
			{
				this->controller.updateController("numberOfPeople", titleOfEvent, numberOfPeopleQString.toUtf8().constData());
			}
			catch (ValidatorException& v)
			{
				QLabel* errorMessage = new QLabel{ QString::fromUtf8(v.what().c_str()) };
				QFont errorMessageFont = errorMessage->font();
				errorMessageFont.setPointSize(30);
				errorMessageFont.setBold(true);
				errorMessage->setFont(errorMessageFont);
				QHBoxLayout* secondaryLayout = new QHBoxLayout{};
				errorMessage->adjustSize();
				errorMessage->setLayout(secondaryLayout);
				errorMessage->show();
			}
			this->numberOfPeopleEdit->setText(QString::fromUtf8(""));
		}
		if (linkQString.isEmpty() == false)
		{
			try
			{
				this->controller.updateController("link", titleOfEvent, linkQString.toUtf8().constData());
			}
			catch (ValidatorException& v)
			{
				QLabel* errorMessage = new QLabel{ QString::fromUtf8(v.what().c_str()) };
				QFont errorMessageFont = errorMessage->font();
				errorMessageFont.setPointSize(30);
				errorMessageFont.setBold(true);
				errorMessage->setFont(errorMessageFont);
				QHBoxLayout* secondaryLayout = new QHBoxLayout{};
				errorMessage->adjustSize();
				errorMessage->setLayout(secondaryLayout);
				errorMessage->show();
			}
			this->linkEdit->setText(QString::fromUtf8(""));
		}
		if (hourQString.isEmpty() == false)
		{
			try
			{
				this->controller.updateController("hour", titleOfEvent, hourQString.toUtf8().constData());
			}
			catch (ValidatorException& v)
			{
				QLabel* errorMessage = new QLabel{ QString::fromUtf8(v.what().c_str()) };
				QFont errorMessageFont = errorMessage->font();
				errorMessageFont.setPointSize(30);
				errorMessageFont.setBold(true);
				errorMessage->setFont(errorMessageFont);
				QHBoxLayout* secondaryLayout = new QHBoxLayout{};
				errorMessage->adjustSize();
				errorMessage->setLayout(secondaryLayout);
				errorMessage->show();
			}
			this->hourEdit->setText(QString::fromUtf8(""));
		}
		if (minuteQString.isEmpty() == false)
		{
			try
			{
				this->controller.updateController("minute", titleOfEvent, minuteQString.toUtf8().constData());
			}
			catch (ValidatorException& v)
			{
				QLabel* errorMessage = new QLabel{ QString::fromUtf8(v.what().c_str()) };
				QFont errorMessageFont = errorMessage->font();
				errorMessageFont.setPointSize(30);
				errorMessageFont.setBold(true);
				errorMessage->setFont(errorMessageFont);
				QHBoxLayout* secondaryLayout = new QHBoxLayout{};
				errorMessage->adjustSize();
				errorMessage->setLayout(secondaryLayout);
				errorMessage->show();
			}
			this->minuteEdit->setText(QString::fromUtf8(""));
		}
		if (newTitleQString.isEmpty() == false)
		{
			try
			{
				this->controller.updateController("title", titleOfEvent, newTitleQString.toUtf8().constData());
			}
			catch (ValidatorException& v)
			{
				QLabel* errorMessage = new QLabel{ QString::fromUtf8(v.what().c_str()) };
				QFont errorMessageFont = errorMessage->font();
				errorMessageFont.setPointSize(30);
				errorMessageFont.setBold(true);
				errorMessage->setFont(errorMessageFont);
				QHBoxLayout* secondaryLayout = new QHBoxLayout{};
				errorMessage->adjustSize();
				errorMessage->setLayout(secondaryLayout);
				errorMessage->show();
			}
			this->titleEdit->setText(QString::fromUtf8(""));
			this->newTitleEdit->setText(QString::fromUtf8(""));
		}
		this->leftList->clear();
		this->populateAdministratorList();
	}
}

void Lab1112Gui::openTheSiteOfEvent()
{
	if (this->leftList->count() > 0)
	{
		try
		{
			const QString& titleQString = this->leftList->currentItem()->text();
			std::string currentEventSTDString = titleQString.toUtf8().constData();
			std::string titleOfEvent;
			int position = 0;
			for (const char& character : currentEventSTDString)
			{
				if (character == ' ')
				{
					titleOfEvent = currentEventSTDString.substr(0, position);
					break;
				}
				else
				{
					position++;
				}
			}
			this->controller.playController(titleOfEvent);
		}
		catch (RepositoryException& r)
		{
			QLabel* errorMessage = new QLabel{ QString::fromUtf8(r.what().c_str()) };
			QFont errorMessageFont = errorMessage->font();
			errorMessageFont.setPointSize(30);
			errorMessageFont.setBold(true);
			errorMessage->setFont(errorMessageFont);
			QHBoxLayout* secondaryLayout = new QHBoxLayout{};
			errorMessage->adjustSize();
			errorMessage->setLayout(secondaryLayout);
			errorMessage->show();
		}
	}
	else
	{
		QLabel* errorMessage = new QLabel{ "UserInterfaceException: Please complete all the fields before adding!" };
		QFont errorMessageFont = errorMessage->font();
		errorMessageFont.setPointSize(30);
		errorMessageFont.setBold(true);
		errorMessage->setFont(errorMessageFont);
		QHBoxLayout* secondaryLayout = new QHBoxLayout{};
		errorMessage->adjustSize();
		errorMessage->setLayout(secondaryLayout);
		errorMessage->show();
	}
}

void Lab1112Gui::sortTheAdministratorList()
{
	this->leftList->clear();
	this->month = "";
	this->populateAdministratorList();
}

void Lab1112Gui::shuffleTheAdministratorList()
{
	this->leftList->clear();
	this->month = "";
	this->populateAdministratorListShuffled();
}


void Lab1112Gui::lockAdministrator()
{
	this->leftList->setEnabled(false);
	this->rightList->setEnabled(false);
	this->titleEdit->setEnabled(false);
	this->newTitleEdit->setEnabled(false);
	this->descriptionEdit->setEnabled(false);
	this->numberOfPeopleEdit->setEnabled(false);
	this->linkEdit->setEnabled(false);
	this->calendar->setEnabled(false);
	this->hourEdit->setEnabled(false);
	this->minuteEdit->setEnabled(false);
	this->addButton->setEnabled(false);
	this->removeButton->setEnabled(false);
	this->updateButton->setEnabled(false);
	this->sortedButton->setEnabled(false);
	this->shuffledButton->setEnabled(false);

}

void Lab1112Gui::lockUser()
{
	this->leftList->setEnabled(false);
	this->rightList->setEnabled(false);
	this->monthEdit->setEnabled(false);
	this->fileMiddleButton->setEnabled(false);
	this->siteMiddleButton->setEnabled(false);
	this->transferMiddleButton->setEnabled(false);
	this->transferBackMiddleButton->setEnabled(false);
	this->nextMiddleButton->setEnabled(false);
	this->browseButton->setEnabled(false);
}

Lab1112Gui::Lab1112Gui(Controller& c, QWidget *p)
	: controller(c), QMainWindow(p)
{
	this->month = "";
	this->initialize();
	this->populateAdministratorList();
	this->populateUserList();
	connect(this->transferMiddleButton, &QPushButton::released, this, &Lab1112Gui::addEventToUsersList);
	connect(this->transferBackMiddleButton, &QPushButton::released, this, &Lab1112Gui::removeEventFromUsersList);
	connect(this->browseButton, &QPushButton::released, this, &Lab1112Gui::sortedChronologically);
	connect(this->siteMiddleButton, &QPushButton::released, this, &Lab1112Gui::openTheSiteOfEvent);
	connect(this->nextMiddleButton, &QPushButton::released, this, &Lab1112Gui::processNextEvent);
	connect(this->fileMiddleButton, &QPushButton::released, this, &Lab1112Gui::openFile);
	connect(this->addButton, &QPushButton::released, this, &Lab1112Gui::addEventToAdministratorList);
	connect(this->removeButton, &QPushButton::released, this, &Lab1112Gui::removeEventFromAdministratorList);
	connect(this->updateButton, &QPushButton::released, this, &Lab1112Gui::updateEventFromAdministratorList);
	connect(this->sortedButton, &QRadioButton::clicked, this, &Lab1112Gui::sortTheAdministratorList);
	connect(this->shuffledButton, &QRadioButton::clicked, this, &Lab1112Gui::shuffleTheAdministratorList);
	QWidget* window = new QWidget{};
	window->setLayout(this->mainLayout);
	setCentralWidget(window);

}

void Lab1112Gui::initialize()
{
	this->mainLayout = new QVBoxLayout{};

	this->upLayout = new QHBoxLayout{};
	this->upLeftLayout = new QVBoxLayout{};
	this->upMiddleLayout = new QVBoxLayout{};
	this->upRightLayout = new QVBoxLayout{};

	this->leftLabel = new QLabel{ "All events" };
	this->leftList = new QListWidget{};
	this->fileMiddleButton = new QPushButton{ "file" };
	this->siteMiddleButton = new QPushButton{ "site" };
	this->transferMiddleButton = new QPushButton{ ">" };
	this->transferBackMiddleButton = new QPushButton{ "<" };
	this->nextMiddleButton = new QPushButton{ "next" };
	this->rightLabel = new QLabel{ "Attendance" };
	this->rightList = new QListWidget{};

	upLeftLayout->addWidget(leftLabel);
	upLeftLayout->addWidget(leftList);

	upMiddleLayout->addWidget(fileMiddleButton);
	upMiddleLayout->addWidget(siteMiddleButton);
	upMiddleLayout->addWidget(transferMiddleButton);
	upMiddleLayout->addWidget(transferBackMiddleButton);
	upMiddleLayout->addWidget(nextMiddleButton);

	upRightLayout->addWidget(rightLabel);
	upRightLayout->addWidget(rightList);

	upLayout->addLayout(upLeftLayout);
	upLayout->addLayout(upMiddleLayout);
	upLayout->addLayout(upRightLayout);

	this->bottomLayout = new QHBoxLayout{};
	this->botLeftLayout = new QFormLayout{};
	this->botRightLayout = new QVBoxLayout{};
	this->botRightTimeLayout = new QHBoxLayout{};
	this->hourLayout = new QFormLayout{};
	this->minuteLayout = new QFormLayout{};

	this->titleEdit = new QLineEdit{};
	this->newTitleEdit = new QLineEdit{};
	this->descriptionEdit = new QLineEdit{};
	this->numberOfPeopleEdit = new QLineEdit{};
	this->linkEdit = new QLineEdit{};
	this->monthEdit = new QLineEdit{};

	this->addButton = new QPushButton{ "add" };
	this->removeButton = new QPushButton{ "remove" };
	this->updateButton = new QPushButton{ "update" };
	this->browseButton = new QPushButton{ "browse" };
	this->buttonLayout = new QVBoxLayout{};
	this->radioButtonLayout = new QHBoxLayout{};
	this->sortedButton = new QRadioButton{ "sorted" };
	this->shuffledButton = new QRadioButton{ "shuffled" };
	this->sortedButton->setChecked(true);

	botLeftLayout->addRow("Title", titleEdit);
	botLeftLayout->addRow("UpdateTitle", newTitleEdit);
	botLeftLayout->addRow("Description", descriptionEdit);
	botLeftLayout->addRow("Number of people", numberOfPeopleEdit);
	botLeftLayout->addRow("Link", linkEdit);
	botLeftLayout->addRow("Month", monthEdit);

	radioButtonLayout->addWidget(sortedButton);
	radioButtonLayout->addWidget(shuffledButton);
	buttonLayout->addWidget(addButton);
	buttonLayout->addWidget(removeButton);
	buttonLayout->addWidget(updateButton);
	buttonLayout->addWidget(browseButton);
	buttonLayout->addLayout(radioButtonLayout);

	botLeftLayout->addRow(buttonLayout);

	this->hourEdit = new QLineEdit{};
	this->minuteEdit = new QLineEdit{};

	hourLayout->addRow("Hour", hourEdit);
	minuteLayout->addRow("Minute", minuteEdit);

	botRightTimeLayout->addLayout(hourLayout);
	botRightTimeLayout->addLayout(minuteLayout);

	this->calendar = new QCalendarWidget{};

	botRightLayout->addWidget(calendar);
	botRightLayout->addLayout(botRightTimeLayout);

	bottomLayout->addLayout(botLeftLayout);
	bottomLayout->addLayout(botRightLayout);

	this->mainLayout->addLayout(upLayout);
	this->mainLayout->addLayout(bottomLayout);
}

void Lab1112Gui::populateAdministratorList()
{
	std::vector<TElem>* elements = new std::vector<TElem>;
	elements = this->controller.browseThroughEventsController(this->month);
	for (TElem element : *elements)
	{
		new QListWidgetItem(QString::fromUtf8(element.printElement().c_str()), this->leftList);
	}
	this->leftList->setCurrentIndex(this->leftList->model()->index(0, 0));
}

void Lab1112Gui::populateAdministratorListShuffled()
{
	std::vector<TElem>* elements = new std::vector<TElem>;
	elements = this->controller.browseThroughEventsController(this->month);
	int added = 0;
	std::vector<int> alreadyAdded;
	while (added != elements->size())
	{
		bool ok = true;
		int position = 0;
		while (ok == true)
		{
			position = std::rand() % elements->size();
			bool found = false;
			for (int element : alreadyAdded)
			{
				if (element == position)
					found = true;
			}
			if (found == false)
			{
				alreadyAdded.push_back(position);
				ok = false;
			}
		}
		new QListWidgetItem(QString::fromUtf8(elements->at(position).printElement().c_str()), this->leftList);
		added++;
	}
	this->leftList->setCurrentIndex(this->leftList->model()->index(0, 0));
}

void Lab1112Gui::populateUserList()
{
	std::vector<TElem>* elements = new std::vector<TElem>;
	elements = this->controller.getAllUserController();
	for (TElem element : *elements)
	{
		new QListWidgetItem(QString::fromUtf8(element.printElement().c_str()), this->rightList);
	}
}