#include "ControllerHTML.h"

ControllerHTML::ControllerHTML(std::vector<TrenchCoat>& repo) :Controller::Controller{ repo }
{
}

ControllerHTML::~ControllerHTML()
{
}

void ControllerHTML::addToBasket()
{
	Controller::addToBasket();
	this->writeBasketToFile();
}

void ControllerHTML::writeBasketToFile()
{
	std::ofstream fout("..\\..\\..\\..\\..\\..\\Basket.html");
	TrenchCoat coat;
	std::vector<TrenchCoat>::iterator it;

	fout << "<!DOCTYPE html>\n";
	fout << "<html>\n";
	fout << "\t<head>\n";
	fout << "\t\t<title>Basket</title>\n";
	fout << "\t</head>\n";
	fout << "\t<body>\n";
	fout << "\t\t<table border=\"1\">\n";

	for (it = this->basket.begin(); it != this->basket.end(); it++)
	{
		coat = *it;
		fout << "\t\t<tr>\n";
		fout << "\t\t\t<td>" << coat.getSize() << "</td>\n";
		fout << "\t\t\t<td>" << coat.getColour() << "</td>\n";
		fout << "\t\t\t<td>" << coat.getPrice() << "</td>\n";
		fout << "\t\t\t<td>" << coat.getQuantity() << "</td>\n";
		fout << "\t\t\t<td><a href = \"" << coat.getPhotoLink() << "\">Link</a></td>\n";
		fout << "\t\t</tr>\n";
	}
	fout << "\t\t\t<td> Total price:" << this->price << "</td>\n";

	fout << "\t\t</table>\n";
	fout << "\t</body>\n";
	fout << "</html>\n";

	fout.close();
}

void ControllerHTML::openBasket() const
{
	std::cout << "Basket";
	ShellExecuteA(NULL, NULL, "chrome.exe", "file:///C:/Users/andre/Desktop/Facultate/Basket.html", NULL, SW_SHOWMAXIMIZED);
}
