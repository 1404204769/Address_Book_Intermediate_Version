#define _CRT_SECURE_NO_WARNINGS
#include "UserMgr.h"
#include "DB.h"
#include <iostream>
using namespace std;
using namespace mysqlpp;

CUserMgr::CUserMgr() {}
CUserMgr::~CUserMgr() {
	VecFree();
}

bool CUserMgr::CreateUser(CUser& user,CDB& db) {
	/*新建一个CUser，具体数据函数内从命令行获取*/
	string strData="";
	cout << "请输入姓名：" << endl;
	getline(cin, strData);
	user.SetName(strData);
	cout << "请输入电话：" << endl;
	getline(cin, strData);
	while (!CheckTel(strData,db)) {
		cout << "请重新输入电话：" << endl;
		cin >> strData;
	}
	user.SetTel(strData);
	cout << "请输入地址：" << endl;
	getline(cin, strData);
	user.SetAddress(strData);
	return true;
}
bool  CUserMgr::AddUser(CDB& db) {
	/*用于将数据添加到addr_book数据库中*/
	CUser user("","","");
	if (!CreateUser(user, db))return false;
	return db.InsertData(user);
}
bool  CUserMgr::ProductUser(CDB& db,int& nNum) {
	/*用于将数据添加到addr_book数据库中*/
	VecFree();
	const clock_t lStart = clock(); //声明start获取开始时间
	cout << "随机生成" << nNum << "人的数据" << endl;
	for (int i = 0; i < nNum; i++) {

		CUser *user = new CUser("","","");
		if (!user)return false;
		RandUser(db ,*user);
		m_vecUser.push_back(user);
		//cout << i + 1 << ".\tname:" << user->GetName() << "\tTel:" << user->GetTel() << "\tAddress:" << user->GetAddress() << endl;
	}
	if (!db.InsertSomeData(m_vecUser)) {
		return false;
	}
	const clock_t lFinish = clock();//声明finish获取结束时间
	printf("\n");
	double dTime = (double)((lFinish - lStart) / CLOCKS_PER_SEC); //定义运行时间
	printf("RunningTime:\n%f 秒\n", dTime);//显示
	//cout << "RunningTime: "<< time <<" 秒"<< endl;//显示
	return true;
}
void CUserMgr::VecFree() {
	/*释放vector数组内的所有指针数据*/
	vector<CUser*>::iterator It = m_vecUser.begin();
	for (; It != m_vecUser.end(); ++It)
	{
		if (*It != nullptr)
		{
			delete* It;
			*It = nullptr;
		}
	}
	m_vecUser.clear();
	return ;
}
bool CUserMgr::Show(const mysqlpp::Query& query) {
	if (!query) {
		cout << "调用数据库接口返回的查找query无效" << endl;
		return false;
	}
	VecFree();
	UseQueryResult Uqres = ((Query&)query).use();
	if (!Uqres) {
		cout << "调用数据库接口返回的res集合无效" << endl;
		return false;
	}
	while (mysqlpp::Row row = Uqres.fetch_row()) {

		CUser* user=new CUser(string(row["name"]), string(row["tel"]), string(row["address"]));
		if (!user)return false;
		m_vecUser.push_back(user);

	}
	int nNum = 0;
	for (auto it : m_vecUser) {
		//printf("ID:%10s\tAccount:\tCreate_time:\n", it.id, it.account, it.create_time);
		if (!it)return false;
		cout << left << ++nNum <<".\tName:" << it->GetName() << "\t\tTel:" << it->GetTel() << "\t\tAddress:" << it->GetAddress() << endl;
	}
	cout << "一共输出" << m_vecUser.size() << "条数据" << endl;
	return true;
}
bool  CUserMgr::ShowOne(CDB& db) {
	/*根据名字展示数据*/
	string strData= "";
	cout << "请输入要查询的对象的名字" << endl;
	getline(cin, strData);
	//cout << "输入的内容为" << strData <<"!" << endl;
	Query query = db.CreateQuery();
	if (!db.SearchOne(query, "name", strData))return false;
	return Show(query);
}
bool  CUserMgr::ShowAllName(CDB& db) {
	//打印输出所有的现存的名字
	Query query = db.CreateQuery();
	if (!db.SearchAll(query))return false;
	return Show(query);
}
void  CUserMgr::RandUser(CDB& db, CUser& user) {
	/*用于生成随机数据*/
	user.SetAddress(RandAddr());
	user.SetName(RandName());
	string strTel = RandTel();
	bool bTel = CheckTel(strTel,db);
	while (!bTel) {
		//cout<< strTel<<"已存在数据库中" << endl;
		strTel = RandTel();
		bTel = CheckTel(strTel, db);
		//cout<<"新的手机号为："<<strTel << endl;
	}
	user.SetTel(strTel);
	/*
	cout << "cpname:" << user.getName() << endl;
	cout << "cpTel:" << user.getTel() << endl;
	cout << "cpAddress:" << user.getAddress() << endl;
	*/
}  
void  CUserMgr::SetSrand() {
	/*修改随机步长*/
	static ULONG timeindex = 0;
	srand((int)time(0) + timeindex);
	timeindex += 0x3;
	if (timeindex > 0xfffffff)
	{
		timeindex = 0;
	}
}
const int& CUserMgr::CUserMgr::RandNum(const int& nval) {
	/*获取随机数*/
	return (int)(rand() % nval);
}
string CUserMgr::RandTel() {
	/*随机产生电话*/
	SetSrand();
	int nNum = 0;
	char TelLast[10] = "";
	//printf("随机电话头:");
	nNum = RandNum(40);
	string Tel(caTelHead[nNum]);
	//区
	nNum = 0;
	for (int i = 0; i < 8; i++) {
		nNum = nNum * 10 + RandNum(10);
	}
	sprintf_s(TelLast, "%08d", nNum);//保证一定有八位数,不足前面补0
	Tel.append(TelLast);
	return Tel;
}
string CUserMgr::RandName() {
	/*随机产生名字*/
	SetSrand();
	int nNum = 0;
	string name("");
	//60%概率 是男性名字
	if (RandNum(100) <= 60) {
		//printf("百家姓+随机男名:");
		//姓
		nNum = RandNum(50);
		name.append(caLastName[nNum]);
		//名
		nNum = RandNum(50);
		name.append(caManName[nNum]);
	}
	else {
		//40%概率 是女性名字
		//printf("百家姓+随机女名:");
		//姓
		nNum = RandNum(50);
		name.append(caLastName[nNum]);
		//名
		nNum = RandNum(50);
		name.append(caWomanName[nNum]);
	}
	return name;
}
string CUserMgr::RandAddr() {
	/*随机产生地址*/
	SetSrand();
	int nNum = 0;
	//省
	nNum = RandNum(34);
	string Address(caProvincial_Name[nNum]);
	//区
	nNum = RandNum(26);
	Address.append(caDistrict_Name[nNum]);
	return Address;
}
bool  CUserMgr::CheckTel(const std::string& strTel, CDB& db) {
	/*用于检查手机号是否规范，并且判断是否存在重复手机号*/
	if (strTel.length() != 11) {
		cout << "手机号位数不正确("<< strTel <<")，请重新输入" << endl;
		return false;
	}
	else {
		for (char c : strTel) {
			if (c <= '9' && c >= '0')continue;
			else {
				cout << "手机号内存在非数字，请重新输入" << endl;
				return false;
			}
		}
	}
	//mysqlpp::Query query = db.CreateQuery();
	//if (!db.SearchOne(query, "tel", strTel)) {
	//	cout << "调用数据库接口返回的查找query无效" << endl;
	//	exit(0);
	//}
	//mysqlpp::StoreQueryResult res = query.store();
	//if (!res.empty()) {
	//	//cout << "调用数据库接口返回的查找res集合不为空，说明该手机号已存在" << endl;
	//	cout << "该手机号已存在!!" << endl;
	//	return false;
	//}
	return true;
}
