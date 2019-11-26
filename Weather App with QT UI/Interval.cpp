#include "Interval.h"

Interval & Interval::operator=(const Interval & interval)
{
	this->start = interval.start;
	this->end = interval.end;
	this->temp = interval.temp;
	this->precip = interval.precip;
	this->desc = interval.desc;
	return *this;
}

Interval::Interval(int start, int end, int temp, int precip, std::string desc) : start{ start }, end{ end }, temp{ temp }, precip{ precip }, desc{ desc }
{
}

Interval::Interval()
{
}

std::string Interval::intervalToString() const
{
	return std::to_string(this->start)+ " "+ std::to_string(this->end) + " " + std::to_string(this->temp) + " "+ std::to_string(this->precip) + " " + this->desc;
}


//std::ostream & operator<<(std::ostream & stream, const Interval & interval)
//{
//	stream << interval.getStart() << ' ' << interval.getEnd() << ' ' << interval.getTemp() << ' ' << interval.getPrecip() << ' ' << interval.getDesc();
//	return stream;
//}

std::istream & operator>>(std::istream & stream, Interval & inter)
{
	std::string desc;
	int start;
	int end;
	int temp;
	int precip;
	stream >> start >> end >> temp >> precip >> desc;
	inter=Interval{ start,end,temp,precip,desc };
	return stream;
}

