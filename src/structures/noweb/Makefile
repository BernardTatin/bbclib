# Makefile

WEAVE = noweave
TANGLE = notangle
PDFLATEX = pdflatex

TARG_SRC = include/standard.h include/rbuffer.h src/rbuffer.c
TARG_PDF = rbuffer.pdf

TEX_DEPS = common/noweb.sty common/prelude.tex

SRC = rbuffer.nw

all: pdf code

code: $(TARG_SRC)

pdf: $(TARG_PDF)

# this method does not send this message :
# make: Circular rbuffer.nw.c <- rbuffer.nw dependency dropped.
$(filter %.h,$(TARG_SRC)): %.h: rbuffer.nw
	$(TANGLE) -R$(shell basename $@) $< > $@

$(filter %.c,$(TARG_SRC)): %.c: rbuffer.nw
	$(TANGLE) -R$(shell basename $@) $< > $@

.PRECIOUS: rbuffer.tex
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
