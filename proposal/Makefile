targets=proposal.pdf
all: $(targets)

proposal.pdf: *.tex sources.bib
	pdflatex proposal.tex
	bibtex proposal
	pdflatex proposal.tex
	pdflpreview proposal.tex


clean:
	rm -f $(targets)
