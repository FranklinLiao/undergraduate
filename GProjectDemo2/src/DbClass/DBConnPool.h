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
	// ��ȡʵ��ָ��
	static DBConnPool* Instanse();
	// ��ʼ����������
	int InitializeAllDBConnections();
	// �ر���������
	void DestroyAllDBConnections();
	//�رս����
	void CloseRecordSet(_RecordsetPtr& record);
	//void CloseConnection(_ConnectionPtr& conn);
	// ��ȡһ����������
	DBConnect* GetAConnection();
	// �������Ӹ����ж���
	int RestoreAConnection(DBConnect* pDBEngine);
	

	void SetDBInfo(LPCSTR strDstAddress, LPCSTR strUsername, LPCSTR strPassword, LPCSTR strDBName,int minConn,int maxConn);
	void SetInstanceNull();
private:
	// Ψһʵ��
	static DBConnPool* m_pInstanse;
private:
	// �������ݿ����Ӷ���
	DBConnectList m_listIdleConnection;
	// ��ʹ�õ����ݿ�����
	DBConnectList m_listBusyConnection;
	// ���б������ٽ���
	CRITICAL_SECTION m_csIdleConnList;
	CRITICAL_SECTION m_csBusyConnList;
	// ������������������ָ�꣺�����С
	int m_nMaxCount;
	int m_nMinCount;
// 	// ���ݿ���Ϣ
	LPCSTR	_strDstAddress;    //����Դ��ַ�������
	LPCSTR	_strUsername;      //���ݿ��û���
	LPCSTR	_strPassword;      //���ݿ�����
	LPCSTR	_strDBName;        //���ݿ�����
	// ά���߳�
	HANDLE m_hMaintanceThread; //�߳̾��
	HANDLE m_hHaveData; //�ź�
	BOOL m_bNeedStop; // �����߳���ͣ�ı�־λ
	BOOL m_bNeedConnection; // ��Ҫ�������ӵı�־
	static	DWORD	WINAPI	thread_run( LPVOID pdata);

public:
	static string m_username;
	static string m_password;
	static string m_dbname;
private:
	// ����һ������
	int InitializeAConnection();
	//�����������ӷ��뵽���ж�����
	int PutAConnection(DBConnect* pDBEngine);
	// �ر�һ������
	void CloseAConnection(DBConnect* pDBEngine);
	// ֹͣ�����߳�
	void StopThread();
	// �ж��Ƿ���Ҫֹͣ
	BOOL IsNeedStop();
	BOOL IsNeedConnection();
};

#endif

