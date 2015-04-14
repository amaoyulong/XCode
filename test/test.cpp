#include <iostream>
#include <vector>
#include <iterator>
#include "xcode.h"


//TEST(DemoTestSuite, TestCase1)

void EXPECT_EQ(std::string s1, std::string s2){
    if (s1==s2){
        std::cout << "Expect succ" << std::endl;
    }else {
        std::cout << "Expect fail \t" << s1 << "\t" << s2 << std::endl;
    }
}

void test()
{
    CXCode x1(CXCode::CHARSET_UTF8);
    std::string sUTF8 = "abc\xe4\xb8\xad\xe5\x9b\xbd\xe4\xba\xba";
    EXPECT_EQ(std::string("abc%u4E2D%u56FD%u4EBA"), CXCode::escape(sUTF8));
    EXPECT_EQ(sUTF8, CXCode::unescape(CXCode::escape(sUTF8)));
    EXPECT_EQ(std::string("abc%u4E2D%u56FD%u4EBA"), CXCode::escape(CXCode::unescape(CXCode::escape(sUTF8))));
    EXPECT_EQ(sUTF8, CXCode::unescape((sUTF8)));
    EXPECT_EQ(std::string("abc%E4%B8%AD%E5%9B%BD%E4%BA%BA"), CXCode::encodeURIComponent(sUTF8));
    EXPECT_EQ(std::string("abc\\u4E2D\\u56FD\\u4EBA"), CXCode::encodeJSONComponent(sUTF8));
    EXPECT_EQ(std::string("abc&#x4E2D;&#x56FD;&#x4EBA;"), CXCode::encodeXMLComponent(sUTF8));

    
    std::string sUCS2 = CXCode::UCS2(CXCode::escape(sUTF8));

    CXCode x2(CXCode::CHARSET_GBS);
    std::string sGB="abc\xd6\xd0\xb9\xfa\xc8\xcb";
    EXPECT_EQ(std::string("abc%u4E2D%u56FD%u4EBA"), CXCode::escape(sGB));
    EXPECT_EQ(sGB, CXCode::unescape(CXCode::escape(sGB)));
    EXPECT_EQ(std::string("abc%u4E2D%u56FD%u4EBA"), CXCode::escape(CXCode::unescape(CXCode::escape(sGB))));
    EXPECT_EQ(sGB, CXCode::unescape((sGB)));
    EXPECT_EQ(std::string("abc%E4%B8%AD%E5%9B%BD%E4%BA%BA"), CXCode::encodeURIComponent(sGB));
    EXPECT_EQ(std::string("abc\\u4E2D\\u56FD\\u4EBA"), CXCode::encodeJSONComponent(sGB));
    EXPECT_EQ(std::string("abc&#x4E2D;&#x56FD;&#x4EBA;"), CXCode::encodeXMLComponent(sGB));
    

    CXCode x3(CXCode::CHARSET_UCS2);
    T_UC tUC[6] = {'a','b','c',20013,22269,20154};
    std::string sUC((char *)tUC, 12);
    EXPECT_EQ(sUC, CXCode::UCS2(sUC));
    EXPECT_EQ(sUCS2, CXCode::escape(sUC));
    EXPECT_EQ(CXCode::UCS2(sUCS2), CXCode::escape(sUC));
    EXPECT_EQ(CXCode::escape(sUC), CXCode::UCS2(CXCode::escape(sUC)));
    EXPECT_EQ(sUC, CXCode::unescape(CXCode::escape(sUC)));
    EXPECT_EQ(sUCS2, CXCode::escape(CXCode::unescape(CXCode::escape(sUC))));
    EXPECT_EQ(sUC, CXCode::unescape((sUC)));
    EXPECT_EQ(std::string("abc%E4%B8%AD%E5%9B%BD%E4%BA%BA"), CXCode::encodeURIComponent(sUC));
    EXPECT_EQ(std::string("abc\\u4E2D\\u56FD\\u4EBA"), CXCode::encodeJSONComponent(sUC));
    EXPECT_EQ(std::string("abc&#x4E2D;&#x56FD;&#x4EBA;"), CXCode::encodeXMLComponent(sUC));

    
    EXPECT_EQ(sUC, CXCode::GBS2UCS((sGB))); 
    EXPECT_EQ(sUTF8, CXCode::GBS2UTF8((sGB)));
    EXPECT_EQ(sUC, CXCode::UTF82UCS((sUTF8)));
    EXPECT_EQ(sGB, CXCode::UTF82GBS((sUTF8)));
    EXPECT_EQ(sGB, CXCode::UCS2GBS((sUC)));
    EXPECT_EQ(sUTF8, CXCode::UCS2UTF8((sUC)));
    
    //std::cout << sUC << std::endl;
   
    //std::cout << CXCode::UCS2(CXCode::escape(sUC))<<std::endl; 
    //std::cout << CXCode::escape(sUC) <<std::endl;
    //std::cout << CXCode::unescape(CXCode::escape(sUC)) <<std::endl;
    //std::cout << std::string("abc%u4E2D%u56FD%u4EBA") <<std::endl;
    //std::cout << CXCode::UCS2("abc%u4E2D%u56FD%u4EBA") <<std::endl;
    //std::cout << CXCode::encodeJSONComponent(CXCode::GBS2UCS((sGB)))<<std::endl; 

//    return 0;
    
}






int main(int argc , char ** argv)
{
    test();
    return 0;
}




