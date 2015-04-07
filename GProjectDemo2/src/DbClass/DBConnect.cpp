#include "stdafx.h"
#include "DBConnect.h"
/**
* @brief    在构造函数中，调用连接数据库的函数，进行连接，并将state进行置位
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
//不需要析构函数进行资源的关闭  手动实现资源的关闭
DBConnect::~DBConnect()
{
  // Close();
}
/**
* @brief    实际进行数据库连接的函数
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
		// 连接到服务器上数据库
		hr = _connection_ptr->Open(szSQL, strUsername, strPassword,adModeUnknown) ;
		if (FAILED(hr))
			return -1;
	} catch (_com_error &err)
	{
		//TRACE(_T("数据库操作失败! 错误信息:%s, 文件:%s, 行:%d.\n"), err.ErrorMessage(), __FILE__, __LINE__);
		cout<<"连接数据库失败"<<endl;
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