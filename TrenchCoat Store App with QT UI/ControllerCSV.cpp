#include "ControllerCSV.h"

ControllerCSV::ControllerCSV(std::vector<TrenchCoat>& repo) : Controller::Controller{repo}
{
	this->writeBasketToFile();
}

ControllerCSV::~ControllerCSV()
{
}

void ControllerCSV::addToBasket()
{
	Controller::addToBasket();
	this->writeBasketToFile();
}

void ControllerCSV::writeBasketToFile()
{
	std::ofstream fout("Basket.csv");
	TrenchCoat coat;

	std::vector<TrenchCoat>::iterator it;
	for (it = this->basket.begin(); it != this->basket.end(); it++) {
		coat = *it;
		fout << coat.getSize() << "," << coat.getColour() << "," << coat.getPrice() << "," << coat.getQuantity() << "," << coat.getPhotoLink() << "\n";
	}
	fout << "\n\t\t\t Total price:" << this->price << "\n";
	fout.close();
}

void ControllerCSV::openBasket() const
{
	std::cout << "Basket:";
	ShellExecuteA(NULL, NULL, "notepad.exe", "Basket.csv", NULL, SW_SHOWMAXIMIZED);
}
