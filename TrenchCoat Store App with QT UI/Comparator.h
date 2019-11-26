#pragma once
template <typename TElem>
class Comparator {
public:
	Comparator<TElem>() {};
	virtual bool compare(TElem &t1, TElem &t2)const =0;
	~Comparator<TElem>() {};
};