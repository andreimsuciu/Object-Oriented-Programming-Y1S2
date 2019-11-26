#pragma once
#include "Controller.h"

typedef struct {
	Controller* ctrl;
} Console;

void run(Console* console);

Console *createConsole(Controller* ctrl);

void destroyConsole(Console* console);
void uiPrint(Console* console);
void uiAdd(Console* console, char **cmds);
void uiDel(Console* console, char **cmds);
void uiUpdate(Console* console, char **cmds);
void uiSortRepoPrice(Console* console, char **cmds);
void uiSortRepoDeparture(Console* console, char **cmds);

void uiType(Console* console, char **cmds);