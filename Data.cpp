#include "data.h"
#include "User.h"
#include<ctime>
#include<iostream>
#include <string>
using namespace std;
bool CheckTel(const string& _inputTel) {
	//用于检查手机号是否规范，并且判断是否存在重复手机号
	if (_inputTel.length() != 11) {
		cout << "手机号位数不正确，请重新输入" << endl;
		return false;
	}
	else {
		for (char c : _inputTel) {
			if (c <= '9' && c >= '0')continue;
			else {
				cout << "手机号内存在非数字，请重新输入" << endl;
				return false;
			}
		}
	}
	return true;
}
//修改随机步长
void SetSrand() {
	static ULONG timeindex = 0;
	srand((int)time(0) + timeindex);
	timeindex += 0x3;
	if (timeindex > 0xfffffff)
	{
		timeindex = 0;
	}
}
//获取随机数
int GetRand(const int& rval) {
	return (int)(rand() % rval);
}
void RandomName(CUser& _input) {
	SetSrand();
	int cnt = 0;
	string name = "";
	//srand((unsigned)time(NULL));
	//60%概率 是男性名字
	if (GetRand(100) <= 60) {
		//printf("百家姓+随机男名:");
		//姓
		cnt = GetRand(50);
		name.append(caLastName[cnt]);
		//名
		cnt = GetRand(50);
		name.append(caManName[cnt]);
	}
	else {
		//40%概率 是女性名字
		//printf("百家姓+随机女名:");
		//姓
		cnt = GetRand(50);
		name.append(caLastName[cnt]);
		//名
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
	//printf("随机电话头:");
	cnt = GetRand(40);
	string Tel(caTelHead[cnt]);
	//区
	cnt = GetRand(9999999) + 10000000;//保证一定有八位数
	sprintf_s(TelLast, "%d", cnt);
	Tel.append(TelLast);
	//std::cout << Tel << std::endl;
	_input.SetTel(Tel);
}
void RandomAddress(CUser& _input) {
	SetSrand();
	int cnt = 0;
	//srand((unsigned)time(NULL));
	//printf("随机省份名:");
	//省
	cnt = GetRand(34);
	string Address(caProvincial_Name[cnt]);
	//区
	cnt = GetRand(26);
	Address.append(caDistrict_Name[cnt]);
	//std::cout << Address << std::endl;
	_input.SetAddress(Address);
}