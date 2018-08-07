#include "stdafx.h"
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<conio.h>
#include<string.h>
#include<math.h>
#include<time.h>

using namespace std;
//using namespace std;
/************************************进程管理*************************************************************/
#define M 5//总进程数
#define N 3//总资源数
#define MAX1 10
#define MAXxiaofei 20    //定义缓冲池的最大容量
int count1 = 5;     //初始产品的数量
int sleepsheng = 1300, sleepxiao = 2000;  //一开始生产者生产速率大于消费者  
int counter;//实际进程的个数
HANDLE ahThread;
HANDLE bhThread;
HANDLE hThread;
int NAll = 0;
int Best[5][2]; //用作寻道长度由低到高排序时存放的数组
int Limit = 0; // 输入寻找的范围磁道数i
int Jage;
float Aver = 0;
struct fcfs {
	char name[10];//进程名称
	int prio;//进程优先级
	float arrivetime;//到达时间
	float number;
	float servicetime;//运行时间
	float starttime;//开始时间
	float finishtime;//完成时间
	float zztime;//周转时间
	float dqzztime;//带权周转时间
};
fcfs a[100];
struct sjf
{
	char name[10];//进程名称
	float arrivetime;//
	float number;
	float servicetime;
	float starttime;
	float finishtime;
	float zztime;
	float dqzztime;
};
sjf b[100];
struct task_struct {
	char name[10];
	int number;
	float come_time;//到达时间
	float run_begin_time;//运行时间
	float run_time;//开始时间
	float run_end_time;//结束时间
	float zztime;
	float dqzztime;
	int prio;
	int order;
	int run_flag;
}tasks[MAX1];

