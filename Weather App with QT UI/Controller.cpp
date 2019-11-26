#include "Controller.h"

Controller::Controller(std::vector<Interval>& repo):repo{repo}
{
	this->readFile();
}

void Controller::readFile()
{
	std::ifstream fin{ "repo.txt" };
	Interval interval;
	this->repo.clear();
	while (fin >> interval)
		this->repo.push_back(interval);
	fin.close();
}

std::vector<Interval>* Controller::getAll()
{
	std::vector<Interval>* copy_vector = new std::vector<Interval>;
	for (int i = 0; i < this->repo.size(); i++)
		copy_vector->push_back(this->repo[i]);
	return copy_vector;
}

std::vector<Interval>* Controller::filter(int precip)
{
	std::vector<Interval>* copy_vector = new std::vector<Interval>;
	for (int i = 0; i < this->repo.size(); i++)
		if(this->repo[i].getPrecip()<precip)
			copy_vector->push_back(this->repo[i]);
	return copy_vector;
}

int Controller::hours(std::string desc)
{
	int hours,total=0;
	for (int i = 0; i < this->repo.size(); i++)
		if (this->repo[i].getDesc() == desc) {
			hours = this->repo[i].getEnd() - this->repo[i].getStart();
			total += hours;
		}
	return total;
}

void Controller::sortTemp()
{
	Interval interval;
	for (unsigned i = 0; i < this->repo.size()-1; i++) {
		for (unsigned j = i + 1; j <= this->repo.size()-1; j++) {
			if (this->compareTemp(this->repo[i], this->repo[j])) {
				interval = this->repo[i];
				this->repo[i] = this->repo[j];
				this->repo[j] = interval;
			}
		}
	}
	//std::sort(this->repo.begin(), this->repo.end(), this->compareTemp);
}
void Controller::update(int temp, int index)
{
	this->repo[index].setTemp(temp);
}
std::string Controller::askColor(int i)
{
	std::string desc = this->repo[i].getDesc();
	return desc;
}
bool Controller::compareTemp(Interval &i1, Interval &i2)
{
	Interval interval;
	if (i1.getTemp() < i2.getTemp())
		return true;
	else
		return false;
}
