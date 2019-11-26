#pragma once
#include<iostream>
#include<string>

template <typename TElem>
class DynamicVector {
private:
	TElem *elems;
	int size;
	int capacity;

public:
	//constructor
	DynamicVector();
	DynamicVector(const DynamicVector<TElem>& vector);
	//destructor
	~DynamicVector();
	
	//dynamic vector functions. they return bool to know if the function succeeds
	bool add(TElem elem);
	bool remove(TElem elem);
	bool update(TElem elem);
	int search(TElem elem);
	std::string toString() const;

	TElem getElem(int pos) const;
	int getSize() const { return this->size; }

	//dynamic vector operator overload
	DynamicVector<TElem>& operator=(const DynamicVector<TElem>& vector);
	DynamicVector<TElem>& operator+(TElem elem);

	void clearVector();
};

//constructor
template <typename TElem>
DynamicVector<TElem>::DynamicVector() {
	this->size = 0;
	this->capacity = 1;
	this->elems = new TElem[1];
}

//we need destructor to free memory
template <typename TElem>
DynamicVector<TElem>::~DynamicVector() {
	delete[] this->elems;
}

//FUNCTIONS:
template <typename TElem>
int DynamicVector<TElem>::search(TElem elem) {
	int i;
	for (i = 0; i < this->size; i++)
		if (this->elems[i] == elem)
			return i;
	return -1;
}

template <typename TElem>
bool DynamicVector<TElem>::add(TElem elem) {
	//check if elem is in vector, if it is return false
	if (this->search(elem) != -1)
		return false;

	//check if we have enough space in the vector. If not,we need to resize
	if (this->size == this->capacity) {
		TElem *newElemVector;
		int i;

		this->capacity = this->capacity *2;
		newElemVector = new TElem[this->capacity];
		for (i = 0; i < this->size; i++)
			newElemVector[i] = this->elems[i];
		delete[] this->elems;
		this->elems = NULL;
		this->elems = newElemVector;
	}
	this->elems[this->size] = elem;
	this->size += 1;
	return true;
}

template <typename TElem>
bool DynamicVector<TElem>::remove(TElem elem) {
	int i;
	for (i = 0; i < this->size && this->elems[i] != elem; i++);
	if (i == this->size)
		return false;
	if (i != this->size - 1)
		this->elems[i] = this->elems[this->size - 1];
	this->size -= 1;
	return true;
}

template <typename TElem>
bool DynamicVector<TElem>::update(TElem elem) {
	int i;
	for (i = 0; i < this->size; i++) {
		if (this->elems[i] == elem) {
			this->elems[i] = elem;
			return true;
		}
	}
	return false;
}

template <typename TElem>
std::string DynamicVector<TElem>::toString() const {
	std::string stringOfElems;
	int i;

	for (i = 0; i < this->size; i++) {
		stringOfElems += "\t";
		stringOfElems += this->elems[i].trenchCoatToString();
		stringOfElems += "\n";
	}

	return stringOfElems;
}

//OPERATORS
template <typename TElem>
DynamicVector<TElem>& DynamicVector<TElem>::operator+(TElem elem)
{
	if (this->search(elem) == true)
		return *this;
	if (this->size == this->capacity)
	{
		TElem *newElems;

		this->capacity *= 2;
		newElems = new TElem[this->capacity];
		for (int i = 0; i < this->size; i++)
		{
			newElems[i] = this->elems[i];
		}
		delete[] this->elems;
		this->elems = newElems;
	}
	this->elems[this->size] = elem;
	this->size += 1;
	return *this;
}

template <typename TElem>
DynamicVector<TElem>& DynamicVector<TElem>::operator=(const DynamicVector<TElem>& vector) {
	TElem *newElemVector;

	this->size = vector.size;
	this->capacity = vector.capacity;
	newElemVector = new TElem[this->capacity];
	for (int i = 0; i < this->size; i++)
		newElemVector[i] = vector.elems[i];
	delete[] this->elems;
	this->elems = NULL;
	this->elems = newElemVector;
	return *this;
}

template <typename TElem>
DynamicVector<TElem>::DynamicVector(const DynamicVector<TElem>& vector) {
	int i;

	this->capacity = vector.capacity;
	this->size = vector.size;
	this->elems = new TElem[this->capacity];
	for (i = 0; i < this->size; i++)
		this->elems[i] = vector.elems[i];
}

template <typename TElem>
TElem DynamicVector<TElem>::getElem(int pos) const
{
	if (pos < this->size && pos >= 0)
		return this->elems[pos];
	TElem empty;
	return empty;
}

template <typename TElem>
void DynamicVector<TElem>::clearVector()
{
	this->capacity = 1;
	this->size = 0;
	delete[] this->elems;
	this->elems = new TElem[1];
}