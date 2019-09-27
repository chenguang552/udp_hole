TARGET=client

CC := g++

# 头文件包含
INCLUDE := -I/usr/local/boost/include 
# 链接库文件
LIBS := -lpthread -L/usr/local/boost/lib -lboost_system 
# 提取Resources文件夹下所有cpp文件目标
SRCS := $(wildcard ./*.cpp)
# 将所有目标后缀改为.o
OBJS := $(patsubst ./%,./%,$(patsubst %cpp, %o, $(SRCS)))

.PHONY : all  clean  objs install

all  : $(TARGET)


FLAGS := -g -Wall -std=c++11 -O3 $(INCLUDE)

SHARE := -fPIC -shared

$(TARGET) : $(OBJS)
	$(CC) $(FLAGS) -o $@ $^ $(LIBS)

./%.o:./%.cpp
	$(CC) -g -std=c++11 -o $@  -c $^ $(INCLUDE)

install:



clean:
	rm $(OBJS) $(TARGET)