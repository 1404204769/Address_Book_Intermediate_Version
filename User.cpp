#include "User.h"
#include<string.h>
#include<iostream>
#define _CRT_SECURE_NO_WARNINGS
using namespace std;
CUser::CUser() {}
CUser::CUser(const string& TemPszName, const string& TemPszTel, const string& TemPszAdress) {
	pszName = TemPszName;
	pszTel = TemPszTel;
	pszAddress = TemPszAdress;
}


CUser::~CUser() {}