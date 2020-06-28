#include <stdio.h>
#include <graphics.h>
#include "color.h"
#include "Coordinate.h"
#include <string>
#include "shape.h"
#include "controller.h"
#include "ege.h"
#include <filesystem>
#include <fstream>
int shape::numOfObjects{ 0 };

int main()
{
	setcaption("Alpaca Drawing Board");
	initgraph(640, 480);
	setfont(18, 0, "宋体"); //设置字体
	int k{ 0 };
	std::vector<Circle*> cStore;
	std::vector<RectangleC*> rStore;
	std::vector<triangle*> tStore;
	std::vector<Line*> LStore;
	std::vector<ploygon*> pStore;
	std::vector<Color*> CoStore;
	std::vector<point*> PoStore;

	for (; k != key_esc; ) // key_esc是ege定义的按键常数
	{
		setcolor(LIGHTGRAY);
		cleardevice();
		outtextxy(125, 0, "欢迎使用Alpaca Drawing Board Ver5.2！");
		outtextxy(185, 25, "1.圆形绘图菜单");
		outtextxy(185, 50, "2.矩形绘图菜单");
		outtextxy(185, 75, "3.三角形绘图菜单");
		outtextxy(185, 100, "4.线段绘图菜单");
		outtextxy(185, 125, "5.多边形绘图菜单");
		outtextxy(185, 150, "6.导出图形对象参数保存至文件");
		outtextxy(185, 175, "7.从文件中导入图形对象参数");
		outtextxy(185, 200, "8.查看当前所有图形对象个数");
		outtextxy(185, 225, "9.调色/坐标运算测试区");
		outtextxy(185, 250, "0.退出");
		k = getch();
		switch (k) {
		case 49: {
			cleardevice(); //清空之前输出的菜单信息，便于接下来的绘图
			int cmenu1{ 0 };
			for (; cmenu1 != 54; )
			{
				setcolor(LIGHTGRAY);
				outtextxy(170, 0, "1.创建一个圆对象");
				outtextxy(170, 25, "2.查看当前已创建圆对象的参数");
				outtextxy(170, 50, "3.绘制存储的圆对象");
				outtextxy(170, 75, "4.删除某个圆对象");
				outtextxy(170, 100, "5.图形间运算菜单");
				outtextxy(170, 125, "6.返回主菜单");
				cmenu1 = getch();
				switch (cmenu1) {
				case 49: {
					char str[15], r[15], c[3], filled[2], size[15];//创建用于接收inputbox的字符串
					inputbox_getline("请输入需要创建的画板大小：", "请输入需要创建的画板大小：(例：(640，480))：(回车确认)", size, 15);
					inputbox_getline("请输入圆心的坐标：", "请输入圆心的坐标(例：(233，233)，符号为英文！)：(回车确认)", str, 15);
					inputbox_getline("请输入圆的半径：", "请输入圆心的半径：(回车确认)", r, 10);
					inputbox_getline("请输入圆的颜色：", "请输入圆的颜色(R代表红色，G代表绿色，B代表蓝色))：(回车确认)", c, 3);
					inputbox_getline("该圆是否填充？：", "该圆是否填充？(填充请输入Y，不填充请输入N)：(回车确认)", filled, 2);
					cStore.push_back(new Circle{ point{str}, std::stoi(r), c, filled, size });//利用接收的数据创建圆对象;
					cleardevice();
					outtextxy(100, 0, "创建成功！");
					getch();
					cleardevice();
					break;
				}
				case 50: {
					cleardevice();
					if (cStore.size() == 0) {
						outtextxy(100, 0, "对象列表为空！");
						getch();
						cleardevice();
						break;
					}
					initgraph(1200, 1200);
					int j = 0;
					char temp[300] = { "" };
					for (auto i : cStore) {
						//sprintf_s(temp, "编号：%d  半径：%d   坐标：(%d,%d) 边框颜色：%s ", j, (*i).getRadius(), (*i).getx(), (*i).gety(), (*i).getcolor()->getString());
						sprintf_s(temp, "编号：%d  半径：%d   坐标：(%d,%d)  边框颜色：%s   是否填充：%d   填充颜色：%s   画板大小：%s", j, (*i).getRadius(), (*i).getx(), (*i).gety(), i->getcolor()->getString().c_str(), (*i).isfilled(), i->getbgcolor()->getString().c_str(), (*i).getsize().c_str());
						outtextxy(0, 25 * j, temp);
						j++;
					}
					getch();
					cleardevice();
					initgraph(640, 480);
					break;
				}
				case 51: {
					cleardevice();
					char id[2];
					inputbox_getline("请输入需要绘制的圆的编号：", "请输入需要绘制的圆的编号：(回车确认)", id, 2);
					if ((std::stoi(id) > cStore.size()) || cStore.size() == 0) {
						outtextxy(100, 0, "请输入正确的编号！");
						getch();
						cleardevice();
						break;
					}
					cStore[std::stoi(id)]->draw();
					getch();
					initgraph(640, 480);
					cleardevice();
					break;
				}
				case 52: {
					cleardevice();
					char id[2];
					inputbox_getline("请输入删除的圆编号：", "请输入需要删除的圆编号：(回车确认)", id, 2);
					if (std::stoi(id) > cStore.size()) {
						outtextxy(100, 0, "请输入正确的编号！");
						getch();
						cleardevice();
						break;
					}
					delete cStore[std::stoi(id)];
					cStore.erase(cStore.begin() + std::stoi(id));
					outtextxy(100, 0, "清除成功！");
					char temp[100];
					sprintf_s(temp, "目前有%d个圆形对象", cStore.size());
					outtextxy(100, 50, temp);
					getch();
					cleardevice();
					break;
				}
				case 53: {
					cleardevice();
					int cmenu_{ 0 };
					for (; cmenu_ != 52;) {
						setcolor(LIGHTGRAY);
						outtextxy(170, 0, "1.比较两个圆的大小");
						outtextxy(170, 25, "2.判断两个圆是否相等");
						outtextxy(170, 50, "3.复制已有圆");
						outtextxy(170, 75, "4.返回上级菜单");
						cmenu_ = getch();
						cleardevice();
						switch (cmenu_) {
						case 49: {
							char id1[2];
							char id2[2];
							inputbox_getline("请输入第一个圆的编号：", "请输入第一个圆的编号：(回车确认)", id1, 2);
							inputbox_getline("请输入第二个圆的编号：", "请输入第二个圆的编号：(回车确认)", id2, 2);
							if (std::stoi(id1) > cStore.size() || std::stoi(id2) > cStore.size()) {
								outtextxy(100, 0, "请输入正确的编号！");
								getch();
								cleardevice();
								break;
							}
							if ((*(cStore[std::stoi(id1)])) > (*(cStore[std::stoi(id2)]))) {
								outtextxy(170, 0, "第一个圆的大小大于第二个圆的大小");
							}
							else if ((*(cStore[std::stoi(id1)])) < (*(cStore[std::stoi(id2)]))) {
								outtextxy(170, 0, "第一个圆的大小小于第二个圆的大小");
							}
							else {
								outtextxy(170, 0, "两个圆大小相等");
							}
							getch();
							cleardevice();
							break;
						}case 50: {
							char id1[2];
							char id2[2];
							inputbox_getline("请输入第一个圆的编号：", "请输入第一个圆的编号：(回车确认)", id1, 2);
							inputbox_getline("请输入第二个圆的编号：", "请输入第二个圆的编号：(回车确认)", id2, 2);
							if (std::stoi(id1) > cStore.size() || std::stoi(id2) > cStore.size()) {
								outtextxy(100, 0, "请输入正确的编号！");
								getch();
								cleardevice();
								break;
							}
							if ((*(cStore[std::stoi(id1)])) == (*(cStore[std::stoi(id2)]))) {
								outtextxy(170, 0, "两个圆的大小相等");
							}
							else if ((*(cStore[std::stoi(id1)])) != (*(cStore[std::stoi(id2)]))) {
								outtextxy(170, 0, "两圆大小不相等");
							}
							getch();
							cleardevice();
							break;
						}case 51: {
							char id[2];
							inputbox_getline("请输入需要复制的圆的编号：", "请输入需要复制的圆的编号：(回车确认)", id, 2);
							if (std::stoi(id) > cStore.size()) {
								outtextxy(100, 0, "请输入正确的编号！");
								getch();
								cleardevice();
								break;
							}
							cStore.push_back(new Circle());
							*(cStore.back()) = *(cStore[std::stoi(id)]);
							outtextxy(170, 0, "复制成功！请到上级菜单查看！");
							getch();
							cleardevice();
							break;
						}
						}
					}
					break;
				}
				}
			}
			cleardevice();//清屏
			break; }
		case 50: {
			cleardevice(); //清空之前输出的菜单信息，便于接下来的绘图
			int cmenu2{ 0 };
			for (; cmenu2 != 54; )
			{
				setcolor(LIGHTGRAY);
				outtextxy(170, 0, "1.创建一个矩形对象");
				outtextxy(170, 25, "2.查看当前已创建矩形对象的参数");
				outtextxy(170, 50, "3.绘制存储的矩形对象");
				outtextxy(170, 75, "4.删除某个矩形对象");
				outtextxy(170, 100, "5.矩形运算菜单");
				outtextxy(170, 125, "6.返回主菜单");
				cmenu2 = getch();
				switch (cmenu2) {
				case 49: {
					cleardevice();
					char p1[15], p2[15], c[3], filled[2], size[15];
					inputbox_getline("请输入需要创建的画板大小：", "请输入需要创建的画板大小：(例：(640，480)符号为英文！)：(回车确认)", size, 15);
					inputbox_getline("请输入矩形左上角顶点的坐标：", "请输入矩形左上角顶点的坐标(例：(233，233)符号为英文！)：(回车确认)", p1, 15);
					inputbox_getline("请输入矩形右下角顶点的坐标：", "请输入矩形右下角顶点的坐标(例：(333，133)符号为英文！)：(回车确认)", p2, 15);
					inputbox_getline("请输入矩形的颜色：", "请输入矩形的颜色(R代表红色，G代表绿色，B代表蓝色))：(回车确认)", c, 3);
					inputbox_getline("该矩形是否填充？：", "该矩形是否填充？(填充请输入Y，不填充请输入N)：(回车确认)", filled, 2);
					rStore.push_back(new RectangleC{ point(p1),point(p2),c,filled,size });//利用point类创建矩形对象
					cleardevice();
					outtextxy(100, 0, "创建成功！");
					getch();
					cleardevice();
					break;
				}
				case 50: {
					cleardevice();
					if (rStore.size() == 0) {
						outtextxy(100, 0, "对象列表为空！");
						getch();
						cleardevice();
						break;
					}
					initgraph(1200, 1200);
					int j = 0;
					char temp[200];
					for (auto i : rStore) {
						sprintf_s(temp, "编号：%d   左上角坐标：%s  右上角坐标：%s  边框颜色：%s   是否填充：%d   填充颜色：%s   画板大小：%s", j, i->getp1().getpS().c_str(), i->getp2().getpS().c_str(), (*i).getcolor()->getString().c_str(), (*i).isfilled(), (*i).getbgcolor()->getString().c_str(), (*i).getsize().c_str());
						outtextxy(0, 25 * j, temp);
						j++;
					}
					getch();
					cleardevice();
					initgraph(640, 480);
					break;
				}
				case 51: {
					cleardevice();
					char id[2];
					inputbox_getline("请输入需要绘制的矩形的编号：", "请输入需要绘制的矩形的编号：(回车确认)", id, 2);
					if ((std::stoi(id) > rStore.size()) || rStore.size() == 0) {
						outtextxy(100, 0, "请输入正确的编号！");
						getch();
						cleardevice();
						break;
					}
					rStore[std::stoi(id)]->draw();
					getch();
					initgraph(640, 480);
					cleardevice();
					break;
				}
				case 52: {
					cleardevice();
					char id[2];
					inputbox_getline("请输入删除的矩形编号：", "请输入需要删除的矩形编号：(回车确认)", id, 2);
					if (std::stoi(id) > rStore.size()) {
						outtextxy(100, 0, "请输入正确的编号！");
						getch();
						cleardevice();
						break;
					}
					delete rStore[std::stoi(id)];
					rStore.erase(rStore.begin() + std::stoi(id));
					outtextxy(100, 0, "清除成功！");
					char temp[100];
					sprintf_s(temp, "目前有%d个矩形对象", rStore.size());
					outtextxy(100, 50, temp);
					getch();
					cleardevice();
				}
				case 53: {
					cleardevice();
					int cmenu_{ 0 };
					for (; cmenu_ != 52;) {
						setcolor(LIGHTGRAY);
						outtextxy(170, 0, "1.比较两个矩形的大小");
						outtextxy(170, 25, "2.判断两个矩形是否相等");
						outtextxy(170, 50, "3.复制已有矩形");
						outtextxy(170, 75, "4.返回上级菜单");
						cmenu_ = getch();
						cleardevice();
						switch (cmenu_) {
						case 49: {
							char id1[2];
							char id2[2];
							inputbox_getline("请输入第一个矩形的编号：", "请输入第一个矩形的编号：(回车确认)", id1, 2);
							inputbox_getline("请输入第二个矩形的编号：", "请输入第二个矩形的编号：(回车确认)", id2, 2);
							if (std::stoi(id1) > rStore.size() || std::stoi(id2) > rStore.size()) {
								outtextxy(100, 0, "请输入正确的编号！");
								getch();
								cleardevice();
								break;
							}
							if ((*(rStore[std::stoi(id1)])) > (*(rStore[std::stoi(id2)]))) {
								outtextxy(170, 0, "第一个矩形的大小大于第二个矩形的大小");
							}
							else if ((*(rStore[std::stoi(id1)])) < (*(rStore[std::stoi(id2)]))) {
								outtextxy(170, 0, "第一个矩形的大小小于第二个矩形的大小");
							}
							else {
								outtextxy(170, 0, "两个矩形大小相等");
							}
							getch();
							cleardevice();
							break;
						}case 50: {
							char id1[2];
							char id2[2];
							inputbox_getline("请输入第一个矩形的编号：", "请输入第一个矩形的编号：(回车确认)", id1, 2);
							inputbox_getline("请输入第二个矩形的编号：", "请输入第二个矩形的编号：(回车确认)", id2, 2);
							if (std::stoi(id1) > rStore.size() || std::stoi(id2) > rStore.size()) {
								outtextxy(100, 0, "请输入正确的编号！");
								getch();
								cleardevice();
								break;
							}
							if ((*(rStore[std::stoi(id1)])) == (*(rStore[std::stoi(id2)]))) {
								outtextxy(170, 0, "两个矩形的大小相等");
							}
							else if ((*(rStore[std::stoi(id1)])) != (*(rStore[std::stoi(id2)]))) {
								outtextxy(170, 0, "两矩形大小不相等");
							}
							getch();
							cleardevice();
							break;
						}case 51: {
							char id[2];
							inputbox_getline("请输入需要复制的矩形的编号：", "请输入需要复制的矩形的编号：(回车确认)", id, 2);
							if (std::stoi(id) > rStore.size()) {
								outtextxy(100, 0, "请输入正确的编号！");
								getch();
								cleardevice();
								break;
							}
							rStore.push_back(new RectangleC());
							*(rStore.back()) = *(rStore[std::stoi(id)]);
							outtextxy(170, 0, "复制成功！请到上级菜单查看！");
							getch();
							cleardevice();
							break;
						}
						}
					}
					break;
				}
				}
			}
			cleardevice();//清屏
			break; }

		case 51: {
			cleardevice();
			int cmenu3{ 0 };
			for (; cmenu3 != 54; )
			{
				setcolor(LIGHTGRAY);
				outtextxy(170, 0, "1.创建一个三角形对象");
				outtextxy(170, 25, "2.查看当前已创建三角形对象的参数");
				outtextxy(170, 50, "3.绘制存储的三角形对象");
				outtextxy(170, 75, "4.删除某个三角形对象");
				outtextxy(170, 100, "5.三角形运算菜单");
				outtextxy(170, 125, "6.返回主菜单");
				cmenu3 = getch();
				switch (cmenu3) {
				case 49: {
					cleardevice();
					char p1[15], p2[15], p3[15], c[3], filled[2], size[15];
					inputbox_getline("请输入需要创建的画板大小：", "请输入需要创建的画板大小：(例：(640，480))符号为英文！：(回车确认)", size, 15);
					inputbox_getline("请输入三角形第一个顶点的坐标：", "请输入三角形第一个顶点的坐标(例：(233，233))符号为英文！：(回车确认)", p1, 15);
					inputbox_getline("请输入三角形第二个顶点的坐标：", "请输入三角形第二个顶点的坐标(例：(333，400))符号为英文！：(回车确认)", p2, 15);
					inputbox_getline("请输入三角形第三个顶点的坐标：", "请输入三角形第三个顶点的坐标(例：(300，300))符号为英文！：(回车确认)", p3, 15);
					inputbox_getline("请输入三角形的颜色：", "请输入三角形的颜色(R代表红色，G代表绿色，B代表蓝色))：(回车确认)", c, 3);
					inputbox_getline("该三角形是否填充？：", "该三角形是否填充？(填充请输入Y，不填充请输入N)：(回车确认)", filled, 2);
					tStore.push_back(new triangle{ point(p1),point(p2),point(p3),c,filled,size });//创建一个三角形对象
					cleardevice();
					outtextxy(100, 0, "创建成功！");
					getch();
					cleardevice();
					break;
				}
				case 50: {
					cleardevice();
					if (tStore.size() == 0) {
						outtextxy(100, 0, "对象列表为空！");
						getch();
						cleardevice();
						break;
					}
					initgraph(1200, 1200);
					int j = 0;
					char temp[200];
					for (auto i : tStore) {
						sprintf_s(temp, "编号：%d   坐标1：%s  坐标2：%s  坐标3：%s  边框颜色：%s   是否填充：%d   填充颜色：%s   画板大小：%s", j, i->getp1().getpS().c_str(), i->getp2().getpS().c_str(), i->getp3().getpS().c_str(), (*i).getcolor()->getString().c_str(), (*i).isfilled(), (*i).getbgcolor()->getString().c_str(), (*i).getsize().c_str());
						outtextxy(0, 25 * j, temp);
						j++;
					}
					getch();
					cleardevice();
					initgraph(640, 480);
					break;
				}
				case 51: {
					cleardevice();
					char id[2];
					inputbox_getline("请输入需要绘制的三角形的编号：", "请输入需要绘制的三角形的编号：(回车确认)", id, 2);
					if ((std::stoi(id) > tStore.size()) || tStore.size() == 0) {
						outtextxy(100, 0, "请输入正确的编号！");
						getch();
						cleardevice();
						break;
					}
					tStore[std::stoi(id)]->draw();
					getch();
					initgraph(640, 480);
					cleardevice();
					break;
				}
				case 52: {
					cleardevice();
					char id[2];
					inputbox_getline("请输入删除的三角形编号：", "请输入需要删除的三角形编号：(回车确认)", id, 2);
					if (std::stoi(id) > tStore.size()) {
						outtextxy(100, 0, "请输入正确的编号！");
						getch();
						cleardevice();
						break;
					}
					delete tStore[std::stoi(id)];
					tStore.erase(tStore.begin() + std::stoi(id));
					outtextxy(100, 0, "清除成功！");
					char temp[100];
					sprintf_s(temp, "目前有%d个三角形对象", tStore.size());
					outtextxy(100, 50, temp);
					getch();
					cleardevice();
				}
				case 53: {
					cleardevice();
					int cmenu_{ 0 };
					for (; cmenu_ != 52;) {
						setcolor(LIGHTGRAY);
						outtextxy(170, 0, "1.比较两个三角形的大小");
						outtextxy(170, 25, "2.判断两个三角形是否相等");
						outtextxy(170, 50, "3.复制已有三角形");
						outtextxy(170, 75, "4.返回上级菜单");
						cmenu_ = getch();
						cleardevice();
						switch (cmenu_) {
						case 49: {
							char id1[2];
							char id2[2];
							inputbox_getline("请输入第一个三角形的编号：", "请输入第一个三角形的编号：(回车确认)", id1, 2);
							inputbox_getline("请输入第二个三角形的编号：", "请输入第二个三角形的编号：(回车确认)", id2, 2);
							if (std::stoi(id1) > tStore.size() || std::stoi(id2) > tStore.size()) {
								outtextxy(100, 0, "请输入正确的编号！");
								getch();
								cleardevice();
								break;
							}
							if ((*(tStore[std::stoi(id1)])) > (*(tStore[std::stoi(id2)]))) {
								outtextxy(170, 0, "第一个三角形的大小大于第二个三角形的大小");
							}
							else if ((*(tStore[std::stoi(id1)])) < (*(tStore[std::stoi(id2)]))) {
								outtextxy(170, 0, "第一个三角形的大小小于第二个三角形的大小");
							}
							else {
								outtextxy(170, 0, "两个三角形大小相等");
							}
							getch();
							cleardevice();
							break;
						}case 50: {
							char id1[2];
							char id2[2];
							inputbox_getline("请输入第一个三角形的编号：", "请输入第一个三角形的编号：(回车确认)", id1, 2);
							inputbox_getline("请输入第二个三角形的编号：", "请输入第二个三角形的编号：(回车确认)", id2, 2);
							if (std::stoi(id1) > tStore.size() || std::stoi(id2) > tStore.size()) {
								outtextxy(100, 0, "请输入正确的编号！");
								getch();
								cleardevice();
								break;
							}
							if ((*(tStore[std::stoi(id1)])) == (*(tStore[std::stoi(id2)]))) {
								outtextxy(170, 0, "两个三角形的大小相等");
							}
							else if ((*(tStore[std::stoi(id1)])) != (*(tStore[std::stoi(id2)]))) {
								outtextxy(170, 0, "两三角形大小不相等");
							}
							getch();
							cleardevice();
							break;
						}case 51: {
							char id[2];
							inputbox_getline("请输入需要复制的三角形的编号：", "请输入需要复制的三角形的编号：(回车确认)", id, 2);
							if (std::stoi(id) > tStore.size()) {
								outtextxy(100, 0, "请输入正确的编号！");
								getch();
								cleardevice();
								break;
							}
							tStore.push_back(new triangle());
							*(tStore.back()) = *(tStore[std::stoi(id)]);
							outtextxy(170, 0, "复制成功！请到上级菜单查看！");
							getch();
							cleardevice();
							break;
						}
						}
					}
					break;
				}
				}
			}
			break;
		}

		case 52: {
			cleardevice();
			int cmenu4{ 0 };
			for (; cmenu4 != 54; )
			{
				setcolor(LIGHTGRAY);
				outtextxy(170, 0, "1.创建一个线段对象");
				outtextxy(170, 25, "2.查看当前已创建线段对象的参数");
				outtextxy(170, 50, "3.绘制存储的线段对象");
				outtextxy(170, 75, "4.删除某个线段对象");
				outtextxy(170, 100, "5.线段运算菜单");
				outtextxy(170, 125, "6.返回主菜单");
				cmenu4 = getch();
				switch (cmenu4) {
				case 49: {
					cleardevice();
					char p1[15], p2[15], c[3], size[15];
					inputbox_getline("请输入需要创建的画板大小：", "请输入需要创建的画板大小：(例：(640，480)符号为英文！)：(回车确认)", size, 15);
					inputbox_getline("请输入线段第一个顶点的坐标：", "请输入线段第一个顶点的坐标(例：(233，233)符号为英文！)：(回车确认)", p1, 15);
					inputbox_getline("请输入线段第二个顶点的坐标：", "请输入线段第二个顶点的坐标(例：(433，433)符号为英文！)：(回车确认)", p2, 15);
					inputbox_getline("请输入线段的颜色：", "请输入线段的颜色(R代表红色，G代表绿色，B代表蓝色))：(回车确认)", c, 3);
					LStore.push_back(new Line(point(p1), point(p2), c, size));//创建线对象
					cleardevice();
					outtextxy(100, 0, "创建成功！");
					getch();
					cleardevice();
					initgraph(640, 480);
					break;
				}
				case 50: {
					cleardevice();
					if (LStore.size() == 0) {
						outtextxy(100, 0, "对象列表为空！");
						getch();
						cleardevice();
						break;
					}
					initgraph(1200, 1200);
					int j = 0;
					char temp[200];
					for (auto i : LStore) {
						sprintf_s(temp, "编号：%d   坐标1：%s  坐标2：%s   边框颜色：%s   画板大小：%s", j, i->getp1().getpS().c_str(), i->getp2().getpS().c_str(), (*i).getcolor()->getString().c_str(), (*i).getsize().c_str());
						outtextxy(0, 25 * j, temp);
						j++;
					}
					getch();
					cleardevice();
					initgraph(640, 480);
					break;
				}
				case 51: {
					cleardevice();
					char id[2];
					inputbox_getline("请输入需要绘制的线段的编号：", "请输入需要绘制的线段的编号：(回车确认)", id, 2);
					if ((std::stoi(id) > LStore.size()) || LStore.size() == 0) {
						outtextxy(100, 0, "请输入正确的编号！");
						getch();
						cleardevice();
						break;
					}
					LStore[std::stoi(id)]->draw();
					getch();
					cleardevice();
					initgraph(640, 480);
					break;
				}
				case 52: {
					cleardevice();
					char id[2];
					inputbox_getline("请输入删除的线段编号：", "请输入需要删除的线段编号：(回车确认)", id, 2);
					if (std::stoi(id) > LStore.size()) {
						outtextxy(100, 0, "请输入正确的编号！");
						getch();
						cleardevice();
						break;
					}
					delete LStore[std::stoi(id)];
					LStore.erase(LStore.begin() + std::stoi(id));
					outtextxy(100, 0, "清除成功！");
					char temp[100];
					sprintf_s(temp, "目前有%d个线段对象", LStore.size());
					outtextxy(100, 50, temp);
					getch();
					cleardevice();
				}
				case 53: {
					cleardevice();
					int cmenu_{ 0 };
					for (; cmenu_ != 52;) {
						setcolor(LIGHTGRAY);
						outtextxy(170, 0, "1.比较两个线段的大小");
						outtextxy(170, 25, "2.判断两个线段是否相等");
						outtextxy(170, 50, "3.复制已有线段");
						outtextxy(170, 75, "4.返回上级菜单");
						cmenu_ = getch();
						cleardevice();
						switch (cmenu_) {
						case 49: {
							char id1[2];
							char id2[2];
							inputbox_getline("请输入第一个线段的编号：", "请输入第一个线段的编号：(回车确认)", id1, 2);
							inputbox_getline("请输入第二个线段的编号：", "请输入第二个线段的编号：(回车确认)", id2, 2);
							if (std::stoi(id1) > LStore.size() || std::stoi(id2) > LStore.size()) {
								outtextxy(100, 0, "请输入正确的编号！");
								getch();
								cleardevice();
								break;
							}
							if ((*(LStore[std::stoi(id1)])) > (*(LStore[std::stoi(id2)]))) {
								outtextxy(170, 0, "第一个线段的大小大于第二个线段的大小");
							}
							else if ((*(LStore[std::stoi(id1)])) < (*(LStore[std::stoi(id2)]))) {
								outtextxy(170, 0, "第一个线段的大小小于第二个线段的大小");
							}
							else {
								outtextxy(170, 0, "两个线段大小相等");
							}
							getch();
							cleardevice();
							break;
						}case 50: {
							char id1[2];
							char id2[2];
							inputbox_getline("请输入第一个线段的编号：", "请输入第一个线段的编号：(回车确认)", id1, 2);
							inputbox_getline("请输入第二个线段的编号：", "请输入第二个线段的编号：(回车确认)", id2, 2);
							if (std::stoi(id1) > LStore.size() || std::stoi(id2) > LStore.size()) {
								outtextxy(100, 0, "请输入正确的编号！");
								getch();
								cleardevice();
								break;
							}
							if ((*(LStore[std::stoi(id1)])) == (*(LStore[std::stoi(id2)]))) {
								outtextxy(170, 0, "两个线段的大小相等");
							}
							else if ((*(LStore[std::stoi(id1)])) != (*(LStore[std::stoi(id2)]))) {
								outtextxy(170, 0, "两线段大小不相等");
							}
							getch();
							cleardevice();
							break;
						}case 51: {
							char id[2];
							inputbox_getline("请输入需要复制的线段的编号：", "请输入需要复制的线段的编号：(回车确认)", id, 2);
							if (std::stoi(id) > LStore.size()) {
								outtextxy(100, 0, "请输入正确的编号！");
								getch();
								cleardevice();
								break;
							}
							LStore.push_back(new Line());
							*(LStore.back()) = *(LStore[std::stoi(id)]);
							outtextxy(170, 0, "复制成功！请到上级菜单查看！");
							getch();
							cleardevice();
							break;
						}
						}
					}
					break;
				}
				}
			}
			break;
		}

		case 53: {
			cleardevice();
			int cmenu5{ 0 };
			for (; cmenu5 != 53; )
			{
				setcolor(LIGHTGRAY);
				outtextxy(170, 0, "1.创建一个多边形对象");
				outtextxy(170, 25, "2.查看当前已创建多边形对象的参数");
				outtextxy(170, 50, "3.绘制存储的多边形对象");
				outtextxy(170, 75, "4.删除某个多边形对象");
				outtextxy(170, 100, "5.返回主菜单");
				cmenu5 = getch();
				switch (cmenu5) {
				case 49: {
					cleardevice();
					char color_[2], filled_[2], ns[2], size[15];
					inputbox_getline("请输入需要创建的画板大小：", "请输入需要创建的画板大小：(例：(640，480)符号为英文！)：(回车确认)", size, 15);
					inputbox_getline("请输入多边形的边数", "请输入多边形的边数", ns, 2);
					if (std::stoi(ns) <= 2) {//判断用户输入的数据是否合法
						outtext("请输入正确的顶点个数！（n >= 3）");
						getch();
						cleardevice();
						break;
					}
					inputbox_getline("请输入边框的颜色", "请输入边框的颜色(R代表红色，G代表绿色，B代表蓝色))(回车确认)", color_, 2);
					inputbox_getline("该多边形是否填充？：", "该多边形是否填充？(填充请输入Y，不填充请输入N)", filled_, 2);
					ploygon* pg1 = new ploygon(ns, color_, filled_, size);//创建多边形对象
					cleardevice();
					outtextxy(100, 0, "创建成功！");
					getch();
					cleardevice();
					break;
				}
				case 50: {
					cleardevice();
					if (pStore.size() == 0) {
						outtextxy(100, 0, "对象列表为空！");
						getch();
						cleardevice();
						break;
					}
					initgraph(1200, 1200);
					int j = 0;
					char temp[200];
					for (auto i : pStore) {
						sprintf_s(temp, "编号：%d   边数：%d   边框颜色：%s   是否填充：%d   填充颜色：%s   画板大小：%s", j, i->getn(), (*i).getcolor()->getString().c_str(), (*i).isfilled(), (*i).getbgcolor()->getString().c_str(), (*i).getsize().c_str());
						outtextxy(0, 25 * j, temp);
						j++;
					}
					getch();
					cleardevice();
					initgraph(640, 480);
					break;
				}
				case 51: {
					cleardevice();
					char id[2];
					inputbox_getline("请输入需要绘制的多边形的编号：", "请输入需要绘制的多边形的编号：(回车确认)", id, 2);
					if (std::stoi(id) > pStore.size()) {
						outtextxy(100, 0, "请输入正确的编号！");
						getch();
						cleardevice();
						break;
					}
					pStore[std::stoi(id)]->draw();
					getch();
					initgraph(640, 480);
					cleardevice();
					break;
				}
				case 52: {
					cleardevice();
					char id[2];
					inputbox_getline("请输入删除的多边形编号：", "请输入需要删除的多边形编号：(回车确认)", id, 2);
					if ((std::stoi(id) > pStore.size()) || pStore.size() == 0) {
						outtextxy(100, 0, "请输入正确的编号！");
						getch();
						cleardevice();
						break;
					}
					delete pStore[std::stoi(id)];
					pStore.erase(pStore.begin() + std::stoi(id));
					outtextxy(100, 0, "清除成功！");
					char temp[100];
					sprintf_s(temp, "目前有%d个多边形对象", pStore.size());
					outtextxy(100, 50, temp);
					getch();
					cleardevice();
				}
				}
			}
			break;
		}

		case 54: {
			cleardevice();
			outtextxy(175, 0, "开始将数据保存成文件......");
			outtextxy(125, 25, "支持圆、三角形、矩形、线段对象参数的导出");
			int num = 0;
			for (auto i : cStore) {
				(*i).writefile();
				num++;
			}
			for (auto i : tStore) {
				(*i).writefile();
				num++;
			}
			for (auto i : rStore) {
				(*i).writefile();
				num++;
			}
			for (auto i : LStore) {
				(*i).writefile();
				num++;
			}
			char notice[100];
			sprintf_s(notice, "已导出%d个对象！按下任意键返回主菜单！", num);
			outtextxy(150, 50, notice);

			getch();
			cleardevice();
			break;
		}
		case 55: {
			cleardevice();
			outtextxy(150, 0, "现在开始从文件读入数据......");
			std::ifstream in;
			in.open("figure.txt");
			int temp;
			int num = 0;
			while (in.peek() != EOF) {//判断是否到达参数列表的尾部，若未到达，则循环存取数据
				num++;//计数
				in >> temp;//读取图形ID
				in.get();//游标进入下一行
				switch (temp) {//不同的图形ID执行不同的存取操作
				case 1: {
					int px, py, radius;
					string color_, filled{ "N" }, bgcolor, size_;
					bool isfilled;
					char point_[15], temp_[1];
					in >> px >> py >> radius;//存取图形的特征信息
					in.get();//进入下一行
					in >> color_ >> isfilled;//读取图形的填充状态信息
					if (isfilled) {//判断图形是否填充，若填充，则接着读取填充颜色信息
						filled = "Y";
						in >> bgcolor;
						if (bgcolor != "R" && bgcolor != "G" && bgcolor != "B") {
							inputbox_getline("发生错误！", "读取一个圆形的填充颜色时发生错误！使用默认颜色:红色 在输入框中回车退出", temp_, 1);
							bgcolor = "R";
						}
					}
					in.get();//进入下一行
					if (color_ != "R" && color_ != "G" && color_ != "B") {//判断图形颜色数据是否合法
						inputbox_getline("发生错误！", "读取一个圆形的边框颜色时发生错误！使用默认颜色:红色 在输入框中回车退出", temp_, 1);//使用输入框的形式提醒用户
						color_ = "R";//使用默认颜色：红色
					}
					in >> size_;//读取画板大小信息
					in.get();
					sprintf_s(point_, "(%d,%d)", px, py);
					if (isfilled) {//使用从文件读取的信息，利用构造函数创建对象
						cStore.push_back(new Circle{ point{point_}, radius, color_, filled, size_,bgcolor });
					}
					else {
						cStore.push_back(new Circle{ point{point_}, radius, color_, filled, size_ });
					}
					break;
				}
				case 2: {
					char p1[10], p2[10], p3[10], temp_[1];
					string color_, filled{ "N" }, bgcolor, size_;
					bool isfilled;
					int p1x, p1y, p2x, p2y, p3x, p3y;
					in >> p1x >> p1y >> p2x >> p2y >> p3x >> p3y;
					in.get();
					in >> color_ >> isfilled;
					if (isfilled) {
						filled = "Y";
						in >> bgcolor;
						if (bgcolor != "R" && bgcolor != "G" && bgcolor != "B") {
							inputbox_getline("发生错误！", "读取一个三角形的填充颜色时发生错误！使用默认颜色:红色 在输入框中回车退出", temp_, 1);
							bgcolor = { "R" };
						}
					}
					in.get();
					if (color_ != "R" && color_ != "G" && color_ != "B") {
						inputbox_getline("发生错误！", "读取一个三角形的边框颜色时发生错误！使用默认颜色：红色 在输入框中回车退出", temp_, 1);
						color_ = { "R" };
					}
					in >> size_;
					in.get();
					sprintf_s(p1, "(%d,%d)", p1x, p1y);
					sprintf_s(p2, "(%d,%d)", p2x, p2y);
					sprintf_s(p3, "(%d,%d)", p3x, p3y);
					if (isfilled) {
						filled = "Y";
						tStore.push_back(new triangle{ point(p1),point(p2),point(p3),color_,filled,size_ ,bgcolor });
					}
					else {
						tStore.push_back(new triangle{ point(p1),point(p2),point(p3),color_,filled,size_ });
					}
					break;
				}
				case 3: {
					int p1x, p1y, p2x, p2y;
					string color_, filled{ "N" }, bgcolor, size_;
					bool isfilled;
					char p1[10], p2[10], temp_[1];
					in >> p1x >> p1y >> p2x >> p2y;
					in.get();
					in >> color_ >> isfilled;
					if (isfilled) {
						filled = "Y";
						in >> bgcolor;
						if (bgcolor != "R" && bgcolor != "G" && bgcolor != "B") {
							inputbox_getline("发生错误！", "读取一个矩形的填充颜色时发生错误！使用默认颜色:红色 在输入框中回车退出", temp_, 1);
							bgcolor = { "R" };
						}
					}
					in.get();
					if (color_ != "R" && color_ != "G" && color_ != "B") {
						inputbox_getline("发生错误！", "读取一个矩形的边框颜色时发生错误！使用默认颜色：红色 在输入框中回车退出", temp_, 1);
						color_ = { "R" };
					}
					in >> size_;
					in.get();
					sprintf_s(p1, "(%d,%d)", p1x, p1y);
					sprintf_s(p2, "(%d,%d)", p2x, p2y);
					if (isfilled) {
						rStore.push_back(new RectangleC{ point(p1),point(p2),color_,filled,size_ ,bgcolor });
					}
					else {
						rStore.push_back(new RectangleC{ point(p1),point(p2),color_,filled,size_ });
					}
					break;
				}
				case 4: {
					int p1x, p1y, p2x, p2y;
					string color_, size_;
					char p1[10], p2[10], temp_[1];
					in >> p1x >> p1y >> p2x >> p2y;
					in.get();
					in >> color_;
					in.get();
					if (color_ != "R" && color_ != "G" && color_ != "B") {
						inputbox_getline("发生错误！", "读取一个线段的颜色时发生错误！使用默认颜色：红色 在输入框中回车退出", temp_, 1);
						color_ = { "R" };
					}
					in >> size_;
					in.get();
					sprintf_s(p1, "(%d,%d)", p1x, p1y);
					sprintf_s(p2, "(%d,%d)", p2x, p2y);
					LStore.push_back(new Line(point(p1), point(p2), color_, size_));
					break;
				}
				}
			}
			char notice[100];
			sprintf_s(notice, "已导入%d个对象！按下任意键返回主菜单！", num);
			outtextxy(125, 25, notice);
			getch();
			cleardevice();
			in.close();
			break;
		}

			   /*
					   case 55: {
						   cleardevice();
						   int x{ 0 }, y{ 0 };
						   char size[15];
						   inputbox_getline("请输入需要创建的画板大小：", "请输入需要创建的画板大小：(例：(640，480))：(回车确认)", size, 15);
						   controller screen1(size);
						   randomize();
						   inputbox_getline("按下回车键开始绘图，若要结束绘图，再按任意键", "按下回车键开始绘图，若要结束绘图，再按任意键", size, 3);//给用户缓冲时间
						   for (; !kbmsg(); delay_fps(300)) {
							   x = (x + 1) % (static_cast<int>(screen1.getpoint().getx()));
							   y = (y + 1) % (static_cast<int>(screen1.getpoint().gety()));
							   cleardevice();
							   setfillcolor(EGERGB(random(255), random(255), random(255)));
							   fillellipse(x + 100, y + 100, 100, 100);
						   }
						   cleardevice();
						   break;
					   }
			   */

		case 56: {
			cleardevice();
			char temp[50];
			sprintf_s(temp, "当前一共有%d个对象", shape::getnumberObjects());
			outtextxy(100, 0, temp);
			getch();
			cleardevice();
			break;
		}

		case 57: {
			cleardevice();
			//以下为自由绘图功能，如需启用请去掉相应注释，并将调色板功能屏蔽
			/*char size[15], col[3];
			int x, y;
			inputbox_getline("请输入需要创建的画板大小：", "请输入需要创建的画板大小：(例：(640，480))：(回车确认)", size, 15);
			controller screen1(size);
			inputbox_getline("请输入绘图的颜色：", "请输入绘图的颜色(R代表红色，G代表绿色，B代表蓝色，W代表白色))：(回车确认)", col, 3);
			inputbox_getline("按下回车键开始绘图，若要结束绘图，再按任意键", "按下回车键开始绘图，若要结束绘图，再按任意键", size, 3);//给用户缓冲时间
			Color c(col);
			for (; !kbmsg(); delay_fps(300)) {
				mousepos(&x, &y);//获取当前鼠标位置
				putpixel(x, y, c.getcolor());//在鼠标当前位置打点
			}*/
			int menu2{ 0 };
			char temp[50];
			Color c{ "(255,255,255)" };
			for (; menu2 != 48;) {
				cleardevice();
				setbkcolor(c.getcolor());
				setcolor(LIGHTGRAY);
				outtextxy(200, 0, "调色面板");
				outtextxy(185, 25, "1.增强RGB亮度(++)");
				outtextxy(185, 50, "2.减弱RGB亮度(--)");
				outtextxy(185, 75, "3.增强红色亮度");
				outtextxy(185, 100, "4.减弱红色亮度");
				outtextxy(185, 125, "5.增强绿色亮度");
				outtextxy(185, 150, "6.减弱绿色亮度");
				outtextxy(185, 175, "7.增强蓝色亮度");
				outtextxy(185, 200, "8.减弱蓝色亮度");
				outtextxy(185, 225, "9.自定义颜色/坐标运算菜单");
				outtextxy(185, 250, "0.退出");
				sprintf_s(temp, "当前RGB三原色组合强度为：(%d,%d,%d)", c[0], c[1], c[2]);
				outtextxy(185, 275, temp);
				menu2 = getch();
				switch (menu2)
				{
				case 49: {
					++c;
					break;
				}
				case 50: {
					--c;
					break;
				}case 51: {
					(*(c.setR()))++;
					c.judge();
					*(c.getAOfcolor()) = EGERGB(c[0], c[1], c[2]);
					break;
				}case 52: {
					(*(c.setR()))--;
					c.judge();
					*(c.getAOfcolor()) = EGERGB(c[0], c[1], c[2]);
					break;
				}case 53: {
					(*(c.setG()))++;
					c.judge();
					*(c.getAOfcolor()) = EGERGB(c[0], c[1], c[2]);
					break;
				}case 54: {
					(*(c.setG()))--;
					c.judge();
					*(c.getAOfcolor()) = EGERGB(c[0], c[1], c[2]);
					break;
				}case 55: {
					(*(c.setB()))++;;
					c.judge();
					*(c.getAOfcolor()) = EGERGB(c[0], c[1], c[2]);
					break;
				}case 56: {
					(*(c.setB()))--;;
					c.judge();
					*(c.getAOfcolor()) = EGERGB(c[0], c[1], c[2]);
					break;
				}
				case 57: {
					int menu3{ 0 };
					cleardevice();
					setbkcolor(BLACK);
					setcolor(LIGHTGRAY);
					for (; menu3 != 48;) {
						cleardevice();
						outtextxy(185, 0, "1.新建自定义颜色");
						outtextxy(185, 25, "2.查看自定义颜色列表");
						outtextxy(185, 50, "3.判断两个颜色是否相等");
						outtextxy(185, 75, "4.删除所有自定义颜色");
						outtextxy(185, 100, "5.新建自定义坐标");
						outtextxy(185, 125, "6.查看自定义坐标列表");
						outtextxy(185, 150, "7.判断两个坐标是否相等");
						outtextxy(185, 175, "8.两个坐标取中点运算");
						outtextxy(185, 200, "9.删除所有自定义坐标");
						outtextxy(185, 225, "0.返回上一级菜单");
						menu3 = getch();
						switch (menu3)
						{
						case 49: {
							cleardevice();
							char r[5], g[5], b[5], allColor[40];
							inputbox_getline("请输入红色亮度：", "请输入红色亮度：(回车确认)", r, 5);
							inputbox_getline("请输入绿色亮度：", "请输入绿色亮度：(回车确认)", g, 5);
							inputbox_getline("请输入蓝色亮度：", "请输入蓝色亮度：(回车确认)", b, 5);
							sprintf_s(allColor, "(%d,%d,%d)", std::stoi(r), std::stoi(g), std::stoi(b));
							CoStore.push_back(new Color{ string(allColor) });
							outtextxy(170, 0, "创建成功！");
							getch();
							cleardevice();
							break;
						}
						case 50: {
							cleardevice();
							int j{ 0 };
							char temp[50];
							for (auto i : CoStore) {
								sprintf_s(temp, "编号：%d  R：%d   G：%d  B：%d", j, (*i)[0], (*i)[1], (*i)[2]);
								outtextxy(0, 25 * j, temp);
								j++;
							}
							getch();
							break;
						}
						case 51: {
							cleardevice();
							char id1[2], id2[2];
							inputbox_getline("请输入第一个颜色编号：", "请输入第一个颜色编号：(回车确认)", id1, 2);
							inputbox_getline("请输入第二个颜色编号：", "请输入第二个颜色编号：(回车确认)", id2, 2);
							if ((*CoStore[std::stoi(id1)]) == (*CoStore[std::stoi(id2)])) {
								outtextxy(170, 0, "两个颜色相等");
							}
							else if ((*CoStore[std::stoi(id1)]) != (*CoStore[std::stoi(id2)])) {
								outtextxy(170, 0, "两个颜色不相等");
							}
							getch();
							cleardevice();
							break;
						}
						case 52: {
							cleardevice();
							for (auto i : CoStore) {
								delete i;
								i = nullptr;
							}
							CoStore.clear();
							outtextxy(170, 0, "清除完成！");
							getch();
							cleardevice();
							break;
						}

						case 53: {
							cleardevice();
							char p[30];
							inputbox_getline("请输入坐标：", "请输入坐标：(回车确认)", p, 30);
							PoStore.push_back(new point{ p });
							outtextxy(170, 0, "创建成功！");
							getch();
							cleardevice();
							break;
						}
						case 54: {
							cleardevice();
							int j{ 0 };
							char temp[30];
							for (auto i : PoStore) {
								sprintf_s(temp, "编号：%d  x：%d   y：%d ", j, (*i)[0], (*i)[1]);
								outtextxy(0, 25 * j, temp);
								j++;
							}
							getch();
							break;
						}
						case 55: {
							cleardevice();
							char id1[2], id2[2];
							inputbox_getline("请输入第一个坐标编号：", "请输入第一个坐标编号：(回车确认)", id1, 2);
							inputbox_getline("请输入第二个坐标编号：", "请输入第二个坐标编号：(回车确认)", id2, 2);
							if ((*PoStore[std::stoi(id1)]) == (*PoStore[std::stoi(id2)])) {
								outtextxy(170, 0, "两个坐标相等");
							}
							else if ((*PoStore[std::stoi(id1)]) != (*PoStore[std::stoi(id2)])) {
								outtextxy(170, 0, "两个坐标不相等");
							}
							getch();
							cleardevice();
							break;
						}
						case 57: {
							cleardevice();
							for (auto i : PoStore) {
								delete i;
								i = nullptr;
							}
							PoStore.clear();
							outtextxy(170, 0, "清除完成！");
							getch();
							cleardevice();
							break;
						}
						case 56: {
							cleardevice();
							char id1[2], id2[2], temp[100];
							inputbox_getline("请输入第一个坐标编号：", "请输入第一个坐标编号：(回车确认)", id1, 2);
							inputbox_getline("请输入第二个坐标编号：", "请输入第二个坐标编号：(回车确认)", id2, 2);
							sprintf_s(temp, "两坐标组成的线段的中点是：(%d,%d)", (*(PoStore[std::stoi(id1)]) + *(PoStore[std::stoi(id2)]))[0], (*(PoStore[std::stoi(id1)]) + *(PoStore[std::stoi(id2)]))[1]);
							outtextxy(170, 0, temp);
							getch();
							cleardevice();
							break;
						}
						}
					}
				}
				}
			}
			getch();
			cleardevice();
			initgraph(640, 480);
			setbkcolor(BLACK);
			break;
		}

		case 48: {
			exit(0);
			break; }
		}
	}
	ege::closegraph();
	return 0;
}