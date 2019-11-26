#include "TrenchCoatValidator.h"

void CoatValidator::valid(TrenchCoat &coat)
{
	if (coat.getSize() == 0)
		throw(ValidException{ "The size cannot be 0!" });
	if (coat.getColour().length() == 0)
		throw(ValidException{ "The colour cannot be empty!" });
	if (coat.getPrice() == 0)
		throw(ValidException{ "The price cannot be 0!" });
	if (coat.getQuantity() == 0)
		throw(ValidException{ "The quantity cannot be 0!" });
	if (coat.getPhotoLink().length() == 0)
		throw(ValidException{ "The link cannot be empty!" });
	
}
