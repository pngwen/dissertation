all: litreview.pdf

litreview.pdf: litreview.tex papers.bib
	pdflatex litreview.tex
	bibtex litreview
	pdflatex litreview.tex
	pdflatex litreview.tex
