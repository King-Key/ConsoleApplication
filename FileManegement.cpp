#include "stdafx.h"
#include "FileManegement.h"


//主函数
int FileManegement::File_Mangement()
{
	int i;
	int Discline[10];//声明准备要生成的随机磁道号的数组
	int Hand;//磁道数
	int Con = 1;
	int n;
	while (Con==1)
	{
		Jage = 0;
		cout << "**************************************************************" << endl;
		cout << "请输入初始的磁道数（0<n<65536):"; cin >> Hand; cout << endl;
		cout << "请输入寻找的范围："; cin >> Limit; cout << endl;
		if (Limit > 65536)
		{
			cout << "超出范围！" << endl;

		}
		else
		{
			/*cout << "************************文件管理*****************************" << endl;
			cout << "                      磁盘调度算法"<<setw(10) << endl;
			cout << "                 【1】 先来先服务算法（FCFS)" << setw(10) << endl;
			cout << "                 【2】 最短寻道时间优先算法(SSTF)" << setw(10) << endl;
			cout << "                 【3】 扫描算法(SCAN)" << setw(10) << endl;
			cout << "                 【4】 循环扫描算法(CSCAN)" << setw(10) << endl;
			cout << "                 【5】 算法比较" << setw(10) << endl;
			cout << "                 【6】 返回上一级" << endl;
			cout << "                 【0】 退出" << setw(10) << endl;
			cout << "*************************************************************" << endl;
			cout << "请输入选项："; cin >> n;*/
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
				cout << "*****************************【先来先服务算法】********************************" << endl;
				SetDI(Discline);//随机生成磁道数
				FCFS(Hand, Discline);//先来先服务算法
				break;
			}
			case 2:
			{
				system("cls");
				cout << "*****************************【最短寻道时间优先算法】********************************" << endl;
				SetDI(Discline);
				SSTF(Hand, Discline);//最短寻道时间优先算法
				break;
			}
			case 3:
			{
				system("cls");
				cout << "*****************************【扫描算法】********************************" << endl;
				SetDI(Discline);
				SCAN(Hand, Discline, 0, 9);//扫描算法
				break;
			}
			case 4:
			{
				system("cls");
				cout << "*****************************【循环扫描算法】********************************" << endl;
				SetDI(Discline);
				CSCAN(Hand, Discline);//循环扫描算法
				break;
			}
			case 5:
			{
				system("cls");
				cout << "*****************************【算法比较】********************************" << endl;
				SetDI(Discline);
				FCFS(Hand, Discline);
				SSTF(Hand, Discline);
				SCAN(Hand, Discline, 0, 9);
				CSCAN(Hand, Discline);
				//N_Step_Scan(Hand, Discline);
				Paixu();
				cout << endl;
				cout << "寻道长度由低到高排序:" ;
				for (i = 0; i < 5; i++)
				{
					cout << Best[i][0]<<"  ";
				}
				cout << endl;
				break;

			}

				
			default:
				cout << "输入选项错误，稍后请重新选择！" << endl;
				Sleep(3000);
				system("cls");
				File_Mangement();
				break;
			}

		}

	}
	return Con;
}

//菜单函数
int FileManegement::show()
{
	int n;
	cout << "************************文件管理*****************************" << endl;
	cout << "                      磁盘调度算法" << setw(10) << endl;
	cout << "                 【1】 先来先服务算法（FCFS)" << setw(10) << endl;
	cout << "                 【2】 最短寻道时间优先算法(SSTF)" << setw(10) << endl;
	cout << "                 【3】 扫描算法(SCAN)" << setw(10) << endl;
	cout << "                 【4】 循环扫描算法(CSCAN)" << setw(10) << endl;
	cout << "                 【5】 算法比较" << setw(10) << endl;
	cout << "                 【0】 返回上一级" << setw(10) << endl;
	cout << "*************************************************************" << endl;
	cout << "请输入选项："; cin >> n;
	return n;
}
//数组Sour复制到数组Dist,复制到x个数
void FileManegement::CopyL(int Sour[], int Dist[], int x)
{
	int i;
	for (i = 0; i <= x; i++)
	{
		Dist[i] = Sour[i];
	}
}

//打印输出数组Pri
void FileManegement::Print(int Pri[], int x)
{
	int i;
	for (i = 0; i <= x; i++)
	{
		cout << Pri[i]<<"  ";
	}

}

//随机生成磁道数
void FileManegement::SetDI(int Discl[])
{
	int i;
	for (i = 0; i <= 9; i++)
	{
		Discl[i] = rand() % Limit;//随机生成10个磁道号
	}
	cout << "需要寻找的磁道号：";
	Print(Discl, 9);
	
}

