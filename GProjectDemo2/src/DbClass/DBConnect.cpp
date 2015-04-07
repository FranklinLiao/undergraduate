#include "stdafx.h"
#include "DBConnect.h"
/**
* @brief    �ڹ��캯���У������������ݿ�ĺ������������ӣ�����state������λ
* @fullName	DBConnect::DBConnect
* @param	strDstAddress
* @param	strUsername
* @param	strPassword
* @param	strDBName
* @param	state
* @return	
* @author	Franklin
* @date		2014/05/26
* @warning	
*/
DBConnect::DBConnect(LPCSTR strDstAddress, LPCSTR strUsername, LPCSTR strPassword, LPCSTR strDBName,BOOL &state)
{
   m_bDBOpen = false;
   if (0 == Open(strDstAddress,strUsername,strPassword,strDBName)){
        state =true;
   } else {
	   state = false;
   }
}
//����Ҫ��������������Դ�Ĺر�  �ֶ�ʵ����Դ�Ĺر�
DBConnect::~DBConnect()
{
  // Close();
}
/**
* @brief    ʵ�ʽ������ݿ����ӵĺ���
* @fullName	DBConnect::Open
* @param	strDstAddress
* @param	strUsername
* @param	strPassword
* @param	strDBName
* @return	int
* @author	Franklin
* @date		2014/05/26
* @warning	
*/
int DBConnect::Open(LPCSTR strDstAddress, LPCSTR strUsername, LPCSTR strPassword, LPCSTR strDBName)
{
	_strDstAddress = strDstAddress;
	_strDBName       = strDBName;
	_strUsername     = strUsername;
	_strPassword     = strPassword;
	
	HRESULT comhr = ::CoInitialize(NULL);
	if (FAILED(comhr)){
		return -1;
	}
	HRESULT hr = _connection_ptr.CreateInstance(__uuidof(Connection));
	if (FAILED(hr)){
		return -1;
	}
	
	char szSQL[SQL_BUFFER_LEN] = {0};
	memset(szSQL, 0, SQL_BUFFER_LEN);
	sprintf(szSQL, "Driver=SQL Server;Server=%s;DATABASE=%s", strDstAddress, strDBName);
	
	try{
		// ���ӵ������������ݿ�
		hr = _connection_ptr->Open(szSQL, strUsername, strPassword,adModeUnknown) ;
		if (FAILED(hr))
			return -1;
	} catch (_com_error &err)
	{
		//TRACE(_T("���ݿ����ʧ��! ������Ϣ:%s, �ļ�:%s, ��:%d.\n"), err.ErrorMessage(), __FILE__, __LINE__);
		cout<<"�������ݿ�ʧ��"<<endl;
		return -1;
	}
	m_bDBOpen = TRUE;
	return 0;
}

int DBConnect::Close()
{
	if (m_bDBOpen) {
		HRESULT hr =_connection_ptr->Close();
		if (FAILED(hr))
		{
			return -1;
		}
		::CoUninitialize();
		m_bDBOpen = FALSE;
	}
	return 0;
}


bool DBConnect::IsOpen() {
	return m_bDBOpen;
}