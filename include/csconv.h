
/*!
 * \file csconv.h
*/

#ifndef _CHSET_CONV_
#define	_CHSET_CONV_

#include <iconv.h>

typedef	char			T_GB;
typedef	unsigned short	T_UC;
typedef unsigned char	T_UTF8;

class XGBUC
{
public:
	static int cv(const T_GB* pgb, size_t ngblen, T_UC* puc, size_t nuclen);
	~XGBUC();
protected:
	XGBUC();
	int conv(const T_GB* pgb, size_t ngblen, T_UC* puc, size_t nuclen);
	iconv_t m_tID;
};

class XUCGB
{
public:
	static int cv(const T_UC* puc, size_t nuclen, T_GB* pgb, size_t ngblen);
	~XUCGB();
protected:
	XUCGB();
	int conv(const T_UC* puc, size_t nuclen, T_GB* pgb, size_t ngblen);
	iconv_t	m_tID;
};

class XUCUTF8
{
public:
	static int cv(const T_UC* puc, size_t nuclen, T_UTF8* putf8, size_t nutf8len);
};

class XUTF8UC
{
public:
	static int cv(const T_UTF8* putf8, size_t nutf8len, T_UC* puc, size_t nuclen);
};

class EndianCheck
{
public:
	static int checkLittle();
};

#endif
