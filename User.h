#pragma once
#ifndef _CUSER_H_
#define _CUSER_H_
#include <string>
#include <iostream>
class CUser {
public:
	CUser();
	CUser(const std::string& TemPszName, const std::string& TemPszTel, const std::string& TemPszAdress);//拷贝函数
	~CUser();
	const std::string& GetName()const { return pszName; }
	const std::string& GetTel()const { return pszTel; }
	const std::string& GetAddress()const { return pszAddress; }
	void SetName(const std::string& _input) { pszName = _input; /*cout << "copy name:" << pszName << endl;*/ }
	void SetTel(const std::string& _input) { pszTel = _input; /*cout << "copy Tel:" << pszTel << endl;*/ }
	void SetAddress(const std::string& _input) { pszAddress = _input; /*cout << "copy Address:" << pszAddress << endl;*/ }
private:
	std::string pszName;//保存名字
	std::string pszTel;//保存手机号
	std::string pszAddress;//保存地址
};
#endif //!_CUSER_H_