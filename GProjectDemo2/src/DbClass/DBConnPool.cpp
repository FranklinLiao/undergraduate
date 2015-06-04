// DBConnPool.cpp: implementation of the DBConnPool class.
#include "stdafx.h"
#include "DBConnPool.h"
DBConnPool* DBConnPool::m_pInstanse = NULL;
//需要在构造函数外初始化
string DBConnPool::m_username = "sa";
string DBConnPool::m_password = "123456";
string DBConnPool::m_dbname = "LTE_OPT";
DBConnPool::DBConnPool()
{
	m_bNeedStop = FALSE;
	m_bNeedConnection = FALSE;
	m_hMaintanceThread = INVALID_HANDLE_VALUE;
	// 线程控制
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
	 //配置完成后，就自动创建连接池
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
	// 先摧毁现有的连接
	DestroyAllDBConnections();
	// 开始按照最小数量开始创建
	DBConnect * pDBConnect = NULL;
	int nCount = 0;
	for (int i = 0; i < m_nMinCount; i++){
		nCount = InitializeAConnection();
	}
	// 创建一个工作线程，用来进行一些后台维护工作
	if (INVALID_HANDLE_VALUE == m_hMaintanceThread){
		m_hMaintanceThread = CreateThread(NULL, NULL, thread_run, (LPVOID)this, 0, NULL);
	}
	//nCount中反应了成功创建了多少连接
	return nCount;
}

void DBConnPool::DestroyAllDBConnections()
{
	// 销毁数据库连接可以使用大锁
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
	// 还有使用中的连接  这里有问题，应该等待使用中的连接使用完成后再进行关闭  
	//此外这里只考虑了使用，在程序中却没有关闭的时候
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
	//建立一个连接
	DBConnect * pDBEngine = new DBConnect(_strDstAddress, _strUsername, _strPassword, _strDBName, bSuccess);
	//bSuccess表示该连接是否成功打开
	if (bSuccess){
		m_bNeedConnection = FALSE;
		//将连接放入到空闲队列中，以便之后的使用
		return PutAConnection(pDBEngine);
	}else{
		delete pDBEngine;
		return m_listIdleConnection.size();
	}
}


/*  
//这个东西应该没用得上   至少没找到函数显示的调用 要么就全部关闭，要么就一直让连接存在
void DBConnPool::CloseAConnection(DBConnect* pDBEngine)
{
    pDBEngine->Close();
	// 从空闲队列将其删除
	EnterCriticalSection(&m_csIdleConnList);
	m_listIdleConnection.remove(pDBEngine);
	LeaveCriticalSection(&m_csIdleConnList);
}
*/

//有疑问   _RecordsetPtr record
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
	// 做一个循环，反复尝试五次取连接，每次间隔1秒钟
	int nTimes = 0;
	while ((m_listIdleConnection.size() < 1) && (nTimes < 5)){
		Sleep(1000);
		nTimes++;
	}
	if (5 == nTimes){
		// 进来肯定是等待了一定时间，但是依然没有连接可用，所以直接报错退出！
		cout<<"Waiting for a connection for a long time, but failed. So this will return Null"<<endl;
		return pDBEngine;
	}
	// 从空闲队列中取出，并且加入到使用队列中
	EnterCriticalSection(&m_csIdleConnList);
	if (m_listIdleConnection.size() > 0) {
		pDBEngine = m_listIdleConnection.front();
		m_listIdleConnection.pop_front();
		// 加入使用的连接队列
		EnterCriticalSection(&m_csBusyConnList);
		m_listBusyConnection.push_back(pDBEngine);
		LeaveCriticalSection(&m_csBusyConnList);
	}
	LeaveCriticalSection(&m_csIdleConnList);
	listSize = m_listIdleConnection.size();
	busySize = m_listBusyConnection.size();
	if (m_listIdleConnection.size() < 1){
		// 剩余空闲连接的数目小于1个时候(0个）需要检查开始创建
		if ((m_listIdleConnection.size() + m_listBusyConnection.size()) < m_nMaxCount) {
			// 还小于最大限制，可以创建
			//通知线程
			SetEvent(m_hHaveData);
			m_bNeedConnection = TRUE;
		} else{
			// 超出限制了，做个记录吧
			cout<<"Database connection reached max count,you have to wait for others to release!"<<endl;
		}
	}
	listSize = m_listIdleConnection.size();
	busySize = m_listBusyConnection.size();
	cout<<"idle is "<<m_listIdleConnection.size()<<endl;
	cout<<"busy is "<<m_listBusyConnection.size()<<endl;
	return pDBEngine;
}

//创建一个连接  将它放入到空闲队列中  这样当需要连接的时候就可以从空闲队列中取出来用
int DBConnPool::PutAConnection(DBConnect* pDBEngine)
{
	if (NULL != pDBEngine){
		// 加入到空闲队列中
		EnterCriticalSection(&m_csIdleConnList);
		m_listIdleConnection.push_back(pDBEngine);
		LeaveCriticalSection(&m_csIdleConnList);
	}
	EnterCriticalSection(&m_csIdleConnList);
	int nCount = m_listIdleConnection.size();
	LeaveCriticalSection(&m_csIdleConnList);
	return nCount;
}

//用完一个连接后  将它放入到空闲队列中  这样当需要连接的时候就可以从空闲队列中取出来用
int DBConnPool::RestoreAConnection(DBConnect* pDBEngine)
{
	if (NULL != pDBEngine){
		// 从使用中的队列取出
		EnterCriticalSection(&m_csBusyConnList);
		m_listBusyConnection.remove(pDBEngine);
		LeaveCriticalSection(&m_csBusyConnList);
		// 加入到空闲队列中
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
	// 因为线程是无限制等待信号的，所以这里先把标志位置为停止，然后发信号让线程检测
	SetEvent(m_hHaveData);

	// 等待退出
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
/* 维护线程                 
	这个线程在不停的运行（没有关闭该线程的话），不停的去检测IsNeedConection信号
	如果这个信号有效的话，就创建新的连接
*/
/************************************************************************/
DWORD WINAPI DBConnPool::thread_run( LPVOID pdata)
{
	DBConnPool * pConPool = (DBConnPool *) pdata;
	while (!pConPool->IsNeedStop())
	{
		// 设置事件为无信号, 并且无限制等待
		ResetEvent(pConPool->m_hHaveData);		
		//如果m_hHaveData信号被激励后，线程就停止等待，开始执行判断IsNeedConnection信号
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