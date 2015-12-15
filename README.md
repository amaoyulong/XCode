# XCode

该项目可作为一个工具，用于编码转换

1，可以将一段字符串在GBK、UTF8、UNICODE这三个常见编码之间进行转换

2，可以将一段字符串转义成网页上常用的格式，如XML转义，JS转义，escape转义等。

## 使用方法：
1，引用头文件

	＃include "xcode.h"
2，CXCode的入参和出参都是字符串，但是CXCode不知道入参的编码格式，在使用前需要先指定

	CXCode x1(CXCode::CHARSET_UTF8);
   通过定义一个对象来指定当前环境的编码格式，环境跟此对象的生命周期一样，
   
   除非重新定义一个新的对象，也可以改变当前环境的编码格式。

   关于指定的编码，只有CXCode::unescape影响的是输出，其他方法影响的是输入。 
3，使用具体方法，可以直接操作，比如：

	std::string out = CXCode::escape(src);

##其他注意事项：
1，本工程依赖于libiconv.a，在mac下依赖于libiconv.dylib
2，具体例子可以参考test下面的test.cpp  	


关于此Project的思路整理到以下几篇csdn的文章：

<http://blog.csdn.net/yulongli/article/details/22894645>

<http://blog.csdn.net/yulongli/article/details/22952127>

<http://blog.csdn.net/yulongli/article/details/22984375>

<http://blog.csdn.net/yulongli/article/details/23671785>

<http://blog.csdn.net/yulongli/article/details/24270515>

最后，感谢felithuang，感谢他的思路和部分代码。
