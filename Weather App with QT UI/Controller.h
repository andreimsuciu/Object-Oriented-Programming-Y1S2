#pragma once
#include <iostream>
#include "Interval.h"
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

class Controller {
private:
	std::vector<Interval> &repo;
	bool compareTemp(Interval &i1, Interval &i2);
public:
	Controller(std::vector<Interval>&repo);
	
	void readFile();
	std::vector<Interval>* getAll();
	std::vector<Interval>* filter(int precip);
	int hours(std::string desc);
	void sortTemp();
	void update(int temp, int index);
	std::string askColor(int i);
};