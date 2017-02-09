CXXFLAGS=-g --std=c++11
CC=g++
ALL=tensorTest tensor.pdf tensor.h

all: $(ALL)
tensorTest: tensorTest.o 
tensorTest.o: tensorTest.cpp tensor.h
tensor.h: tensor.nw
	notangle -Rtensor.h -L'#line %L "%F"%N' tensor.nw > tensor.h

tensor.pdf: tensor.nw
	noweave -delay tensor.nw > tensor.tex
	pdflatex tensor.tex
	pdflatex tensor.tex
	pdflatex tensor.tex
	makeindex tensor
	splitindex tensor
	pdflatex tensor.tex
clean:
	rm -f $(ALL) *.o a.out
