#pragma once
#ifndef _CUSERMGR_H_
#define _CUSERMGR_H_
#include<vector>
#include "User.h"
using namespace std;
class CUserMgr {
public://内部的逻辑函数
	CUserMgr();
	~CUserMgr();
	void GetUser(CUser& _input);//用于生成随机数据
	bool AddUser(const CUser& _input);//用于将数据添加到VecByTel数组内
	bool SaveInfoToFile();//文件写操作
	bool ReadInfoFromFile();//文件读操作
	void ShowName()const;//打印输出所有的现存的名字
	void ShowDetailByName(const string& _searchName)const;//输入用户的名字查询对应的信息
private:
	const char* const m_filename = "UserDatabase.txt";//用于保存数据的文件，不可以更改
	vector<CUser>VecByTel;//使用手机号作为索引，因为名字可能一样但是手机号不可能一样
};
#endif // !_CUSERMGR_H_

