#pragma once
//文件管理
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<iomanip>
#include<Windows.h>
using namespace std;

class FileManegement
{
	int NALL = 0;
	int Best[5][2];//用作寻道长度由低到高排序时存放的数组
	int Limit = 0;//输入寻找的范围磁道数i
	int Jage;
	float Aver = 0;
	
public:
	int File_Mangement();
	void CopyL(int Sour[], int Dist[], int x);//数组Sour复制到数组Dist,复制到x个数
	void SetDI(int Discl[]);//随机生成磁道数
	void Print(int Pri[], int x);//打印输出数组Pri
	void Deling(int Sour[], int x, int y);//数组Sour把x位置上的数删除，并把y前面的数向前移动，y后的数保持不变（即会出现两个y）
	void FCFS(int Han, int Discl[]);//先来先服务算法
	void SSTF(int Han, int Discl[]);//最短寻道时间优先算法
	int SCAN(int Han, int Discl[], int x, int y);//扫描算法
	void CSCAN(int Han, int Discl[]);//循环扫描算法
	//void N_Step_Scan(int Han1, int Discl[]);//N步扫描算法
	void Paixu();//寻道长度由低到高排序
	int show();//菜单函数
	//void Pri();
};

