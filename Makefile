# 编译器
CC=g++
# 编译选项
CFLAGS=-c -Wall -lnlohmann
# 可执行文件名
EXECUTABLE=FJE
# 所有的目标文件
OBJECTS=FJE.o fje.o

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

main.o: main.cpp fje.hpp
	$(CC) $(CFLAGS) FJE.cpp

fje.o: fje.cpp fje.hpp
	$(CC) $(CFLAGS) fje.cpp

clean:
	rm -rf *.o $(EXECUTABLE)

