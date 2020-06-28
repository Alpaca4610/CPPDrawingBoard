#include "Coordinate.h"
#include <exception>

point::point() :point("(300,300)") {}

point::point(std::string s_)//将字符串形式的坐标转换成两个int类型并存储在成员变量中
{
	pS = s_;
	convert(s_);
}

void point::convert(std::string s_)
{
	int n = s_.find_first_of(",");
	this->x = std::stoi(s_.substr(1, n - 1));
	int n2 = s_.find_last_of(")");
	this->y = std::stoi(s_.substr(n + 1, n2 - n - 1));
}

int point::getx() const//getter
{
	return x;
}

int point::gety() const//getter
{
	return y;
}

void point::setpoint(std::string s_)//setter
{
	convert(s_);
}

std::string point::getpS()
{
	return pS;
}

point point::operator+(const point& p_)
{
	char temp[30];
	sprintf_s(temp, "(%f,%f)", 0.5 * (this->x + 1.0 * p_.x), 0.5 * (this->y + 1.0 * p_.y));
	return point(temp);
}

bool point::operator==(const point p_)
{
	return (((this->x) == p_.x) && ((this->y) == p_.y));
}

bool point::operator!=(const point p_)
{
	return !(((this->x) == p_.x) && ((this->y) == p_.y));
}

int& point::operator[](const int index)
{
	if (index == 0)
		return x;
	else if (index == 1)
		return y;
	else
		throw std::exception{ "out of range!" };
}