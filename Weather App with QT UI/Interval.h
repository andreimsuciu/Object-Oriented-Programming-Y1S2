#pragma once
#include <iostream>
#include <string>
class Interval;
//std::ostream &operator<<(std::ostream &stream, const Interval &interval);
std::istream &operator>>(std::istream &stream, Interval &interval);

class Interval {
	//friend std::ostream &operator<<(std::ostream &stream, const Interval &interval);
	friend std::istream &operator>>(std::istream &stream, Interval &inter);
private:
	int start;
	int end;
	int temp;
	int precip;
	std::string desc;
public:
	int getStart() const { return this->start; }
	int getEnd() const { return this->end; }
	int getTemp() const { return this->temp; }
	void setTemp(int otherTemp) { this->temp = otherTemp; }
	int getPrecip() const { return this->precip; }
	std::string getDesc() const { return this->desc; }

	Interval& operator=(const Interval& interval);
	Interval(int start, int end, int temp, int precip, std::string desc);
	Interval();
	std::string intervalToString()const;
};