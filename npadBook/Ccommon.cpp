#include "StdAfx.h"
#include "Ccommon.h"


//ȫ��db url
TCHAR *appDbPath=NULL;
extern HANDLE m_dllHandle;
TCHAR *getAppDbPath(){
	if(appDbPath!=NULL)
		return appDbPath;
	appDbPath=new TCHAR[MAX_PATH];
	ZeroMemory(appDbPath,MAX_PATH);
	getExeUrl(appDbPath);
	appDbPath=wcscat(appDbPath,_T("data\\notebook.sqlite"));
	return appDbPath;
}

Ccommon::Ccommon(void)
{
}

Ccommon::~Ccommon(void)
{
}

void Ccommon::transFormSinQuote(CString &source)
{
	//source.Replace("'","''");
}

void Ccommon::getExeUrl(CString *url)
{

	TCHAR exefileurl[MAX_PATH];
	GetModuleFileName((HMODULE)m_dllHandle,exefileurl,MAX_PATH);
	(_tcsrchr(exefileurl, _T('\\')))[1] = 0;
	*url=exefileurl;
}

// ɾ��Ŀ¼�������ļ�
bool Ccommon::DeleteDirectory(const CString  &pathName)
{
	CFileFind fFind;
	CString dirName=pathName;	
	if(dirName.Right(1)!=_T("\\"))
		dirName+=_T("\\");
	CString tempName=dirName;
	dirName+=_T("*.*");
	CString deletefile;
	BOOL isFind=fFind.FindFile(dirName);
	int num=0;
	while(isFind)
	{
		num++;
		isFind=fFind.FindNextFileW();
		if(!fFind.IsDirectory() && !fFind.IsDots())
		{
			//�����ļ�
			tempName=fFind.GetFilePath();
			DeleteFile(tempName);
			num--;
		}
		else if(fFind.IsDirectory() && !fFind.IsDots())
			DeleteDirectory(fFind.GetFilePath());
	}
	fFind.Close();
	if(num==0)
		return true; //�ļ���Ϊ��
	else
		return false;
}

//must delete ret value
LPSTR unicodeToAnsi(LPCWSTR str){
	BOOL bUsedDefaultChar;
	UINT alen=WideCharToMultiByte(CP_ACP,0,str,-1,NULL,0,NULL,NULL);
	LPSTR pMultiByteStr = new char[alen+1];
	memset( ( void* )pMultiByteStr, 0, sizeof( char ) * (alen+1 ) );
	// convert to ANSI string

	WideCharToMultiByte(CP_ACP, 0,(str), -1, pMultiByteStr,alen,NULL, &bUsedDefaultChar);
	// create the ANSI file
	return pMultiByteStr;
}
void getExeUrl(TCHAR *exefileurl)
{
	//TCHAR exefileurl[MAX_PATH];
	GetModuleFileName((HMODULE)m_dllHandle,exefileurl,MAX_PATH);
	(wcsrchr(exefileurl,_T('\\')))[1] = 0;
}

//you need free ��zFilename
char *unicodeToUtf8(const WCHAR *zWideFilename)   
{   
	int nByte;   
	char *zFilename;   
	nByte = WideCharToMultiByte(CP_UTF8, 0, zWideFilename, -1, 0, 0, 0, 0);   
	zFilename = (char *)malloc(nByte);   
	if(zFilename == 0)   
	{   
		return 0;   
	}   
	nByte = WideCharToMultiByte(CP_UTF8, 0, zWideFilename, -1, zFilename, nByte, 0, 0);   
	if( nByte == 0 )   
	{   
		free(zFilename);   
		zFilename = 0;   
	}   
	return zFilename;   
}
wstring ANSIToUnicode( const string& str )
{
	int  len = 0;
	len = str.length();
	int  unicodeLen = ::MultiByteToWideChar( CP_ACP,
		0,
		str.c_str(),
		-1,
		NULL,
		0 );  
	wchar_t *  pUnicode;  
	pUnicode = new  wchar_t[unicodeLen+1];  
	memset(pUnicode,0,(unicodeLen+1)*sizeof(wchar_t));  
	::MultiByteToWideChar( CP_ACP,
		0,
		str.c_str(),
		-1,
		(LPWSTR)pUnicode,
		unicodeLen );  
	wstring  rt;  
	rt = ( wchar_t* )pUnicode;
	delete  pUnicode; 

	return  rt;  
}
wstring UTF8ToUnicode( const string& str )
{
	int  len = 0;
	len = str.length();
	int  unicodeLen = ::MultiByteToWideChar( CP_UTF8,
		0,
		str.c_str(),
		-1,
		NULL,
		0 );  
	wchar_t *  pUnicode;  
	pUnicode = new  wchar_t[unicodeLen+1];  
	memset(pUnicode,0,(unicodeLen+1)*sizeof(wchar_t));  
	::MultiByteToWideChar( CP_UTF8,
		0,
		str.c_str(),
		-1,
		(LPWSTR)pUnicode,
		unicodeLen );  
	wstring  rt;  
	rt = ( wchar_t* )pUnicode;
	delete  pUnicode; 

	return  rt;  
}
string UnicodeToUTF8( const wstring& str )
{
	char*     pElementText;
	int    iTextLen;
	// wide char to multi char
	iTextLen = WideCharToMultiByte( CP_UTF8,
		0,
		str.c_str(),
		-1,
		NULL,
		0,
		NULL,
		NULL );
	pElementText = new char[iTextLen + 1];
	memset( ( void* )pElementText, 0, sizeof( char ) * ( iTextLen + 1 ) );
	::WideCharToMultiByte( CP_UTF8,
		0,
		str.c_str(),
		-1,
		pElementText,iTextLen,0,0);
	string ret;
	ret=pElementText;
	delete pElementText;
	return ret;
}
string ansiToUtf8(string &str){
	 return UnicodeToUTF8(ANSIToUnicode(str));
}

bool isutf8(CHAR *str)
{
	int i = 0;
	int size = strlen(str);

	while(i < size)
	{
		int step = 0;
		if((str[i] & 0x80) == 0x00)
		{
			step = 1;
		}
		else if((str[i] & 0xe0) == 0xc0)
		{
			if(i + 1 >= size) return false;
			if((str[i + 1] & 0xc0) != 0x80) return false;

			step = 2;
		}
		else if((str[i] & 0xf0) == 0xe0)
		{
			if(i + 2 >= size) return false;
			if((str[i + 1] & 0xc0) != 0x80) return false;
			if((str[i + 2] & 0xc0) != 0x80) return false;

			step = 3;
		}
		else
		{
			return false;
		}

		i += step;
	}

	if(i == size) return true;

	return false;
}