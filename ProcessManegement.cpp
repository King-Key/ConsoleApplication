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
/************************************���̹���*************************************************************/
#define M 5//�ܽ�����
#define N 3//����Դ��
#define MAX1 10
#define MAXxiaofei 20    //���建��ص��������
int count1 = 5;     //��ʼ��Ʒ������
int sleepsheng = 1300, sleepxiao = 2000;  //һ��ʼ�������������ʴ���������  
int counter;//ʵ�ʽ��̵ĸ���
HANDLE ahThread;
HANDLE bhThread;
HANDLE hThread;
int NAll = 0;
int Best[5][2]; //����Ѱ�������ɵ͵�������ʱ��ŵ�����
int Limit = 0; // ����Ѱ�ҵķ�Χ�ŵ���i
int Jage;
float Aver = 0;
struct fcfs {
	char name[10];//��������
	int prio;//�������ȼ�
	float arrivetime;//����ʱ��
	float number;
	float servicetime;//����ʱ��
	float starttime;//��ʼʱ��
	float finishtime;//���ʱ��
	float zztime;//��תʱ��
	float dqzztime;//��Ȩ��תʱ��
};
fcfs a[100];
struct sjf
{
	char name[10];//��������
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
	float come_time;//����ʱ��
	float run_begin_time;//����ʱ��
	float run_time;//��ʼʱ��
	float run_end_time;//����ʱ��
	float zztime;
	float dqzztime;
	int prio;
	int order;
	int run_flag;
}tasks[MAX1];

