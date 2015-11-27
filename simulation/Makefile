CPPFLAGS=--std=gnu++11 -g
LD=g++
CC=g++

motorTest: motorTest.o motor.o numeric.o
motorTestPlot: motorTest
	./motorTest > plot/motor.tsv
	$(MAKE) -C plot

numericTest: numericTest.o numeric.o
clean:
	rm -f *.o motorTest
