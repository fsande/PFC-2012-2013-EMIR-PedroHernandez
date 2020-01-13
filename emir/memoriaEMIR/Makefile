# -----------------------
# Proyecto Final de Carrera
#  
#
# by Francisco de Sande <fsande@ull.es>
# date: 20.06.2012
# ---

LATEX    = latex
BIBTEX   = bibtex
PDFLATEX = pdflatex
L2HTML   = latex2html
DVIPS    = dvips
BASURA   = *.dvi *.bbl *.aux *.toc *.lof *.lot *.lol *.log *.blg *.out *~ *.ps *.backup *.pdf.old

MASTER   = main.tex
SRC      = \
            previo/agrade.tex previo/cita.tex previo/dedica.tex previo/portada.tex previo/preliminares.tex \

DVI = $(MASTER:.tex=.dvi)
BIB = $(MASTER:.tex=.bib)
PS  = $(MASTER:.tex=.ps)
PDF = $(MASTER:.tex=.pdf)
MASTERSIN =  $(MASTER:.tex=)

all: 
	touch main.`date +%Y-%m-%d`.pdf
	$(MAKE) pdf
#	mv main.`date +%Y-%m-%d`.pdf main.`date +%Y-%m-%d`.pdf.old
#	mv main.pdf main.`date +%Y-%m-%d`.pdf

HTML: $(PDF)
	$(L2HTML) -dir HTML -split 4 -local_icons -long_titles 20 $(MASTER)

pdf: $(MASTER) $(SRC)
	$(PDFLATEX) $(MASTER) && $(MAKE) bib && $(PDFLATEX) $(MASTER) && $(PDFLATEX) $(MASTER)

ps: $(MASTER) $(SRC) $(DVI)
	$(DVIPS) -o $(PS) $(DVI)

bib: bibliografia/bibliografia.bib
	$(BIBTEX) $(MASTERSIN)

$(DVI): $(MASTER) $(SRC)
	$(LATEX) $(MASTER); $(MAKE) bib; $(LATEX) $(MASTER); $(LATEX) $(MASTER)   

clean:
	$(RM) *.dvi *.bbl *.aux *.toc *.lof *.lot *.log *.blg *.lol *.brf *~ *.out HTML/*
	rm -rf *.aux

del:
	$(RM) -R $(BASURA);
	cd bibliografia;    $(RM) -R $(BASURA);  \
	cd ../capitulos;    $(RM) -R $(BASURA);  \
	cd ../previo;       $(RM) -R $(BASURA);  \
	cd ../apendices;    $(RM) -R $(BASURA)

mrproper:
	$(MAKE) delete

#.SUFFIXES: .tex .dvi. .ps .pdf
#
#%.dvi: %.tex
#	$(LATEX) $(SRC)
#
# end
# --
