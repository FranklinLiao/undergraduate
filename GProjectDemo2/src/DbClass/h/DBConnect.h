#ifndef _DBCONNECT_H
#define _DBCONNECT_H
#define  SQL_BUFFER_LEN 1024
#include "stdafx.h"
#include <list>
#include <windows.h>
#include <string>
#include <vector>
#include <iostream>
#include <iomanip> //for setw()
#include <cstring>
using namespace std;
#import "C:\Program Files\Common Files\System\ado\msado15.dll" no_namespace rename("EOF","EndOfFile")

class DBConnect {
	//构造函数和析构函数
	public:
		DBConnect(LPCSTR strDstAddress, 
			LPCSTR strUsername, 
			LPCSTR strPassword,	
			LPCSTR strDBName,
			BOOL &state);
		~DBConnect();

	//开放的函数和成员变量
	public:
		// 连接到数据库
		int Open(LPCSTR strDstAddress, LPCSTR strUsername, LPCSTR strPassword, LPCSTR strDBName);
		// 关闭数据库
		int Close();
		// 数据库是否已连接
		bool IsOpen();

		//int          GetSubmitInfo(vector<SOAP_SUBMIT_SMS> &vecsoapSms);    
		_ConnectionPtr _connection_ptr; //ADO的数据库连接智能指针
		//int          InsertHistory(int id);

	//私有的函数和成员变量
	private:
		//ADODB::_ConnectionPtr           _connection_ptr;   //ADO的数据库连接智能指针
		bool                            _isAdoValid;       //ADO环境是否已经初化成功标志量
		bool							m_bDBOpen;
		LPCSTR							_strDstAddress;    //数据源地址或服务名
		LPCSTR							_strUsername;      //数据库用户名
		LPCSTR							_strPassword;      //数据库密码
		LPCSTR							_strDBName;        //数据库名称
		void         VarientToString(_variant_t var, string& str);
};	

#endif