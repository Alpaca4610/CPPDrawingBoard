#include "color.h"
#include <exception>

Color::Color() :Color("W") {  }
Color::Color(const std::string s) {
	s_color = s;
	if ('(' == s_color[0]) {
		int n = s_color.find_first_of(",");
		this->R = std::stoi(s_color.substr(1, n - 1));
		int n2 = s_color.find_last_of(",");
		this->G = std::stoi(s_color.substr(n + 1, n2 - n - 1));
		int n3 = s_color.find_last_of(")");
		this->B = std::stoi(s_color.substr(n2 + 1, n3 - n2 - 1));
		color = EGERGB(R, G, B);
	}
	else {
		setColor(s_color);
		R = EGEGET_R(color);
		G = EGEGET_G(color);
		B = EGEGET_B(color);
	}
}
color_t Color::getcolor() {//getter
	return color;
}

color_t* Color::getAOfcolor() {//getter
	return &color;
}

void Color::setColor(std::string s) {//setter
	switch (s[0]) {
	case(82):
		color = RED;//使用ege定义的颜色宏
		break;
	case(71):
		color = GREEN;
		break;
	case(66):
		color = BLUE;
		break;
	case(87):
		color = LIGHTGRAY;
	case(78):
		color = BLACK;
		break;
	}
}

std::string Color::getString()
{
	return this->s_color;
}

std::string* Color::getAOfString()
{
	return &s_color;
}

bool Color::operator==(const Color& c_)
{
	return (((this->R == c_.R) && (this->G == c_.G) && (this->B == c_.B)) ? 1 : 0);
}

bool Color::operator!=(const Color& c_)
{
	return (((this->R == c_.R) && (this->G == c_.G) && (this->B == c_.B)) ? 0 : 1);;
}

int& Color::operator[](const int i)
{
	if (0 == i)
		return this->R;
	else if (1 == i)
		return this->G;
	else if (2 == i)
		return this->B;
	else
		throw std::exception("out of range!");
}

Color& Color::operator--(void)
{
	(this->R)--;
	(this->G)--;
	(this->B)--;
	judge();
	(this->color) = EGERGB(R, G, B);
	return *(this);
}

Color Color::operator--(int dummy)
{
	Color temp = *(this);
	(this->R)--;
	(this->G)--;
	(this->B)--;
	judge();
	(this->color) = EGERGB(R, G, B);
	return temp;
}

Color& Color::operator++(void)
{
	(this->R)++;
	(this->G)++;
	(this->B)++;
	judge();
	(this->color) = EGERGB(R, G, B);
	return *(this);
}

Color Color::operator++(int dummy)
{
	Color temp = *(this);
	(this->R)++;
	(this->G)++;
	(this->B)++;
	judge();
	(this->color) = EGERGB(R, G, B);
	return temp;
}

int* Color::setR()
{
	return &R;
}

int* Color::setG()
{
	return &G;
}

int* Color::setB()
{
	return &B;
}

void Color::judge()
{
	if (R > 255) {
		R = 255;
	}if (G > 255) {
		G = 255;
	}if (B > 255) {
		B = 255;
	}if (R > 255) {
		R = 255;
	}if (R < 0) {
		R = 0;
	}if (G < 0) {
		G = 0;
	}if (B < 0) {
		B = 0;
	}
}