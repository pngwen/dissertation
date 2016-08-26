targets=proposal.pdf
all: $(targets)

proposal.pdf: *.tex sources.bib
	pdflatex proposal.tex
	bibtex proposal
	pdflatex proposal.tex
	pdfpreview proposal.tex


clean:
	rm -f $(targets)
