// DBConnPool.cpp: implementation of the DBConnPool class.
#include "stdafx.h"
#include "DBConnPool.h"
DBConnPool* DBConnPool::m_pInstanse = NULL;
//��Ҫ�ڹ��캯�����ʼ��
string DBConnPool::m_username = "sa";
string DBConnPool::m_password = "123456";
string DBConnPool::m_dbname = "LTE_OPT";
DBConnPool::DBConnPool()
{
	m_bNeedStop = FALSE;
	m_bNeedConnection = FALSE;
	m_hMaintanceThread = INVALID_HANDLE_VALUE;
	// �߳̿���
	m_hHaveData = CreateEvent (NULL, TRUE, FALSE, _T("DataConnPool"));
	InitializeCriticalSection(&m_csIdleConnList);
	InitializeCriticalSection(&m_csBusyConnList);
}

void DBConnPool::SetDBInfo(LPCSTR strDstAddress, LPCSTR strUsername, LPCSTR strPassword, LPCSTR strDBName,int minConn,int maxConn)
{
	_strDBName = strDBName;
	_strDstAddress = strDstAddress;
	_strPassword = strPassword;
	_strUsername = strUsername;
	 m_nMaxCount = maxConn;
	 m_nMinCount = minConn;
	 //������ɺ󣬾��Զ��������ӳ�
	 int validateConnection = InitializeAllDBConnections();
}

DBConnPool::~DBConnPool()
{
	m_hMaintanceThread = INVALID_HANDLE_VALUE;
	m_bNeedStop = TRUE;
	CloseHandle(m_hHaveData);
	CloseHandle(m_hMaintanceThread);
    DeleteCriticalSection(&m_csIdleConnList);
	DeleteCriticalSection(&m_csBusyConnList);
}

DBConnPool *DBConnPool::Instanse()
{
	if (NULL == m_pInstanse){
        m_pInstanse = new DBConnPool();
		m_pInstanse->SetDBInfo("127.0.0.1",m_username.c_str(),m_password.c_str(),m_dbname.c_str(),30,50);
	}
	return m_pInstanse;
}

int DBConnPool::InitializeAllDBConnections()
{
	// �ȴݻ����е�����
	DestroyAllDBConnections();
	// ��ʼ������С������ʼ����
	DBConnect * pDBConnect = NULL;
	int nCount = 0;
	for (int i = 0; i < m_nMinCount; i++){
		nCount = InitializeAConnection();
	}
	// ����һ�������̣߳���������һЩ��̨ά������
	if (INVALID_HANDLE_VALUE == m_hMaintanceThread){
		m_hMaintanceThread = CreateThread(NULL, NULL, thread_run, (LPVOID)this, 0, NULL);
	}
	//nCount�з�Ӧ�˳ɹ������˶�������
	return nCount;
}

void DBConnPool::DestroyAllDBConnections()
{
	// �������ݿ����ӿ���ʹ�ô���
	EnterCriticalSection(&m_csIdleConnList);
	DBConnectList::iterator itIdle = m_listIdleConnection.begin();
	DBConnectList::iterator itIdleEnd = m_listIdleConnection.end();
	if(!m_listIdleConnection.empty()) {
		while (itIdle != itIdleEnd){
			if (NULL != (*itIdle)){
				(*itIdle)->Close();
			}
			itIdle++;
		}
		m_listIdleConnection.clear();
	}
	LeaveCriticalSection(&m_csIdleConnList);
	// ����ʹ���е�����  ���������⣬Ӧ�õȴ�ʹ���е�����ʹ����ɺ��ٽ��йر�  
	//��������ֻ������ʹ�ã��ڳ�����ȴû�йرյ�ʱ��
	EnterCriticalSection(&m_csBusyConnList);
	DBConnectList::iterator itBusy = m_listBusyConnection.begin();
    DBConnectList::iterator itBusyEnd = m_listBusyConnection.end();
	if(!m_listBusyConnection.empty()) {
		while (itBusy != itBusyEnd){
			if (NULL != (*itBusy)){
				while((*itBusy)->IsOpen()) {
					Sleep(5000);
				}
				(*itBusy)->Close();
			}
			itBusy++;
		}
		m_listBusyConnection.clear();
	}
	LeaveCriticalSection(&m_csBusyConnList);
}

