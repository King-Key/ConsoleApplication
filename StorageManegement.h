#pragma once
//�洢����
class StorageManegement
{
	int adnum = 10;    //��ַ��
	int yenum = 3;    //ҳ�����Ŀ
	int yesize = 1024;      //ҳ���С
	int adzu[100];       //��ŵ�ַ�����飬���ڱ������������99����ַ��100�����ݿռ��Ѿ�����


public:
	void set0adzu();  //��������0
	void suiji();  //������ɵ�ַ��
	void printad();//��ӡ��ַ
	void fifopage();  //�Ƚ��ȳ�ҳ������㷨
	void setmax(int page[5][2], int x); //����ĳ������Ϊ0
	int findmax(int page[5][2]); //�ҵ����δ��ʹ�õ�������������Ϊ��С
	void lrupage();    //������δ��ʹ��ҳ������㷨
	int cunchumain();
};

