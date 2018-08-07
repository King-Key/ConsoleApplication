#include "stdafx.h"
#include "DeviceManegement.h"


//���м�
void DeviceManegement::Initilize(bank &x)//��ʼ��
{
	int i, j;

	cout << "**********************************���м��㷨**********************************" << endl;
	cout << "����������������(" << M << "*" << N<<"):" << endl;
	for (i = 0; i < M; i++)//��������������
	{
		for (j = 0; j < N; j++)
		{
			cin >> x.Max[i][j];
		}
	}
	cout << "������������Allocation(" << M<< "*" << N << "):" << endl;
	for (i = 0; i < M; i++)//���÷������
	{
		for (j = 0; j < N; j++)
		{
			cin >> x.Allocation[i][j];
		}
	}
	for (i = 0; i < M; i++)//�����������
	{
		for (j = 0; j < N; j++)
		{
			x.Need[i][j] = x.Max[i][j] - x.Allocation[i][j];
		}
	}
	cout << "������" << N << "���������Դ��������";
	for (i = 0; i < N; i++)//���ÿ�������Դ����
	{
		cin >> x.Avaliable[i];
	}
}
int DeviceManegement::Safe_test(bank x)//��鰲ȫ��
{
	//bank ss;
	int i, j;
	int safeprocess[M];//��ȫ��������
	int work[N];//������Դ����
	int Finish[M];//������ɱ�־����
	for (i = 0; i < N; i++)//��ʼʱ��������Դ�������ǿ�����Դ����
		work[i] = x.Avaliable[i];
	for (i = 0; i < M; i++)//��ʼ��finish���󣬿�ʼΪfalse
		Finish[i] = false;
	int k = 0;//��ȫ�������к�
	for (i = 0; i < M; i++)//ÿ�ζ��ӵ�һ�����̿�ʼѭ��
	{
		if (Finish[i] == false)
		{
			for (j = 0; j < N; j++)
			{
				if (x.Need[i][j] > work[j])//�����ǰNeed�������work�������������Ҫ��
					break;//�˳�
			}
			if (j == N)//��i����������ִ������
			{
				safeprocess[k++] = i;//�����̺Ŵ��밲ȫ����������
				for (int q = 0; q < N; q++)//�޸Ŀ�����Դ����
					work[q] += x.Allocation[i][q];//work������work��Allocation֮��
				Finish[i] = true;//��finish������Ϊtrue
				i = -1;
			}
		}
	}
	for (i = 0; i<M; i++)//����־���飬�����FALSE���Ҳ�����ȫ����
		if (!Finish[i])
		{
			cout << "�Ҳ�����ȫ���У�ϵͳ���ڲ���ȫ״̬��" << endl;
			return 0;

		}

	cout << "��һ����ȫ���У�";
	for (i = 0; i < M; i++)
	    cout << safeprocess[i] + 1<<" -> ";//����ȫ���������е���ʾ����
	cout << "ϵͳ���ڰ�ȫ״̬" << endl;
	return 1;
}
void DeviceManegement::Resource_allocate(bank &x)//ϵͳ�Խ�����Դ����Ĵ���
{
	while (true)
	{
		bank temp = x;//��ʱ��������x�ĳ�ֵ
		int Request[N];//��������
		int number;//���̺�
		int i, j;
		cout << "������Ҫ������Դ�Ľ��̺ţ�����-1�˳�����";
		cin >> number;
		if (number == -1)
		{
			break;
		}
		cout << "�����������" << N << "����Դ����Դ����";
		for (i = 0; i < N; i++)
			cin >> Request[i];//����������
		for (i = 0; i < N; i++)
		{
			if (Request[i] > x.Need[number - 1][i])//����������Դ�����������Դ
			{
				cout << "��������Ҫ����Դ��Ŀ�Ѿ����������ֵ��ϵͳ�����Է�����Դ" << endl;
				return;
			}
			if (Request[i] > x.Avaliable[i])//����������Դ���ڿ�������Դ
			{
				cout << "ϵͳ�пɷ�����ԴС������Ҫ��Դ��ϵͳ�����Է���" << endl;
				return;
			}

		}
		for (i = 0; i < N; i++)//����ϵͳ���Է�����Դ����������Դ�����鿴�Ƿ�ȫ
		{
			x.Avaliable[i] -= Request[i];
			x.Need[number - 1][i] -= Request[i];
			x.Allocation[number - 1][i] += Request[i];
		}
		if (Safe_test(x))//��ȫ�Լ����Ϊ��ȫ
		{
			printf("ϵͳ����Ϊ�ý��̷�����Դ\n");
			printf("������ɺ��Need����Ϊ:\n");
			for (i = 0; i < M; i++)
			{
				for (j = 0; j < N; j++)
				{
					cout << x.Need[i][j]<<"  ";
					
				}
				cout << endl;
			}
			cout << endl;
			cout << "������ɺ��Allocation����Ϊ��" << endl;

			for (i = 0; i < M; i++)
			{
				for (j = 0; j < N; j++)
				{
					cout << x.Allocation[i][j]<<"  ";
				}
				cout << endl;
			}
			cout << endl;
			cout << "������ɺ��Available����Ϊ��" << endl;
			for (i = 0; i < N; i++)
			{
				cout << x.Avaliable[i]<<"  ";
			}
			cout << endl;
			return;
		}
		else
		{
			cout << "ϵͳ��Ϊ�ý��̷�����Դ" << endl;
			x = temp;//�޸���ؾ��󣬲�������Դ
			return;
		}
	}
}

//�豸����
void DeviceManegement::shebeimain(void)
{
	bank current;//�������
	Initilize(current);//��ʼ��
	Safe_test(current);//��鰲ȫ��

	Resource_allocate(current);

}