#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Assig11.h"
#include "ControllerCSV.h"
#include <qlistwidget.h>
#include <QRadioButton> 
#include <QLinearGradient> 

class Assig11 : public QMainWindow
{
	Q_OBJECT

public:
	Assig11(ControllerCSV &ctrl,QWidget *parent = Q_NULLPTR);
	void populateList();

private:
	Ui::Assig11Class ui;
	ControllerCSV &ctrl;

public slots:
	void addToAdminList();
	void removeFromAdminList();
	void updateAdminList();
	void sort();
	void shuffle();
};
