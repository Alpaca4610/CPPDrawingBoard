#pragma once
#include <ege.h>
#include <graphics.h>
#include <string>

class Color
{
private:
	color_t color{ LIGHTGRAY };
	std::string s_color;
	int R, G, B;
public:
	Color();
	Color(const std::string);
	color_t getcolor();
	color_t* getAOfcolor();
	void setColor(std::string);
	std::string getString();
	std::string* getAOfString();
	bool operator==(const Color&);
	bool operator!=(const Color&);
	int& operator[](const int);
	Color& operator--(void);
	Color operator--(int dummy);
	Color& operator++(void);
	Color operator++(int dummy);
	int* setR();
	int* setG();
	int* setB();
	void judge();
};
