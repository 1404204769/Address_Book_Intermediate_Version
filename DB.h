#pragma once
#ifndef _DB_H_
#define _DB_H_

#pragma once

#include <mysql++.h>
#include <ssqls.h>
#include <null.h>
#include <string>
class CDB {
public:
	CDB(std::string _db, std::string  _Server, std::string _User, std::string _Password, int _Port):m_db(_db),m_Server(_Server),m_User(_User),m_Password(_Password),m_Port(_Port){}
	void getConnect(mysqlpp::Connection& con);
	std::string SQL_inject(const std::string& resource_str);
	bool StrReplase(std::string& resource_str, const std::string& str_sub, const std::string& str_new);
	bool SearchInTest(mysqlpp::Connection& con);/*��ѯd_test���ڵ�������Ϣ*/
	bool SearchByColumnData(mysqlpp::Connection& con, const std::string& strColumnName, const std::string& strAccount);/*������������ݿ���Ͷ�Ӧ��ֵ��ѯ�Ƿ����*/
	bool InsertAccount(mysqlpp::Connection& con, const std::string& strAccount);/*����һ���µ�ֵ�����ݿ��У�ֻ��Ҫ�����˻�account��ֵ����*/
	bool Update(mysqlpp::Connection& con, const std::string& strTable, const std::string& strColumnName, const std::string& strNewData, const std::string& strOldData);/*�������ݿ��е�ֵ���������ݿ��Ҫ�޸ĵľ�ֵ����ֵ*/
	bool UpdateByAccount(mysqlpp::Connection& con, const std::string& strNewData, const std::string& strOldData);/*�����˻����ƣ��������˻�������˻���*/
	bool Delete(mysqlpp::Connection& con, const std::string& strTable, const std::string& strColumnName, const std::string& strDelData);/*�������ݿ����Լ���Ӧ��ֵɾ�����ݿ�ֵ*/
	bool DeleteByAccount(mysqlpp::Connection& con, const std::string& strDelAccount);/*ɾ���˻���Ϣ�������˻�������*/
private:
	std::string m_db, m_Server, m_User, m_Password;
	int m_Port;

};
#endif