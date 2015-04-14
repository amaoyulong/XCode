
/*!
 * \file csconv.cpp
*/

#include "csconv.h"

template <class _CS1, class _CS2>
static int csconv(iconv_t tID, const _CS1* pcs1, size_t nlen1, _CS2* pcs2, size_t nlen2)
{
	size_t nleft1 = nlen1*sizeof(_CS1);
	size_t nleft2 = nlen2*sizeof(_CS2);
	char* cpcs1 = (char*)pcs1;
	char* cpcs2 = (char*)pcs2;
	size_t nConv = iconv(tID, &cpcs1, &nleft1, &cpcs2, &nleft2);
	if (nConv==(size_t)-1)
	{
		return -1;
	}
	return (nlen2-nleft2/sizeof(_CS2));
}

XGBUC::XGBUC()
{
	//m_tID = iconv_open("UCS-2", "GBK");
	if (EndianCheck::checkLittle()==0){
		m_tID = iconv_open("UCS-2LE", "GB18030");  // 支持更多的字符
	}else {
		m_tID = iconv_open("UCS-2BE", "GB18030");  // 支持更多的字符
	}
}
XGBUC::~XGBUC()
{
	iconv_close(m_tID);
}
int XGBUC::conv(const T_GB* pgb, size_t ngblen, T_UC* puc, size_t nuclen)
{
	return csconv(m_tID, pgb, ngblen, puc, nuclen);
}
int XGBUC::cv(const T_GB* pgb, size_t ngblen, T_UC* puc, size_t nuclen)
{
	static XGBUC s_oGbUc;
	return s_oGbUc.conv(pgb, ngblen, puc, nuclen);
}

XUCGB::XUCGB()
{
	if (EndianCheck::checkLittle()==0){
		m_tID = iconv_open("GB18030", "UCS-2LE");  // 支持更多的字符
	}else {
		m_tID = iconv_open("GB18030", "UCS-2BE");  // 支持更多的字符
	}
}
XUCGB::~XUCGB()
{
	iconv_close(m_tID);
}
int XUCGB::conv(const T_UC* puc, size_t nuclen, T_GB* pgb, size_t ngblen)
{
	return csconv(m_tID, puc, nuclen, pgb, ngblen);
}
int XUCGB::cv(const T_UC* puc, size_t nuclen, T_GB* pgb, size_t ngblen)
{
	static XUCGB s_oUcGb;
	return s_oUcGb.conv(puc, nuclen, pgb, ngblen);
}


/*
 *  unicode 与utf8的转化关系
 *  0000 0000 - 0000 007F		0XXX XXXX
 *  0000 0080 - 0000 07FF		110X XXXX 10XX XXXX
 *  0000 0800 - 0000 FFFF		1110 XXXX 10XX XXXX 10XX XXXX
 */

int XUCUTF8::cv(const T_UC* puc, size_t nuclen, T_UTF8* putf8, size_t nutf8len)
{
	const T_UC* ucbpos = puc;
	const T_UC* ucepos = puc+nuclen;
	T_UTF8* utf8bpos = putf8;
	T_UTF8* utf8epos = putf8+nutf8len;
	while (ucbpos< ucepos && utf8bpos<utf8epos)
	{
		if (*ucbpos < 0x80)
		{
			*utf8bpos++ = *ucbpos++;
		}
		else if (*ucbpos < 0x800)
		{
			if (utf8epos-utf8bpos < 2)
			{
				break;
			}
			*utf8bpos++ = ((*ucbpos&0x7C0)>>6) | 0xC0;
			*utf8bpos++ = (*ucbpos++ & 0x3F) | 0x80;
		}
		else
		{
			if (utf8epos-utf8bpos < 3)
			{
				break;
			}
			*utf8bpos++ = ((*ucbpos&0xF000)>>12) | 0xE0;
			*utf8bpos++ = ((*ucbpos&0x0FC0)>>6) | 0x80;
			*utf8bpos++ = ((*ucbpos++&0x3F)) | 0x80;
		}
	}
	return (utf8bpos-putf8);
}


int XUTF8UC::cv(const T_UTF8* putf8, size_t nutf8len, T_UC* puc, size_t nuclen)
{
	const T_UTF8 * utf8bpos = putf8;
	const T_UTF8 * utf8epos = putf8 + nutf8len;

	T_UC * ucbpos = puc;
	T_UC * ucepos = puc + nuclen;

	while(utf8bpos<utf8epos && ucbpos< ucepos)
	{
		if (*utf8bpos < 0x80)	//asc
		{
			*ucbpos++ = *utf8bpos++;
		}
		else if ( (*utf8bpos&0xE0) == 0xE0 )	//三個字節
		{
			if (ucepos - ucbpos < 2)
			{
				break;
			}			

			*ucbpos = (T_UC(*utf8bpos++ & 0x0F)) << 12;
			*ucbpos |= (T_UC(*utf8bpos++ & 0x3F)) << 6;
			*ucbpos++ |= (T_UC(*utf8bpos++ & 0x3F));
		}
		else if ((*utf8bpos&0xC0) == 0xC0)
		{			
			if (ucepos - ucbpos < 2)
			{
				break;
			}										
			*ucbpos = (T_UC(*utf8bpos++ & 0x1F)) << 6;
			*ucbpos++ |= (T_UC(*utf8bpos++ & 0x3F));
		}
		else
		{
			utf8bpos++;		//暂时只支持gb2312，两个字节的特殊字符，utf8最多用3个字节存储
		}
	}
	return 	ucbpos-puc;
}

int EndianCheck::checkLittle(){
	int number = 1;
    if(*(char *)&number)
        return 0;
    
    return -1;
}



