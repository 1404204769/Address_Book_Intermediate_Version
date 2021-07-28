#define _CRT_SECURE_NO_WARNINGS
#include "UserMgr.h"
#include "Data.h"
#include <iostream>

CUserMgr::CUserMgr() {
	VecByTel.clear();
	ReadInfoFromFile();
}
CUserMgr::~CUserMgr() {
	SaveInfoToFile();
	VecByTel.clear();
}
void CUserMgr::GetUser(CUser& _input) {
	//用于生成随机数据
	RandomName(_input);
	RandomTel(_input);
	RandomAddress(_input);
	/*cout << "cpname:" << _input.getName() << endl;
	cout << "cpTel:" << _input.getTel() << endl;
	cout << "cpAddress:" << _input.getAddress() << endl;*/
}
bool CUserMgr::AddUser(const CUser& _input) {
	//用于将数据添加到VecByTel数组内
	VecByTel.push_back(_input);
	return true;
}
bool CUserMgr::SaveInfoToFile() {
	//文件写操作
	FILE* fp = fopen(m_filename, "w");
	if (fp == nullptr) {
		cout << "文件（" << m_filename << "）无法打开" << endl;
		return false;
	}
	size_t nveclen = VecByTel.size();
	for (size_t i = 0; i < nveclen; i++) {
		fprintf(fp, "%s\t%s\t%s\n", VecByTel[i].GetName().c_str(), VecByTel[i].GetTel().c_str(), VecByTel[i].GetAddress().c_str());
	}
	fclose(fp);
	return true;
}
bool CUserMgr::ReadInfoFromFile() {
	//文件读操作
	char TemPszAddress[50] = { 0 };//创建临时的数据存储位
	char TemPszName[20] = { 0 };
	char TemPszTel[20] = { 0 };
	FILE* fp = fopen(m_filename, "r");
	if (fp == nullptr) {
		fp = fopen(m_filename, "w+");
		if (fp == nullptr) {
			cout << "文件（" << m_filename << "）无法打开" << endl;
			return false;
		}
	}
	while (fscanf(fp, "%s\t%s\t%s\n", TemPszName, TemPszTel, TemPszAddress) != EOF) {
		CUser TemUser(TemPszName, TemPszTel, TemPszAddress);
		AddUser(TemUser);
		memset(TemPszName, 0, sizeof(TemPszName));
		memset(TemPszTel, 0, sizeof(TemPszTel));
		memset(TemPszAddress, 0, sizeof(TemPszAddress));
	}
	fclose(fp);
	return true;
}
void CUserMgr::ShowName()const {
	if (VecByTel.empty()) {
		cout << "当前无数据" << endl;
		return;
	}
	cout << "通讯录数据如下" << endl;
	//打印输出所有的现存的名字
	for (int i = 0; i < VecByTel.size(); i++) {
		cout << i + 1 << "." << VecByTel[i].GetName() << "\t" << endl;
	}
	cout << "数据输出完毕" << endl;
}
void CUserMgr::ShowDetailByName(const string& _searchName) const {
	//输入用户的名字查询对应的信息
	bool _findByName = false;
	for (auto it : VecByTel) {
		if (it.GetName() == _searchName) {
			cout << "name:" << it.GetName() << endl;
			cout << "Tel:" << it.GetTel() << endl;
			cout << "Address:" << it.GetAddress() << endl;
			_findByName = true;
		}
	}
	if (_findByName) {
		cout << "数据输出完毕" << endl;
	}
	else {
		cout << "未找到此人的信息" << endl;
	}
}