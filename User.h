#pragma once
#ifndef _USER_H_
#define _USER_H_
#include <string>
#include<mysql++.h>
class CUser {
public:
	CUser() = delete;
	CUser(const std::string& TstrName, const std::string& TstrTel, const std::string& TstrAddre);//拷贝函数
	const std::string& GetName()const { return m_strName; }
	void SetName(const std::string& _input) { m_strName = _input; }

	const std::string& GetTel()const { return m_strTel; }
	void SetTel(const std::string& _input) { m_strTel = _input; }

	const std::string& GetAddress()const { return m_strAddr; }
	void SetAddress(const std::string& _input) { m_strAddr = _input;}

private:
	std::string m_strName;/*名字*/
	std::string m_strTel;/*手机号*/
	std::string m_strAddr;/*地址*/
};
#endif //!_USER_H_