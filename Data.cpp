#include "data.h"
#include "User.h"
#include<ctime>
#include<iostream>
#include <string>
using namespace std;
bool CheckTel(const string& _inputTel) {
	//���ڼ���ֻ����Ƿ�淶�������ж��Ƿ�����ظ��ֻ���
	if (_inputTel.length() != 11) {
		cout << "�ֻ���λ������ȷ������������" << endl;
		return false;
	}
	else {
		for (char c : _inputTel) {
			if (c <= '9' && c >= '0')continue;
			else {
				cout << "�ֻ����ڴ��ڷ����֣�����������" << endl;
				return false;
			}
		}
	}
	return true;
}
//�޸��������
void SetSrand() {
	static ULONG timeindex = 0;
	srand((int)time(0) + timeindex);
	timeindex += 0x3;
	if (timeindex > 0xfffffff)
	{
		timeindex = 0;
	}
}
//��ȡ�����
int GetRand(const int& rval) {
	return (int)(rand() % rval);
}
void RandomName(CUser& _input) {
	SetSrand();
	int cnt = 0;
	string name = "";
	//srand((unsigned)time(NULL));
	//60%���� ����������
	if (GetRand(100) <= 60) {
		//printf("�ټ���+�������:");
		//��
		cnt = GetRand(50);
		name.append(caLastName[cnt]);
		//��
		cnt = GetRand(50);
		name.append(caManName[cnt]);
	}
	else {
		//40%���� ��Ů������
		//printf("�ټ���+���Ů��:");
		//��
		cnt = GetRand(50);
		name.append(caLastName[cnt]);
		//��
		cnt = GetRand(50);
		name.append(caWomanName[cnt]);
	}
	//std::cout << name << std::endl;
	_input.SetName(name);
}
void RandomTel(CUser& _input) {
	SetSrand();
	int cnt = 0;
	char TelLast[10] = "";
	//srand((unsigned)time(NULL));
	//printf("����绰ͷ:");
	cnt = GetRand(40);
	string Tel(caTelHead[cnt]);
	//��
	cnt = GetRand(9999999) + 10000000;//��֤һ���а�λ��
	sprintf_s(TelLast, "%d", cnt);
	Tel.append(TelLast);
	//std::cout << Tel << std::endl;
	_input.SetTel(Tel);
}
void RandomAddress(CUser& _input) {
	SetSrand();
	int cnt = 0;
	//srand((unsigned)time(NULL));
	//printf("���ʡ����:");
	//ʡ
	cnt = GetRand(34);
	string Address(caProvincial_Name[cnt]);
	//��
	cnt = GetRand(26);
	Address.append(caDistrict_Name[cnt]);
	//std::cout << Address << std::endl;
	_input.SetAddress(Address);
}