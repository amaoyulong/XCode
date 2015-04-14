
#所有include路径
ALLINC                  = ../include
INC                     = $(patsubst %,-I%,$(ALLINC)) 

#LIB路径配置
PATH_LIB                = ../lib 
LIB                     = $(patsubst %,-L%,$(PATH_LIB))


LINK                    = -liconv -lxcode


#得到C,CPP文件的
CPP_FILE = $(wildcard ./*.cpp )

#通过.C,.CPP文件名称得到.O文件名称
OUT_FILE = $(patsubst ./%.cpp, ./%, $(CPP_FILE))

CC_FLAGS = $(C_FLAGS) 

#输出文件
all:$(OUT_FILE)
%:%.cpp
	$(CXX) $(C_FLAGS) -o $* $*.cpp -g -DDEBUG $(INC) $(LIB) $(LINK) 
ifeq ($(DEBUG_FLAG),0)
	strip $*
endif

debug:
	$(MAKE) $(MFLAGS) DEBUG_FLAG=1 C_FLAGS="$(C_FLAGS) $(DEBUGFLAGS)" all
clean:
	$(RM) $(OUT_FILE) 
mkdir:
	if (test -d $(PATH_CGI)) ; then pwd ; else mkdir $(PATH_CGI) ; fi
	