using namespace std;
struct bank {
	int Avaliable[N];//��������Դ����
	int Max[M][N];//����������
	int Allocation[M][N];//�������
	int Need[M][N];//�������
};
//�����ߺ��� 
void Proclucer()//�����ߺ���  
{
	while (1)
	{
		if (count1 >= 20)
		{
			cout << "���������!�ȴ� 1 ��!" << endl;
			Sleep(3000);
		}
		else
		{
			count1++;
			//printf("������һ����Ʒ����ǰ�Ĳ�Ʒ����������:%d\n\n", count1);
			cout << "������һ����Ʒ����ǰ��Ʒ��������Ϊ��" << count1 << endl;
			Sleep(1300);
		}
	}
}
// �����ߺ���
void Consumer()//�����ߺ���
{
	while (1)
	{
		if (count1 == 0)
		{
			//printf("������ѿգ��ȴ�2�룡\n");
			cout << "������������ȴ�2�룡" << endl;
			Sleep(2000);
		}
		else
		{
			count1--;
			//printf("ȡ����һ����Ʒ����ǰ��Ʒ��������:%d\n\n", count1);
			cout << "ȡ����һ����Ʒ����ǰ��Ʒ������Ϊ��" << count1 << endl;
			Sleep(2000);
		}
	}
}
//ֹͣ����
int tStop()
{
	int l = getchar();
	return 1;
}
//��ʼ����
void Start()
{
	ahThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Proclucer, NULL, 0, NULL);
	bhThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Consumer, NULL, 0, NULL);
	hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)tStop, NULL, 0, NULL);    //���߳�
	int IsStop = tStop();
	if (IsStop == 0)
	{
		CloseHandle(ahThread);
		CloseHandle(bhThread);
		CloseHandle(hThread);
	}
}
//ֹͣ
void setqishicanshu()
{
	cout << "ע�������й����м���0�����»س������򼴻�ֹͣ" << endl;
	cout << endl;

}
//���̵���������
void shengchanzhexiaofeizhe()//������
{
	setqishicanshu();

	cout << "***********����ַ��ز�������������*******************" << endl;
	Start();//��ʼ
	printf("\n");
}
//������������������
void shengchanzhexiaofeizhemain()
{
	shengchanzhexiaofeizhe();
	while (1)
	{
		int  IsStop = tStop();
		if (getchar() != NULL)       //ֹͣ���� 
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
//������������
void shengchanzhemain()
{
	cout << "***********************�����������������⡿************************" << endl;
	cout << "��ʼʱ�Ĳ�Ʒ��Ϊ" << count1 << endl;
	shengchanzhexiaofeizhemain();
}
//�����ȷ���
//����
void input(fcfs *p, int N1)//�����ȷ���
{
	int i;
	//printf("�����������  ���̵���ʱ��  ��������ʱ��  ����������:\n");
	
	for (i = 0; i <= N1 - 1; i++)
	{
		cout << "�������" << i + 1 << "�����̵���Ϣ" << endl;

		cout << "���ƣ�"; cin >> p[i].name; cout << endl;
	
		cout<<"��ţ�"; cin >> p[i].number; cout << endl;

		cout<<"����ʱ�䣺"; cin >> p[i].arrivetime; cout << endl;

		cout<<"����ʱ�䣺"; cin >> p[i].servicetime; cout << endl;

		cout << "���ȼ�"; cin >> p[i].prio; cout << endl;
	}

}
//���
void Print(fcfs *p, float arrivetime, float number, float servicetime, float starttime, float finishtime, float zztime, float dqzztime, int prio, int N1)
{
	int k;
	//printf("run order:");
	//printf("%s", p[0].name);
	for (k = 1; k < N1; k++)
	{
		//	printf("-->%s", p[k].name);
	}
	printf("\n������Ϣ:\n");
	printf("name arrivetime number  servicetime starttime finishtime zztime dqzztime prio\n");
	for (k = 0; k <= N1 - 1; k++)
	{
		printf("%s\t%-.3f\t%-.3f\t%-.3f\t%-.3f\t%-.3f\t%-.3f\t%-.3f\t%-.d\n", p[k].name, p[k].arrivetime, p[k].number,
			p[k].servicetime, p[k].starttime, p[k].finishtime, p[k].zztime, p[k].dqzztime, p[k].prio);
	}
}
//����
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
//�����ȷ���������
void xianlaixianfuwu()
{
	int N1;
	cout << "***********************�������ȷ����㷨��************************" << endl;
	cout << "�������������";cin >> N1;
	input(a, N1);
	FCFS(a, N1);
}//�����ȷ���

void xianlaimain()
{
	xianlaixianfuwu();
}
void Sinput(sjf *p, int N1)
{
	int i;
	for (i = 0; i <= N1 - 1; i++)
	{
		cout << "�������" << i + 1 << "�����̵���Ϣ" << endl;

		cout << "���ƣ�"; cin >> p[i].name; cout << endl;

		cout << "��ţ�"; cin >> p[i].number; cout << endl;

		cout << "����ʱ�䣺"; cin >> p[i].arrivetime; cout << endl;

		cout << "����ʱ�䣺"; cin >> p[i].servicetime; cout << endl;
	}
}
void SPrint(sjf *p, float arrivetime, float number, float servicetime, float starttime, float finishtime, float zztime, float dqzztime, int N1)
{
	int k;
	printf("\nִ��˳��:\n");
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

//����ҵ���ȵ����㷨
void sjfmain()
{
	int M11;
	cout << "************************������ҵ���ȵ����㷨��**************************" << endl;
	cout << "�������������"; cin >> M11;
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
	cout << "�������������"; cin >> counter;
	for (i = 0; i < counter; i++)
	{
		
		cout << "�������" << i + 1 << "�����̵���Ϣ" << endl;
	
		cout << "���ƣ�"; cin >> tasks[i].name; cout << endl;

		cout << "��ţ�"; cin >> tasks[i].number; cout << endl;

		cout << "����ʱ�䣺"; cin >> tasks[i].come_time; cout << endl;

		cout << "����ʱ�䣺"; cin >> tasks[i].run_time; cout << endl;

		cout << "���ȼ���"; cin >> tasks[i].prio; cout << endl;

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
	//printf("ƽ����תʱ��=%5.2f\n", turn_round_time / counter);
	//printf("ƽ����Ȩ��תʱ��=%5.2f\n", w / counter);
	//system("pause");
	return 0;
}
//������Ȩ���ȵ����㷨
void youxianquanmain()
{
	cout << "************************��������Ȩ���ȵ����㷨��**************************" << endl;
	pinput();
	ps();
	poutput();
}

void ProcessManegement::jinchengmain()
{

	int x, i = 1;
	while (i)
	{
		cout << "************************���̹�������㷨***************************" << endl;
		cout << "                ��1��    ������Ȩ���ȵ����㷨 " << endl;
		cout << "                ��2��    ����ҵ���ȵ����㷨  " << endl;
		cout << "                ��3��    �����ȷ�������㷨  " << endl;
		cout << "                ��4��    ����������������ģ��  " << endl;
		cout << "                ��0��        ������һ�� " << endl;
		cout << "*******************************************************************" << endl;
		cout << "  ������ѡ�";cin >> x;

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


