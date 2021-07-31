#include "DB.h"
using namespace std;
using namespace mysqlpp;


CDB::CDB():m_Conn(true),m_nPort(3306){}
bool CDB::InitConnect(const std::string& strDB, const std::string& strServer, const std::string& strUser, const std::string& strPassword, const int& nPort) {
	
	try {
		/*建立数据库连接*/
		m_strDB = strDB;
		m_strServer = strServer;
		m_strUser = strUser;
		m_strPassword = strPassword;
		m_nPort = nPort;
		if(!m_Conn.set_option(new mysqlpp::SetCharsetNameOption("latin1")))return false;//设置字符编码为uft8
		if(!m_Conn.set_option(new mysqlpp::ReconnectOption(true)))return false;
		if (!m_Conn.connect(m_strDB.c_str(), m_strServer.c_str(), m_strUser.c_str(), m_strPassword.c_str(), m_nPort)) {
			//cout << m_Conn.error() << endl;
			cout << "数据库链接失败" << endl;
			return false;
		}
		Query query = m_Conn.query("set names latin1");
		if (!query)return false;
		if (!query.exec()) 
			cout << "查询失败" << endl;
	}
	catch (const mysqlpp::BadQuery& er) {
		// Handle any query errors
		cerr << "Query error: " << er.what() << endl;
		return false;
	}
	catch (const mysqlpp::BadConversion& er) {
		// Handle bad conversions
		cerr << "Conversion error: " << er.what() << endl <<
			"\tretrieved data size: " << er.retrieved <<
			", actual size: " << er.actual_size << endl;
		return false;
	}
	catch (const mysqlpp::Exception& er) {
		// Catch-all for any other MySQL++ exceptions
		cerr << "Error: " << er.what() << endl;
		return false;
	}
	return true;
}
Query CDB::CreateQuery() {
	try {
		if (!m_Conn) {
				cout << "Connection失效，请重新连接" << endl;
				return nullptr;
		}
	}
	catch (const mysqlpp::BadQuery& er) {
		// Handle any query errors
		cerr << "Query error: " << er.what() << endl;
		return nullptr;
	}
	catch (const mysqlpp::BadConversion& er) {
		// Handle bad conversions
		cerr << "Conversion error: " << er.what() << endl <<
			"\tretrieved data size: " << er.retrieved <<
			", actual size: " << er.actual_size << endl;
		return nullptr;
	}
	catch (const mysqlpp::Exception& er) {
		// Catch-all for any other MySQL++ exceptions
		cerr << "Error: " << er.what() << endl;
		return nullptr;
	}
	return m_Conn.query();
}
bool CDB::SearchAll(mysqlpp::Query& query) {
	
	try {
		/*查询addr_book表内的所有信息*/
		const string strSQL = "select * from addr_book;";
		//cout << "SQL语句为：" << strSQL << endl;
		if (!query) {
			cout << "Query失效，请重新连接" << endl;
			return false;
		}
		query << strSQL;
		//cout << "Query:" << query << endl;
	}
	catch (const mysqlpp::BadQuery& er) {
		// Handle any query errors
		cerr << "Query error: " << er.what() << endl;
		return false;
	}
	catch (const mysqlpp::BadConversion& er) {
		// Handle bad conversions
		cerr << "Conversion error: " << er.what() << endl <<
			"\tretrieved data size: " << er.retrieved <<
			", actual size: " << er.actual_size << endl;
		return false;
	}
	catch (const mysqlpp::Exception& er) {
		// Catch-all for any other MySQL++ exceptions
		cerr << "Error: " << er.what() << endl;
		return false;
	}
	return true;
}
bool CDB::SearchOne(Query& query,const std::string& strColumn, const std::string& strValue) {
	
	try {
		/*根据输入的数据库项和对应的值查询是否存在*/
		if (!query) {
			cout << "Query失效，请重新连接" << endl;
			return false;
		}
		query << "select * from addr_book where %0:column = %1q:value;";
		query.parse();
		query.template_defaults["column"] = strColumn.c_str();
		query.template_defaults["value"] = strValue.c_str();
		//cout << "Query:" << query << endl;
		if (!query)return false;
	}
	catch (const mysqlpp::BadQuery& er) {
		// Handle any query errors
		cerr << "Query error: " << er.what() << endl;
		return false;
	}
	catch (const mysqlpp::BadConversion& er) {
		// Handle bad conversions
		cerr << "Conversion error: " << er.what() << endl <<
			"\tretrieved data size: " << er.retrieved <<
			", actual size: " << er.actual_size << endl;
		return false;
	}
	catch (const mysqlpp::Exception& er) {
		// Catch-all for any other MySQL++ exceptions
		cerr << "Error: " << er.what() << endl;
		return false;
	}
	return true;
}
bool CDB::InsertData(const CUser& newUser) {
	/*插入一条新的值到数据库中，只需要输入账户account的值即可*/
	try {
		Query query = CreateQuery();
		if (!query) {
			cout << "Query失效，请重新连接" << endl;
			return false;
		}
		query << "insert into addr_book(name,tel,address) values(%0q:name, %1q:tel, %2q:addr)";
		query.parse();
		query.template_defaults["name"] = newUser.GetName().c_str();
		query.template_defaults["tel"] = newUser.GetTel().c_str();
		query.template_defaults["addr"] = newUser.GetAddress().c_str();
		//cout << "Query:" << query.str() << endl;
		if (!query)return false;
		if (!query.exec()) {
			//cout << "插入失败" << endl;
			return false;
		}
		//cout << "插入成功" << endl;
	}
	catch (const mysqlpp::BadQuery& er) {
		// Handle any query errors
		cerr << "Query error: " << er.what() << endl;
		return false;
	}
	catch (const mysqlpp::BadConversion& er) {
		// Handle bad conversions
		cerr << "Conversion error: " << er.what() << endl <<
			"\tretrieved data size: " << er.retrieved <<
			", actual size: " << er.actual_size << endl;
		return false;
	}
	catch (const mysqlpp::Exception& er) {
		// Catch-all for any other MySQL++ exceptions
		cerr << "Error: " << er.what() << endl;
		return false;
	}
	return true;
}
bool CDB::InsertSomeData(const std::vector<CUser*>& vecUser) {
	
	try {
		/*插入一条新的值到数据库中，只需要输入账户account的值即可*/
		/*  //逐条插入的话10万条数据需要432s时间
		for (CUser* User : vecUser) {
			if (!InsertData(*User)) {
				return false;
			}
		}
		*/
		MYSQL mysql;
		mysql_init(&mysql);
		mysql_set_character_set(&mysql, "latin1");
		mysql_real_connect(&mysql, m_strServer.c_str(), m_strUser.c_str(), m_strPassword.c_str(), m_strDB.c_str(), m_nPort, NULL, 0);
		mysql_autocommit(&mysql, 0);//关闭自动提交
		int cursor = 1;
		for (CUser* pUser : vecUser) {
			if (!pUser)return false;
			Query query = CreateQuery();
			if (!query) {
				cout << "Query失效，请重新连接" << endl;
				return false;
			}
			query << "insert into addr_book(name,tel,address) values(%0q:name, %1q:tel, %2q:addr)";
			query.parse();
			query.template_defaults["name"] = pUser->GetName().c_str();
			query.template_defaults["tel"] = pUser->GetTel().c_str();
			query.template_defaults["addr"] = pUser->GetAddress().c_str();
			//cout << cursor <<".\t" << query.str() << endl;
			int nSuccess = mysql_query(&mysql, query.str().c_str());
			if (nSuccess != 0) {
				const char* pMysql_err = mysql_error(&mysql);
				printf("%s\n", pMysql_err);
				return false;
			}
			cursor++;
			if (cursor == 50000) {//每50000条记录提交一次
				mysql_commit(&mysql);
				cursor = 0;
				printf("提交事务完毕\n");
			}
		}if (cursor != 0) {//每50000条记录提交一次
			mysql_commit(&mysql);
			printf("提交事务完毕\n");
		}
		mysql_close(&mysql);
	}
	catch (const mysqlpp::BadQuery& er) {
		// Handle any query errors
		cerr << "Query error: " << er.what() << endl;
		return false;
	}
	catch (const mysqlpp::BadConversion& er) {
		// Handle bad conversions
		cerr << "Conversion error: " << er.what() << endl <<
			"\tretrieved data size: " << er.retrieved <<
			", actual size: " << er.actual_size << endl;
		return false;
	}
	catch (const mysqlpp::Exception& er) {
		// Catch-all for any other MySQL++ exceptions
		cerr << "Error: " << er.what() << endl;
		return false;
	}
	return true;
}
