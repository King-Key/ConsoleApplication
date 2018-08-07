#include "stdafx.h"
#include "FileManegement.h"


//������
int FileManegement::File_Mangement()
{
	int i;
	int Discline[10];//����׼��Ҫ���ɵ�����ŵ��ŵ�����
	int Hand;//�ŵ���
	int Con = 1;
	int n;
	while (Con==1)
	{
		Jage = 0;
		cout << "**************************************************************" << endl;
		cout << "�������ʼ�Ĵŵ�����0<n<65536):"; cin >> Hand; cout << endl;
		cout << "������Ѱ�ҵķ�Χ��"; cin >> Limit; cout << endl;
		if (Limit > 65536)
		{
			cout << "������Χ��" << endl;

		}
		else
		{
			/*cout << "************************�ļ�����*****************************" << endl;
			cout << "                      ���̵����㷨"<<setw(10) << endl;
			cout << "                 ��1�� �����ȷ����㷨��FCFS)" << setw(10) << endl;
			cout << "                 ��2�� ���Ѱ��ʱ�������㷨(SSTF)" << setw(10) << endl;
			cout << "                 ��3�� ɨ���㷨(SCAN)" << setw(10) << endl;
			cout << "                 ��4�� ѭ��ɨ���㷨(CSCAN)" << setw(10) << endl;
			cout << "                 ��5�� �㷨�Ƚ�" << setw(10) << endl;
			cout << "                 ��6�� ������һ��" << endl;
			cout << "                 ��0�� �˳�" << setw(10) << endl;
			cout << "*************************************************************" << endl;
			cout << "������ѡ�"; cin >> n;*/
			n = show();
			switch (n)
			{
			case 0:
			{	
				system("cls");
				return 0;
				
				break;
				
			}
			case 1:
			{
				system("cls");
				cout << "*****************************�������ȷ����㷨��********************************" << endl;
				SetDI(Discline);//������ɴŵ���
				FCFS(Hand, Discline);//�����ȷ����㷨
				break;
			}
			case 2:
			{
				system("cls");
				cout << "*****************************�����Ѱ��ʱ�������㷨��********************************" << endl;
				SetDI(Discline);
				SSTF(Hand, Discline);//���Ѱ��ʱ�������㷨
				break;
			}
			case 3:
			{
				system("cls");
				cout << "*****************************��ɨ���㷨��********************************" << endl;
				SetDI(Discline);
				SCAN(Hand, Discline, 0, 9);//ɨ���㷨
				break;
			}
			case 4:
			{
				system("cls");
				cout << "*****************************��ѭ��ɨ���㷨��********************************" << endl;
				SetDI(Discline);
				CSCAN(Hand, Discline);//ѭ��ɨ���㷨
				break;
			}
			case 5:
			{
				system("cls");
				cout << "*****************************���㷨�Ƚϡ�********************************" << endl;
				SetDI(Discline);
				FCFS(Hand, Discline);
				SSTF(Hand, Discline);
				SCAN(Hand, Discline, 0, 9);
				CSCAN(Hand, Discline);
				//N_Step_Scan(Hand, Discline);
				Paixu();
				cout << endl;
				cout << "Ѱ�������ɵ͵�������:" ;
				for (i = 0; i < 5; i++)
				{
					cout << Best[i][0]<<"  ";
				}
				cout << endl;
				break;

			}

				
			default:
				cout << "����ѡ������Ժ�������ѡ��" << endl;
				Sleep(3000);
				system("cls");
				File_Mangement();
				break;
			}

		}

	}
	return Con;
}

//�˵�����
int FileManegement::show()
{
	int n;
	cout << "************************�ļ�����*****************************" << endl;
	cout << "                      ���̵����㷨" << setw(10) << endl;
	cout << "                 ��1�� �����ȷ����㷨��FCFS)" << setw(10) << endl;
	cout << "                 ��2�� ���Ѱ��ʱ�������㷨(SSTF)" << setw(10) << endl;
	cout << "                 ��3�� ɨ���㷨(SCAN)" << setw(10) << endl;
	cout << "                 ��4�� ѭ��ɨ���㷨(CSCAN)" << setw(10) << endl;
	cout << "                 ��5�� �㷨�Ƚ�" << setw(10) << endl;
	cout << "                 ��0�� ������һ��" << setw(10) << endl;
	cout << "*************************************************************" << endl;
	cout << "������ѡ�"; cin >> n;
	return n;
}
//����Sour���Ƶ�����Dist,���Ƶ�x����
void FileManegement::CopyL(int Sour[], int Dist[], int x)
{
	int i;
	for (i = 0; i <= x; i++)
	{
		Dist[i] = Sour[i];
	}
}

