#include "Comparators.h"
ComparatorDescendingByPrice::ComparatorDescendingByPrice(){}
ComparatorDescendingByPrice::~ComparatorDescendingByPrice(){}

bool ComparatorDescendingByPrice::compare(TrenchCoat &t1, TrenchCoat &t2)const {
	if (t1.getPrice() > t2.getPrice())
		return true;
	return false;
}

ComparatorAscendingByQuantity::ComparatorAscendingByQuantity(){}
ComparatorAscendingByQuantity::~ComparatorAscendingByQuantity(){}

bool ComparatorAscendingByQuantity::compare(TrenchCoat &t1, TrenchCoat &t2)const {
	if (t1.getQuantity() < t2.getQuantity())
		return true;
	return false;
}
