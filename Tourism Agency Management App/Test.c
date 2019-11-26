#include "Repo.h"
#include "Offer.h"
#include <stdlib.h>
#include <assert.h>

void test_repo() {
	Offer offer;
	offer = createOffer("Paris", "city break", 23, 998);
	//char* str = toString(offer);
	//printf("%s", str);
	//free(str);

	OfferRepo* repo = createOfferRepo(2);
	assert(repo->capacity == 2);
	assert(repo->length == 0);

	add(repo, offer);
	assert(repo->length == 1);

	Offer offer2 = createOffer("Milano", "city break", 34, 872);
	add(repo, offer2);
	assert(repo->length == 2);

	Offer offer3 = createOffer("Rome", "city break", 2, 600);
	add(repo, offer3);
	assert(repo->length == 3);
	assert(repo->capacity == 4);

	add(repo, offer);
	//int price = repo->offers[2].price;
	//if (repo->offers[2].price == price)
	//	printf("%d", price);
	del(repo, offer);
	assert(repo->length == 2);

	Offer offer4 = createOffer("Bucuresti", "city break", 3, 872);
	del(repo, offer4);
	assert(repo->length == 2);

	Offer offer5 = createOffer("Rome", "sea side", 2, 800);
	update(repo, offer5);
	assert(repo->length == 2);
	//str = toString(repo->offers[1]);
	//printf("%s", str);
}
