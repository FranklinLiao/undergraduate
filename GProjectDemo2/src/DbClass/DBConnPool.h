// DBConnPool.h: interface for the DBConnPool class.
#ifndef _DBCONNPOOL_H
#define _DBCONNPOOL_H
#include "stdafx.h"
#include "DBConnect.h"
#include <string>
#include <iostream>
#include <list>
using namespace std;

typedef list<DBConnect*>  DBConnectList;
class  DBConnPool  
{
public:
	DBConnPool();
	virtual ~DBConnPool();

public:
	// 获取实例指针
	static DBConnPool* Instanse();
	// 初始化所有连接
	int InitializeAllDBConnections();
	// 关闭所有连接
	void DestroyAllDBConnections();
	//关闭结果集
	void CloseRecordSet(_RecordsetPtr& record);
	//void CloseConnection(_ConnectionPtr& conn);
	// 获取一个空闲连接
	DBConnect* GetAConnection();
	// 交还连接给空闲队列
	int RestoreAConnection(DBConnect* pDBEngine);
	

	void SetDBInfo(LPCSTR strDstAddress, LPCSTR strUsername, LPCSTR strPassword, LPCSTR strDBName,int minConn,int maxConn);
	void SetInstanceNull();
private:
	// 唯一实例
	static DBConnPool* m_pInstanse;
private:
	// 空闲数据库连接队列
	DBConnectList m_listIdleConnection;
	// 在使用的数据库连接
	DBConnectList m_listBusyConnection;
	// 队列保护的临界区
	CRITICAL_SECTION m_csIdleConnList;
	CRITICAL_SECTION m_csBusyConnList;
	// 可用连接总数的两个指标：最大、最小
	int m_nMaxCount;
	int m_nMinCount;
// 	// 数据库信息
	LPCSTR	_strDstAddress;    //数据源地址或服务名
	LPCSTR	_strUsername;      //数据库用户名
	LPCSTR	_strPassword;      //数据库密码
	LPCSTR	_strDBName;        //数据库名称
	// 维护线程
	HANDLE m_hMaintanceThread; //线程句柄
	HANDLE m_hHaveData; //信号
	BOOL m_bNeedStop; // 管理线程起停的标志位
	BOOL m_bNeedConnection; // 需要创建连接的标志
	static	DWORD	WINAPI	thread_run( LPVOID pdata);

public:
	static string m_username;
	static string m_password;
	static string m_dbname;
private:
	// 创建一个连接
	int InitializeAConnection();
	//将创立的连接放入到空闲队列中
	int PutAConnection(DBConnect* pDBEngine);
	// 关闭一个连接
	void CloseAConnection(DBConnect* pDBEngine);
	// 停止工作线程
	void StopThread();
	// 判断是否需要停止
	BOOL IsNeedStop();
	BOOL IsNeedConnection();
};

#endif

