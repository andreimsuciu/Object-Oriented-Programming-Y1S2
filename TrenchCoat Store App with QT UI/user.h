#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_user.h"
#include "ControllerCSV.h"
#include <qlistwidget.h>

class user : public QMainWindow
{
	Q_OBJECT

public:
	user(ControllerCSV &ctrl, QWidget *parent = Q_NULLPTR);
	void populateList();
	void populateSizeList();
	void populateBasket();

private:
	Ui::userClass ui;
	ControllerCSV &ctrl;

public slots:
	void addToList();
	void next();
	void create();
};