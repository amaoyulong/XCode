
#include "xcode.h"
#include "csconv.h"
#include "trans.h"


CXCode::enCharSetType CXCode::s_charSet = CXCode::CHARSET_GBS;



std::string CXCode::GBS2UCS(const std::string &sData)
{
	CXCode x(CHARSET_GBS);
	return UCS2(sData);
}

std::string CXCode::UCS2GBS(const std::string &sData)
{
	CXCode x(CHARSET_GBS);
	return decodeUCS2(sData);
}

std::string CXCode::UTF82UCS(const std::string &sData)
{
	CXCode x(CHARSET_UTF8);
	return UCS2(sData);
}

std::string CXCode::UCS2UTF8(const std::string &sData)
{
	CXCode x(CHARSET_UTF8);
	return decodeUCS2(sData);
}

std::string CXCode::GBS2UTF8(const std::string &sData)
{
	return 	UCS2UTF8(GBS2UCS(sData));
}

std::string CXCode::UTF82GBS(const std::string &sData)
{
	return 	UCS2GBS(UTF82UCS(sData));
}


// return char string ascii
static std::string __encodeBase(const bool esc[256], const T_UC* bpos, const T_UC* epos, const char* prefix2, const char* prefix4, const char* subfix)
{
	int bSize2 = strlen(prefix2);  // %xx format
	int bSize4 = strlen(prefix4);	//%uxxxx format
	int eSize = strlen(subfix);
	
	char v2[16] = {0};
	char v4[16] = {0};
	char* p2 = v2+bSize2;
	char* p4 = v4+bSize4;

	memcpy(v2, prefix2, bSize2);
	memcpy(v4, prefix4, bSize4);
	memcpy(p2+2, subfix, eSize);
	memcpy(p4+4, subfix, eSize);

	int s2 = bSize2+2+eSize;
	int s4 = bSize4+4+eSize;

	std::string sValue((bSize4+eSize+4)*(epos-bpos), 0);
	char* tpos = &sValue[0];

	while (bpos < epos)
	{
		if (*bpos & 0xff00)
		{
			CTrans::ITOX4(*bpos, p4);
			memcpy(tpos, v4, s4);
			tpos += s4;
			++bpos;
		}
		else if (esc[*bpos & 0xff])
		{
			CTrans::ITOX2(*bpos, p2);
			memcpy(tpos, v2, s2);
			tpos += s2;
			++bpos;
		}
		else
		{
			*tpos++ = *bpos++;
		}
	}
	sValue.resize(tpos - &sValue[0]);

	return sValue;
}

std::string CXCode::escape(const std::string& sData)
{
	const static bool s_esc[256] =
	{
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
	};

	std::string sUCValue = UCS2(sData);

	const T_UC* bpos = (T_UC*)&sUCValue[0];
	const T_UC* epos = bpos + (sUCValue.size()/sizeof(T_UC));

	std::string sValue = __encodeBase(s_esc, bpos, epos, "%", "%u", "");

	if (CXCode::GetCharSet()==CXCode::CHARSET_UCS2)
	{
		CXCode x2(CXCode::CHARSET_UTF8);
		return UCS2(sValue);
	}

	return sValue;
}


std::string CXCode::UCS2(const std::string& sData)
{
	T_UC* tUC = NULL;
	int nUClen = 0;

	if (sData.size()==0)
	{
		return sData;
	}

	if (CXCode::GetCharSet()==CXCode::CHARSET_UCS2)
	{
		return sData;
	}

	if (CXCode::GetCharSet()==CXCode::CHARSET_UTF8)
	{
		tUC = new T_UC[sData.size()];
		nUClen = XUTF8UC::cv((T_UTF8*)&sData[0], sData.size(), tUC, sData.size());

	}
	else if (CXCode::GetCharSet()==CXCode::CHARSET_GBS)
	{
		tUC = new T_UC[sData.size()];
		nUClen = XGBUC::cv((T_GB*)&sData[0], sData.size(), tUC, sData.size());
	}

	if (nUClen < 0)
	{
		nUClen = 0;
	}
	std::string sValue((char*)tUC, nUClen*sizeof(T_UC));	//如果nUClen=0的話，tUC是個野指針.問題不大

	if (tUC != NULL)
	{
		delete[] tUC;
	}
	return sValue;
}

