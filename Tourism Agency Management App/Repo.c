#include "Repo.h"
#include <windows.h>
#include<stdio.h>
#include <stdlib.h>
#include <stdbool.h>


OfferRepo* createOfferRepo(int capacity) {

	OfferRepo* repo =(OfferRepo*)malloc(sizeof(OfferRepo));
	//check if space is allocated
	if (repo == NULL)
		return NULL;

	//initialize
	repo->capacity = capacity;
	repo->length = 0;

	//allocate space for elems
	repo->offers = (Offer*)malloc(capacity * sizeof(Offer));

	if (repo->offers == NULL)
		return NULL;
	return repo;
}

int offersOfType(OfferRepo* repo, OfferRepo* typeRepo,char *type, int date) {

	if (strcmp(type, "seaside") != 0 && strcmp(type, "city break") != 0 && strcmp(type, "mountain") != 0) {
		return -1; //invalid type
	}
	if ((date < 0) || (date > 31)) {
		return -2; //invalid date
	}
	for (int i = 0; i <= repo->length; i++) {
		if (strcmp(repo->offers[i].type, type) == 0 && repo->offers[i].departureDate > date) {
			add(typeRepo, repo->offers[i]);
		}
	}
	return 1; //typeRepo was made
}

void destroy(OfferRepo* repo){

	if (repo == NULL)
		return;

	// free the space allocated for the planets
	free(repo->offers);
	repo->offers = NULL;

	// free the space allocated for the dynamic array
	free(repo);
	repo = NULL;
}

// Resizes the array, allocating more space.
void resize(OfferRepo* repo)
{
	if (repo== NULL)
		return;

	repo->capacity *= 2;
	Offer* aux = (Offer*)realloc(repo->offers, repo->capacity * sizeof(Offer));
	if (aux == NULL)
		return; // array cannot be resized
	repo->offers = aux;
}

int add(OfferRepo* repo, Offer offer)
{
	if (repo == NULL)
		return;
	if (repo->offers == NULL)
		return;
	
	for (int i = 0; i <= repo->length; i++) {
		if (strcmp(repo->offers[i].destination, offer.destination) == 0 && repo->offers[i].departureDate == offer.departureDate) {
			//Offer already added!
			return 0;
		}	
	}

	// resize the array, if necessary
	if (repo->length == repo->capacity)
		resize(repo);
	repo->offers[repo->length] = offer;
	repo->length++;
	return 1; //Element added!
}

int del(OfferRepo* repo, Offer offer)
{
	if (repo == NULL)
		return;
	if (repo->offers == NULL)
		return;

	for (int i = 0; i <= repo->length; i++) {
		if (strcmp(repo->offers[i].destination, offer.destination) == 0 && repo->offers[i].departureDate == offer.departureDate) {
			for (int j = i; j < repo->length; j++) {
				repo->offers[j] = repo->offers[j+1];
			}
			repo->length--;
			return 1; //Element removed!
		}
	}
	return 0; //Element does not exist
}

int update(OfferRepo* repo, Offer offer)
{
	if (repo == NULL)
		return -1;
	if (repo->offers == NULL)
		return -1;

	for (int i = 0; i <= repo->length; i++) {
		if (strcmp(repo->offers[i].destination, offer.destination) == 0 && repo->offers[i].departureDate == offer.departureDate) {
			repo->offers[i] = offer;
			return 1; //Element updated
		}
	}
	return 0; //element does not exist and was not updated
}

int comparatorPrice(const void *offer1, const void *offer2) {
	Offer a, b;
	a = *(Offer*)offer1;
	b = *(Offer*)offer2;
	if (a.price < b.price)
		return -1;
	if (a.price > b.price)
		return 1;
	return 0;
}

void sortRepoPrice(OfferRepo* repo) {
	qsort((void*)repo->offers, repo->length, sizeof(Offer), comparatorPrice);
}

int comparatorDeparture(const void *offer1, const void *offer2) {
	Offer a, b;
	a = *(Offer*)offer1;
	b = *(Offer*)offer2;
	if (a.departureDate < b.departureDate)
		return -1;
	if (a.departureDate > b.departureDate)
		return 1;
	return 0;
}

void sortRepoDeparture(OfferRepo* repo) {
	qsort((void*)repo->offers, repo->length, sizeof(Offer), comparatorDeparture);
}



char *repoToString(OfferRepo repo, char *str) {
	int i;
	char *result, *currentOffer;

	if (repo.length == 0)
		return 0;
	result = (char*)malloc(sizeof(char) * 100 * repo.length);
	currentOffer = (char*)malloc(sizeof(char) * 100 * repo.length);

	result[0] = '\0';

	for (i = 0; i < repo.length; i++) {
		if (strlen(str) == 0 || containsString(repo.offers[i], str) == 1) {
			currentOffer = offerToString(repo.offers[i]);
			strcat(result, currentOffer);
			strcat(result, ";\n");
		}
	}

	free(currentOffer);
	return result;
}