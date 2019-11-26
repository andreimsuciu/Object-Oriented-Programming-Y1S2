#pragma once
#include "Offer.h"

typedef struct { 
	Offer* offers;  
	int length;
	int capacity;
} OfferRepo;

OfferRepo* createOfferRepo(int capacity);
void destroy(OfferRepo* offer);

char *repoToString(OfferRepo repo, char *str);

int del(OfferRepo* repo, Offer offer);
int add(OfferRepo* repo, Offer offer);
int update(OfferRepo* repo, Offer offer);

void sortRepoPrice(OfferRepo* repo);
int comparatorPrice(const void *offer1, const void *offer2);
void sortRepoDeparture(OfferRepo* repo);
int comparatorDeparture(const void *offer1, const void *offer2);

int offersOfType(OfferRepo* repo, OfferRepo* typeRepo, char *type, int date);
