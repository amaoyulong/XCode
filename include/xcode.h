
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
	/*! \brief 对字符串编译功能与JavaScript.escape()类似 */
	static std::string escape(const std::string& sData);

	/*! \brief 对字符串编码进行解码功能与JavaScript.unescape()类似 */
	static std::string unescape(const std::string& sData);

	/*! \brief 将字符串转成Unicode2编码格式 */
	static std::string UCS2(const std::string& sData);

	/*! \brief 对字符串编码功能与JavaScript.encodeURIComponent()类似，注意，并不是所有的unicode字符都可以正常输出 */
	static std::string encodeURIComponent(const std::string& sData);

		/*! \brief 与encodeURIComponent对应的解码功能 */
	static std::string decodeURIComponent(const std::string& sData);
		

	/*! \brief 对json数据编码后可以输出,同JavaScript.JSON.stringify()类似，不过这里与前台不太一样，16进制的表示统一用大写A-F，前台是小写a-f*/
	static std::string encodeJSONComponent(const std::string& sData);

	/*! \brief 对字符串编码进行XML编码功能 */
	static std::string encodeXMLComponent(const std::string& sData);

	static int VALIDGBCode(const std::string& sData, std::string& sValidData);

public:
	/*! \brief 一系列编码转化函数，不区分来源*/
	static std::string GBS2UCS(const std::string &sData);
	static std::string UCS2GBS(const std::string &sData);
	static std::string UCS2UTF8(const std::string &sData);
	static std::string UTF82UCS(const std::string &sData);
	static std::string GBS2UTF8(const std::string &sData);
	static std::string UTF82GBS(const std::string &sData);
protected:


private:
	/*! \brief 将字符串由Unicode2编码格式转化成其他格式 */
	static std::string decodeUCS2(const std::string& sData);

	/*! \brief 将utf8字符串encodeURL,是encodeURIComponent的中间函数  */
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
