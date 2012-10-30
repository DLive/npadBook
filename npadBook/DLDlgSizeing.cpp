#include "StdAfx.h"
#include "DLDlgSizeing.h"

DLDlgSizeing::DLDlgSizeing(void)
{
}
DLDlgSizeing::DLDlgSizeing(HWND hwnd)
{
	m_hwnd=hwnd;
	mustCY=0;
	mustCX=0;
	m_head=NULL;
}

DLDlgSizeing::~DLDlgSizeing(void)
{
}

sizeInfo* DLDlgSizeing::add(float x,float y,float cx,float cy,int ID,UINT mask,int posMethod)
{
	
	sizeInfo *tmp=new sizeInfo();
	tmp->x=x;
	tmp->y=y;
	tmp->cx=cx;
	tmp->cy=cy;
	tmp->controlID=ID;
	tmp->mask=mask;
	tmp->nextNode=NULL;
	tmp->method=posMethod;
	if(m_head==NULL){
		m_head=tmp;
	}
	else{
		tmp->nextNode=m_head;
		m_head=tmp;
	}
	return tmp;
}
BOOL DLDlgSizeing::mushCY(int y){
	
		mustCY+=y;
	return TRUE;
}
BOOL DLDlgSizeing::sizeChange(int width,int height)
{
	
	if(!m_hwnd)
		return FALSE;
	sizeInfo* tmp=m_head;
	int x,y,cx,cy;
	while(tmp){
		HWND th=GetDlgItem(m_hwnd,tmp->controlID);
		if(!th){
			tmp=tmp->nextNode;
			continue;
		}
		if(tmp->method==M_NORMAL){
			 x=width*tmp->x;
			 y=tmp->y;//偷懒一下  height*
			 cx=(width-mustCX)*tmp->cx;
			 cy=(height-mustCY)*tmp->cy;
		}else if(tmp->method==M_BOTTOM_RELATIVE){
			//底部减去相对高度
			x=tmp->x;
			y=height-tmp->y;
		}
		
		
		SetWindowPos(th,HWND_BOTTOM,x,y,cx,cy,tmp->mask);
		tmp=tmp->nextNode;
	}
}