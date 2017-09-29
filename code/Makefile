CXXFLAGS=-g --std=c++11
CC=g++
ALL=tensorTest tensor.pdf tensor.h tensor.tex

all: $(ALL)
tensorTest: tensorTest.o 
tensorTest.o: tensorTest.cpp tensor.h
tensor.h: tensor.nw
	notangle -Rtensor.h -L'#line %L "%F"%N' tensor.nw > tensor.h

vocabulary.h: influence.nw
	notangle -Rvocabulary.h -L'#line %L "%F"%N' influence.nw > vocabulary.h
vocabulary.cpp: influence.nw
	notangle -Rvocabulary.cpp -L'#line %L "%F"%N' influence.nw > vocabulary.cpp
vocabulary.o: vocabulary.h vocabulary.cpp

tensor.tex: tensor.nw
	noweave -delay tensor.nw > tensor.tex

tensor.pdf: tensor.tex
	pdflatex tensor.tex
	pdflatex tensor.tex
	pdflatex tensor.tex
	makeindex tensor
	splitindex tensor
	pdflatex tensor.tex
clean:
	rm -f $(ALL) *.o a.out *.pdf *.aux *.idx *.ilg *ind *.log
