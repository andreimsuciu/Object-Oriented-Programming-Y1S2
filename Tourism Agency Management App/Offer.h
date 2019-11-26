#pragma once
typedef struct {
	char destination[20], type[20];
	int departureDate, price;
} Offer;

Offer createOffer(char destination[], char type[], int departureDate, int price);
int validateOffer(Offer offer);
int equal(Offer offer1, Offer offer2);
int containsString(Offer offer, char *str);

char* offerToString(Offer offer);
char* getDestination(Offer* offer);
char* getType(Offer* offer);
int getDepartureDate(Offer* offer);
int getPrice(Offer* offer);
