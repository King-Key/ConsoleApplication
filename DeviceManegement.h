#pragma once
//�豸����
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<conio.h>
#include<string.h>
#include<math.h>
#include<time.h>
#define M 5//������Ŀ
#define N 3//��Դ����
class DeviceManegement
{
	struct bank {
		int Avaliable[N];//��������Դ����
		int Max[M][N];//����������
		int Allocation[M][N];//�������
		int Need[M][N];//�������
	};
public:
	//���м��㷨
	void Initilize(bank &x);
	int Safe_test(bank x);
	void Resource_allocate(bank &x);

	void shebeimain(void);
};

