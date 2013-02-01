CC      := g++
AR		:= ar
LD      := ld
CFLAGS  := -fPIC
INC     := -I/usr/include/ImageMagick/ -I../../zxing_cpp/core/src/
LIB     := -lMagickWand -lMagick++ -lMagickCore -L../../zxing_cpp/build/ -lzxing
LDFLAGS := -shared
SOURCE  := $(wildcard *.cpp)
OBJS    := $(patsubst %.cpp,%.o,$(SOURCE))
TARGET := libqrdecode.so

all:$(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) $(LIB) -o $(TARGET) 
	@rm *.o -rf

%.o:%.cpp
	@echo Compiling $< ...
	@$(CC) -c $(CFLAGS)  $(INC) $< -o $*.o

.PHONY: clean

clean:
	rm *.so *.o -rf $(TARGET)
