#pragma once

typedef struct articleInfo{
	int ID;
	TCHAR filePath[MAX_PATH];
	TCHAR title[MAX_PATH];
	TCHAR className[MAX_PATH];
	int cID;
	int bufferID;//notepad++ID
	BOOL isSavetoDb;
	BOOL isTemp;
	//BOOL isANSI;
	BOOL isSavetoLocal;
	articleInfo *nextNode;
} articleInfo;

enum FindType {FID,FcID,FBufferID,FFilePath};
//enum FindType {FID,FcID,FBufferID};

class CArticleManager
{
public:
	CArticleManager(void);
	~CArticleManager(void);

	enum FindType {ID,cID,BufferID};
	articleInfo *m_head;

	articleInfo* add_ID(int ID,int bufID,TCHAR * filePath,int cID);
	articleInfo* add(int ID,int bufID,TCHAR * filePath,int cID);
	articleInfo* add_bufferID(int ID,int bufID,TCHAR * filePath,int cID);
	articleInfo *find(int info,int findType=FID);
	articleInfo *find(LPCTSTR filePath);
	BOOL del(int info,int type);
};
