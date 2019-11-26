#include "Controller.h"
#include "Offer.h"
#include "Repo.h"
#include<stdio.h>
#include <stdlib.h>
#include <string.h>

Controller *createController(OfferRepo* repo) {
	Controller *ctrl;
	ctrl = (Controller*)malloc(sizeof(Controller));
	ctrl->repo = repo;
	return ctrl;
}

int offersOfTypeCtrl(Controller *ctrl, OfferRepo* typeRepo, char *type, int date) {
	int retValue;
	retValue = offersOfType(ctrl->repo, typeRepo, type, date);
	return retValue;
}

void destroyController(Controller *ctrl) {
	free(ctrl);
	ctrl = NULL;
}

int addCtrl(Controller *controller, char destination[], char type[], int departureDate, int price) {
	int retValue;
	Offer offer = createOffer(destination, type, departureDate, price);
	if (validateOffer(offer) == 0)
		return -1; //printf("Invalid element");
	retValue=add(controller->repo, offer);
	return retValue; //returns 1, if element added; 0 if not
}

int delCtrl(Controller *controller, char destination[], int departureDate) {
	int retValue;
	Offer offer = createOffer(destination, "city break", departureDate, 0);
	if (validateOffer(offer) == 0)
		return -1; // printf("Invalid element");
	retValue=del(controller->repo, offer);
	return retValue; //return 1 if offer delted, 0 if not
}

int updateCtrl(Controller *controller, char destination[], char type[], int departureDate, int price) {
	int retValue;
	Offer offer = createOffer(destination, type, departureDate, price);
	if (validateOffer(offer) == 0)
		return -1;//printf("Invalid element");
	retValue=update(controller->repo, offer);
	return retValue; //returns 1 if offer updated, 0 if not
}

void sortRepoPriceCtrl(Controller* ctrl) {
	sortRepoPrice(ctrl->repo);
}

void sortRepoDepartureCtrl(Controller* ctrl) {
	sortRepoDeparture(ctrl->repo);
}

char *repoToStringCtrl(Controller ctrl, char *str) {
	return repoToString(*(ctrl.repo), str);
}

void initialOffers(Controller* ctrl) {
	Offer offer;
	//veltravel.ro
	offer = createOffer("Paris", "city break", 1, 175);
	add(ctrl->repo, offer);

	offer = createOffer("London", "city break", 20, 137);
	add(ctrl->repo, offer);

	offer = createOffer("Munchen", "city break", 18, 248);
	add(ctrl->repo, offer);

	offer = createOffer("Milano", "city break", 7, 100);
	add(ctrl->repo, offer);
	//selecttravel.ro
	offer = createOffer("Mallnitz", "mountain", 5, 345);
	add(ctrl->repo, offer);

	offer = createOffer("Misurina", "mountain", 13, 410);
	add(ctrl->repo, offer);

	offer = createOffer("Bansko", "mountain", 19, 230);
	add(ctrl->repo, offer);
	//veltravel.ro
	offer = createOffer("Capri", "seaside", 3, 384);
	add(ctrl->repo, offer);

	offer = createOffer("Lisbon", "seaside", 16, 303);
	add(ctrl->repo, offer);

	offer = createOffer("Tel Aviv", "seaside", 26, 258);
	add(ctrl->repo, offer);
}