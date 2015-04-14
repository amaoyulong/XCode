
#include <iomanip>
#include <cstdlib>
#include <sstream>

#include "trans.h"
#include "csconv.h"

int64_t CTrans::STOI(const char* szValue)
{
	int64_t iTmp = szValue == NULL ? 0 : atoll(szValue);
	return iTmp < INT_MIN ? INT_MIN : (iTmp > UINT_MAX ? UINT_MAX : iTmp);
}

int64_t CTrans::STOI(const std::string& sValue)
{
	return STOI(sValue.c_str());
}

long long CTrans::STOI64(const char* szValue)
{
	return szValue == NULL ? 0 : atoll(szValue);
}

long long CTrans::STOI64(const std::string& sValue)
{
	return atoll(sValue.c_str());
}
	
double CTrans::STOF(const char* szValue)
{
	return szValue == NULL ? 0 : atof(szValue);
}

double CTrans::STOF(const std::string& sValue)
{
	return atof(sValue.c_str());
}

const std::string CTrans::ITOS(int64_t iValue, std::streamsize nPrecision, std::streamsize nWide, char chFill, std::ios::fmtflags fmt)
{
	std::string sValue;
	std::stringstream strm;
	strm.setf(fmt);
	strm<<std::setprecision(nPrecision)<<std::setw(nWide)<<std::setfill(chFill)<<iValue;
	strm>>sValue;
	return sValue;
}

const std::string CTrans::FTOS(double dValue, std::streamsize nPrecision, std::streamsize nWide, char chFill, std::ios::fmtflags fmt)
{
	std::string sValue;
	std::stringstream strm;
	strm.setf(fmt);
	strm<<std::setprecision(nPrecision)<<std::setw(nWide)<<std::setfill(chFill)<<dValue;
	strm>>sValue;
	return sValue;
}


char CTrans::HTOC(const char* szValue)
{
	unsigned char c1 = (szValue[1] >= 'A') ? (szValue[1] - ('A' - 10)) : (szValue[1] - '0');
	unsigned char c2 = (szValue[2] >= 'A') ? (szValue[2] - ('A' - 10)) : (szValue[2] - '0');
	return (c1 <<= 4) += c2;
}


/*  
const std::string CTrans::CTOH(char cValue)
{
	static char MAPX[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
	if (cValue < 0 || cValue >= '0' && cValue <= '9' || cValue >= 'A' && cValue <= 'Z' || cValue >= 'a' && cValue <= 'z')
	{
		return std::string(1, cValue);
	}
	std::string sValue("%");
	sValue += MAPX[(unsigned char)cValue>>4];
	sValue += MAPX[cValue&0x0F];
	return sValue;
}
*/

// 因版本兼容问题，本函数暂只针对COOKIE和URL做最弱过滤
const std::string CTrans::CTOH(char cValue)
{
	static char MAPX[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
	if ((cValue >= 0 && cValue <= '\40') || cValue==';' || cValue=='=' || cValue=='%' || cValue=='?' || cValue=='&')
	{
		std::string sValue("%");
		sValue += MAPX[(unsigned char)cValue>>4];
		sValue += MAPX[cValue&0x0F];
		return sValue;
	}
	return std::string(1, cValue);
}

int CTrans::X2TOI(const char vx[2])
{
	static int MAPX[256] = 
	{
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	};
	return (MAPX[((const unsigned char*)vx)[0]]<<0x04)|(MAPX[((const unsigned char*)vx)[1]]);
}

int CTrans::X4TOI(const char vx[4])
{
	return (X2TOI(vx)<<0x08)|(X2TOI(vx+2));
}

char* CTrans::X2TOC(const char vx[2], char vc[1])
{
	vc[0] = (char)X2TOI(vx);
	return vc;
}

char* CTrans::X4TOC(const char vx[4], char vc[2])
{
	T_UC tUC = (T_UC)X4TOI(vx);
	int iNum = XUCGB::cv(&tUC, 1, vc, 2);
	if (tUC != 0)
	{
		if (1 == iNum)
		{
			vc[1] = '?';
		}
		else if (2 != iNum)
		{
			vc[0] = vc[1] = '?';
		}
	}
	return vc;
}

char* CTrans::ITOX2(int x, char vx[2])
{
	static char MAPX[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
	vx[0] = MAPX[(unsigned char)x>>4];
	vx[1] = MAPX[x&0x0F];
	return vx;
}

char* CTrans::ITOX4(int x, char vx[4])
{
	ITOX2((unsigned short)(x&0xFF00)>>8, vx);
	ITOX2(x&0xFF, vx+2);
	return vx;
}

char* CTrans::CTOX2(const char vc[1], char vx[2])
{
	return ITOX2(vc[0], vx);
}

char* CTrans::CTOX4(const char vc[2], char vx[4])
{
	T_UC tUC = 0;
	if (XGBUC::cv(vc, 2, &tUC, 1)<0)
	{
		tUC = 32;
	}

	return ITOX4(tUC, vx);
}

