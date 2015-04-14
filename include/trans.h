#ifndef    TRANS_H
#define    TRANS_H

#include <string>
#include <iostream>

class CTrans
{
public:
    /*!
     * \brief ���������ַ���ת��Ϊ��������
    */
    static int64_t STOI(const char* szValue);

    /*!
     * \brief ���������ַ���ת��Ϊ��������
    */
    static int64_t STOI(const std::string& sValue);

	/*!
     * \brief ���������ַ���ת��Ϊ��������
    */
    static long long STOI64(const char* szValue);

    /*!
     * \brief ���������ַ���ת��Ϊ��������
    */
    static long long STOI64(const std::string& sValue);

    /*!
     * \brief ���������ַ���ת��Ϊ��������
    */
    static double STOF(const char* szValue);

    /*!
     * \brief ���������ַ���ת��Ϊ��������
    */
    static double STOF(const std::string& sValue);

    /*!
     * \brief ����������ת��Ϊ�ַ���
     * \param[in] iValue: ��ת��������
     * \param[in] nPrecision: С������λ��(��Щ��Ч)
     * \param[in] nWidth: ��λ��
     * \param[in] nFill: ����ַ�
     * \param[in] fmt: ����IOS����־,��ϸ��־�ɲο�IOS��־
     * \return string ת���õ��ַ���
    */
		static const std::string ITOS(int64_t iValue, std::streamsize nPrecision=-1, std::streamsize nWide=-1, char chFill=' ', std::ios::fmtflags fmt=std::ios::fixed);
		
    /*!
     * \brief �Ѹ�������ת��Ϊ�ַ���
     * \param[in] dValue: ��ת��������
     * \param[in] nPrecision: С������λ��
     * \param[in] nWidth: ��λ��
     * \param[in] nFill: ����ַ�
     * \param[in] fmt: ����IOS����־,��ϸ��־�ɲο�IOS��־
     * \return string ת���õ��ַ���
    */
    static const std::string FTOS(double dValue, std::streamsize nPrecision=-1, std::streamsize nWide=-1, char chFill=' ', std::ios::fmtflags fmt=std::ios::fixed);
    
    /*!
     * \brief ��%XX����ת������Ӧ�ַ�,�� "%41"->'A'
     * \param[in] szValue: %XX����,��'%'��ͷX[0-9A-F]
     * \return char ��Ӧ���ַ�
    */
    static char HTOC(const char* szValue);

    /*!
     * \brief ���ַ�ת����%XX��ʽ,��'A'->%41
     * \param[in] cValue: �ַ�����[0-255]
     * \return string ��Ӧ�ַ���
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

