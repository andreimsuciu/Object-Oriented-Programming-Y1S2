#pragma once

#include "Controller.h"
#include <iostream>

class ControllerCSV :public Controller {
public:
	ControllerCSV(std::vector<TrenchCoat>& repo);
	~ControllerCSV();

	virtual void addToBasket() override;

	virtual void writeBasketToFile() override;
	virtual void openBasket() const override;
};