#define _CRT_SECURE_NO_WARNINGS
#include "UserMgr.h"
#include "DB.h"
#include <iostream>
using namespace std;
using namespace mysqlpp;

CUserMgr::CUserMgr() {}
CUserMgr::~CUserMgr() {}

bool CUserMgr::CreateUser(CUser& newUser,CDB& TDB) {
	/*新建一个CUser，具体数据函数内从命令行获取*/
	char pszTData[50]="";
	cout << "请输入姓名：" << endl;
	cin >> pszTData;
	newUser.SetName(pszTData);
	cout << "请输入电话：" << endl;
	cin >> pszTData;
	while (!CheckTel(pszTData,TDB)) {
		cout << "请重新输入电话：" << endl;
		cin >> pszTData;
	}
	newUser.SetTel(pszTData);
	cout << "请输入地址：" << endl;
	cin >> pszTData;
	newUser.SetAddress(pszTData);
	return true;
}
bool  CUserMgr::AddUser(CDB& TDB) {
	/*用于将数据添加到addr_book数据库中*/
	CUser newUser;
	CreateUser(newUser,TDB);
	return TDB.InsertData(newUser);
}
bool  CUserMgr::ProductUser(CDB& TDB,int& nNum) {
	/*用于将数据添加到addr_book数据库中*/
	VecFree();
	static clock_t start = clock(); //获取开始时间
	double dTime=0; //定义运行时间
	static clock_t sStart = clock(); //声明start获取开始时间
	cout << "随机生成" << nNum << "人的数据" << endl;
	for (int i = 0; i < nNum; i++) {
		CUser *TUser = new CUser();
		RandUser(TDB ,*TUser);
		m_vecUser.push_back(TUser);
		//cout << i + 1 << ".\tname:" << TUser->GetName() << "\tTel:" << TUser->GetTel() << "\tAddress:" << TUser->GetAddress() << endl;
	}

	if (!TDB.InsertSomeData(m_vecUser)) {
		return false;
	}
	static clock_t sFinish = clock();//声明finish获取结束时间
	printf("\n");
	dTime = (double)(sFinish - sStart) / CLOCKS_PER_SEC;
	printf("RunningTime:\n%f 秒\n", dTime);//显示
	//cout << "RunningTime: "<< time <<" 秒"<< endl;//显示
	return true;
}
void CUserMgr::VecFree() {
	/*释放vector数组内的所有指针数据*/
	vector<CUser*>::iterator It = m_vecUser.begin();
	for (; It != m_vecUser.end(); ++It)
	{
		if (*It != NULL)
		{
			delete* It;
			*It = NULL;
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

		CUser* TUser = new CUser();
		TUser->SetName(string(row["name"]));
		TUser->SetTel(string(row["tel"]));
		TUser->SetAddress(string(row["address"]));
		m_vecUser.push_back(TUser);

	}
	for (auto it : m_vecUser) {
		//printf("ID:%10s\tAccount:\tCreate_time:\n", it.id, it.account, it.create_time);
		cout << left << "Name:" << it->GetName() << "\t\tTel:" << it->GetTel() << "\t\tAddress:" << it->GetAddress() << endl;
	}
	cout << "一共输出" << m_vecUser.size() << "条数据" << endl;
	return true;
}
bool  CUserMgr::ShowOne(CDB& TDB) {
	/*根据名字展示数据*/
	string strTData= "";
	cout << "请输入要查询的对象的名字" << endl;
	getline(cin, strTData);
	//cout << "输入的内容为" << strTData <<"!" << endl;
	Query query = TDB.CreateQuery();
	if (!TDB.SearchOne(query, "name", strTData))return false;
	return Show(query);
}
bool  CUserMgr::ShowAllName(CDB& TDB) {
	//打印输出所有的现存的名字
	Query query = TDB.CreateQuery();
	if (!TDB.SearchAll(query))return false;
	return Show(query);
}
void  CUserMgr::RandUser(CDB& TDB, CUser& _input) {
	/*用于生成随机数据*/
	_input.SetAddress(RandAddr());
	_input.SetName(RandName());
	string strTel = RandTel();
	bool bTel = CheckTel(strTel,TDB);
	while (!bTel) {
		cout<< strTel<<"已存在数据库中" << endl;
		strTel = RandTel();
		bTel = CheckTel(strTel, TDB);
		cout<<"新的手机号为："<<strTel << endl;
	}
	_input.SetTel(strTel);
	/*
	cout << "cpname:" << _input.getName() << endl;
	cout << "cpTel:" << _input.getTel() << endl;
	cout << "cpAddress:" << _input.getAddress() << endl;
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
const int& CUserMgr::CUserMgr::RandNum(const int& rval) {
	/*获取随机数*/
	return (int)(rand() % rval);
}
string CUserMgr::RandTel() {
	/*随机产生电话*/
	SetSrand();
	int cnt = 0;
	char TelLast[10] = "";
	//srand((unsigned)time(NULL));
	//printf("随机电话头:");
	cnt = RandNum(40);
	string Tel(caTelHead[cnt]);
	//区
	cnt = RandNum(9999999) + 10000000;//保证一定有八位数
	sprintf_s(TelLast, "%d", cnt);
	Tel.append(TelLast);
	//std::cout << Tel << std::endl;
	return Tel;
}
string CUserMgr::RandName() {
	/*随机产生名字*/
	SetSrand();
	int cnt = 0;
	string name("");
	//srand((unsigned)time(NULL));
	//60%概率 是男性名字
	if (RandNum(100) <= 60) {
		//printf("百家姓+随机男名:");
		//姓
		cnt = RandNum(50);
		name.append(caLastName[cnt]);
		//name.append(r[cnt]);
		//名
		cnt = RandNum(50);
		name.append(caManName[cnt]);
		//name.append(l[cnt]);
	}
	else {
		//40%概率 是女性名字
		//printf("百家姓+随机女名:");
		//姓
		cnt = RandNum(50);
		name.append(caLastName[cnt]);
		//name.append(r[cnt]);
		//名
		cnt = RandNum(50);
		name.append(caWomanName[cnt]);
		//name.append(l[cnt]);
	}
	//std::cout << name << std::endl;
	return name;
}
string CUserMgr::RandAddr() {
	/*随机产生地址*/
	SetSrand();
	int cnt = 0;
	//srand((unsigned)time(NULL));
	//printf("随机省份名:");
	//省
	cnt = RandNum(34);
	string Address(caProvincial_Name[cnt]); 
	//cnt = RandNum(50);
	//string Address(r[cnt]);
	//区
	cnt = RandNum(26);
	Address.append(caDistrict_Name[cnt]);
	//cnt = RandNum(50);
	//Address.append(l[cnt]);
	//std::cout << Address << std::endl;
	return Address;
}
bool  CUserMgr::CheckTel(const std::string& _inputTel, CDB& TDB) {
	/*用于检查手机号是否规范，并且判断是否存在重复手机号*/
	if (_inputTel.length() != 11) {
		cout << "手机号位数不正确，请重新输入" << endl;
		return false;
	}
	else {
		for (char c : _inputTel) {
			if (c <= '9' && c >= '0')continue;
			else {
				cout << "手机号内存在非数字，请重新输入" << endl;
				return false;
			}
		}
	}
	//mysqlpp::Query query = TDB.CreateQuery();
	//if (!TDB.SearchOne(query, "tel", _inputTel)) {
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
