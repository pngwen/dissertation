targets=defense.pdf ut-dissertation.pdf
figures=diagrams/* images/*
all: $(targets)

ut-dissertation.pdf: $(figures) *.tex chapters/*.tex front-matter/*.tex back-matter/*.tex sources.bib
	pdflatex ut-dissertation.tex
	bibtex ut-dissertation
	pdflatex ut-dissertation.tex
	pdflatex ut-dissertation.tex
	pdflatex ut-dissertation.tex

defense.pdf: $(figures) defense.tex sources.bib
	pdflatex defense.tex
	bibtex defense
	pdflatex defense.tex
	pdflatex defense.tex
	pdflatex defense.tex


clean:
	rm -f $(targets)
