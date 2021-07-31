#include "User.h"
#include<string.h>
#include<iostream>
#define _CRT_SECURE_NO_WARNINGS
using namespace std;

CUser::CUser(const std::string& TstrName, const std::string& TstrTel, const std::string& TstrAddre) {
	m_strName = TstrName;
	m_strTel = TstrTel;
	m_strAddr = TstrAddre ;
}

