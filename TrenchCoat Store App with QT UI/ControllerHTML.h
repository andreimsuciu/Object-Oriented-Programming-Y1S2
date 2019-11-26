#pragma once

#include "Controller.h"
#include <iostream>

class ControllerHTML :public Controller {
public:
	ControllerHTML(std::vector<TrenchCoat>& repo);
	~ControllerHTML();

	virtual void addToBasket() override;

	virtual void writeBasketToFile() override;
	virtual void openBasket() const override;
};