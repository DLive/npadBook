#pragma once
#include "CppSQLite3U.h"
class CConndb
{
public:
	CConndb(void);
	~CConndb(void);
	
	//����
	int insert(CString &comText);
	//����
	//_ConnectionPtr m_pConnection;
	//_RecordsetPtr	m_pRecordset;//�����
	void search(CString &sqlcmd);
	void getarticle(CString &cmdsql);
	int m_geteffectnum(CString &cmdsql);
	//_variant_t RecordsAffecteds; //Ӱ������
	BOOL excuteSql(CString &cmdsql);
	int excuteSql2(CString &cmdsql);
	int getCount(CString &cmdsql);
	// ɾ����¼
	bool deleteRecord(CString no);
	
	CppSQLite3DB *m_db;
	CppSQLite3Query *m_query;
	//��ҳ����
	//int		m_recodeCount; //������
	//int		m_paperCoutn;	//��ҳ��
	//int		m_paperNum;		//ÿҳ����

	int		setPageInfo(CString &sqlcmd,int pageSize);

};
