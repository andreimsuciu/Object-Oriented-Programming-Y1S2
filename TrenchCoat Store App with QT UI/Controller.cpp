#include "Controller.h"
#include <Windows.h>
#include <shellapi.h>

Controller::Controller(std::vector<TrenchCoat>& repo): repo{ repo } {
	this->readFile();
	this->basket = std::vector<TrenchCoat>{ };
	this->sizeList = std::vector<TrenchCoat>{ };
	this->price = 0;
	this->coatsNumber = 0;
}

Controller::~Controller() {
}

void Controller::addCoat(int size, std::string colour, int price, int quantity, std::string photoLink) {
	TrenchCoat coat{ size,colour,price,quantity,photoLink };
	std::vector<TrenchCoat>::iterator it;
	CoatValidator valid;

	valid.valid(coat);
	it = find(this->repo.begin(), this->repo.end(), coat);
	if (it == this->repo.end()) {
		this->repo.push_back(coat);
		this->writeFile();
	}
	else
		throw(RepoException{ "This coat is already in the store!" });
}

void Controller::updateCoat(int size, std::string colour, int price, int quantity, std::string photoLink) {
	TrenchCoat coat{ size,colour,price,quantity,photoLink };
	std::vector<TrenchCoat>::iterator it;
	CoatValidator valid;
	
	valid.valid(coat);
	it = find(this->repo.begin(), this->repo.end(), coat);
	if (it != this->repo.end()) {
		this->repo.erase(it);
		this->repo.push_back(coat);
		this->writeFile();
	}
	else
		throw(RepoException{ "This coat is NOT in the store!" });
}

void Controller::removeCoat(int size, std::string colour) {
	TrenchCoat coat{ size,colour,0,0," " };
	std::vector<TrenchCoat>::iterator it;
	
	it = find(this->repo.begin(), this->repo.end(), coat);
	if (it != this->repo.end()) {
		this->repo.erase(it);
		this->writeFile();
	}
	else
		throw(RepoException{ "This coat is NOT in the store!" });
}

std::string Controller::printCoats() {
	std::string res;
	std::vector<TrenchCoat>::iterator it;

	if (this->repo.size() == 0)
		throw(RepoException{ "The store is empty! Nothing to print!" });
	for (it = this->repo.begin(); it != this->repo.end(); it++)
	{
		res += it->trenchCoatToString();
		res += "\n";
	}
	return res;
}

void Controller::createSizeList(int size) {
	TrenchCoat coat;
	std::vector<TrenchCoat>::iterator it;

	this->sizeList.clear();

	for (it = this->repo.begin(); it != this->repo.end(); ++it) {
		coat = *it;
		if (size == 0 || coat.getSize()==size)
			this->sizeList.push_back(coat);
	}
}

TrenchCoat Controller::displayNextCoat() {
	TrenchCoat coat;
	std::vector<TrenchCoat>::iterator it;

	if (this->sizeList.size() == 0)
		throw(RepoException{ "The size list is empty!" });
	coat = this->sizeList[this->coatsNumber];
	if (this->coatsNumber + 1 == this->sizeList.size())
		this->coatsNumber = 0;
	else
		this->coatsNumber++;
	ShellExecuteA(NULL, NULL, "chrome.exe", coat.getPhotoLink().c_str(), NULL, SW_SHOWMAXIMIZED);
	return coat;
}

std::string Controller::print_sizeList() {
	std::vector<TrenchCoat>::iterator it;
	std::string res;

	if (this->sizeList.size() == 0)
		throw(RepoException{ "The size list is empty!" });
	for (it = this->sizeList.begin(); it != this->sizeList.end(); it++)
	{
		res += it->trenchCoatToString();
		res += "\n";
	}
	return res;
}

void Controller::addToBasket() {
	int pos;
	std::vector<TrenchCoat>::iterator it;
	TrenchCoat coat;

	if (this->sizeList.size() == 0)
		throw(RepoException{ "The size list is empty" });
	if (this->coatsNumber == 0)
		pos = this->sizeList.size() - 1;
	else
		pos = this->coatsNumber - 1;

	coat = this->sizeList[pos];
	it = find(this->basket.begin(), this->basket.end(), coat);
	if (it == this->basket.end()) {
		this->basket.push_back(coat);
		this->price += this->sizeList[pos].getPrice();
	}
}

