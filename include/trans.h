#ifndef    TRANS_H
#define    TRANS_H

#include <string>
#include <iostream>

class CTrans
{
public:
    /*!
     * \brief 解析并把字符串转化为整型数据
    */
    static int64_t STOI(const char* szValue);

    /*!
     * \brief 解析并把字符串转化为整型数据
    */
    static int64_t STOI(const std::string& sValue);

	/*!
     * \brief 解析并把字符串转化为整型数据
    */
    static long long STOI64(const char* szValue);

    /*!
     * \brief 解析并把字符串转化为整型数据
    */
    static long long STOI64(const std::string& sValue);

    /*!
     * \brief 解析并把字符串转化为浮点数据
    */
    static double STOF(const char* szValue);

    /*!
     * \brief 解析并把字符串转化为浮点数据
    */
    static double STOF(const std::string& sValue);

    /*!
     * \brief 把整型数据转化为字符串
     * \param[in] iValue: 待转换的数据
     * \param[in] nPrecision: 小数精度位数(在些无效)
     * \param[in] nWidth: 总位数
     * \param[in] nFill: 填充字符
     * \param[in] fmt: 其它IOS流标志,详细标志可参考IOS标志
     * \return string 转换好的字符串
    */
		static const std::string ITOS(int64_t iValue, std::streamsize nPrecision=-1, std::streamsize nWide=-1, char chFill=' ', std::ios::fmtflags fmt=std::ios::fixed);
		
    /*!
     * \brief 把浮点数据转化为字符串
     * \param[in] dValue: 待转换的数据
     * \param[in] nPrecision: 小数精度位数
     * \param[in] nWidth: 总位数
     * \param[in] nFill: 填充字符
     * \param[in] fmt: 其它IOS流标志,详细标志可参考IOS标志
     * \return string 转换好的字符串
    */
    static const std::string FTOS(double dValue, std::streamsize nPrecision=-1, std::streamsize nWide=-1, char chFill=' ', std::ios::fmtflags fmt=std::ios::fixed);
    
    /*!
     * \brief 把%XX数据转换成相应字符,如 "%41"->'A'
     * \param[in] szValue: %XX数据,以'%'开头X[0-9A-F]
     * \return char 相应的字符
    */
    static char HTOC(const char* szValue);

    /*!
     * \brief 把字符转换成%XX形式,如'A'->%41
     * \param[in] cValue: 字符数据[0-255]
     * \return string 相应字符串
    */
    static const std::string CTOH(char cValue);

	static int X2TOI(const char vx[2]);
	static int X4TOI(const char vx[4]);
	static char* X2TOC(const char vx[2], char vc[1]);
	static char* X4TOC(const char vx[4], char vc[2]);
	static char* ITOX2(int x, char vx[2]);
	static char* ITOX4(int x, char vx[4]);
	static char* CTOX2(const char vc[1], char vx[2]);
	static char* CTOX4(const char vc[2], char vx[4]);
};

inline std::string operator + (const std::string& _s, const int64_t& _i)
{
	return _s+CTrans::ITOS(_i);
}

inline std::string operator + (const int64_t& _i, const std::string& _s)
{
	return CTrans::ITOS(_i)+_s;
}

#endif

