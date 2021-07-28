#include "DB.h"
using namespace std;
using namespace mysqlpp;
sql_create_3(d_test, 1, 3,
	mysqlpp::sql_bigint, id,
	mysqlpp::sql_varchar, account,
	mysqlpp::sql_timestamp, create_time
);
void CDB::getConnect(mysqlpp::Connection& con) {
	con.set_option(new mysqlpp::SetCharsetNameOption("gbk"));//设置字符编码为uft8
	if (!con.connect(m_db.c_str(), m_Server.c_str(), m_User.c_str(), m_Password.c_str(), m_Port)) {
		cout << "数据库链接失败" << endl;
	}
}
bool CDB::StrReplase(string& resource_str, const string& str_sub, const string& str_new)
{
	string::size_type pos = 0;
	string::size_type a = str_sub.size();
	string::size_type b = str_new.size();
	while ((pos = resource_str.find(str_sub, pos)) != string::npos)
	{
		resource_str.replace(pos, a, str_new);
		pos += b;
	}
	return true;
}
string CDB::SQL_inject(const string& resource_str) {
	//cout << "替换前" << resource_str << endl;
	string _resource_str(resource_str);
	StrReplase(_resource_str, "'", "\\'");
	StrReplase(_resource_str, "\"", "\\\"");
	//cout << "替换后" << resource_str << endl;
	return _resource_str;
}
bool CDB::SearchInTest(Connection& con) {
	const string strSQL = "select * from d_test;";
	//cout << "SQL语句为：" << strSQL << endl;
	Query query = con.query(strSQL);
	if (!query)return false;
	vector<d_test>vecarr;
	query.storein(vecarr);
	for (auto it : vecarr) {
		//printf("ID:%10s\tAccount:\tCreate_time:\n", it.id, it.account, it.create_time);
		cout << left << "ID:" << it.id << "\t\tAccount:" << it.account << "\t\t\tCreate_time:" << it.create_time << endl;
	}
	cout << "一共输出" << vecarr.size() << "条数据" << endl;
	return true;
}
bool CDB::SearchByColumnData(Connection& con, const string& strColumnName, const string& strAccount) {
	const string strSQL = "select * from d_test where " + SQL_inject(strColumnName) + "='" + SQL_inject(strAccount) + "';";
	cout << "SQL语句为：" << strSQL << endl;
	Query query = con.query(strSQL);
	if (!query)return false;
	vector<d_test>vecarr;
	query.storein(vecarr);
	mysqlpp::StoreQueryResult
	if (vecarr.size() == 0) return false;
	for (auto it : vecarr) {
		cout << "ID:" << it.id << "\t\tAccount:" << it.account << "\t\t\tCreate_time:" << it.create_time << endl;
	}
	return true;
}
bool CDB::InsertAccount(Connection& con, const string& strAccount) {
	d_test row(0, SQL_inject(strAccount), NOW());
	Query query = con.query();
	if (!query)return false;
	query.insert(row);
	if (!query.exec()) {
		cout << "插入失败" << endl;
		return false;
	}
	cout << "插入成功" << endl;
	return true;
}
bool CDB::Update(Connection& con, const string& strTable, const string& strColumnName, const string& strNewData, const string& strOldData) {
	if (!SearchByColumnData(con, strColumnName, strOldData)) {
		cout << "该数据库中没有此数据" << endl;
		return false;
	}
	const string  strSQL = "update " + strTable + " set " + strColumnName + "='" + strNewData + "' where " + strColumnName + "='" + strOldData + "';";
	//cout << "SQL语句为：" << strSQL << endl;
	Query query = con.query(strSQL);
	if (!query)return false;
	if (!query.exec()) {
		cout << "更新失败" << endl;
		return false;
	}
	cout << "更新成功" << endl;
	if (!SearchByColumnData(con, strColumnName, strNewData)) {
		cout << "发生错误，该数据库中没有查到更新后的数据" << endl;
		return false;
	}
	return true;
}
bool CDB::UpdateByAccount(Connection& con, const string& strNewData, const string& strOldData) {
	return Update(con, "d_test", "account", SQL_inject(strNewData), SQL_inject(strOldData));
}

bool CDB::Delete(Connection& con, const string& strTable, const string& strColumnName, const string& strDelData) {
	if (!SearchByColumnData(con, strColumnName, strDelData)) {
		cout << "该数据库中没有此数据" << endl;
		return false;
	}
	const string strSQL = "delete from " + strTable + " where " + strColumnName + "= '" + strDelData + "';";
	cout << "SQL语句为：" << strSQL << endl;
	Query query = con.query(strSQL);
	if (!query)return false;
	if (!query.exec()) {
		cout << "删除失败" << endl;
		return false;
	}
	cout << "删除成功" << endl;
	return true;
}
bool CDB::DeleteByAccount(Connection& con, const string& strDelAccount) {
	return Delete(con, "d_test", "Account", SQL_inject(strDelAccount));
}