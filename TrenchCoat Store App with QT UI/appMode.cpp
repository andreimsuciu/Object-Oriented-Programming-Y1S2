#include "appMode.h"
appMode::appMode(ControllerCSV &ctrl,QWidget *parent) : QMainWindow(parent), ctrl{ctrl}
{
	ui.setupUi(this);
	this->w = new Assig11(ctrl,this);
	this->u = new user(ctrl, this);
	connect(this->ui.adminButton, &QPushButton::clicked, this, &appMode::admin);
	connect(this->ui.userButton, &QPushButton::clicked, this, &appMode::showUser);
}

void appMode::admin() {
	this->w->show();
}

void appMode::showUser() {
	
	this->u->show();
}