std::string CXCode::encodeXMLComponent(const std::string& sData)
{
	const static bool s_esc[256] =
	{
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
	};

	std::string sUCValue = UCS2(sData);
	T_UC* bpos = (T_UC*)&sUCValue[0];
	const T_UC* epos = bpos + (sUCValue.size()/sizeof(T_UC));

	while (bpos < epos)
	{
		if (*bpos < 32 && *bpos!=13 && *bpos!=10) 
		{
			*bpos = T_UC('?');
		}
		++bpos;
	}
	bpos = (T_UC*)&sUCValue[0];

	std::string sValue = __encodeBase(s_esc, bpos, epos, "&#x", "&#x", ";");

	// if (CXCode::GetCharSet()==CXCode::CHARSET_UCS2)
	// {
	// 	CXCode x2(CXCode::CHARSET_UTF8);
	// 	return UCS2(sValue);
	// }

	return sValue;
}


std::string CXCode::unescape(const std::string& sData)
{
	struct HEX
	{
		static bool isHex(T_UC ch)
		{
			return ((ch>='0' && ch<='9') || (ch>='A' && ch<='F') || (ch>='a' && ch<='f'));
		}
	};


	std::string sUCValue = UCS2(sData);
	std::string sValue(sUCValue.size(), 0);

	T_UC *ucbpos = (T_UC *)&sUCValue[0];
	T_UC *ucepos = ucbpos + sUCValue.size()/sizeof(T_UC);

	T_UC *ucbResult =  (T_UC *)&sValue[0];
//	T_UC *uceResult =  ucbResult + sValue.size() / sizeof(T_UC);

	#define HEXUCTOI(uc) ((uc >= 'a')? (uc - 'a' + 10) : (uc >= 'A') ? (uc - 'A' + 10) : (uc - '0'))

	while (ucbpos < ucepos)
	{
		if (*ucbpos != 0x25)		// %
		{
			*ucbResult++ = *ucbpos++;
		}
		else if((*(ucbpos+1)=='u' || *(ucbpos+1)=='U') && (ucepos>ucbpos+5) && HEX::isHex(*(ucbpos+2)) && HEX::isHex(*(ucbpos+3)) && HEX::isHex(*(ucbpos+4)) && HEX::isHex(*(ucbpos+5)))
		{
			*ucbResult++ = (HEXUCTOI(*(ucbpos+2))<<12) | (HEXUCTOI(*(ucbpos+3))<<8) | (HEXUCTOI(*(ucbpos+4))<<4) | (HEXUCTOI(*(ucbpos+5)));
			ucbpos=ucbpos+6;
		}
		else if ((ucepos>ucbpos+2) && HEX::isHex(*(ucbpos+1)) && HEX::isHex(*(ucbpos+2)) )
		{
			*ucbResult++ = (HEXUCTOI(*(ucbpos+1))<<4) | (HEXUCTOI(*(ucbpos+2)));
			ucbpos=ucbpos+3;
		}
		else
		{
			*ucbResult++ = *ucbpos++;
		}
	}
	sValue.resize((ucbResult-(T_UC *)&sValue[0])*sizeof(T_UC));

	return decodeUCS2(sValue);
}

std::string CXCode::decodeUCS2(const std::string& sData)
{
	if (CXCode::GetCharSet()==CXCode::CHARSET_UCS2)
	{
		return sData;
	}

	std::string sValue(sData.size()/sizeof(T_UC)*4, 0);
	int nUClen = sData.size() / sizeof(T_UC);
	int nlen = 0;

	if (CXCode::GetCharSet()==CXCode::CHARSET_UTF8)
	{
		nlen = XUCUTF8::cv((T_UC*)&sData[0], nUClen, (T_UTF8*)&sValue[0], sValue.size());
		if (nlen<0) nlen=0;
		sValue.resize(nlen * sizeof(T_UTF8));
	}
	else if (CXCode::GetCharSet()==CXCode::CHARSET_GBS)
	{
		nlen = XUCGB::cv((T_UC*)&sData[0], nUClen, (T_GB*)&sValue[0], sValue.size());
		if (nlen<0) nlen=0;
		sValue.resize(nlen * sizeof(T_GB));
	}
	
	return sValue;
}


