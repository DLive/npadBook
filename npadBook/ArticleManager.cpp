#include "StdAfx.h"
#include "ArticleManager.h"

CArticleManager::CArticleManager(void)
{
	m_head=NULL;
}

CArticleManager::~CArticleManager(void)
{

}
//事先检查ID是否存在
articleInfo* CArticleManager::add_ID(int ID,int bufID,TCHAR * filePath,int cID){
	articleInfo* tmp=find(ID);
	if(!tmp){
		return add(ID,bufID,filePath,cID);
	}
	return tmp;
}
//事先检查ID是否存在
articleInfo* CArticleManager::add_bufferID(int ID,int bufID,TCHAR * filePath,int cID){
	articleInfo* tmp=find(bufID,FBufferID);
	if(!tmp){
		return add(ID,bufID,filePath,cID);
	}
	return tmp;
}
//只添加
articleInfo* CArticleManager::add(int ID,int bufID,TCHAR * filePath,int cID){
	articleInfo *tmp=new articleInfo();
	tmp->ID=ID;
	tmp->bufferID=bufID;
	tmp->cID=cID;
	tmp->isSavetoDb=TRUE;
	tmp->isSavetoLocal=TRUE;
	tmp->isTemp=FALSE;
	lstrcpy(tmp->filePath,filePath);
	if(m_head==NULL){
		m_head=tmp;
	}
	else{
		tmp->nextNode=m_head;
		m_head=tmp;
	}
	return tmp;
}
BOOL CArticleManager::del(int info,int type)
{
	if(m_head!=NULL){
		articleInfo *pNode=m_head;
		articleInfo *parentNode=pNode;
		while(pNode!=NULL){
			switch (type)
			{
			case FID:
				if(pNode->ID==info){
					if(pNode->nextNode)
						parentNode->nextNode=pNode->nextNode;
					if(pNode==m_head){
						if(pNode->nextNode==NULL)
							m_head=NULL;
						else
							m_head=pNode->nextNode;
					}
					delete pNode;
					return TRUE;
				}
				else{
					parentNode=pNode;
					if(pNode)
						pNode=pNode->nextNode;

				}
				break;
			case FcID:
				if(pNode->cID==info){
					if(pNode->nextNode)
						parentNode->nextNode=pNode->nextNode;
					if(pNode==m_head){
						m_head=pNode->nextNode;
					}
					delete pNode;
					return TRUE;
				}
				else{
					parentNode=pNode;
					if(pNode)
						pNode=pNode->nextNode;

				}
				break;
			case FBufferID:
				if(pNode->bufferID==info){
					if(pNode->nextNode)
						parentNode->nextNode=pNode->nextNode;
					if(pNode==m_head){
						m_head=pNode->nextNode;
					}
					delete pNode;
					return TRUE;
				}
				else{
					parentNode=pNode;
					if(pNode)
						pNode=pNode->nextNode;
					
				}
				break;
			}

		}
	}
	else{
		return NULL;
	}
}
articleInfo *CArticleManager::find(int info,int findType){
	if(m_head!=NULL){
		articleInfo *pNode=m_head;
		while(pNode!=NULL){
			switch (findType)
			{
			case FID:
				if(pNode->ID==info)
					return pNode;
				else
					pNode=pNode->nextNode;
				break;
			case FcID:
				if(pNode->cID==info)
					return pNode;
				else
					pNode=pNode->nextNode;
				break;
			case FBufferID:
				if(pNode->bufferID==info)
					return pNode;
				else
					pNode=pNode->nextNode;
				break;
			}
			
		}
	}
	else{
		return NULL;
	}
	return NULL;
} 
articleInfo *CArticleManager::find(LPCTSTR filePath){
	if(m_head!=NULL){
		articleInfo *pNode=m_head;
		while(pNode!=NULL){
			if(lstrcmp(pNode->filePath,filePath)==0)
				return pNode;
			else
				pNode=pNode->nextNode;
		}
	}
	else{
		return NULL;
	}
	return NULL;
} 


