#define _CRT_SECURE_NO_WARNINGS
#include "UserMgr.h"
#include "DB.h"
#include<iostream>
using namespace std;
CUserMgr g_UserMgr;
CUser g_User;
CDB g_DB;
int Choice() {
	cout << "请输入要执行的功能" << endl;
	cout << "0.退出程序" << endl;
	cout << "1.显示所有人的姓名" << endl;
	cout << "2.查询指定姓名" << endl;
	cout << "3.输入新的数据" << endl;
	cout << "4.随机产生数据" << endl;
	int nchoice;
	cin >> nchoice;
	getchar();
	switch (nchoice)
	{
	case 1:
		if (!g_UserMgr.ShowAllName(g_DB)) {
			cout << "查询错误，系统出错" << endl;
		}cout << "查询完毕" << endl;
		
		break;
	case 2: {
		if (!g_UserMgr.ShowOne(g_DB)) {
			cout << "查询错误，系统出错" << endl;
		}else 
			cout << "查询完毕" << endl;
	}break;
	case 3: {
		if (!g_UserMgr.AddUser(g_DB)) {
			cout << "用户插入失败" << endl;
		}else 
			cout << "用户插入成功" << endl;
		//g_CUsermgr.showName();
	}break;
	case 4: {
		cout << "请输入要产生多少条数据" << endl;
		int ninput;
		cin >> ninput;
		if (!g_UserMgr.ProductUser(g_DB, ninput)) {
			cout << "插入失败，终止批量产生数据" << endl;
		}else 
			cout << "插入成功，批量产生数据已结束" << endl;
	}break;
	default:
		return 0;
		break;
	}
	return nchoice;
}
int main() {
	g_DB.InitConnect("test", "localhost", "root", "root", 3306);
	while (1) {
		system("cls");
		cout << "欢迎使用李志诚的通讯录" << endl;
		if (Choice() == 0)
			break;
		system("pause");
	}
	return 0;
}