std::string Controller::displayBasket() {
	std::string res;
	std::vector<TrenchCoat>::iterator it;

	if (this->basket.size() == 0)
		throw(RepoException{ "Your basket is empty!" });
	for (it = this->basket.begin(); it != this->basket.end(); it++)
	{
		res += it->trenchCoatToString();
		res += "\n";
	}
	return res;
}

void Controller::readFile() {
	std::ifstream fin("repo.txt");
	TrenchCoat coat;
	this->repo.clear();
	while (fin >> coat)
		this->repo.push_back(coat);
	fin.close();
}

void Controller::writeFile() {
	std::ofstream fout("repo.txt");
	std::vector<TrenchCoat>::iterator iterator;

	for (iterator = this->repo.begin(); iterator != this->repo.end(); iterator++)
		fout << *iterator << "\n";
	fout.close();
}

std::vector<TrenchCoat>* Controller::getAll()
{
	std::vector<TrenchCoat>* copy_vector = new std::vector<TrenchCoat>;
	for (int i = 0; i < this->repo.size(); i++)
		copy_vector->push_back(this->repo[i]);
	return copy_vector;
}

std::vector<TrenchCoat>* Controller::getSizeList()
{
	std::vector<TrenchCoat>* copy_vector = new std::vector<TrenchCoat>;
	for (int i = 0; i < this->sizeList.size(); i++)
		copy_vector->push_back(this->sizeList[i]);
	return copy_vector;
}

std::vector<TrenchCoat>* Controller::getBasket()
{
	std::vector<TrenchCoat>* copy_vector = new std::vector<TrenchCoat>;
	for (int i = 0; i < this->basket.size(); i++)
		copy_vector->push_back(this->repo[i]);
	return copy_vector;
}

void Controller::sortL()
{
	TrenchCoat coat;
	for (unsigned i = 0; i < this->repo.size() - 1; i++) {
		for (unsigned j = i + 1; j <= this->repo.size() - 1; j++) {
			if (this->repo[i].getPrice()< this->repo[j].getPrice()) {
				coat = this->repo[i];
				this->repo[i] = this->repo[j];
				this->repo[j] = coat;
			}
		}
	}
}

void Controller::shuffle()
{
	std::random_shuffle(this->repo.begin(), this->repo.end());
}

void Controller::sortRepo(Comparator<TrenchCoat> &c) const {
	TrenchCoat coat;
	for (unsigned i = 0; i <= this->repo.size(); i++)
	{
		for (unsigned j = i+1; i <= this->repo.size(); j++) {
			if (c.compare(this->repo[i], this->repo[j])) {
				coat = this->repo[i];
				this->repo[i] = this->repo[j];
				this->repo[j] = coat;
			}
		}
	}
}

/*
void Controller::initialize() {
	TrenchCoat coat;

	coat = TrenchCoat(36, "blue", 250, 50, "https://www.pinterest.com/pin/155514993353442607/");
	this->repo.add(coat);

	coat = TrenchCoat(38, "black", 500, 10, "https://www.amazon.com/uxcell-Double-Breasted-Pockets-Peacoat/dp/B00NBWJK0U");
	this->repo.add(coat);

	coat = TrenchCoat(42, "beige", 400, 25, "https://ro.pinterest.com/pin/349029039846712356/");
	this->repo.add(coat);

	coat = TrenchCoat(42, "orange", 800, 3, "https://ro.pinterest.com/pin/349029039846710424/");
	this->repo.add(coat);

	coat = TrenchCoat(36, "red", 1000, 2, "https://ro.pinterest.com/pin/349029039846710393/");
	this->repo.add(coat);

	coat = TrenchCoat(38, "gray", 325, 34, "https://ro.pinterest.com/pin/349029039846710398/");
	this->repo.add(coat);

	coat = TrenchCoat(38, "white", 530, 27, "https://ro.pinterest.com/pin/349029039845857164/");
	this->repo.add(coat);
}
*/