int DBConnPool::InitializeAConnection(){
	int listSize = m_listIdleConnection.size();
	int busySize = m_listBusyConnection.size();
	BOOL bSuccess = FALSE;
	//����һ������
	DBConnect * pDBEngine = new DBConnect(_strDstAddress, _strUsername, _strPassword, _strDBName, bSuccess);
	//bSuccess��ʾ�������Ƿ�ɹ���
	if (bSuccess){
		m_bNeedConnection = FALSE;
		//�����ӷ��뵽���ж����У��Ա�֮���ʹ��
		return PutAConnection(pDBEngine);
	}else{
		delete pDBEngine;
		return m_listIdleConnection.size();
	}
}


/*  
//�������Ӧ��û�õ���   ����û�ҵ�������ʾ�ĵ��� Ҫô��ȫ���رգ�Ҫô��һֱ�����Ӵ���
void DBConnPool::CloseAConnection(DBConnect* pDBEngine)
{
    pDBEngine->Close();
	// �ӿ��ж��н���ɾ��
	EnterCriticalSection(&m_csIdleConnList);
	m_listIdleConnection.remove(pDBEngine);
	LeaveCriticalSection(&m_csIdleConnList);
}
*/

//������   _RecordsetPtr record
void DBConnPool::CloseRecordSet(_RecordsetPtr& record) {
	try {
			if(record->State)
				record->Close();
		} catch(_com_error e) {
			cout<<"close database record  failed "<<endl;
		}
}

//void DBConnPool::CloseConnection(_ConnectionPtr& conn) {
//	try {
//		if(conn->State) {
//			conn->Close();
//		}
//	} catch(_com_error e) {
//		cout<<"close database connectionPtr  failed "<<endl;
//	}
//}


DBConnect* DBConnPool::GetAConnection()
{
	int listSize = m_listIdleConnection.size();
	int busySize = m_listBusyConnection.size();
	DBConnect * pDBEngine = NULL;
	// ��һ��ѭ���������������ȡ���ӣ�ÿ�μ��1����
	int nTimes = 0;
	while ((m_listIdleConnection.size() < 1) && (nTimes < 5)){
		Sleep(1000);
		nTimes++;
	}
	if (5 == nTimes){
		// �����϶��ǵȴ���һ��ʱ�䣬������Ȼû�����ӿ��ã�����ֱ�ӱ����˳���
		cout<<"Waiting for a connection for a long time, but failed. So this will return Null"<<endl;
		return pDBEngine;
	}
	// �ӿ��ж�����ȡ�������Ҽ��뵽ʹ�ö�����
	EnterCriticalSection(&m_csIdleConnList);
	if (m_listIdleConnection.size() > 0) {
		pDBEngine = m_listIdleConnection.front();
		m_listIdleConnection.pop_front();
		// ����ʹ�õ����Ӷ���
		EnterCriticalSection(&m_csBusyConnList);
		m_listBusyConnection.push_back(pDBEngine);
		LeaveCriticalSection(&m_csBusyConnList);
	}
	LeaveCriticalSection(&m_csIdleConnList);
	listSize = m_listIdleConnection.size();
	busySize = m_listBusyConnection.size();
	if (m_listIdleConnection.size() < 1){
		// ʣ��������ӵ���ĿС��1��ʱ��(0������Ҫ��鿪ʼ����
		if ((m_listIdleConnection.size() + m_listBusyConnection.size()) < m_nMaxCount) {
			// ��С��������ƣ����Դ���
			//֪ͨ�߳�
			SetEvent(m_hHaveData);
			m_bNeedConnection = TRUE;
		} else{
			// ���������ˣ�������¼��
			cout<<"Database connection reached max count,you have to wait for others to release!"<<endl;
		}
	}
	listSize = m_listIdleConnection.size();
	busySize = m_listBusyConnection.size();
	cout<<"idle is "<<m_listIdleConnection.size()<<endl;
	cout<<"busy is "<<m_listBusyConnection.size()<<endl;
	return pDBEngine;
}

