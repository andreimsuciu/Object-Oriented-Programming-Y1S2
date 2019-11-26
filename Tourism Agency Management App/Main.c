#include<stdio.h>
#include "Offer.h"
#include "Repo.h"
#include "Controller.h"
#include "Console.h"
#include <stdbool.h>
#include <windows.h>
#include <stdlib.h>
#include <crtdbg.h>
#include <assert.h>



int main() {
	//test_repo();
	OfferRepo* repo = createOfferRepo(20);
	Controller* ctrl = createController(repo);
	Console* console = createConsole(ctrl);

	run(console);

	destroy(repo);
	destroyController(ctrl);
	destroyConsole(console);
	system("pause");
	_CrtDumpMemoryLeaks();

	return 0;
}