#include "stdafx.h"
#include "StorageManegement.h"


//��������0
void StorageManegement::set0adzu()  
{
	int i;
	for (i = 0; i<100; i++)
	{
		adzu[i] = 0;
	}
}

//������ɵ�ַ��
void StorageManegement::suiji()  
{
	int i;
	srand((int)time(NULL));
	for (i = 1; i <= adnum; i++)
	{
		adzu[i] = rand() % 10000;          //Ĭ������10000���ڵĵ�ַ
	}
}

//��ӡ��ַ
void StorageManegement::printad()  //��ӡ��ַ
{
	int i;
	cout << "Ŀǰת��Ϊ�ĵ�ַ�У�";
	for (i = 1; i <= adnum; i++)
	{
		cout << adzu[i] / yesize << "  ";
	}
	cout << endl;
}

//�Ƚ��ȳ�ҳ������㷨
void StorageManegement::fifopage()  //�Ƚ��ȳ�ҳ������㷨
{
	printad();  //��ӡ��ַ
	int i, j, y, x = 1, queye = 0, shan = 0, kong = 3;
	int page[5];
	page[1] = -1;
	page[2] = -1;
	page[3] = -1;
	page[4] = -1;    //��ʼ��ҳ��
	for (i = 1; i <= adnum; i++)
	{
		x = 1;
		cout << "���ε�ַΪ�� ";   //�������ԭ�еĵ�ַ
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
			shan = (shan) % (yenum)+1;    //���������ݴ��������ʱ��shan��Ϊ�����ݵĵ�ַ��¼�ͼ�1����ҳ����Ϊһ��ѭ��
			page[shan] = adzu[i] / yesize;

		}
		cout << adzu[i] / yesize << " " << " " << " " << " ";
		for (y = 1; y <= yenum; y++)
		{

			if (page[y] == -1)
			{
				cout << " " << "  ";   //�������Ϊ-1����ʾΪ��
			}
			else
			{

				cout << page[y] << "  ";
			}
		}
		cout << endl;

	}
	cout << "ȱҳ����Ϊ��" << queye << "   ȱҳ��Ϊ��" << (double)queye / adnum * 100 << "%" << endl;

}

//����ĳ������Ϊ0
void StorageManegement::setmax(int page[5][2], int x)  
{
	for (int i = 1; i <= yenum; i++)
	{
		page[i][1]++;
	}
	page[x][1] = 0;
}

//�ҵ����δ��ʹ�õ�������������Ϊ��С
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

//������δ��ʹ��ҳ������㷨
void StorageManegement::lrupage()    //������δ��ʹ��ҳ������㷨
{

	printad();  //��ӡ��ַ
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
		cout << "���ε�ַΪ��";
		for (j = 1; j <= yenum; j++)
		{

			if (page[j][0] == adzu[i] / yesize)
			{
				setmax(page, j);    //��ҳ����ĳ�����ݱ���ѯ���������ı�ע��Ϊ0.��ʾ����ձ�ʹ�ù�
				x = 0;
				break;
			}
		}
		if (x == 1)
		{
			queye++;
			//shan=(shan)%(yenum)+1;
			page[findmax(page)][0] = adzu[i] / yesize;	//��ҳ���м��������ҳ���������Ǹ��滻		
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
	cout << "ȱҳ����Ϊ��" << queye << endl;
	cout<< "   ȱҳ��Ϊ��" << (double)queye / adnum * 100 << "%" << endl;


}

//������
int StorageManegement::cunchumain()
{
	

	int x1, i = 1, i1 = 1, j, i2 = 1;
	set0adzu();
	while (i1)
	{
		cout << "*****************************�洢����******************************" << endl;
		cout << "                       ҳ���������㷨ģ��             " << endl;
		cout << "                        ��1��    FIFO�㷨                 " << endl;
		cout << "                        ��2��    LRU�㷨                  " << endl;
		cout << "                        ��0��    ������һ��                     " << endl;
		cout << "*******************************************************************" << endl;
		cout << "������ѡ�";cin >> x1;
		switch (x1)
		{
		case 1:
		{
			system("cls");
			cout << "***************************FIFO�㷨******************************" << endl;
			cout << "�������ַ�ĸ�����С��100����" ;cin >> adnum;
			while (adnum>100 || adnum<0)
			{
				cout << "��ַ���������������ַ������С��100����";
				cin >> adnum;
			}
			cout << "������ҳ���������2~4����";cin >> yenum;
			while (yenum>4 || yenum<2)
			{
				cout << "ҳ����������������ҳ���������2~4����";
				cin >> yenum;
			}
			cout << "������ҳ�泤�ȣ�1024~3072����";
			cin >> yesize;
			while (yesize>3072 || yesize<1024)
			{
				cout << "ҳ�泤�ȴ���������ҳ�泤�ȣ�1024~3072����";
				cin >> yesize;
			}
			i1 = 1;
			set0adzu();//�������
			for (j = 1; j <= adnum; j++)   //������ڶ�����ʼ��¼��Ҳ�Ǳ�Ǵ�1��ʼ
			{
				cout << "�������" << j << "����ַ:";
				cin >> adzu[j];
				cout << endl;
			}
			fifopage();
			break;
		}
		case 2:
		{
			system("cls");
			cout << "***************************LRU�㷨 ******************************" << endl;
			cout << "�������ַ�ĸ�����С��100����";
			cin >> adnum;
			while (adnum>100 || adnum<0)
			{
				cout << "��ַ���������������ַ������С��100����";
				cin >> adnum;
			}
			cout << "������ҳ���������2~4����";
			cin >> yenum;
			while (yenum>4 || yenum<2)
			{
				cout << "ҳ����������������ҳ���������2~4����";
				cin >> yenum;
			}
			cout << "������ҳ�泤�ȣ�1024~3072����";
			cin >> yesize;
			while (yesize>3072 || yesize<1024)
			{
				cout << "ҳ�泤�ȴ���������ҳ�泤�ȣ�1024~3072����";
				cin >> yesize;
			}
			i1 = 1;
			set0adzu();//�������
			for (j = 1; j <= adnum; j++)   //������ڶ�����ʼ��¼��Ҳ�Ǳ�Ǵ�1��ʼ
			{
				cout << "�������" << j << "����ַ:";
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
			cout << "����ѡ��������Ժ��������룡" << endl;
			Sleep(1000);
			system("cls");
			cunchumain();
			break;
		}
	}
	return x1;
}