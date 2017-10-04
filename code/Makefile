CXXFLAGS=-g --std=c++11
CC=g++
ALL=tensorTest tensor.pdf tensor.h tensor.tex influence.tex influence.pdf vocab build-corpus

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

vocab.cpp: influence.nw
	notangle -Rvocab.cpp -L'#line %L "%F"%N' influence.nw > vocab.cpp

build-corpus: influence.nw
	notangle -Rbuild-corpus influence.nw > build-corpus
	chmod +x build-corpus

vocab.o: vocabulary.h vocab.cpp
vocab: vocab.o vocabulary.o

tensor.tex: tensor.nw
	noweave -delay tensor.nw > tensor.tex

influence.tex: influence.nw
	noweave -delay influence.nw > influence.tex

tensor.pdf: tensor.tex
	pdflatex tensor.tex
	pdflatex tensor.tex
	pdflatex tensor.tex
	makeindex tensor
	splitindex tensor
	pdflatex tensor.tex

influence.pdf: influence.tex
	pdflatex influence.tex
	pdflatex influence.tex
	pdflatex influence.tex
	#makeindex influence
	#splitindex influence 
	pdflatex influence.tex

clean:
	rm -f $(ALL) *.o a.out *.pdf *.aux *.idx *.ilg *ind *.log
