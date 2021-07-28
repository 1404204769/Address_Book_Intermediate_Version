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
	//���������������
	RandomName(_input);
	RandomTel(_input);
	RandomAddress(_input);
	/*cout << "cpname:" << _input.getName() << endl;
	cout << "cpTel:" << _input.getTel() << endl;
	cout << "cpAddress:" << _input.getAddress() << endl;*/
}
bool CUserMgr::AddUser(const CUser& _input) {
	//���ڽ�������ӵ�VecByTel������
	VecByTel.push_back(_input);
	return true;
}
bool CUserMgr::SaveInfoToFile() {
	//�ļ�д����
	FILE* fp = fopen(m_filename, "w");
	if (fp == nullptr) {
		cout << "�ļ���" << m_filename << "���޷���" << endl;
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
	//�ļ�������
	char TemPszAddress[50] = { 0 };//������ʱ�����ݴ洢λ
	char TemPszName[20] = { 0 };
	char TemPszTel[20] = { 0 };
	FILE* fp = fopen(m_filename, "r");
	if (fp == nullptr) {
		fp = fopen(m_filename, "w+");
		if (fp == nullptr) {
			cout << "�ļ���" << m_filename << "���޷���" << endl;
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
		cout << "��ǰ������" << endl;
		return;
	}
	cout << "ͨѶ¼��������" << endl;
	//��ӡ������е��ִ������
	for (int i = 0; i < VecByTel.size(); i++) {
		cout << i + 1 << "." << VecByTel[i].GetName() << "\t" << endl;
	}
	cout << "����������" << endl;
}
void CUserMgr::ShowDetailByName(const string& _searchName) const {
	//�����û������ֲ�ѯ��Ӧ����Ϣ
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
		cout << "����������" << endl;
	}
	else {
		cout << "δ�ҵ����˵���Ϣ" << endl;
	}
}