#pragma once
#include "Controller.h"
#include <iostream>
#include <string>
#include <string.h>

class Console {
private:
	Controller& ctrl;

public:
	Console(Controller& ctrl);
	~Console();

	void runAdmin();
	void ui_helpAdmin();
	void ui_add(std::string input[20]);
	void ui_update(std::string input[20]);
	void ui_remove(std::string input[20]);
	void ui_sort(std::string input[20]);
	void ui_print();

	void runUser();
	void ui_helpUser();
	void ui_nextCoat();
	void ui_printSizeList();
	void ui_addToBasket();
	void ui_printBasket();
	void ui_openBasket();
};