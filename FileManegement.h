#pragma once
//�ļ�����
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<iomanip>
#include<Windows.h>
using namespace std;

class FileManegement
{
	int NALL = 0;
	int Best[5][2];//����Ѱ�������ɵ͵�������ʱ��ŵ�����
	int Limit = 0;//����Ѱ�ҵķ�Χ�ŵ���i
	int Jage;
	float Aver = 0;
	
public:
	int File_Mangement();
	void CopyL(int Sour[], int Dist[], int x);//����Sour���Ƶ�����Dist,���Ƶ�x����
	void SetDI(int Discl[]);//������ɴŵ���
	void Print(int Pri[], int x);//��ӡ�������Pri
	void Deling(int Sour[], int x, int y);//����Sour��xλ���ϵ���ɾ��������yǰ�������ǰ�ƶ���y��������ֲ��䣨�����������y��
	void FCFS(int Han, int Discl[]);//�����ȷ����㷨
	void SSTF(int Han, int Discl[]);//���Ѱ��ʱ�������㷨
	int SCAN(int Han, int Discl[], int x, int y);//ɨ���㷨
	void CSCAN(int Han, int Discl[]);//ѭ��ɨ���㷨
	//void N_Step_Scan(int Han1, int Discl[]);//N��ɨ���㷨
	void Paixu();//Ѱ�������ɵ͵�������
	int show();//�˵�����
	//void Pri();
};

