#pragma once
typedef struct sizeInfo{
	float x;
	float y;
	float cx;
	float cy;
	int method;
	int controlID;
	UINT mask;
	sizeInfo* nextNode;
}sizeInfo;
enum MPOSITION{M_NORMAL,M_BOTTOM_RELATIVE,M_TOP_RELATIVE,M_LEFTTOP_RELATIVE};
class DLDlgSizeing
{
public:
	DLDlgSizeing(void);
	DLDlgSizeing(HWND hwnd);
	~DLDlgSizeing(void);

	HWND m_hwnd;
	sizeInfo *m_head;
	sizeInfo* add(float x,float y,float cx,float cy,int ID,UINT mask=0,int posMethod=M_NORMAL);
	BOOL sizeChange(int width,int height);
	BOOL mushCY(int y);
	int mustCX;
	int mustCY;
	
};
