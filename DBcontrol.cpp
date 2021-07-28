#include "DB.h"
#include "test.h"
#include <iostream>
#include <string>
using namespace mysqlpp;
using namespace std;
int main() {

	CDB db("test","localhost","root","root",3306);
	mysqlpp::Connection con(false);//定义了mysql连接对象；
	db.getConnect(con);
	int nchoice = 1;
	string strAccount, strDelAccount, strNewAccount;
	while (nchoice) {
		system("cls");
		cout << "请选择你想要的功能" << endl;
		cout << "0.退出" << endl;
		cout << "1.新建账户" << endl;
		cout << "2.查询所有" << endl;
		cout << "3.删除用户" << endl;
		cout << "4.修改账户" << endl;
		cout << "5.查找账户" << endl;
		cin >> nchoice;
		getchar();
		switch (nchoice) {
		case 0:
			return  0; break;
		case 1: {
			cout << "请输入要新建的账号名" << endl;
			getline(cin, strAccount);
			db.InsertAccount(con, strAccount);
		}break;
		case 2: {
			db.SearchInTest(con);
		}break;
		case 3: {
			cout << "请输入要删除的账号名" << endl;
			getline(cin, strDelAccount);
			db.DeleteByAccount(con, strDelAccount);
		}break;
		case 4: {
			cout << "请输入要修改的账号名" << endl;
			getline(cin, strAccount);
			cout << "请输入修改后的账号名" << endl;
			getline(cin, strNewAccount);
			db.UpdateByAccount(con, strNewAccount, strAccount);
		}break;
		case 5: {
			cout << "请输入要查找的账号名" << endl;
			getline(cin, strAccount);
			if (!db.SearchByColumnData(con, "account", strAccount)) {
				cout << "查无此人" << endl;
			}
		}break;
		default: {
			cout << "功能选择失败，请重新选择" << endl;
		}break;
		}
		system("pause");
	}
	return 0;
}
