# -----------------------
# Presentacion HAC-Leganés
# 
# by R. Reyes
# date: 09.07.2012
# ---
##### User configurable options #####
LATEX    = latex
BIBTEX   = bibtex
PDFLATEX = pdflatex
DVIPS    = dvips
L2HTML   = latex2html
PLOT     = gnuplot
SRC      = 20130716_PFC_EMIR.tex
MASSRC   = 20130716_PFC_EMIR.tex
DVI	     = $(SRC:.tex=.dvi)
BIB	     = $(SRC:.tex=.bib)
PS	     = $(SRC:.tex=.ps)
SRCSIN   = $(SRC:.tex=)
### End User configurable options ###

default: pdf

all:
	$(MAKE) ps

pdf: $(SRC) 
	$(PDFLATEX) $(SRC) && $(PDFLATEX) $(SRC)  && $(PDFLATEX) $(SRC);
	
html: $(PS)
	$(L2HTML) -dir HTML -split 4 -local_icons -long_titles 20 $(SRC)

ps: $(DVI)
	$(DVIPS) -o $(PS) $(DVI)

clean:
	$(RM) *.dvi *.bbl *.aux *.toc *.lof *.lot *.log *.blg *.out *~ basura* HTML/* *.nav *.snm *.vrb
	$(RM) tex/*.aux tex/*~
delete:
	$(MAKE) clean; $(RM) *~ $(SRCSIN).pdf $(SRCSIN).ps

%.dvi: %.tex
#	$(LATEX) $(SRC) && $(MAKE) bib && $(LATEX) $(SRC) && $(LATEX) $(SRC)
	$(LATEX) $(SRC) 
	

# end
# --