/*std::string CXCode::encodeJSONComponent(const std::string& sData)
{
	const static bool s_esc[256] =
	{
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
	};

	std::string sUCValue = UCS2(sData);
	const T_UC* bpos = (T_UC*)&sUCValue[0];
	const T_UC* epos = bpos + (sUCValue.size()/sizeof(T_UC));

	std::string sValue = __encodeBase(s_esc, bpos, epos, "\\u00", "\\u", "");
		   
	if (CXCode::GetCharSet()==CXCode::CHARSET_UCS2)
	{
		return UCS2(sValue);
	}

	return sValue;
} */

std::string CXCode::encodeJSONComponent(const std::string& sData)
{
	std::string sUCValue = UCS2(sData);
	T_UC* bpos = (T_UC*)&sUCValue[0];
	const T_UC* epos = bpos + (sUCValue.size()/sizeof(T_UC));

	T_UC * tUC = new T_UC[sData.size() * 4];
	T_UC * ptUC = tUC;

	while (bpos < epos)
	{
		if (*bpos == '\\' || *bpos== '\"' )
		{
			*ptUC++ = '\\';
			*ptUC++ = *bpos;
		}
		else if (*bpos == '\n')
		{
			*ptUC++ = '\\';
			*ptUC++ = 'n';
		}
		else if (*bpos == '\r')
		{
			*ptUC++ = '\\';
			*ptUC++ = 'r';
		}
		else if (*bpos == '\b')
		{
			*ptUC++ = '\\';
			*ptUC++ = 'b';
		}
		else if (*bpos == '\f')
		{
			*ptUC++ = '\\';
			*ptUC++ = 'f';
		}
		else if (*bpos == '\t')
		{
			*ptUC++ = '\\';
			*ptUC++ = 't';
		}
		else
		{
			*ptUC++ = *bpos;
		}
		
		++bpos;
	}
	bpos = tUC;
	epos = ptUC;

	const static bool s_esc[256] =
	{
		1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
	};

	std::string sValue = __encodeBase(s_esc, bpos, epos, "\\u00", "\\u", "");

	if (tUC != NULL)
	{
		delete[] tUC;
	}
		   
	// if (CXCode::GetCharSet()==CXCode::CHARSET_UCS2)
	// {
	// 	CXCode x2(CXCode::CHARSET_UTF8);
	// 	return UCS2(sValue);
	// }

	return sValue;
}


std::string CXCode::encodeURIComponent(const std::string& sData)
{
	if (CXCode::GetCharSet()==CXCode::CHARSET_UTF8)
	{
		return 	encodeURIUTF8Component(sData);		
	}
	
	return 	encodeURIUTF8Component(UCS2UTF8(UCS2(sData)));

}

std::string CXCode::encodeURIUTF8Component(const std::string& sData)
{
	const static bool s_esc[256] =
	{
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
	};

	std::string sValue;
	sValue.reserve(sData.size() * 4);

	T_UTF8 *bpos = (T_UTF8*)&sData[0];
	T_UTF8 *epos = bpos + sData.size();
	
	while (bpos<epos)
	{
		if (!s_esc[*bpos & 0xff])
		{
			sValue += *bpos;
		}
		else
		{
			char vx[4]={'%', 0, 0, 0};
			CTrans::ITOX2(*bpos, vx+1);
			sValue += vx;
		}
		bpos++;
	}	
	return sValue;
}

std::string CXCode::decodeURIComponent(const std::string& sData)
{
	std::string sResult = sData;
	int x, y;

	for (x = 0, y = 0; sData[y]; x++, y++) 
	{
		if((sResult[x] = sData[y]) == '%') 
		{
			sResult[x] = x2c(&sData[y+1]);
			y += 2;
		}
	}
	
	if(CXCode::GetCharSet()==CXCode::CHARSET_UTF8)
	{
		return sResult.substr(0, x);
	}
	
	return CXCode::UTF82GBS(sResult.substr(0, x));	
}

int CXCode::VALIDGBCode(const std::string& sData, std::string& sValidData)
{
	if(sData.empty())
	{
		return 0;
	}
	
	std::string sUC(sData.size()*2, 0);
    std::string sGB(sData.size(), 0);
	int ilUC = XGBUC::cv((T_GB*)&sData[0], sData.size(), (T_UC*)&sUC[0], sData.size());
    if (ilUC < 0)
    {
		return -1;
    }
    int ilGB = XUCGB::cv((T_UC*)&sUC[0], ilUC, (T_GB*)&sGB[0], sGB.size());
    if (ilGB < 0)
    {
		return -2;
    }
	
    sGB.resize(ilGB);
	sValidData = sGB;
    return 0;
}
