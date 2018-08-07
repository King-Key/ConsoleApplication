#include "stdafx.h"
#include "StorageManegement.h"


//将数组清0
void StorageManegement::set0adzu()  
{
	int i;
	for (i = 0; i<100; i++)
	{
		adzu[i] = 0;
	}
}

//随机生成地址数
void StorageManegement::suiji()  
{
	int i;
	srand((int)time(NULL));
	for (i = 1; i <= adnum; i++)
	{
		adzu[i] = rand() % 10000;          //默认生成10000以内的地址
	}
}

//打印地址
void StorageManegement::printad()  //打印地址
{
	int i;
	cout << "目前转化为的地址有：";
	for (i = 1; i <= adnum; i++)
	{
		cout << adzu[i] / yesize << "  ";
	}
	cout << endl;
}

//先进先出页面管理算法
void StorageManegement::fifopage()  //先进先出页面管理算法
{
	printad();  //打印地址
	int i, j, y, x = 1, queye = 0, shan = 0, kong = 3;
	int page[5];
	page[1] = -1;
	page[2] = -1;
	page[3] = -1;
	page[4] = -1;    //初始化页表
	for (i = 1; i <= adnum; i++)
	{
		x = 1;
		cout << "本次地址为： ";   //先输出下原有的地址
		for (j = 1; j <= yenum; j++)
		{

			if (page[j] == adzu[i] / yesize)
			{
				x = 0;
				break;
			}
		}
		if (x == 1)
		{
			queye++;
			shan = (shan) % (yenum)+1;    //当有新数据代替旧数据时，shan作为新数据的地址记录就加1，已页表数为一个循环
			page[shan] = adzu[i] / yesize;

		}
		cout << adzu[i] / yesize << " " << " " << " " << " ";
		for (y = 1; y <= yenum; y++)
		{

			if (page[y] == -1)
			{
				cout << " " << "  ";   //如果数据为-1，表示为空
			}
			else
			{

				cout << page[y] << "  ";
			}
		}
		cout << endl;

	}
	cout << "缺页次数为：" << queye << "   缺页率为：" << (double)queye / adnum * 100 << "%" << endl;

}

//设置某个数据为0
void StorageManegement::setmax(int page[5][2], int x)  
{
	for (int i = 1; i <= yenum; i++)
	{
		page[i][1]++;
	}
	page[x][1] = 0;
}

//找到最久未被使用的数，并将其置为最小
int StorageManegement::findmax(int page[5][2]) 
{
	int max = 1, x;
	for (int i = 1; i <= yenum; i++)
	{
		if (page[i][1] >= page[max][1])
		{
			max = i;
		}

	}
	x = max;
	for (int i = 1; i <= yenum; i++)
	{
		page[i][1]++;
	}
	page[max][1] = 0;
	return x;
}

//最近最久未被使用页面管理算法
void StorageManegement::lrupage()    //最近最久未被使用页面管理算法
{

	printad();  //打印地址
	int i, j, y, x = 1, queye = 0, shan = 0, kong = 3;
	int page[5][2];
	page[1][0] = -1;
	page[2][0] = -1;
	page[3][0] = -1;
	page[4][0] = -1;
	page[1][1] = 3;
	page[2][1] = 2;
	page[3][1] = 1;
	page[4][1] = 0;
	for (i = 1; i <= adnum; i++)
	{
		x = 1;
		cout << "本次地址为：";
		for (j = 1; j <= yenum; j++)
		{

			if (page[j][0] == adzu[i] / yesize)
			{
				setmax(page, j);    //当页表中某个数据被查询过，该数的标注计为0.表示最近刚被使用过
				x = 0;
				break;
			}
		}
		if (x == 1)
		{
			queye++;
			//shan=(shan)%(yenum)+1;
			page[findmax(page)][0] = adzu[i] / yesize;	//从页表中几个数里找出标记最大的那个替换		
		}
		cout << adzu[i] / yesize << " " << " " << " " << " ";
		for (y = 1; y <= yenum; y++)
		{
			if (page[y][0] == -1)
			{
				cout << " " << "  ";
			}
			else
			{
				cout << page[y][0] << "  ";
			}
		}
		cout << endl;

	}
	cout << "缺页次数为：" << queye << endl;
	cout<< "   缺页率为：" << (double)queye / adnum * 100 << "%" << endl;


}

//主函数
int StorageManegement::cunchumain()
{
	

	int x1, i = 1, i1 = 1, j, i2 = 1;
	set0adzu();
	while (i1)
	{
		cout << "*****************************存储管理******************************" << endl;
		cout << "                       页面管理调度算法模拟             " << endl;
		cout << "                        【1】    FIFO算法                 " << endl;
		cout << "                        【2】    LRU算法                  " << endl;
		cout << "                        【0】    返回上一级                     " << endl;
		cout << "*******************************************************************" << endl;
		cout << "请输入选项：";cin >> x1;
		switch (x1)
		{
		case 1:
		{
			system("cls");
			cout << "***************************FIFO算法******************************" << endl;
			cout << "请输入地址的个数（小于100）：" ;cin >> adnum;
			while (adnum>100 || adnum<0)
			{
				cout << "地址个数错误，请输入地址个数（小于100）：";
				cin >> adnum;
			}
			cout << "请输入页面的数量（2~4）：";cin >> yenum;
			while (yenum>4 || yenum<2)
			{
				cout << "页面数量错误，请输入页面的数量（2~4）：";
				cin >> yenum;
			}
			cout << "请输入页面长度（1024~3072）：";
			cin >> yesize;
			while (yesize>3072 || yesize<1024)
			{
				cout << "页面长度错误，请输入页面长度（1024~3072）：";
				cin >> yesize;
			}
			i1 = 1;
			set0adzu();//清空数组
			for (j = 1; j <= adnum; j++)   //从数组第二个开始记录，也是标记从1开始
			{
				cout << "请输入第" << j << "个地址:";
				cin >> adzu[j];
				cout << endl;
			}
			fifopage();
			break;
		}
		case 2:
		{
			system("cls");
			cout << "***************************LRU算法 ******************************" << endl;
			cout << "请输入地址的个数（小于100）：";
			cin >> adnum;
			while (adnum>100 || adnum<0)
			{
				cout << "地址个数错误，请输入地址个数（小于100）：";
				cin >> adnum;
			}
			cout << "请输入页面的数量（2~4）：";
			cin >> yenum;
			while (yenum>4 || yenum<2)
			{
				cout << "页面数量错误，请输入页面的数量（2~4）：";
				cin >> yenum;
			}
			cout << "请输入页面长度（1024~3072）：";
			cin >> yesize;
			while (yesize>3072 || yesize<1024)
			{
				cout << "页面长度错误，请输入页面长度（1024~3072）：";
				cin >> yesize;
			}
			i1 = 1;
			set0adzu();//清空数组
			for (j = 1; j <= adnum; j++)   //从数组第二个开始记录，也是标记从1开始
			{
				cout << "请输入第" << j << "个地址:";
				cin >> adzu[j];
				cout << endl;
			}
			lrupage();
			break;
		}
		case 0:
		{
			system("cls");
			return 0;
			break;
		}

		default:
			cout << "输入选项错误，请稍后重新输入！" << endl;
			Sleep(1000);
			system("cls");
			cunchumain();
			break;
		}
	}
	return x1;
}