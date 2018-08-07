// ConsoleApplication.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<Windows.h>
#include<iomanip>

//#include"Process_mangement.h"
using namespace std;


int main()
{
	/*操作系统实验总共分为四个部分
	1 进程管理
	2 设备管理
	3 文件管理
	4 存储管理
	*/
	int changenum;
	cout << "*******************操作系统实训项目***********************" << endl;
	cout << "*                  【1】  进程管理" << setw(24) << "*" << endl;
	cout << "*                  【2】  设备管理" << setw(24) << "*" << endl;
	cout << "*                  【3】  文件管理" << setw(24) << "*" << endl;
	cout << "*                  【4】  存储管理" << setw(24) << "*" << endl;
	cout << "*                  【0】  退    出" << setw(24) << "*" << endl;
	cout << "**********************************************************" << endl;
	cout << "请输入选项："; cin >> changenum;
	switch (changenum)
	{
	case 0:break;
	case 1:
	{
		system("cls");
		//ProcessManegement PM;
		//PM.jinchengmain();
	
	    ProcessManegement PM;
		PM.jinchengmain();
		main();
		break;
	}
	case 2:
	{
		system("cls");
		DeviceManegement DM;
		DM.shebeimain();
		main();
		break;
	}
	case 3:
	{
		system("cls");
		FileManegement F;
		F.File_Mangement();
		main();
		break;
	}
	case 4:
	{
		system("cls");
		StorageManegement SM;
		SM.cunchumain();
		main();
		break;
	}

	default:
		cout << "输入选项错误，请稍后重新输入！" << endl;
		Sleep(1000);
		system("cls");
		main();
		break;
	}

    return changenum;
}

