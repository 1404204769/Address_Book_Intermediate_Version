#include "DB.h"
#include "test.h"
#include <iostream>
#include <string>
using namespace mysqlpp;
using namespace std;
int main() {

	CDB db("test","localhost","root","root",3306);
	mysqlpp::Connection con(false);//������mysql���Ӷ���
	db.getConnect(con);
	int nchoice = 1;
	string strAccount, strDelAccount, strNewAccount;
	while (nchoice) {
		system("cls");
		cout << "��ѡ������Ҫ�Ĺ���" << endl;
		cout << "0.�˳�" << endl;
		cout << "1.�½��˻�" << endl;
		cout << "2.��ѯ����" << endl;
		cout << "3.ɾ���û�" << endl;
		cout << "4.�޸��˻�" << endl;
		cout << "5.�����˻�" << endl;
		cin >> nchoice;
		getchar();
		switch (nchoice) {
		case 0:
			return  0; break;
		case 1: {
			cout << "������Ҫ�½����˺���" << endl;
			getline(cin, strAccount);
			db.InsertAccount(con, strAccount);
		}break;
		case 2: {
			db.SearchInTest(con);
		}break;
		case 3: {
			cout << "������Ҫɾ�����˺���" << endl;
			getline(cin, strDelAccount);
			db.DeleteByAccount(con, strDelAccount);
		}break;
		case 4: {
			cout << "������Ҫ�޸ĵ��˺���" << endl;
			getline(cin, strAccount);
			cout << "�������޸ĺ���˺���" << endl;
			getline(cin, strNewAccount);
			db.UpdateByAccount(con, strNewAccount, strAccount);
		}break;
		case 5: {
			cout << "������Ҫ���ҵ��˺���" << endl;
			getline(cin, strAccount);
			if (!db.SearchByColumnData(con, "account", strAccount)) {
				cout << "���޴���" << endl;
			}
		}break;
		default: {
			cout << "����ѡ��ʧ�ܣ�������ѡ��" << endl;
		}break;
		}
		system("pause");
	}
	return 0;
}
