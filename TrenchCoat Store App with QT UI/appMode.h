#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_appMode.h"
#include "ControllerCSV.h"
#include <qlistwidget.h>
#include "Assig11.h"
#include "user.h"
class appMode : public QMainWindow
{
	Q_OBJECT

public:
	appMode(ControllerCSV &ctrl,QWidget *parent = Q_NULLPTR);


private:
	Ui::appMode ui;
	ControllerCSV &ctrl;
	Assig11 *w;
	user *u;

public slots:
	void admin();
	void showUser();
};
