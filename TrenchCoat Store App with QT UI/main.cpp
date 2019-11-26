#include "Assig11.h"
#include "appMode.h"
#include "user.h"

#include <QtWidgets/QApplication>
#include <iostream>
#include <crtdbg.h>
#include <string>

#include "DynamicVector.h"
#include "TrenchCoat.h"
#include "Console.h"
#include "Controller.h"
#include "ControllerCSV.h"
#include "ControllerHTML.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	std::vector<TrenchCoat> repo;
	ControllerCSV ctrl_csv{ repo };
	ControllerHTML ctrl_html{ repo };

	auto mainW = new appMode(ctrl_csv);

	mainW->show();

	return a.exec();
}
