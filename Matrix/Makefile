all:
	$(CC) -c sqlite3.c
	$(AR) -rcs sqlite3.a sqlite3.o
	$(CXX) -std=c++11 -o Matrix Matrix.cpp sqlite3.a
	strip Matrix

.PHONY: clean
clean:
	$(RM) *.o *.a *.out Matrix
