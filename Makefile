targets=litreview.pdf proposal.pdf
all: $(targets)

litreview.pdf: litreview.tex papers.bib
	pdflatex litreview.tex
	bibtex litreview
	pdflatex litreview.tex
	#pdfpreview litreview.tex

proposal.pdf: proposal.tex proposal/*.tex papers.bib
	pdflatex proposal.tex
	#bibtex proposal
	pdflatex proposal.tex
	#pdflpreview proposal.tex


clean:
	rm -f $(targets)
