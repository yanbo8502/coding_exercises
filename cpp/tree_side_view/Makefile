LIBS=  -lpthread  
HDRS = $(wildcard *.h)
SRCS = $(wildcard *.cpp)
OBJS = $(patsubst %.cpp, %.o, $(SRCS))
DEPS = $(patsubst %.cpp, %.d, $(SRCS))

TARGET = test
CXX = clang++

compile: $(OBJS)
	$(CXX)  -g  -o  $(TARGET)  $(OBJS)  $(LIBS) 

-include $(DEPS)

%.o: %.cpp
	$(CXX) -c  -g -MMD -std=c++11 $<

.PHONY: clean

clean:
	-rm *.o
	-rm *.d
	-rm *.gch
	-rm $(TARGET)

run:
	./$(TARGET)

all: clean compile run