using namespace std;
struct bank {
	int Avaliable[N];//可利用资源向量
	int Max[M][N];//最大需求矩阵
	int Allocation[M][N];//分配矩阵
	int Need[M][N];//需求矩阵
};
//生产者函数 
void Proclucer()//生产者函数  
{
	while (1)
	{
		if (count1 >= 20)
		{
			cout << "缓冲池已满!等待 1 秒!" << endl;
			Sleep(3000);
		}
		else
		{
			count1++;
			//printf("生产了一个产品！当前的产品的总数量是:%d\n\n", count1);
			cout << "生产了一个产品，当前产品的总数量为：" << count1 << endl;
			Sleep(1300);
		}
	}
}
// 消费者函数
void Consumer()//消费者函数
{
	while (1)
	{
		if (count1 == 0)
		{
			//printf("缓冲池已空！等待2秒！\n");
			cout << "缓冲池已满，等待2秒！" << endl;
			Sleep(2000);
		}
		else
		{
			count1--;
			//printf("取出了一个产品！当前产品的数量是:%d\n\n", count1);
			cout << "取出了一个产品，当前产品的数量为：" << count1 << endl;
			Sleep(2000);
		}
	}
}
//停止函数
int tStop()
{
	int l = getchar();
	return 1;
}
//开始函数
void Start()
{
	ahThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Proclucer, NULL, 0, NULL);
	bhThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Consumer, NULL, 0, NULL);
	hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)tStop, NULL, 0, NULL);    //多线程
	int IsStop = tStop();
	if (IsStop == 0)
	{
		CloseHandle(ahThread);
		CloseHandle(bhThread);
		CloseHandle(hThread);
	}
}
//停止
void setqishicanshu()
{
	cout << "注：在运行过程中键入0并按下回车，程序即会停止" << endl;
	cout << endl;

}
//进程调度主函数
void shengchanzhexiaofeizhe()//主函数
{
	setqishicanshu();

	cout << "***********会出现返回不了主界面的情况*******************" << endl;
	Start();//开始
	printf("\n");
}
//生产者消费者主函数
void shengchanzhexiaofeizhemain()
{
	shengchanzhexiaofeizhe();
	while (1)
	{
		int  IsStop = tStop();
		if (getchar() != NULL)       //停止进程 
		{
			TerminateThread(ahThread, 1);
			TerminateThread(bhThread, 1);
			TerminateThread(hThread, 1);
			CloseHandle(ahThread);
			CloseHandle(bhThread);
			CloseHandle(hThread);
			break;
		}
	}
}
//生产者主函数
void shengchanzhemain()
{
	cout << "***********************【生产者消费者问题】************************" << endl;
	cout << "开始时的产品数为" << count1 << endl;
	shengchanzhexiaofeizhemain();
}
//先来先服务
//输入
void input(fcfs *p, int N1)//先来先服务
{
	int i;
	//printf("输入进程名称  进程到达时间  进程运行时间  进程优先数:\n");
	
	for (i = 0; i <= N1 - 1; i++)
	{
		cout << "请输入第" << i + 1 << "调进程的信息" << endl;

		cout << "名称："; cin >> p[i].name; cout << endl;
	
		cout<<"编号："; cin >> p[i].number; cout << endl;

		cout<<"到达时间："; cin >> p[i].arrivetime; cout << endl;

		cout<<"运行时间："; cin >> p[i].servicetime; cout << endl;

		cout << "优先级"; cin >> p[i].prio; cout << endl;
	}

}
//输出
void Print(fcfs *p, float arrivetime, float number, float servicetime, float starttime, float finishtime, float zztime, float dqzztime, int prio, int N1)
{
	int k;
	//printf("run order:");
	//printf("%s", p[0].name);
	for (k = 1; k < N1; k++)
	{
		//	printf("-->%s", p[k].name);
	}
	printf("\n进程信息:\n");
	printf("name arrivetime number  servicetime starttime finishtime zztime dqzztime prio\n");
	for (k = 0; k <= N1 - 1; k++)
	{
		printf("%s\t%-.3f\t%-.3f\t%-.3f\t%-.3f\t%-.3f\t%-.3f\t%-.3f\t%-.d\n", p[k].name, p[k].arrivetime, p[k].number,
			p[k].servicetime, p[k].starttime, p[k].finishtime, p[k].zztime, p[k].dqzztime, p[k].prio);
	}
}
//排序
void sort(fcfs *p, int N1)
{
	for (int i = 0; i <= N1 - 1; i++)
		for (int j = 0; j <= i; j++)
			if (p[i].arrivetime < p[j].arrivetime)
			{
				fcfs temp;
				temp = p[i];
				p[i] = p[j];
				p[j] = temp;
			}
}
void deal(fcfs *p, float arrivetime, float servicetime, float starttime, float finishtime, float zztime, float dqzztime, int prio, int N1)
{
	int k;
	for (k = 0; k <= N1 - 1; k++)
	{
		if (p[k].arrivetime > p[k - 1].finishtime)
		{
			p[k].starttime = p[k].arrivetime;
			p[k].finishtime = p[k].arrivetime + p[k].servicetime;
		}
		else
		{
			p[k].starttime = p[k - 1].finishtime;
			p[k].finishtime = p[k - 1].finishtime + p[k].servicetime;
		}

	}
	for (k = 0; k <= N1 - 1; k++)
	{
		p[k].zztime = p[k].finishtime - p[k].arrivetime;
		p[k].dqzztime = p[k].zztime / p[k].servicetime;
	}
}
void FCFS(fcfs *p, int N1)
{
	float arrivetime = 0, number = 0, servicetime = 0, starttime = 0, finishtime = 0, zztime = 0, dqzztime = 0;
	int prio = 0;
	sort(p, N1);
	deal(p, arrivetime, servicetime, starttime, finishtime, zztime, dqzztime, prio, N1);
	Print(p, arrivetime, number, servicetime, starttime, finishtime, zztime, dqzztime, prio, N1);
}
//先来先服务主函数
void xianlaixianfuwu()
{
	int N1;
	cout << "***********************【先来先服务算法】************************" << endl;
	cout << "请输入进程数：";cin >> N1;
	input(a, N1);
	FCFS(a, N1);
}//先来先服务

