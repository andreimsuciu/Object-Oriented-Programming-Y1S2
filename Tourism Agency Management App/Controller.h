#pragma once
#include "Repo.h"


typedef struct {
	OfferRepo* repo;
} Controller;

Controller *createController(OfferRepo* repo);
void destroyController(Controller *ctrl);
char *repoToStringCtrl(Controller ctrl, char *str);

int delCtrl(Controller *controller, char destination[], int departureDate);
int addCtrl(Controller *controller, char destination[], char type[], int departureDate, int price);
int updateCtrl(Controller *controller, char destination[], char type[], int departureDate, int price);

void sortRepoPriceCtrl(Controller* ctrl);
void sortRepoDepartureCtrl(Controller* ctrl);

int offersOfTypeCtrl(Controller *ctrl, OfferRepo* typeRepo, char *type, int date);

void initialOffers(Controller* ctrl);