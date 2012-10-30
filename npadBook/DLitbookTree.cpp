// DLitbookTree.cpp : ʵ���ļ�
//

#include "stdafx.h"

#include "DLitbookTree.h"
#include "Conndb.h"


// DLitbookTree

IMPLEMENT_DYNAMIC(DLitbookTree, CTreeCtrl)

DLitbookTree::DLitbookTree()
{

}

DLitbookTree::~DLitbookTree()
{
}


BEGIN_MESSAGE_MAP(DLitbookTree, CTreeCtrl)
	ON_WM_CREATE()
	ON_NOTIFY_REFLECT(NM_DBLCLK, &DLitbookTree::OnNMDblclk)
END_MESSAGE_MAP()



// DLitbookTree ��Ϣ�������



int DLitbookTree::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CTreeCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	classInit();
	
	return 0;
}

// ��ʼ��
BOOL DLitbookTree::classInit(void)
{
	this->DeleteAllItems();
	//���ͼʾ�б�

	Cil1.Create(16,16,ILC_COLORDDB|ILC_MASK,0,2);
	Cil1.Add(AfxGetApp()->LoadIcon(IDI_FILES0));
	Cil1.Add(AfxGetApp()->LoadIcon(IDI_FILES1));
	this->SetImageList(&Cil1,TVSIL_NORMAL);
	Cil1.SetBkColor(this->GetBkColor());
	//this->InsertItem(TVIF_TEXT|TVIF_PARAM|TVIF_IMAGE|TVIF_SELECTEDIMAGE,_T("���з���"),0,1,0,0,0,NULL,NULL);
	//this->SetExtendedStyle(0,TVS_HASLINES|TVS_LINESATROOT|TVS_HASBUTTONS|TVS_SHOWSELALWAYS|TVS_DISABLEDRAGDROP);

	CString cmdsql;
	cmdsql=_T("SELECT * from class order by lv ASC,parentid ASC,id ASC");
	CConndb getclass;
	getclass.search(cmdsql);
	HTREEITEM hItem,hSubItem;//�����
	if(!getclass.m_query->eof())
	{
		CString classname;
		int pid;
		int curlv=1;
		int curparentid=0;
		_variant_t var;
		DWORD cid;
		int i=0;
		while(!getclass.m_query->eof())
		{
			var=getclass.m_query->getIntField(_T("id"));
			if(var.vt!=VT_NULL)
				cid=var.ulVal;

			var=getclass.m_query->getStringField(_T("classname"));
			if(var.vt!=VT_NULL)
				classname=(LPCSTR)_bstr_t(var);
			var=getclass.m_query->getIntField(_T("parentid"));
			if(var.vt!=VT_NULL)
				pid=var.intVal;
			var=getclass.m_query->getIntField(_T("lv"));
			if(var.vt!=VT_NULL)
				curlv=var.intVal;

			if(pid!=0)
			{
				curlv--;//�õ�����ĸ��ڵ����
				if(pid!=curparentid)
				{
					int beginlv=1;
					hItem=FindItem(*this,this->GetRootItem(),pid,&curlv,&beginlv);
					curparentid=pid;
				}
				hSubItem = this->InsertItem(TVIF_TEXT|TVIF_PARAM|TVIF_IMAGE|TVIF_SELECTEDIMAGE,classname,0,1,0,0,cid,hItem,TVI_LAST);
			}
			else
			{
				this->InsertItem(TVIF_TEXT|TVIF_PARAM|TVIF_IMAGE|TVIF_SELECTEDIMAGE,classname,0,1,0,0,cid,TVI_ROOT,TVI_LAST);
			}


			i++;
			getclass.m_query->nextRow();
		}

	}

	return 0;
}

HTREEITEM DLitbookTree::FindItem(CTreeCtrl& tree, HTREEITEM item, DWORD strText,int* findLevel,int* curLevel)
{
	HTREEITEM hFind;	
	if(item == NULL)
		return NULL;

	while(item != NULL)
	{
		if(*findLevel==*curLevel)
		{
			//ֻ���ڵ���ָ�����ʱ,�űȽ�
			DWORD cc=tree.GetItemData(item);
			if(cc == strText)
				return item;
		}

		if(tree.ItemHasChildren(item))
		{
			(*curLevel)++;//��ȼ�һ
			item = tree.GetChildItem(item);
			hFind = FindItem(tree, item, strText,findLevel,curLevel);		
			if(hFind)
			{
				return hFind;		
			}
			else
			{
				item= tree.GetNextSiblingItem(tree.GetParentItem(item));
				(*curLevel)--;//��ȼ�һ
			}
		}
		else
		{
			item = tree.GetNextSiblingItem(item);
			if(item == NULL)
				return NULL;
		}		
	}

	return item;
}
void DLitbookTree::OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//CTreeCtrl* pTb=(CTreeCtrl*)GetDlgItem(IDC_RESULTCLASTREE);
	//int data;
	//data=this->GetItemData(this->GetSelectedItem());
	//searchClassId(data);
	*pResult = 0;
}