void xianlaimain()
{
	xianlaixianfuwu();
}
void Sinput(sjf *p, int N1)
{
	int i;
	for (i = 0; i <= N1 - 1; i++)
	{
		cout << "请输入第" << i + 1 << "调进程的信息" << endl;

		cout << "名称："; cin >> p[i].name; cout << endl;

		cout << "编号："; cin >> p[i].number; cout << endl;

		cout << "到达时间："; cin >> p[i].arrivetime; cout << endl;

		cout << "运行时间："; cin >> p[i].servicetime; cout << endl;
	}
}
void SPrint(sjf *p, float arrivetime, float number, float servicetime, float starttime, float finishtime, float zztime, float dqzztime, int N1)
{
	int k;
	printf("\n执行顺序:\n");
	printf("%s", p[0].name);
	for (k = 1; k < N1; k++)
	{
		printf("-->%s", p[k].name);
	}
	printf("\nname\tarrivetime\tnumber\tservicetime\tstarttime\tfinishtime\tzztime\tdqzztime\n");
	for (k = 0; k <= N1 - 1; k++)
	{
		printf("%s\t%-.2f\t%-.2f\t%-.2f\t%-.2f\t%-.2f\t%-.2f\t%-.2f\t\n\n", p[k].name,
			p[k].arrivetime, p[k].servicetime, p[k].starttime, p[k].finishtime,
			p[k].zztime, p[k].dqzztime);
	}
}
void Ssort(sjf *p, int N1)
{
	for (int i = 0; i <= N1 - 1; i++)
		for (int j = 0; j <= i; j++) {
			if (p[i].arrivetime < p[j].arrivetime)
			{
				sjf temp;
				temp = p[i];
				p[i] = p[j];
				p[j] = temp;
			}
			if (p[i].arrivetime = p[j].arrivetime) {
				for (int i = 0; i <= N1 - 1; i++)
					for (int j = 0; j <= i; j++) {
						if (p[i].servicetime < p[j].servicetime)
						{
							sjf temp;
							temp = p[i];
							p[i] = p[j];
							p[j] = temp;
						}
					}
			}

		}
	for (int i = 1; i < N1; i++)
	{
		if (p[i].arrivetime < p[0].finishtime)
		{
			sjf s;
			s = p[i];
		}

	}
}
void Sdeal(sjf *p, float arrivetime, float servicetime, float starttime, float finishtime, float zztime, float dqzztime, int N1)
{
	int k;
	for (k = 0; k <= N1 - 1; k++)
	{
		if (k == 0)
		{
			p[k].starttime = p[k].arrivetime;
			p[k].finishtime = p[k].arrivetime + p[k].servicetime;
		}
		else
		{
			p[k].starttime = p[k - 1].finishtime;
			p[k].finishtime = p[k - 1].finishtime + p[k].servicetime;
		}
	}
	for (k = 0; k <= N1 - 1; k++)
	{
		p[k].zztime = p[k].finishtime - p[k].arrivetime;
		p[k].dqzztime = p[k].zztime / p[k].servicetime;
	}
}
void SJF(sjf *p, int N1)
{
	float arrivetime = 0, number = 0, servicetime = 0, starttime = 0, finishtime = 0, zztime = 0, dqzztime = 0;
	Ssort(p, N1);
	Sdeal(p, arrivetime, servicetime, starttime, finishtime, zztime, dqzztime, N1);
	SPrint(p, arrivetime, number, servicetime, starttime, finishtime, zztime, dqzztime, N1);
}

//短作业优先调度算法
void sjfmain()
{
	int M11;
	cout << "************************【短作业优先调度算法】**************************" << endl;
	cout << "请输入进程数："; cin >> M11;
	Sinput(b, M11);
	SJF(b, M11);
}

