#include "controller.h"

controller::controller() :controller("(640,480)") {}

controller::controller(std::string size_)//接收字符串构造成point类型，再利用point中的getter函数获取长宽
{
	p1 = point(size_);
	initgraph(p1.getx(), p1.gety());
}

point controller::getpoint()
{
	return p1;
}

void controller::close()
{
	closegraph();
}