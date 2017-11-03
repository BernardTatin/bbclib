# Makefile

WEAVE = noweave
TANGLE = notangle
PDFLATEX = pdflatex

TARG_SRC = rbuffer.h
#rbuffer.c
TARG_PDF = rbuffer.pdf

FILTER = common/better-code.sh

SRC = rbuffer.nw

all: $(TARG_PDF) $(TARG_SRC)

%.h: %.nw
	$(TANGLE) -R$@ $< > $@

# %.c: %.nw
# 	$(TANGLE) -R$@ $< > $@

%.tex: %.nw
	$(shell rm $<.nw; $(FILTER) $< > $<.nw; $(WEAVE) -delay -autodefs c -index $<.nw > $@)

%.pdf: %.tex common/prelude.tex
	$(PDFLATEX) $<
	$(PDFLATEX) $<
	$(PDFLATEX) $<

clean:
	rm -Rfv *.tex *.aux *.log *.out *.toc
	rm -Rfv $(TARG_SRC) $(TARG_PDF)
