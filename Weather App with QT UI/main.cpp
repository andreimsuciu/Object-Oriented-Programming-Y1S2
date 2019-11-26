#include "preg.h"
#include <QtWidgets/QApplication>
#include <iostream>
#include <crtdbg.h>
#include <string>
#include "Controller.h"
#include "Interval.h"
#include "Tests.h"
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	std::vector<Interval> repo;
	Controller ctrl{ repo };
	test();
	preg w(ctrl);

	w.show();
	return a.exec();
}
