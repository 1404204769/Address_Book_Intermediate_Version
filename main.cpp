#define _CRT_SECURE_NO_WARNINGS
#include "UserMgr.h"
#include "Data.h"
#include "DB.h"
#include<iostream>
using namespace std;
CUserMgr g_UserMgr;
CUser g_User;
char g_c[50];
CUser Input() {
	char ca[50];
	CUser temUser;
	cout << "������������" << endl;
	cin >> ca;
	temUser.SetName(ca);
	cout << "������绰��" << endl;
	cin >> ca;
	while (!CheckTel(ca)) {
		cout << "����������绰��" << endl;
		cin >> ca;
	}
	temUser.SetTel(ca);
	cout << "�������ַ��" << endl;
	cin >> ca;
	temUser.SetAddress(ca);
	return temUser;
}
void ProductData(int num) {
	double time; //��������ʱ��
	static clock_t sstart = clock(); //����start��ȡ��ʼʱ��
	cout << "�������" << num << "�˵�����" << endl;
	for (int i = 0; i < num; i++) {
		g_UserMgr.GetUser(g_User);
		cout << i + 1 << ".\tname:" << g_User.GetName() << "\tTel:" << g_User.GetTel() << "\tAddress:" << g_User.GetAddress() << endl;
		g_UserMgr.AddUser(g_User);
	}
	static clock_t sfinish = clock();//����finish��ȡ����ʱ��
	printf("\n");
	time = (double)(sfinish - sstart) / CLOCKS_PER_SEC;
	printf("RunningTime:\n%f ��\n", time);//��ʾ
}
int Choice() {
	cout << "������Ҫִ�еĹ���" << endl;
	cout << "0.�˳�����" << endl;
	cout << "1.��ʾ�����˵�����" << endl;
	cout << "2.��ѯָ������" << endl;
	cout << "3.�����µ�����" << endl;
	cout << "4.�����������" << endl;
	int nchoice;
	cin >> nchoice;
	switch (nchoice)
	{
	case 1:
		g_UserMgr.ShowName();
		break;
	case 2: {
		cout << "������Ҫ��ѯ�Ķ��������" << endl;
		cin >> g_c;
		g_UserMgr.ShowDetailByName(g_c);
	}break;
	case 3: {
		g_User = Input();
		g_UserMgr.AddUser(g_User);
		//g_CUsermgr.showName();
	}break;
	case 4: {
		cout << "������Ҫ��������������" << endl;
		int ninput;
		cin >> ninput;
		ProductData(ninput);
	}break;
	default:
		return 0;
		break;
	}
	return nchoice;
}
int test() {
	while (1) {
		system("cls");
		cout << "��ӭʹ����־�ϵ�ͨѶ¼" << endl;
		if (Choice() == 0)
			break;
		system("pause");
	}
	return 0;
}