//��ӡ�������Pri
void FileManegement::Print(int Pri[], int x)
{
	int i;
	for (i = 0; i <= x; i++)
	{
		cout << Pri[i]<<"  ";
	}

}

//������ɴŵ���
void FileManegement::SetDI(int Discl[])
{
	int i;
	for (i = 0; i <= 9; i++)
	{
		Discl[i] = rand() % Limit;//�������10���ŵ���
	}
	cout << "��ҪѰ�ҵĴŵ��ţ�";
	Print(Discl, 9);
	
}

//����Sour��xλ���ϵ���ɾ��������yǰ�������ǰ�ƶ���y��������ֲ��䣨�����������y��
void FileManegement::Deling(int Sour[], int x, int y)
{
	int i;
	for (i = x; i < y; i++)
	{
		Sour[i] = Sour[i + 1];
		x++;
	}
}

//�����ȷ����㷨ʵ��
void FileManegement::FCFS(int Han, int Discl[])
{
	int Rline[10];//��������ɵĴŵ�������Discl���Ƹ�������Rline
	int i, k, ALL, Temp;//Temp�Ǽ����ƶ��Ĵŵ��������ʱ����
	ALL = 0;//ͳ��ȫ���Ĵŵ�������
	k = 9;//�޶�10���Ĵŵ���
	CopyL(Discl, Rline, 9);//���ƴŵ��ŵ���ʱ������Rline
	cout << endl;
	cout << "����FCFS�㷨�ķ���˳��Ϊ��" ;
	ALL = Han - Rline[0];
	for (i = 0; i < 9; i++)
	{
		Temp = Rline[0] - Rline[1];//����ƶ��ŵ�����ǰһ���ŵ�����ȥ��һ���ŵ����ó���ʱ���ƶ�����
		if (Temp < 0)
		{
			Temp = (-Temp);//�ƶ��ŵ���Ϊ��ʱ������෴����Ϊ�ƶ��ŵ���
			
		}
		cout << Rline[0] << "  ";
		ALL = ALL + Temp;//���
		Deling(Rline, 0, k);//ÿ���ŵ�����ǰ�ƶ�һλ
		k--;

	}
	Best[Jage][1] = ALL;//Best[][1]����ƶ��ŵ���
	Best[Jage][0] = 1;//Best[][0]����㷨�����Ϊ��1
	Jage++;//�������ż�1
	Aver = ((float)ALL) / 10;//��ƽ��Ѱ������
	cout << endl;
	cout << "�ƶ��ŵ�����" << ALL << endl;
	cout << "ƽ��Ѱ�����ȣ�" << Aver << endl;

}

//���Ѱ��ʱ�������㷨ʵ��
void FileManegement::SSTF(int Han, int Discl[])
{
	int i, j, k, h, ALL;
	int Temp;
	int Rline[10];
	int Min;
	ALL = 0;
	k = 9;
	CopyL(Discl, Rline, 9);
	cout << endl;
	cout << "����SST�㷨�ŵ��ķ���˳��Ϊ��" ;
	for (i = 0; i <= 9; i++)
	{
		Min = 64000;
		for (j = 0; j <= k; j++)//��ѭ��Ѱ���뵱ǰ�ŵ������Ѱ����ʱ��Ĵŵ���
		{
			if (Rline[j] > Han)//������ڵ�ǰ��ִ����һ��
				Temp = Rline[j] - Han;
			else
				Temp = Han - Rline[j];//�����ʱ���ƶ�����

			if (Temp < Min)//���ÿ���һ�ε��ƶ�����С��Min,ִ����һ��
			{
				Min = Temp;
				h = j;
			}

		}
		ALL = ALL + Min;//ͳ���ƶ�����
		cout << Rline[h] << "  ";
		Han = Rline[h];
		Deling(Rline, h, k);
		k--;
	}

	Best[Jage][1] = ALL;
	Best[Jage][0] = 2;
	Jage++;
	Aver = ((float)ALL) / 10;
	cout << endl;
	cout << "�ƶ��ŵ�����" << ALL << endl;
	cout << "ƽ��Ѱ�����ȣ�" << Aver << endl;

}

