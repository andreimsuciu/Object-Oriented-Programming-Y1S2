#include "Console.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Console *createConsole(Controller* ctrl) {
	Console *console;

	console = (Console*)malloc(sizeof(Console));
	console->ctrl = ctrl;
	return console;
}

void destroyConsole(Console* console) {
	free(console);
	console = NULL;
}

void uiHelp() {
	printf("Possible commands:\n");
	printf("\t1.Adding an offer: add <destination> <type> <departure date> <price>\n");
	printf("\t2.Deleting an offer: del <destination> <departure date>\n");
	printf("\t3.Updating an offer: update <destination> <type> <departure date> <price>\n");
	printf("\t4.Sort after price: price <string>\n");
	printf("\t5.Sort after departure date: departure <string>\n");
	printf("\t6.Show only offers of type, starting from a given date: type <type> <date>\n");
	printf("\t7.Print database: print\n");
	printf("\thelp\n");
	printf("\texit\n");
	printf("\n");
}

void run(Console* console) {
	char **cmds;
	char *command, *token;
	int i, wordsInCommand;

	printf("Welcome to Happy Holidays offer management app! \nMany thanks to selecttravel.ro and veltravel.ro for providing credible offers!\n");
	printf("\n");
	uiHelp();

	initialOffers(console->ctrl);
	cmds = (char**)malloc(20 * sizeof(char*));//read 10 words
	for (i = 0; i < 20; i++)
		cmds[i] = (char*)malloc(100 * sizeof(char));
	command = (char*)malloc(10000 * sizeof(char));

	while (1) {
		printf("\nPlease insert a command:\n");
		fgets(command, 10000, stdin);
		wordsInCommand = 0;
		token = strtok(command, " \n\t");

		while (token != NULL && wordsInCommand < 20) {
			strcpy(cmds[wordsInCommand], token);
			wordsInCommand++;
			token = strtok(NULL, " \n\t");
		}

		if (wordsInCommand == 1 && strcmp(cmds[0], "help") == 0) {
			uiHelp();
		}
		else if (wordsInCommand == 1 && strcmp(cmds[0], "exit") == 0) {
			for (i = 0; i < 20; i++) {
				free(cmds[i]);
			}
			free(cmds);
			free(command);
			return;
		}
		else if (wordsInCommand == 5 && strcmp(cmds[0], "add") == 0) {
			uiAdd(console, cmds);
		}
		else if (wordsInCommand == 3 && strcmp(cmds[0], "del") == 0) {
			uiDel(console, cmds);
		}
		else if (wordsInCommand == 5 && strcmp(cmds[0], "update") == 0) {
			uiUpdate(console, cmds);
		}
		else if ((wordsInCommand == 2 || wordsInCommand == 1) && strcmp(cmds[0], "price") == 0) {
			if (wordsInCommand == 2)
				uiSortRepoPrice(console, cmds);
			else if (wordsInCommand == 1)
				uiSortRepoPrice(console, cmds[1]);
		}
		else if ((wordsInCommand == 2 || wordsInCommand == 1) && strcmp(cmds[0], "departure") == 0) {
			if (wordsInCommand == 2)
				uiSortRepoDeparture(console, cmds);
			else if (wordsInCommand == 1)
				uiSortRepoDeparture(console, cmds[1]);
		}
		else if (wordsInCommand == 3 && strcmp(cmds[0], "type") == 0) {
			uiType(console, cmds);
		}
		else if (wordsInCommand == 1 && strcmp(cmds[0], "print") == 0) {
			uiPrint(console);
		}
		else
			printf("Invalid command!");
	}

}

void uiType(Console* console, char **cmds) {
	int departureDate, returnValue;
	char *res;
	OfferRepo* typeRepo = createOfferRepo(20);
	departureDate = atoi(cmds[2]);

	if (strcmp(cmds[1], "citybreak") == 0)
		returnValue = offersOfTypeCtrl(console->ctrl, typeRepo, "city break", departureDate);
	else
		returnValue = offersOfTypeCtrl(console->ctrl, typeRepo, cmds[1], departureDate);

	if (returnValue == -1)
		printf("Type invalid!\n");
	else if (returnValue == -2)
		printf("Date invalid!\n");
	else if (returnValue == 1) {
		res = repoToString(*typeRepo, "");
		printf("%s\n", res);
		free(res);
		destroy(typeRepo);
	}
		
}

void uiPrint(Console* console) {
	char *res;

	res = repoToStringCtrl(*(console->ctrl), "");
	printf("%s\n", res);
	free(res);
}

void uiAdd(Console* console, char **cmds) {
	int departureDate, price, returnValue;

	departureDate = atoi(cmds[3]);
	price = atoi(cmds[4]);
	if (strcmp(cmds[2], "citybreak") == 0)
		returnValue = addCtrl(console->ctrl, cmds[1], "city break", departureDate, price);
	else 
		returnValue = addCtrl(console->ctrl, cmds[1], cmds[2], departureDate, price);
	if (returnValue == 1)
		printf("Offer added succesfully!\n");
	else if (returnValue == 0)
		printf("Offer is already in the database!\n");
	else if (returnValue < 0)
		printf("There was a problem with the format!\n");
}

void uiDel(Console* console, char **cmds) {
	int res;
	int departureDate = atoi(cmds[2]);
	res = delCtrl(console->ctrl, cmds[1], departureDate);
	if (res == 1)
		printf("Offer deleted succesfully!\n");
	else if (res == 0)
		printf("Offer is not in database!\n");
	else if (res < 0)
		printf("Invalid format for offer\n");
}

void uiUpdate(Console* console, char **cmds) {
	int departureDate, price, returnValue;

	departureDate = atoi(cmds[3]);
	price = atoi(cmds[4]);
	if (strcmp(cmds[2], "citybreak") == 0)
		returnValue =updateCtrl(console->ctrl, cmds[1], "city break", departureDate, price);
	else
		returnValue = updateCtrl(console->ctrl, cmds[1], cmds[2], departureDate, price);
	if (returnValue == 1)
		printf("Offer updated succesfully!\n");
	else if (returnValue == 0)
		printf("Offer was NOT found in the database!\n");
	else if (returnValue < 0)
		printf("There was a problem with the format!\n");
}

void uiSortRepoPrice(Console* console, char **cmds) {
	char *res;

	sortRepoPriceCtrl(console->ctrl);
	res = repoToStringCtrl(*(console->ctrl), cmds);
	printf("%s\n", res);
	free(res);
}

void uiSortRepoDeparture(Console* console, char **cmds) {
	char *res;

	sortRepoDepartureCtrl(console->ctrl);
	res = repoToStringCtrl(*(console->ctrl), cmds);
	printf("%s\n", res);
	free(res);
}