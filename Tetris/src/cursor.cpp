#include "cursor.h"
#include <iostream>

using namespace std;

/*
\033[nA 光标上移n行
\033[nB 光标下移n行
\033[nC 光标右移n行
\033[nD 光标左移n行
\033[y;xH设置光标位置
\033[2J 清屏
\033[K 清除从光标到行尾的内容
\033[s 保存光标位置
\033[u 恢复光标位置
\033[?25l 隐藏光标
\033[?25h 显示光标
*/

void Cursor::save(){
    cout<<"\33[s";
}

void Cursor::resume(){
    cout<<"\33[u";
}

void Cursor::move_to(int x, int y)
{
	int i;
	for(i = 0; i < x; i++) //\33[nC]
		cout<<"\33[2C";
	for(i = 0; i < y; i++)
		cout<<"\33[1B";
}

/* 
\033[0m 关闭所有属性
\033[1m 高亮
\033[2m 亮度减半
\033[3m 斜体
\033[4m 下划线
\033[5m 闪烁
\033[6m 快闪
\033[7m 反显
\033[8m 消隐
\033[9m 中间一道横线
10-19 关于字体的
21-29 基本与1-9正好相反
30-37 设置前景色
    30 黑 31 红 32 绿 33 黄 34 蓝色 35 紫色 36 深绿 37 白色
38 打开下划线, 设置默认前景色
39 关闭下划线, 设置默认前景色
40-47 设置背景色
    40 黑色 41 红色 42 绿色 43 棕色 44 蓝色 45 品红 46 孔雀蓝 47 白色
48 不知道什么东西
49 设置默认背景色
50-89 没用
90-109 设置前景背景的，比之前的颜色浅
*/
void Cursor::draw_block(enum_color color){
    switch(color)
	{
		case BLACK     :cout<<"\033[40;30m  \033[0m";break;
		case RED       :cout<<"\033[41;31m  \033[0m";break;
		case GREEN     :cout<<"\033[42;32m  \033[0m";break;
		case YELLOW    :cout<<"\033[43;33m  \033[0m";break;
		case BLUE      :cout<<"\033[44;34m  \033[0m";break;
		case PURPLE    :cout<<"\033[45;35m  \033[0m";break;
		case DEEP_GREEN:cout<<"\033[46;36m  \033[0m";break;
		case WHITE     :cout<<"\033[47;37m  \033[0m";break;
		case CLEAR     :cout<<"\033[8m  ";
		default: break;
	}
}