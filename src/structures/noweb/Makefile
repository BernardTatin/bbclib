# Makefile

WEAVE = noweave
TANGLE = notangle
PDFLATEX = pdflatex

TARG_SRC = rbuffer.h
TARG_PDF = rbuffer.pdf

SRC = rbuffer.nw

all: $(TARG_PDF) $(TARG_SRC)

%.h: %.nw
	$(TANGLE) $< > $@

%.tex: %.nw
	$(WEAVE) -delay -autodefs c -index $< > $@

%.pdf: %.tex common/prelude.tex
	$(PDFLATEX) $<
	$(PDFLATEX) $<
	$(PDFLATEX) $<

clean:
	rm -Rfv *.tex *.aux *.log *.out *.toc
	rm -Rfv $(TARG_SRC) $(TARG_PDF)