//ɨ���㷨ʵ��
int FileManegement::SCAN(int Han, int Discl[], int x, int y)
{
	int j, k, h, m, n, ALL = 0;
	int t = 0;
	int Temp;
	int Min;
	int Rline[10];
	int Order = 1;
	k = y;
	m = 2;//����while����ִ�У�ȷ����ǰ�ŵ��������ⶼҪɨ�赽
	CopyL(Discl, Rline, 9);
	cout << endl;
	cout << "����SCAN�㷨�ŵ��ķ���˳��Ϊ��" ;
	Min = 64000;
	for (j = x; j <= y; j++)//Ѱ���뵱ǰ�ŵ����Ѱ��ʱ��Ĵŵ���
	{
		if (Rline[j] > Han)
		{
			Temp = Rline[j] - Han;
		}
		else
		{
			Temp = Han - Rline[j];	
		}

		if (Temp < Min)
		{
			Min = Temp;
			h = j;
		}
	}

	ALL = ALL + Min;
	cout << Rline[h]<<"  ";
	if (Rline[h] >= Han)//�жϴŵ����ƶ�����
	{
		//Order = 0;
		t = 1;
	}
	Han = Rline[h];
	Deling(Rline, h, k);
	k--;
	while (m>0)
	{
		if (Order == 1)//Order=1:�ŵ������ƶ�
		{
			for (j = x; j <= y; j++)
			{
				h = -1;
				Min = 64000;
				for (n = x; n <= k; n++)
				{
					if (Rline[n] <= Han)
					{
						Temp = Han - Rline[n];
						if (Temp < Min)
						{
							Min = Temp;
							h = n;
						}
					}
				}
				if (h != -1)
				{
					ALL = ALL + Min;
					cout << Rline[h]<<"  ";
					Han = Rline[h];
					Deling(Rline, h, k);
					k--;
				}
			}
			Order = 0;
			m--;
		}
		else//Order=0���ŵ������ƶ�
		{
			for (j = x; j <= y; j++)
			{
				h = -1;
				Min = 64000;
				for (n = x; n <= k; n++)
				{
					if (Rline[n] > Han)
					{
						Temp = Rline[n] - Han;
						if (Temp < Min)
						{
							Min = Temp;
							h = n;
						}
					}
				}
				if (h != -1)
				{
					ALL = ALL + Min;
					cout << Rline[h]<<"  ";
					Han = Rline[h];
					Deling(Rline, h, k);
					k--;
				}
			}
			Order = 1;
			m--;
		}
	}
	NALL = NALL + ALL;
	if ((y - x) > 5)
	{
		Best[Jage][1] = ALL;
		Best[Jage][0] = 3;
		Jage++;
		Aver = ((float)ALL) / 10;
		cout << endl;
		cout << "�ŵ��ƶ���Ϊ��" << ALL << endl;
		cout << "ƽ��Ѱ������Ϊ��" << Aver << endl;


	}
	if (t == 1)
		cout << "�ŵ����������ƶ�" << endl;
	else
		cout << "�ŵ����������ƶ�" << endl;
	return	Han;
}

//ѭ��ɨ���㷨ʵ��
void FileManegement::CSCAN(int Han, int Discl[])
{
	int j, h, n, m, Temp, k, ALL, Last, i;
	int Rline[10];
	int Min;
	int tmp = 0;
	m = 2;
	k = 9;
	ALL = 0;
	Last = Han;
	CopyL(Discl, Rline, 9);
	cout << endl;
	cout << "����CSCAN�㷨�ŵ��ķ���˳��Ϊ��" ;
	while (k>=0)
	{
		for (j = 0; j <= 9; j++)
		{
			h = -1;
			Min = 64000;
			for (n = 0; n <= k; n++)
			{
				if (Rline[n] >= Han)
				{
					Temp = Rline[n] - Han;
					if (Temp < Min)
					{
						Min = Temp;
						h = n;
					}
				}
			}
			if (h != -1)
			{
				ALL = ALL + Min;
				cout << Rline[h]<<"  ";
				Han = Rline[h];
				Last = Rline[h];
				Deling(Rline, h, k);
				k--;
			}
			

		}
		if (k >= 0)
		{
			tmp = Rline[0];
			for (i = 0; i < k; i++)//���ʣ�´ŵ��ŵ���Сֵ
			{
				if (tmp > Rline[i])
					tmp = Rline[i];
				Han = tmp;//��С�Ĵŵ��Ÿ�Han
				Temp = Last - tmp;//���������С�ľ����
				ALL = ALL + Temp;
			}
		}

	}
	Best[Jage][1] = ALL;
	Best[Jage][0] = 4;
	Jage++;
	Aver = ((float)ALL) / 10;
	cout << endl;
	cout << "�ƶ��Ĵŵ���Ϊ��" << ALL << endl;
	cout << "ƽ��Ѱ������Ϊ��" << Aver << endl;


}

void FileManegement::Paixu()	
{
	int i, j, Temp;
	for (i = 0; i < 5; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (Best[j][1] > Best[j + 1][1])
			{
				Temp = Best[j + 1][1];
				Best[j + 1][1] = Best[j][1];
				Best[j][1] = Temp;
				Temp = Best[j + 1][0];
				Best[j + 1][0] = Best[j][0];
				Best[j][0] = Temp;

			}
		}
	}

}