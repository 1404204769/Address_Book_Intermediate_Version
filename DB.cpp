#include "DB.h"
using namespace std;
using namespace mysqlpp;


CDB::CDB():m_Conn(true),m_nPort(3306){}
bool CDB::InitConnect(std::string _db, std::string  _Server, std::string _User, std::string _Password, int _Port) {
	
	try {
		/*建立数据库连接*/
		m_strDB = _db;
		m_strServer = _Server;
		m_strUser = _User;
		m_strPassword = _Password;
		m_nPort = _Port;
		m_Conn.set_option(new mysqlpp::SetCharsetNameOption("latin1"));//设置字符编码为uft8
		m_Conn.set_option(new mysqlpp::ReconnectOption(true));

		m_Conn.connect(m_strDB.c_str(), m_strServer.c_str(), m_strUser.c_str(), m_strPassword.c_str(), m_nPort);


		cout << m_Conn.error() << endl;
		if (!m_Conn.connected()) {
			cout << "数据库链接失败" << endl;
			return false;
		}
		Query query = m_Conn.query("set names latin1");
		if (!query.exec()) {
			cout << "set 失败" << endl;
		}
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
//bool CDB::RefreshConnect() {
//	/*重新建立数据库连接*/
//	m_Conn.disconnect();
//	m_Conn.set_option(new mysqlpp::SetCharsetNameOption("latin1"));//设置字符编码为uft8
//	m_Conn.set_option(new mysqlpp::ReconnectOption(true));
//	m_Conn.connect(m_strDB.c_str(), m_strServer.c_str(), m_strUser.c_str(), m_strPassword.c_str(), m_nPort);
//	cout << m_Conn.error() << endl;
//	if (!m_Conn.connected()) {
//		cout << "数据库链接失败" << endl;
//		return false;
//	}
//	Query query = m_Conn.query("set names latin1");
//	if (!query.exec()) {
//		cout << "query查询 失败" << endl;
//	}
//	return true;
//}
//std::string CDB::SQL_inject(const std::string& resource_str) {
//	/*防止SQL注入，检查字符串中有无单引号双引号*/
//	//cout << "替换前" << resource_str << endl;
//	string _resource_str(resource_str);
//	StrReplase(_resource_str, "'", "\\'");
//	StrReplase(_resource_str, "\"", "\\\"");
//	//cout << "替换后" << resource_str << endl;
//	return _resource_str;
//}
//bool CDB::StrReplase(std::string& resource_str, const std::string& str_sub, const std::string& str_new) {
//	/*字符串替换函数*/
//	string::size_type pos = 0;
//	string::size_type strLA = str_sub.size();
//	string::size_type strLB = str_new.size();
//	while ((pos = resource_str.find(str_sub, pos)) != string::npos)
//	{
//		resource_str.replace(pos, strLA, str_new);
//		pos += strLB;
//	}
//	return true;
//}
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
		if (!mysql_real_connect(&mysql, m_strServer.c_str(), m_strUser.c_str(), m_strPassword.c_str(), m_strDB.c_str(), m_nPort, NULL, 0))
		{
			printf("MySQL数据库连接失败。\n");
			return false;
		}
		mysql_autocommit(&mysql, 0);//关闭自动提交
		int cursor = 1;
		for (CUser* User : vecUser) {
			Query query = CreateQuery();
			if (!query) {
				cout << "Query失效，请重新连接" << endl;
				return false;
			}
			query << "insert into addr_book(name,tel,address) values(%0q:name, %1q:tel, %2q:addr)";
			query.parse();
			query.template_defaults["name"] = User->GetName().c_str();
			query.template_defaults["tel"] = User->GetTel().c_str();
			query.template_defaults["addr"] = User->GetAddress().c_str();
			//cout << cursor <<".\t" << query.str() << endl;
			int nSuccess = mysql_query(&mysql, query.str().c_str());
			if (nSuccess != 0) {
				const char* mysql_err = mysql_error(&mysql);
				printf("%s\n", mysql_err);
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
