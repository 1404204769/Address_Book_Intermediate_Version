#ifndef _DB_H_
#define _DB_H_

#pragma once

#include <mysql++.h>
#include "User.h"

class CDB {
public:
	CDB();
	bool InitConnect(std::string _db, std::string  _Server, std::string _User, std::string _Password, int _Port);/*建立数据库连接*/
	bool RefreshConnect();/*重新连接Connection*/
	mysqlpp::Query CreateQuery();/*创建一个query查询*/
	std::string SQL_inject(const std::string& resource_str);/*防止SQL注入，检查字符串中有无单引号双引号*/
	bool StrReplase(std::string& resource_str, const std::string& str_sub, const std::string& str_new);/*字符串替换函数*/
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