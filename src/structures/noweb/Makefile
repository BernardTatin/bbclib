# Makefile

WEAVE = noweave
TANGLE = notangle
PDFLATEX = pdflatex

PROJECT = bbclib

TARG_SRC = include/standard.h include/rbuffer.h src/rbuffer.c
TARG_PDF = $(PROJECT).pdf

TEX_DEPS = common/noweb.sty common/prelude.tex

SRC = $(PROJECT).nw

all: pdf code

code: $(TARG_SRC)

pdf: $(TARG_PDF)

# this method does not send this message :
# make: Circular rbuffer.nw.c <- rbuffer.nw dependency dropped.
$(filter %.h,$(TARG_SRC)): %.h: $(SRC)
	$(TANGLE) -R$(shell basename $@) $< > $@

$(filter %.c,$(TARG_SRC)): %.c: $(SRC)
	$(TANGLE) -R$(shell basename $@) $< > $@

.PRECIOUS: $(PROJECT).tex
%.tex: %.nw
	$(WEAVE) -delay -autodefs c -index $< > $@

%.pdf: %.tex  $(TEX_DEPS)
	$(PDFLATEX) $<
	$(PDFLATEX) $<
	$(PDFLATEX) $<

clean:
	rm -Rfv *.tex *.aux *.log *.out *.toc
	rm -Rfv $(TARG_SRC) $(TARG_PDF)

.PHONY: all clean pdf code
