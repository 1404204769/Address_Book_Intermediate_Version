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
	cout << "请输入姓名：" << endl;
	cin >> ca;
	temUser.SetName(ca);
	cout << "请输入电话：" << endl;
	cin >> ca;
	while (!CheckTel(ca)) {
		cout << "请重新输入电话：" << endl;
		cin >> ca;
	}
	temUser.SetTel(ca);
	cout << "请输入地址：" << endl;
	cin >> ca;
	temUser.SetAddress(ca);
	return temUser;
}
void ProductData(int num) {
	double time; //定义运行时间
	static clock_t sstart = clock(); //声明start获取开始时间
	cout << "随机生成" << num << "人的数据" << endl;
	for (int i = 0; i < num; i++) {
		g_UserMgr.GetUser(g_User);
		cout << i + 1 << ".\tname:" << g_User.GetName() << "\tTel:" << g_User.GetTel() << "\tAddress:" << g_User.GetAddress() << endl;
		g_UserMgr.AddUser(g_User);
	}
	static clock_t sfinish = clock();//声明finish获取结束时间
	printf("\n");
	time = (double)(sfinish - sstart) / CLOCKS_PER_SEC;
	printf("RunningTime:\n%f 秒\n", time);//显示
}
int Choice() {
	cout << "请输入要执行的功能" << endl;
	cout << "0.退出程序" << endl;
	cout << "1.显示所有人的姓名" << endl;
	cout << "2.查询指定姓名" << endl;
	cout << "3.输入新的数据" << endl;
	cout << "4.随机产生数据" << endl;
	int nchoice;
	cin >> nchoice;
	switch (nchoice)
	{
	case 1:
		g_UserMgr.ShowName();
		break;
	case 2: {
		cout << "请输入要查询的对象的名字" << endl;
		cin >> g_c;
		g_UserMgr.ShowDetailByName(g_c);
	}break;
	case 3: {
		g_User = Input();
		g_UserMgr.AddUser(g_User);
		//g_CUsermgr.showName();
	}break;
	case 4: {
		cout << "请输入要产生多少条数据" << endl;
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
		cout << "欢迎使用李志诚的通讯录" << endl;
		if (Choice() == 0)
			break;
		system("pause");
	}
	return 0;
}