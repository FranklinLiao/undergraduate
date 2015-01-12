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
	//���캯������������
	public:
		DBConnect(LPCSTR strDstAddress, 
			LPCSTR strUsername, 
			LPCSTR strPassword,	
			LPCSTR strDBName,
			BOOL &state);
		~DBConnect();

	//���ŵĺ����ͳ�Ա����
	public:
		// ���ӵ����ݿ�
		int Open(LPCSTR strDstAddress, LPCSTR strUsername, LPCSTR strPassword, LPCSTR strDBName);
		// �ر����ݿ�
		int Close();
		// ���ݿ��Ƿ�������
		bool IsOpen();

		//int          GetSubmitInfo(vector<SOAP_SUBMIT_SMS> &vecsoapSms);    
		_ConnectionPtr _connection_ptr; //ADO�����ݿ���������ָ��
		//int          InsertHistory(int id);

	//˽�еĺ����ͳ�Ա����
	private:
		//ADODB::_ConnectionPtr           _connection_ptr;   //ADO�����ݿ���������ָ��
		bool                            _isAdoValid;       //ADO�����Ƿ��Ѿ������ɹ���־��
		bool							m_bDBOpen;
		LPCSTR							_strDstAddress;    //����Դ��ַ�������
		LPCSTR							_strUsername;      //���ݿ��û���
		LPCSTR							_strPassword;      //���ݿ�����
		LPCSTR							_strDBName;        //���ݿ�����
		void         VarientToString(_variant_t var, string& str);
};	

#endif