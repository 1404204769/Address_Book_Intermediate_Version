#pragma once
#ifndef _USER_H_
#define _USER_H_
#include <string>
#include <iostream>
#include <mysql++.h>
#include <ssqls.h>
class CUser {
public:
	CUser();
	CUser(const std::string& TstrName, const std::string& TstrTel, const std::string& TstrAddre);//拷贝函数
	~CUser();
	const std::string& GetName()const { return m_strName; }
	const std::string& GetTel()const { return m_strTel; }
	const std::string& GetAddress()const { return m_strAddr; }
	void SetName(const std::string& _input) { 
		m_strName = _input;
		/*cout << "copy name:" << pszName << endl;*/ 
	}
	void SetTel(const std::string& _input) { 
		m_strTel = _input; 
		/*cout << "copy Tel:" << pszTel << endl;*/ 
	}
	void SetAddress(const std::string& _input) { 
		m_strAddr = _input;
		/*cout << "copy Address:" << pszAddress << endl;*/ 
	}
private:
	std::string m_strName;/*名字*/
	std::string m_strTel;/*手机号*/
	std::string m_strAddr;/*地址*/
};
#endif //!_USER_H_