//����һ������  �������뵽���ж�����  ��������Ҫ���ӵ�ʱ��Ϳ��Դӿ��ж�����ȡ������
int DBConnPool::PutAConnection(DBConnect* pDBEngine)
{
	if (NULL != pDBEngine){
		// ���뵽���ж�����
		EnterCriticalSection(&m_csIdleConnList);
		m_listIdleConnection.push_back(pDBEngine);
		LeaveCriticalSection(&m_csIdleConnList);
	}
	EnterCriticalSection(&m_csIdleConnList);
	int nCount = m_listIdleConnection.size();
	LeaveCriticalSection(&m_csIdleConnList);
	return nCount;
}

//����һ�����Ӻ�  �������뵽���ж�����  ��������Ҫ���ӵ�ʱ��Ϳ��Դӿ��ж�����ȡ������
int DBConnPool::RestoreAConnection(DBConnect* pDBEngine)
{
	if (NULL != pDBEngine){
		// ��ʹ���еĶ���ȡ��
		EnterCriticalSection(&m_csBusyConnList);
		m_listBusyConnection.remove(pDBEngine);
		LeaveCriticalSection(&m_csBusyConnList);
		// ���뵽���ж�����
		EnterCriticalSection(&m_csIdleConnList);
		m_listIdleConnection.push_back(pDBEngine);
		LeaveCriticalSection(&m_csIdleConnList);
	}
	EnterCriticalSection(&m_csIdleConnList);
	int nCount = m_listIdleConnection.size();
	LeaveCriticalSection(&m_csIdleConnList);
	return nCount;
}

void DBConnPool::StopThread()
{
	m_bNeedStop = TRUE;
	// ��Ϊ�߳��������Ƶȴ��źŵģ����������Ȱѱ�־λ��Ϊֹͣ��Ȼ���ź����̼߳��
	SetEvent(m_hHaveData);

	// �ȴ��˳�
	WaitForSingleObject(m_hMaintanceThread, INFINITE);
	CloseHandle(m_hMaintanceThread);
}

BOOL DBConnPool::IsNeedStop()
{
	return m_bNeedStop;
}

BOOL DBConnPool::IsNeedConnection()
{
	return m_bNeedConnection;
}
/************************************************************************/
/* ά���߳�                 
	����߳��ڲ�ͣ�����У�û�йرո��̵߳Ļ�������ͣ��ȥ���IsNeedConection�ź�
	�������ź���Ч�Ļ����ʹ����µ�����
*/
/************************************************************************/
DWORD WINAPI DBConnPool::thread_run( LPVOID pdata)
{
	DBConnPool * pConPool = (DBConnPool *) pdata;
	while (!pConPool->IsNeedStop())
	{
		// �����¼�Ϊ���ź�, ���������Ƶȴ�
		ResetEvent(pConPool->m_hHaveData);		
		//���m_hHaveData�źű��������߳̾�ֹͣ�ȴ�����ʼִ���ж�IsNeedConnection�ź�
		WaitForSingleObject(pConPool->m_hHaveData, INFINITE);
		if (pConPool->IsNeedConnection())
		{
		//	g_pSvrLog->AddRunLog(LL_DEBUG, _T("Create a new DB connection."));
			pConPool->InitializeAConnection();
		}
	}
	return 0;
}

void DBConnPool::SetInstanceNull() {
	if(m_pInstanse!=NULL) {
		DestroyAllDBConnections();
		m_pInstanse = NULL;
	}
} 