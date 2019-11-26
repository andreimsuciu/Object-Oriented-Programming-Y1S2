#include "Console.h"

Console::Console(Controller& controller) : ctrl{ controller }
{
}


Console::~Console()
{
}

//Admin functionalities

void Console::ui_helpAdmin()
{
	std::cout << "\nPossible commands:\n";
	std::cout << "Adding a coat: add <size><colour><price><quantity><photoLink>\n";
	std::cout << "Updating a coat: update <size><colour><price><quantity><photoLink>\n";
	std::cout << "Removing a coat: remove <size><colour>\n";
	std::cout << "Print the coats: print\n";
	std::cout << "Exit: exit\n";
	std::cout << "Insert command: ";
}

void Console::runAdmin()
{
	std::string input_string, input[20];
	char *str, *ptr;
	int cmds;

	std::cout << "Entering admin mode...\n";

	while (true)
	{
		this->ui_helpAdmin();

		cmds = 0;
		std::getline(std::cin, input_string);
		str = new char[input_string.length() + 1];
		strcpy(str, input_string.c_str());
		ptr = strtok(str, " \t\n");
		while (ptr != NULL && cmds < 20)
		{
			input[cmds++] = ptr;
			ptr = strtok(NULL, " \t\n");
		}

		if (cmds == 6 && input[0] == "add")
		{
			this->ui_add(input);
		}
		else if (cmds == 2 && input[0] == "sort")
		{
			this->ui_sort(input);
		}
		else if (cmds == 6 && input[0] == "update")
		{
			this->ui_update(input);
		}
		else if (cmds == 3 && input[0] == "remove")
		{
			this->ui_remove(input);
		}
		else if (cmds == 1 && input[0] == "print")
		{
			this->ui_print();
		}
		else if (cmds == 1 && input[0] == "exit")
			return;
		else
			std::cout << "Invalid command!\n";
	}
}

void Console::ui_add(std::string input[20]) {
	int size, price, quantity;

	size = std::atoi(input[1].c_str());
	price = std::atoi(input[3].c_str());
	quantity = std::atoi(input[4].c_str());
	try {
		this->ctrl.addCoat(size, input[2], price, quantity, input[5]);
	}
	catch (ValidException &exception)
	{
		std::cout << exception.msg() << '\n';
		return;
	}
	catch (RepoException &exception)
	{
		std::cout << exception.msg() << '\n';
		return;
	}
	std::cout << "Coat was added to the shop\n";
}

void Console::ui_sort(std::string input[20]) {
	if (input[1] == "price") {
		ComparatorDescendingByPrice c;
		this->ctrl.sortRepo(c);
	}
	else if (input[1] == "quantity") {
		ComparatorAscendingByQuantity c;
		this->ctrl.sortRepo(c);
	}
	else {
		std::cout << "Incorect sorting method";
		return;
	}
}

void Console::ui_update(std::string input[20]) {
	int size, price, quantity;

	size = std::atoi(input[1].c_str());
	price = std::atoi(input[3].c_str());
	quantity = std::atoi(input[4].c_str());

	try {
		this->ctrl.updateCoat(size, input[2], price, quantity, input[5]);
	}
	catch (ValidException &exception)
	{
		std::cout << exception.msg() << '\n';
		return;
	}
	catch (RepoException &exception)
	{
		std::cout << exception.msg() << '\n';
		return;
	}
	std::cout << "Coat was updated\n";
}

void Console::ui_remove(std::string input[20]) {
	int size;
	size = std::atoi(input[1].c_str());

	try {
		this->ctrl.removeCoat(size, input[2]);
	}
	catch (RepoException &exception)
	{
		std::cout << exception.msg() << '\n';
		return;
	}
	std::cout << "Coat was removed from the shop\n";
}

void Console::ui_print()
{
	std::string result;
	try {
		result = this->ctrl.printCoats();
	}
	catch (RepoException &exception)
	{
		std::cout << exception.msg() << '\n';
		return;
	}
	std::cout << result;
}

void Console::ui_helpUser()
{
	std::cout << "\nPossible commands:\n";
	std::cout << "Print all coats in the store: shop\n";
	std::cout << "Make a list of a given size: list<size>\n";
	std::cout << "Print all coats in the list: print list\n";
	std::cout << "Print next coat in the list: next\n";
	std::cout << "Print shopping basket: basket\n";
	std::cout << "Add the coat to the bakset: add\n";
	std::cout << "Open basket:open\n";
	std::cout << "Exit: exit\n";
	std::cout << "Insert command: ";
}

void Console::runUser() {
	std::string input_string, input[20];
	char *str, *ptr;
	int cmds;


	std::cout << "Hello! How can I help you today?\n";

	while (true)
	{
		this->ui_helpUser();

		cmds = 0;
		std::getline(std::cin, input_string);
		str = new char[input_string.length() + 1];
		strcpy(str, input_string.c_str());
		ptr = strtok(str, " \t\n");
		while (ptr != NULL && cmds < 20)
		{
			input[cmds++] = ptr;
			ptr = strtok(NULL, " \t\n");
		}

		if (cmds == 1 && input[0] == "exit")
			return;
		if ((cmds == 2 || cmds == 1) && input[0] == "list")
		{
			if (cmds == 2) {
				int size = std::atoi(input[1].c_str());
				this->ctrl.createSizeList(size);
			}
			else
			{
				this->ctrl.createSizeList(0);
			}
		}
		else if (cmds == 2 && input[0] == "print")
			this->ui_printSizeList();
		else if (cmds == 1 && input[0] == "shop")
			this->ui_print();
		else if (cmds == 1 && input[0] == "next")
		{
			this->ui_nextCoat();
		}
		else if (cmds == 1 && input[0] == "add")
		{
			this->ui_addToBasket();
		}
		else if (cmds == 1 && input[0] == "basket")
		{
			this->ui_printBasket();
		}
		else if (cmds == 1 && input[0] == "open") {
			this->ui_openBasket();
		}
		else if (cmds == 1 && input[0] == "exit")
			return;
		else
			std::cout << "Invalid command!\n";
	}
}

void Console::ui_printSizeList() {
	std::string res;
	try {
		res = this->ctrl.print_sizeList();
	}
	catch (RepoException &exception)
	{
		std::cout << exception.msg() << '\n';
		return;
	}
	std::cout << res;
}

void Console::ui_nextCoat() {
	TrenchCoat coat; 
	try {
		coat=this->ctrl.displayNextCoat();
	}
	catch (RepoException &exception)
	{
		std::cout << exception.msg() << '\n';
		return;
	}
	std::cout << coat.trenchCoatToString() << "\n";
}

void Console::ui_addToBasket() {
	try {
		this->ctrl.addToBasket();
	}
	catch (RepoException &exception)
	{
		std::cout << exception.msg() << '\n';
		return;
	}
}

void Console::ui_printBasket() {
	std::string res;
	try {
		res=this->ctrl.displayBasket();
	}
	catch (RepoException &exception)
	{
		std::cout << exception.msg() << '\n';
		return;
	}
	std::string price = std::to_string(this->ctrl.getBasketPrice());
	std::cout << res;
	std::cout <<"\t"<< "Total: " <<price<< "$";
}

void Console::ui_openBasket()
{
	this->ctrl.openBasket();
}
