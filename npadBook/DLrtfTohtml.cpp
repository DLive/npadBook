// DLrtfTohtml.cpp : ʵ���ļ�
//

#include "stdafx.h"

#include "DLrtfTohtml.h"


// CDLrtfTohtml

CDLrtfTohtml::CDLrtfTohtml()
{
}

CDLrtfTohtml::~CDLrtfTohtml()
{
}
void CDLrtfTohtml::ansitounicode()
{
	//char pbuf[]="\'ce\'d2\'c0\'b4\'c1\'cb";
	//AfxmessageBox("%s","0xce0xd20xc00xb40xc10xcb"
	//CString content;
	//size_t len=strlen(pbuf)+1;
	// int wlen=MultiByteToWideChar(CP_OEMCP,0,pbuf,len,NULL,0);
	// MultiByteToWideChar(CP_ACP,0,pbuf,len,content.GetBuffer(),wlen);
	 //unsigned char *src = "\'ce\'d2\'c0\'b4\'c1\'cb"; /* ��ת�����ִ� */
  //  unsigned char dst[256] = {0}; /* ת��������� */
  //  unsigned char buf[1024] = {0}; /* ��ʽ��ת������ִ� */
  //  size_t src_len = strlen(src);
  //  size_t dst_len = sizeof(dst);
  //  unsigned char *in = src;
  //  unsigned char *out = dst;
  //  
  //  iconv_t cd;
  //  int i;  
  //  int j;  
  //  
  //  cd = iconv_open("CP936", "UNICODE"); /* ��GB2312�ַ���ת��ΪUTF-8�ַ��� */
  //  if ((iconv_t)-1 == cd)
  //  {
  //      return -1;
  //  }

  //  printf("src: %s\n", src);
  //  iconv(cd, &in, &src_len, &out, &dst_len); /* ִ��ת�� */
}


// CDLrtfTohtml ��Ա����
