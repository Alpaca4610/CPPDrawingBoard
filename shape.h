#pragma once
#include "Coordinate.h"
#include "color.h"
#include <vector>
#include <cmath>
using std::string;

class shape {
private:
	Color* color;
	Color* fcolor;
	bool filled{ false };
	string size;
	static int numOfObjects;
public:
	void convertBool(string);
	shape();
	shape(string, string, string, string);
	bool isfilled();
	void setfilled(bool);
	Color* getcolor();
	Color* getbgcolor();
	virtual void draw() = 0;
	string getsize();
	string* getAOfsize();
	bool* getisfilled();
	static int getnumberObjects();
	static int* getAOnumberObjects();
	virtual void writefile() = 0;
	~shape();
};

class Circle :public shape {
private:
	point p;
	int radius;
public:
	//Circle(Circle&);
	Circle();
	Circle(point, int, string, string, string, string bgc0lor = "D");
	int getx() const;
	int gety() const;
	int getRadius() const;
	virtual void draw() override;
	virtual void writefile() override;
	bool operator<(const Circle&);
	bool operator>(const Circle&);
	bool operator<=(const Circle&);
	bool operator>=(const Circle&);
	bool operator==(const Circle&);
	bool operator!=(const Circle&);
	Circle& operator=(Circle&);
	~Circle();
};

class RectangleC :public shape {
private:
	point p1, p2;
public:
	//RectangleC(RectangleC&);
	RectangleC();
	RectangleC(point, point, string, string, string, string bgc0lor = "D");
	point getp1() const;
	point getp2() const;
	virtual void draw() override;
	virtual void writefile() override;
	int getArea();
	bool operator<(RectangleC&);
	bool operator>(RectangleC&);
	bool operator<=(RectangleC&);
	bool operator>=(RectangleC&);
	bool operator==(RectangleC&);
	bool operator!=(RectangleC&);
	point operator[](const int&);
	RectangleC& operator=(RectangleC&);
	~RectangleC();
};

class triangle :public shape {
private:
	point p1, p2, p3;
public:
	//triangle(triangle&);
	triangle();
	triangle(point, point, point, string, string, string, string bgc0lor = "D");
	point getp1();
	point getp2();
	point getp3();
	virtual void draw() override;
	virtual void writefile() override;
	double getArea();
	bool operator<(triangle&);
	bool operator>(triangle&);
	bool operator<=(triangle&);
	bool operator>=(triangle&);
	bool operator==(triangle&);
	bool operator!=(triangle&);
	point operator[](const int&);
	triangle& operator=(triangle&);
	~triangle();
};

class Line {
private:
	point p1, p2;
	Color* color;
	string size;
	//static int numOfObjects;
public:
	//Line(Line&);
	Line();
	Line(point, point, string, string);
	Color* getcolor();
	point getp1();
	point getp2();
	string getsize();
	string* getAOfsize();
	double getLength();
	bool operator<(Line&);
	bool operator>(Line&);
	bool operator<=(Line&);
	bool operator>=(Line&);
	bool operator==(Line&);
	bool operator!=(Line&);
	point operator[](const int&);
	Line& operator=(Line&);
	void draw();
	void writefile();
	~Line();
};

class ploygon :public shape {
private:
	std::vector<int> p;
	int n;
public:
	ploygon(ploygon&);
	ploygon(string, string, string, string);
	int getn();
	int* getp();
	virtual void draw() override;
	virtual void writefile() override;
	~ploygon();
};
