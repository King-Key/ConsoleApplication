#pragma once
//设备管理
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<conio.h>
#include<string.h>
#include<math.h>
#include<time.h>
#define M 5//进程数目
#define N 3//资源种类
class DeviceManegement
{
	struct bank {
		int Avaliable[N];//可利用资源向量
		int Max[M][N];//最大需求矩阵
		int Allocation[M][N];//分配矩阵
		int Need[M][N];//需求矩阵
	};
public:
	//银行家算法
	void Initilize(bank &x);
	int Safe_test(bank x);
	void Resource_allocate(bank &x);

	void shebeimain(void);
};

