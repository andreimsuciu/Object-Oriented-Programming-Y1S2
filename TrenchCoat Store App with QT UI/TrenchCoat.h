#pragma once
#include <iostream>
#include <iostream>
#include "DynamicVector.h"
class TrenchCoat;
std::ostream &operator<<(std::ostream &stream, const TrenchCoat &coat);
std::istream &operator>>(std::istream &stream, TrenchCoat &coat);

class TrenchCoat
{
	friend std::ostream &operator<<(std::ostream &stream, const TrenchCoat &coat);
	friend std::istream &operator>>(std::istream &stream, TrenchCoat &coat);

private:
	int size;
	std::string colour;
	int price;
	int quantity;
	std::string photoLink;

public:
	TrenchCoat(int size, std::string colour, int price, int quantity, std::string photoLink);
	TrenchCoat();
	TrenchCoat(const TrenchCoat& coat);

	TrenchCoat& operator=(const TrenchCoat& coat);
	bool operator==(const TrenchCoat& coat) const;
	bool operator!=(const TrenchCoat& coat) const;

	std::string trenchCoatToString() const;

	DynamicVector<TrenchCoat>& operator+(DynamicVector<TrenchCoat>& vector);

	int getSize() const { return this->size; }
	int getPrice() const { return this->price; }
	int getQuantity() const { return this->quantity; }
	std::string getColour() const { return this->colour; }
	std::string getPhotoLink() const{ return this->photoLink; }
};

