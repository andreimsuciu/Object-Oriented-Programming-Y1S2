#pragma once
#include "Comparator.h"
#include "TrenchCoat.h"
class ComparatorDescendingByPrice: public Comparator<TrenchCoat>
{
public:
	ComparatorDescendingByPrice();
	bool compare(TrenchCoat &t1, TrenchCoat &t2)const override;
	~ComparatorDescendingByPrice();
};

class ComparatorAscendingByQuantity : public Comparator<TrenchCoat>
{
public:
	ComparatorAscendingByQuantity();
	bool compare(TrenchCoat &t1, TrenchCoat &t2)const override;
	~ComparatorAscendingByQuantity();
};