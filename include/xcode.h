
/*!
 * \file xcode.h
 * \author yulongli
 * \date 2012-02-22
*/

#ifndef	__XCODE_H__
#define	__XCODE_H__

#include <string>
#include "csconv.h"

class CXCode
{
public:
	enum enCharSetType
	{
		CHARSET_BEGIN		= 0,
		CHARSET_GBS			= 0,
		CHARSET_UTF8		= 1,
		CHARSET_UCS2		= 2,

		CHARSET_END
	};

public:
	CXCode(enCharSetType chCharSet)
	{
		 m_charSet =  s_charSet;
		 s_charSet =  chCharSet;
	}
	~CXCode()
	{
		s_charSet =  m_charSet;
	}	
	static enCharSetType GetCharSet(void)
	{
		return s_charSet;
	}

public:
	/*! \brief ���ַ������빦����JavaScript.escape()���� */
	static std::string escape(const std::string& sData);

	/*! \brief ���ַ���������н��빦����JavaScript.unescape()���� */
	static std::string unescape(const std::string& sData);

	/*! \brief ���ַ���ת��Unicode2�����ʽ */
	static std::string UCS2(const std::string& sData);

	/*! \brief ���ַ������빦����JavaScript.encodeURIComponent()���ƣ�ע�⣬���������е�unicode�ַ�������������� */
	static std::string encodeURIComponent(const std::string& sData);

		/*! \brief ��encodeURIComponent��Ӧ�Ľ��빦�� */
	static std::string decodeURIComponent(const std::string& sData);
		

	/*! \brief ��json���ݱ����������,ͬJavaScript.JSON.stringify()���ƣ�����������ǰ̨��̫һ����16���Ƶı�ʾͳһ�ô�дA-F��ǰ̨��Сдa-f*/
	static std::string encodeJSONComponent(const std::string& sData);

	/*! \brief ���ַ����������XML���빦�� */
	static std::string encodeXMLComponent(const std::string& sData);

	static int VALIDGBCode(const std::string& sData, std::string& sValidData);

public:
	/*! \brief һϵ�б���ת����������������Դ*/
	static std::string GBS2UCS(const std::string &sData);
	static std::string UCS2GBS(const std::string &sData);
	static std::string UCS2UTF8(const std::string &sData);
	static std::string UTF82UCS(const std::string &sData);
	static std::string GBS2UTF8(const std::string &sData);
	static std::string UTF82GBS(const std::string &sData);
protected:


private:
	/*! \brief ���ַ�����Unicode2�����ʽת����������ʽ */
	static std::string decodeUCS2(const std::string& sData);

	/*! \brief ��utf8�ַ���encodeURL,��encodeURIComponent���м亯��  */
	static std::string encodeURIUTF8Component(const std::string& sData);

	static char x2c(const char *what)
	{
		char digit;

		digit = (what[0] >= 'A' ? (what[0] - 'A') + 10 : (what[0] - '0'));
		digit *= 16;
		digit += (what[1] >= 'A' ? (what[1] - 'A') + 10 : (what[1] - '0'));
		
		return digit;
	}

private:
	static enCharSetType s_charSet;
	enCharSetType m_charSet;	
};

#endif
