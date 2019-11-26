#include "Offer.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

Offer createOffer(char destination[], char type[], int departureDate, int price) {
	Offer offer;
	strcpy(offer.destination, destination);
	strcpy(offer.type, type);
	offer.departureDate = departureDate;
	offer.price = price;
	return offer;
}

int validateOffer(Offer offer) {
	if (strcmp(offer.type, "seaside") != 0 && strcmp(offer.type, "city break") != 0 && strcmp(offer.type, "mountain") != 0)
		return 0;
	if (offer.departureDate < 0 || offer.departureDate>31)
		return 0;
	if (offer.price < 0)
		return 0;
	//if all is fine, the offer should be validated
	return 1;
}

int equal(Offer offer1, Offer offer2) {
	if (strcmp(offer1.destination, offer2.destination) == 0 && strcmp(offer1.departureDate, offer2.departureDate) == 0)
		return 1;
	return 0;
}

int containsString(Offer offer, char *str) {
	if (strstr(offer.destination, str) != NULL || strcmp(offer.type, str) == 0)
		return 1;
	return 0;
}

char* offerToString(Offer offer) {
	char *offerString = (char*)malloc(100 * sizeof(char));
	char *intString = (char*)malloc(20 * sizeof(char));

	offerString[0] = '\0';

	strcat(offerString, offer.destination);
	strcat(offerString, " ");

	strcat(offerString, offer.type);
	strcat(offerString, " ");

	_itoa(offer.departureDate, intString, 10);
	strcat(offerString, intString);
	strcat(offerString, " ");

	_itoa(offer.price, intString, 10);
	strcat(offerString, intString);
	strcat(offerString, " ");
	
	free(intString);
	return offerString;
}

char* getDestination(Offer* offer) {
	return offer->destination;
}

char* getType(Offer* offer) {
	return offer->type;
}

int getDepartureDate(Offer* offer) {
	return offer->departureDate;
}

int getPrice(Offer* offer) {
	return offer->price;
}