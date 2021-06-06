ARCH ?= x86_64-w64-mingw32-

all:
	$(CC) -c sqlite3.c
	$(AR) -rcs sqlite3.a sqlite3.o
	$(CXX) -std=c++11 -O3 -o Matrix Matrix.cpp sqlite3.a
	strip Matrix

windows:
	$(ARCH)gcc -c sqlite3.c
	$(ARCH)ar -rcs sqlite3.a sqlite3.o
	$(ARCH)windres matrix.rc -O coff -o Matrix.res
	$(ARCH)g++ -std=c++11 -O3 -o Matrix Matrix.cpp sqlite3.a Matrix.res
	$(ARCH)strip Matrix.exe

.PHONY: clean
clean:
	$(RM) *.o *.a *.out *.res Matrix
