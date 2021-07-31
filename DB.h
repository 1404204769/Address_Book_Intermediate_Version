#ifndef _DB_H_
#define _DB_H_

#pragma once

#include <mysql++.h>
#include "User.h"

class CDB {
public:
	CDB();
	bool InitConnect(const std::string& strDB, const std::string& strServer, const std::string& strUser, const std::string& strPassword, const int& nPort);/*建立数据库连接*/
	mysqlpp::Query CreateQuery();/*创建一个query查询*/
	bool SearchAll(mysqlpp::Query& query);/*查询addr_book表内的所有信息*/
	bool SearchOne(mysqlpp::Query& query, const std::string& strColumn, const std::string& strValue);/*根据输入的数据库项和对应的值查询是否存在*/
	bool InsertData(const CUser& newUser);/*插入一条新的值到数据库中，只需要输入账户account的值即可*/
	bool InsertSomeData(const std::vector<CUser*>& vecUser);/*插入一条新的值到数据库中，只需要输入账户account的值即可*/
	
private:
	std::string m_strDB, m_strServer, m_strUser, m_strPassword;
	int m_nPort;
	mysqlpp::Connection m_Conn;

};
#endif