#include "stdafx.h"
#include "DeviceManegement.h"


//银行家
void DeviceManegement::Initilize(bank &x)//初始化
{
	int i, j;

	cout << "**********************************银行家算法**********************************" << endl;
	cout << "请输入最大需求矩阵(" << M << "*" << N<<"):" << endl;
	for (i = 0; i < M; i++)//设置最大需求矩阵
	{
		for (j = 0; j < N; j++)
		{
			cin >> x.Max[i][j];
		}
	}
	cout << "请输入分配矩阵Allocation(" << M<< "*" << N << "):" << endl;
	for (i = 0; i < M; i++)//设置分配矩阵
	{
		for (j = 0; j < N; j++)
		{
			cin >> x.Allocation[i][j];
		}
	}
	for (i = 0; i < M; i++)//设置需求矩阵
	{
		for (j = 0; j < N; j++)
		{
			x.Need[i][j] = x.Max[i][j] - x.Allocation[i][j];
		}
	}
	cout << "请输入" << N << "类可利用资源的数量：";
	for (i = 0; i < N; i++)//设置可利用资源向量
	{
		cin >> x.Avaliable[i];
	}
}
int DeviceManegement::Safe_test(bank x)//检查安全性
{
	//bank ss;
	int i, j;
	int safeprocess[M];//安全序列向量
	int work[N];//空闲资源矩阵
	int Finish[M];//进程完成标志矩阵
	for (i = 0; i < N; i++)//开始时可利用资源向量就是空闲资源矩阵
		work[i] = x.Avaliable[i];
	for (i = 0; i < M; i++)//初始化finish矩阵，开始为false
		Finish[i] = false;
	int k = 0;//安全序列排列号
	for (i = 0; i < M; i++)//每次都从第一个进程开始循环
	{
		if (Finish[i] == false)
		{
			for (j = 0; j < N; j++)
			{
				if (x.Need[i][j] > work[j])//如果当前Need矩阵大于work矩阵，则不满足分配要求
					break;//退出
			}
			if (j == N)//第i个进程满足执行条件
			{
				safeprocess[k++] = i;//将进程号存入安全序列向量中
				for (int q = 0; q < N; q++)//修改空闲资源矩阵
					work[q] += x.Allocation[i][q];//work矩阵是work和Allocation之和
				Finish[i] = true;//将finish矩阵置为true
				i = -1;
			}
		}
	}
	for (i = 0; i<M; i++)//检查标志数组，如果有FALSE则找不到安全序列
		if (!Finish[i])
		{
			cout << "找不到安全序列，系统处于不安全状态！" << endl;
			return 0;

		}

	cout << "有一个安全序列：";
	for (i = 0; i < M; i++)
	    cout << safeprocess[i] + 1<<" -> ";//将安全序列向量中的显示出来
	cout << "系统处于安全状态" << endl;
	return 1;
}
void DeviceManegement::Resource_allocate(bank &x)//系统对进程资源申请的处理
{
	while (true)
	{
		bank temp = x;//临时变量储存x的初值
		int Request[N];//请求向量
		int number;//进程号
		int i, j;
		cout << "请输入要申请资源的进程号（输入-1退出）：";
		cin >> number;
		if (number == -1)
		{
			break;
		}
		cout << "请输入需求的" << N << "类资源的资源数：";
		for (i = 0; i < N; i++)
			cin >> Request[i];//输入请求量
		for (i = 0; i < N; i++)
		{
			if (Request[i] > x.Need[number - 1][i])//若是所需资源大于需求的资源
			{
				cout << "进程所需要的资源数目已经超出其最大值，系统不予以分配资源" << endl;
				return;
			}
			if (Request[i] > x.Avaliable[i])//若是所需资源大于可利用资源
			{
				cout << "系统中可分配资源小于所需要资源，系统不予以分配" << endl;
				return;
			}

		}
		for (i = 0; i < N; i++)//假设系统可以分配资源，将所需资源分配后查看是否安全
		{
			x.Avaliable[i] -= Request[i];
			x.Need[number - 1][i] -= Request[i];
			x.Allocation[number - 1][i] += Request[i];
		}
		if (Safe_test(x))//安全性检查结果为安全
		{
			printf("系统可以为该进程分配资源\n");
			printf("分配完成后的Need矩阵为:\n");
			for (i = 0; i < M; i++)
			{
				for (j = 0; j < N; j++)
				{
					cout << x.Need[i][j]<<"  ";
					
				}
				cout << endl;
			}
			cout << endl;
			cout << "分配完成后的Allocation矩阵为：" << endl;

			for (i = 0; i < M; i++)
			{
				for (j = 0; j < N; j++)
				{
					cout << x.Allocation[i][j]<<"  ";
				}
				cout << endl;
			}
			cout << endl;
			cout << "分配完成后的Available矩阵为：" << endl;
			for (i = 0; i < N; i++)
			{
				cout << x.Avaliable[i]<<"  ";
			}
			cout << endl;
			return;
		}
		else
		{
			cout << "系统不为该进程分配资源" << endl;
			x = temp;//修改相关矩阵，不分配资源
			return;
		}
	}
}

//设备管理
void DeviceManegement::shebeimain(void)
{
	bank current;//定义变量
	Initilize(current);//初始化
	Safe_test(current);//检查安全性

	Resource_allocate(current);

}