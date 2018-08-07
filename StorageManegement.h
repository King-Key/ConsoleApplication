#pragma once
//存储管理
class StorageManegement
{
	int adnum = 10;    //地址数
	int yenum = 3;    //页表的数目
	int yesize = 1024;      //页面大小
	int adzu[100];       //存放地址的数组，由于本程序最多输入99个地址，100个数据空间已经够用


public:
	void set0adzu();  //将数组清0
	void suiji();  //随机生成地址数
	void printad();//打印地址
	void fifopage();  //先进先出页面管理算法
	void setmax(int page[5][2], int x); //设置某个数据为0
	int findmax(int page[5][2]); //找到最久未被使用的数，并将其置为最小
	void lrupage();    //最近最久未被使用页面管理算法
	int cunchumain();
};

