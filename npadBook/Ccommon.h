#pragma once
#include   <iostream> 
#include   <string> 

using   namespace   std;

class Ccommon
{
public:
	Ccommon(void);
	~Ccommon(void);

	//accessת�壭�����żӱ�
	void transFormSinQuote(CString &source);
	void getExeUrl(CString *url);
	// ɾ��Ŀ¼�������ļ�
	bool DeleteDirectory(const CString &pathName);


};

TCHAR *getAppDbPath();

LPSTR unicodeToAnsi(LPCWSTR str);
char *unicodeToUtf82(LPCWSTR str);  //str����ȥ��ᱻɾ
void getExeUrl(TCHAR *exefileurl);
char *unicodeToUtf8(const WCHAR *zWideFilename);
wstring ANSIToUnicode( const string& str );
wstring UTF8ToUnicode( const string& str );
string ansiToUtf8(string &str);

bool isutf8(CHAR *str);