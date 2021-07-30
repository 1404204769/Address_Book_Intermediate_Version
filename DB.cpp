#include "DB.h"
using namespace std;
using namespace mysqlpp;


CDB::CDB():m_Conn(true),m_nPort(3306){}
bool CDB::InitConnect(std::string _db, std::string  _Server, std::string _User, std::string _Password, int _Port) {
	/*建立数据库连接*/
	m_strDB = _db;
	m_strServer = _Server;
	m_strUser = _User;
	m_strPassword = _Password;
	m_nPort = _Port;
	m_Conn.set_option(new mysqlpp::SetCharsetNameOption("latin1"));//设置字符编码为uft8
	m_Conn.set_option(new mysqlpp::ReconnectOption(true));
	
	m_Conn.connect(m_strDB.c_str(), m_strServer.c_str(), m_strUser.c_str(), m_strPassword.c_str(), m_nPort);
	
	
	cout<<m_Conn.error()<<endl;
	if (!m_Conn.connected()) {
		cout << "数据库链接失败" << endl;
		return false;
	}
	Query query = m_Conn.query("set names latin1");
	if (!query.exec()) {
		cout << "set 失败" << endl;
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
	/*查询addr_book表内的所有信息*/
	const string strSQL = "select * from addr_book;";
	//cout << "SQL语句为：" << strSQL << endl;
	if (!query) {
		cout << "Query失效，请重新连接" << endl;
		return false;
	}
	query << strSQL;
	//cout << "Query:" << query << endl;
	return true;
}
bool CDB::SearchOne(Query& query,const std::string& strColumn, const std::string& strValue) {
	/*根据输入的数据库项和对应的值查询是否存在*/
	if (!query) {
		cout << "Query失效，请重新连接" << endl;
		return false;
	}
	query  << "select * from addr_book where %0:column = %1q:value;";
	query.parse();
	query.template_defaults["column"] = strColumn.c_str();
	query.template_defaults["value"] = strValue.c_str();
	//cout << "Query:" << query << endl;
	if (!query)return false;
	return true;

}
bool CDB::InsertData(const CUser& newUser) {
	/*插入一条新的值到数据库中，只需要输入账户account的值即可*/
	Query query = CreateQuery();
	if (!query) {
		cout << "Query失效，请重新连接" << endl;
		return false;
	}
	query << "insert into addr_book values(%0q:name, %1q:tel, %2q:addr)";
	query.parse();
	query.template_defaults["name"] = newUser.GetName().c_str();
	query.template_defaults["tel"] = newUser.GetTel().c_str();
	query.template_defaults["addr"] = newUser.GetAddress().c_str();
	//cout << "Query:" << query << endl;
	if (!query)return false;
	if (!query.exec()) {
		//cout << "插入失败" << endl;
		return false;
	}
	//cout << "插入成功" << endl;
	return true;
	
}
bool CDB::InsertSomeData(const std::vector<CUser*>& vecUser) {
	/*插入一条新的值到数据库中，只需要输入账户account的值即可*/
	for (CUser *User : vecUser) {
		if (!InsertData(*User)) {
			return false;
		}
	}
	return true;
}
