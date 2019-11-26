#include "TrenchCoat.h"
#include <string>
#include <iostream>

TrenchCoat::TrenchCoat(int size, std::string colour, int price, int quantity, std::string photoLink) {
	this->size = size;
	this->colour = colour;
	this->price = price;
	this->quantity = quantity;
	this->photoLink = photoLink;
}

TrenchCoat::TrenchCoat() {
	this->size = 0;
	this->colour = " ";
	this->price = 0;
	this->quantity = 0;
	this->photoLink = " ";
}

TrenchCoat::TrenchCoat(const TrenchCoat& coat) {
	this->size = coat.size;
	this->colour = coat.colour;
	this->price = coat.price;
	this->quantity = coat.quantity;
	this->photoLink = coat.photoLink;
}

bool TrenchCoat::operator==(const TrenchCoat& coat) const {
	return this->size == coat.size && this->colour == coat.colour;
}

bool TrenchCoat::operator!=(const TrenchCoat& coat) const {
	return this->size != coat.size || this->colour != coat.colour;
}

std::string TrenchCoat::trenchCoatToString() const {
	return std::to_string(this->size) + " " + this->colour + " " + std::to_string(this->price) + "$" + " " + std::to_string(this->quantity) + " " + this->photoLink;
}

TrenchCoat& TrenchCoat::operator=(const TrenchCoat& coat) {
	this->size = coat.size;
	this->colour = coat.colour;
	this->price = coat.price;
	this->quantity = coat.quantity;
	this->photoLink = coat.photoLink;
	return *this;
}

DynamicVector<TrenchCoat>& TrenchCoat::operator+(DynamicVector<TrenchCoat>& vect)
{
	if (vect.search(*this) != -1)
		return vect;
	vect.add(*this);
	return vect;
}

std::istream &operator>>(std::istream &stream, TrenchCoat &coat)
{
	std::string colour,photoLink;
	int size,price,quantity;

	stream >> size >> colour >> price >> quantity >> photoLink;
	coat = TrenchCoat{ size, colour, price, quantity, photoLink };
	return stream;
}

std::ostream& operator<<(std::ostream& stream, const TrenchCoat &coat)
{
	stream << coat.getSize() << ' ' << coat.getColour() << ' ' << coat.getPrice() << ' ' << coat.getQuantity() << ' ' << coat.getPhotoLink();
	return stream;
}



