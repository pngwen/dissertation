targets=proposal.pdf proposal-slides.pdf
all: $(targets)

proposal.pdf: *.tex sources.bib
	pdflatex proposal.tex
	bibtex proposal
	pdflatex proposal.tex
	pdflatex proposal.tex

proposal-slides.pdf: *.tex sources.bib
	pdflatex proposal-slides.tex
	bibtex proposal-slides
	pdflatex proposal-slides.tex
	pdflatex proposal-slides.tex


clean:
	rm -f $(targets)
