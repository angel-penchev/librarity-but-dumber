LATEXC=pdflatex
BIBTEXC=bibtex

DOCUMENTATION=documentation
CITATIONS=citations

LATEXC_OPTIONS=--shell-escape

.SUFFIXES:
.SUFFIXES: .bib .pdf .tex

build: $(DOCUMENTATION).pdf

$(DOCUMENTATION).pdf: $(DOCUMENTATION).bbl $(DOCUMENTATION).tex
	$(LATEXC) $(LATEXC_OPTIONS) $(DOCUMENTATION).tex
	$(LATEXC) $(LATEXC_OPTIONS) $(DOCUMENTATION).tex

$(DOCUMENTATION).bbl: $(DOCUMENTATION).aux
	$(BIBTEXC) $(DOCUMENTATION).aux

$(DOCUMENTATION).aux: $(CITATIONS).bib
	$(LATEXC) $(LATEXC_OPTIONS) $(DOCUMENTATION).tex
	$(LATEXC) $(LATEXC_OPTIONS) $(DOCUMENTATION).tex

clean:
	rm -rf *.aux *.lof *.log *.lot *.toc *.bbl *.blg *.pdf *-blx.bib *.out *.run.xml *.fdb_latexmk *.fls _minted-*