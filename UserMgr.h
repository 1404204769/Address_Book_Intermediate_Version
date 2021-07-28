#pragma once
#ifndef _CUSERMGR_H_
#define _CUSERMGR_H_
#include<vector>
#include "User.h"
using namespace std;
class CUserMgr {
public://�ڲ����߼�����
	CUserMgr();
	~CUserMgr();
	void GetUser(CUser& _input);//���������������
	bool AddUser(const CUser& _input);//���ڽ�������ӵ�VecByTel������
	bool SaveInfoToFile();//�ļ�д����
	bool ReadInfoFromFile();//�ļ�������
	void ShowName()const;//��ӡ������е��ִ������
	void ShowDetailByName(const string& _searchName)const;//�����û������ֲ�ѯ��Ӧ����Ϣ
private:
	const char* const m_filename = "UserDatabase.txt";//���ڱ������ݵ��ļ��������Ը���
	vector<CUser>VecByTel;//ʹ���ֻ�����Ϊ��������Ϊ���ֿ���һ�������ֻ��Ų�����һ��
};
#endif // !_CUSERMGR_H_