int ps()
{
	float temp_time = 0;
	int i = 0, j;
	int number_schedul, temp_counter;
	int max_priority;
	max_priority = tasks[i].prio;
	j = 1;
	while ((j<counter) && (tasks[i].come_time == tasks[j].come_time))
	{
		if (tasks[j].prio > tasks[i].prio)
		{
			max_priority = tasks[j].prio;
			i = j;
		}
		j++;
	}
	number_schedul = i;
	tasks[number_schedul].run_begin_time = tasks[number_schedul].come_time;
	tasks[number_schedul].run_end_time = tasks[number_schedul].run_begin_time + tasks[number_schedul].run_time;
	tasks[number_schedul].run_flag = 1;
	temp_time = tasks[number_schedul].run_end_time;
	tasks[number_schedul].order = 1;
	temp_counter = 1;
	while (temp_counter < counter)
	{
		max_priority = 0;
		for (j = 0; j < counter; j++)
		{
			if ((tasks[j].come_time <= temp_time) && (!tasks[j].run_flag))
				if (tasks[j].prio > max_priority)
				{
					max_priority = tasks[j].prio;
					number_schedul = j;
				}
		}
		tasks[number_schedul].run_begin_time = temp_time;
		tasks[number_schedul].run_end_time = tasks[number_schedul].run_begin_time + tasks[number_schedul].run_time;
		tasks[number_schedul].run_flag = 1;
		temp_time = tasks[number_schedul].run_end_time;
		temp_counter++;
		tasks[number_schedul].order = temp_counter;
	}
	return 0;
}
int pinput()
{

	int i;
	cout << "请输入进程数："; cin >> counter;
	for (i = 0; i < counter; i++)
	{
		
		cout << "请输入第" << i + 1 << "条进程的信息" << endl;
	
		cout << "名称："; cin >> tasks[i].name; cout << endl;

		cout << "编号："; cin >> tasks[i].number; cout << endl;

		cout << "到达时间："; cin >> tasks[i].come_time; cout << endl;

		cout << "运行时间："; cin >> tasks[i].run_time; cout << endl;

		cout << "优先级："; cin >> tasks[i].prio; cout << endl;

		tasks[i].run_begin_time = 0;
		tasks[i].run_end_time = 0;
		tasks[i].order = 0;
		tasks[i].run_flag = 0;
	}
	return 0;
}
int poutput()
{
	int i;
	float turn_round_time = 0, f1, w = 0;
	printf("name number come_time run_time run_begin_time run_end_time priority order turn_round_time zztime dqzztime\n");
	for (i = 0; i < counter; i++)
	{
		f1 = tasks[i].run_end_time - tasks[i].come_time;
		turn_round_time += f1;
		w += (f1 / tasks[i].run_time);
		tasks[i].zztime = tasks[i].run_end_time - tasks[i].come_time;
		tasks[i].dqzztime = tasks[i].zztime / tasks[i].run_time;
		printf("%s\t%d\t%5.3f\t%5.3f\t%5.3f\t\t%5.3f\t\t%d\t%d\t%5.3f\t%5.3f\t%5.3f\n", tasks[i].name, tasks[i].number, tasks[i].come_time, tasks[i].run_time,
			tasks[i].run_begin_time, tasks[i].run_end_time, tasks[i].prio, tasks[i].order, f1, tasks[i].zztime, tasks[i].dqzztime);
	}
	//printf("平均周转时间=%5.2f\n", turn_round_time / counter);
	//printf("平均带权周转时间=%5.2f\n", w / counter);
	//system("pause");
	return 0;
}
//高优先权优先调度算法
void youxianquanmain()
{
	cout << "************************【高优先权优先调度算法】**************************" << endl;
	pinput();
	ps();
	poutput();
}

void ProcessManegement::jinchengmain()
{

	int x, i = 1;
	while (i)
	{
		cout << "************************进程管理调度算法***************************" << endl;
		cout << "                【1】    高优先权优先调度算法 " << endl;
		cout << "                【2】    短作业优先调度算法  " << endl;
		cout << "                【3】    先来先服务调度算法  " << endl;
		cout << "                【4】    生产者消费者问题模拟  " << endl;
		cout << "                【0】        返回上一级 " << endl;
		cout << "*******************************************************************" << endl;
		cout << "  请输入选项：";cin >> x;

		switch (x)
		{
		case 1:
		{
			system("cls");
			youxianquanmain();

			break;
		}
		case 2:
		{
			system("cls");
			sjfmain();
			break;
		}
		case 3:
		{
			system("cls");
			xianlaimain();
			break;
		}
		case 4:
		{
			system("cls");
			shengchanzhemain();
			break;
		}
		case 0:
		{
			system("cls");
			i = 0;
			break;
		}
		}
	}
}


