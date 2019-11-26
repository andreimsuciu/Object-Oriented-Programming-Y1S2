#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_preg.h"
#include "Controller.h"
#include <qlistwidget.h>

class preg : public QMainWindow
{
	Q_OBJECT

public:
	preg(Controller &ctrl,QWidget *parent = Q_NULLPTR);
	void populateList();

private:
	Ui::pregClass ui;
	Controller &ctrl;
public slots:
	void filter();
	void hours();
	void sort();
	void update();
	void colorItems();
};
