#pragma once
#include "DynamicVector.h"
#include "TrenchCoat.h"
#include "TrenchCoatValidator.h"
#include "Comparators.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm> 
#include <Windows.h>
#include <shellapi.h>
#include <algorithm>

class Controller {
protected:
	std::vector<TrenchCoat> &repo;
	std::vector<TrenchCoat> sizeList;
	std::vector<TrenchCoat> basket;
	int price;
	int coatsNumber;

public:
	Controller(std::vector<TrenchCoat>& repo);
	~Controller();

	void addCoat(int size, std::string colour, int price, int quantity, std::string photoLink);
	void updateCoat(int size, std::string colour, int price, int quantity, std::string photoLink);
	void removeCoat(int size, std::string colour);

	std::string printCoats();
	//void initialize();

	void createSizeList(int size);
	std::string print_sizeList();
	TrenchCoat displayNextCoat();

	virtual void addToBasket();
	std::string displayBasket();

	int getBasketPrice() { return this->price; }

	void sortRepo(Comparator<TrenchCoat> &c) const;

	//text file operations
	void readFile();
	void writeFile();

	//CSV and HTML
	virtual void writeBasketToFile() = 0;
	virtual void openBasket() const = 0;

	std::vector<TrenchCoat>* getAll();
	std::vector<TrenchCoat>* getSizeList();
	std::vector<TrenchCoat>* getBasket();

	void sortL();
	void shuffle();
};