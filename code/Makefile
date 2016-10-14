CXXFLAGS=-g --std=c++11
CC=g++
ALL=tensorTest

tensorTest: tensorTest.o tensor.o
tensorTest.o: tensorTest.cpp tensor.h
tensor.o: tensor.cpp tensor.h
clean:
	rm -f $(ALL) *.o a.out