//数组Sour把x位置上的数删除，并把y前面的数向前移动，y后的数保持不变（即会出现两个y）
void FileManegement::Deling(int Sour[], int x, int y)
{
	int i;
	for (i = x; i < y; i++)
	{
		Sour[i] = Sour[i + 1];
		x++;
	}
}

//先来先服务算法实现
void FileManegement::FCFS(int Han, int Discl[])
{
	int Rline[10];//将随机生成的磁道数数组Discl复制给少数族Rline
	int i, k, ALL, Temp;//Temp是计算移动的磁道距离的临时变量
	ALL = 0;//统计全部的磁道数数量
	k = 9;//限定10个的磁道数
	CopyL(Discl, Rline, 9);//复制磁道号到临时的数组Rline
	cout << endl;
	cout << "按照FCFS算法的访问顺序为：" ;
	ALL = Han - Rline[0];
	for (i = 0; i < 9; i++)
	{
		Temp = Rline[0] - Rline[1];//求出移动磁道数，前一个磁道数减去后一个磁道数得出临时的移动距离
		if (Temp < 0)
		{
			Temp = (-Temp);//移动磁道数为负时，算出相反数即为移动磁道数
			
		}
		cout << Rline[0] << "  ";
		ALL = ALL + Temp;//求和
		Deling(Rline, 0, k);//每个磁道数向前移动一位
		k--;

	}
	Best[Jage][1] = ALL;//Best[][1]存放移动磁道数
	Best[Jage][0] = 1;//Best[][0]存放算法的序号为：1
	Jage++;//排序的序号加1
	Aver = ((float)ALL) / 10;//求平均寻道次数
	cout << endl;
	cout << "移动磁道数：" << ALL << endl;
	cout << "平均寻道长度：" << Aver << endl;

}

//最短寻道时间优先算法实现
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
	cout << "按照SST算法磁道的访问顺序为：" ;
	for (i = 0; i <= 9; i++)
	{
		Min = 64000;
		for (j = 0; j <= k; j++)//内循环寻找与当前磁道号最短寻道的时间的磁道号
		{
			if (Rline[j] > Han)//如果大于当前，执行下一句
				Temp = Rline[j] - Han;
			else
				Temp = Han - Rline[j];//求出临时的移动距离

			if (Temp < Min)//如果每求出一次的移动距离小于Min,执行下一句
			{
				Min = Temp;
				h = j;
			}

		}
		ALL = ALL + Min;//统计移动距离
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
	cout << "移动磁道数：" << ALL << endl;
	cout << "平均寻道长度：" << Aver << endl;

}

//扫描算法实现
int FileManegement::SCAN(int Han, int Discl[], int x, int y)
{
	int j, k, h, m, n, ALL = 0;
	int t = 0;
	int Temp;
	int Min;
	int Rline[10];
	int Order = 1;
	k = y;
	m = 2;//控制while语句的执行，确保当前磁道由内向外都要扫描到
	CopyL(Discl, Rline, 9);
	cout << endl;
	cout << "按照SCAN算法磁道的访问顺序为：" ;
	Min = 64000;
	for (j = x; j <= y; j++)//寻找与当前磁道最短寻道时间的磁道号
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
	if (Rline[h] >= Han)//判断磁道的移动方向
	{
		//Order = 0;
		t = 1;
	}
	Han = Rline[h];
	Deling(Rline, h, k);
	k--;
	while (m>0)
	{
		if (Order == 1)//Order=1:磁道向内移动
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
		else//Order=0：磁道向外移动
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
		cout << "磁道移动数为：" << ALL << endl;
		cout << "平均寻道长度为：" << Aver << endl;


	}
	if (t == 1)
		cout << "磁道由内向外移动" << endl;
	else
		cout << "磁道由外向内移动" << endl;
	return	Han;
}

//循环扫描算法实现
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
	cout << "按照CSCAN算法磁道的访问顺序为：" ;
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
			for (i = 0; i < k; i++)//算出剩下磁道号的最小值
			{
				if (tmp > Rline[i])
					tmp = Rline[i];
				Han = tmp;//最小的磁道号给Han
				Temp = Last - tmp;//求最大与最小的距离差
				ALL = ALL + Temp;
			}
		}

	}
	Best[Jage][1] = ALL;
	Best[Jage][0] = 4;
	Jage++;
	Aver = ((float)ALL) / 10;
	cout << endl;
	cout << "移动的磁道数为：" << ALL << endl;
	cout << "平均寻道长度为：" << Aver << endl;


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