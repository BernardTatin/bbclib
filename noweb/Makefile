# Makefile

WEAVE = noweave
TANGLE = notangle
PDFLATEX = pdflatex

PROJECT = bbclib

TARG_SRC = include/standard.h include/rbuffer.h src/rbuffer.c
TARG_PDF = $(PROJECT).pdf

TEX_DEPS = common/newnoweb.sty common/prelude.tex

SRC = $(PROJECT).nw
MORENW = standard.nw rbuffer.nw annexes.nw
ALLNW = $(SRC) $(MORENW)
_tmpnw = _noweb.nw

all: pdf code

code: $(TARG_SRC)

pdf: $(TARG_PDF)

# this method does not send this message :
# make: Circular rbuffer.nw.c <- rbuffer.nw dependency dropped.
$(filter %.h,$(TARG_SRC)): %.h: $(ALLNW)
	$(TANGLE) -R$(shell basename $@) $(ALLNW) > $@

$(filter %.c,$(TARG_SRC)): %.c: $(ALLNW)
	$(TANGLE) -R$(shell basename $@) $(ALLNW) > $@

.PRECIOUS: $(PROJECT).tex
$(PROJECT).tex: $(ALLNW)
	cat $(ALLNW) > $(_tmpnw)
	$(WEAVE) -n -delay -autodefs c -index $(_tmpnw) > $@

	# rm -fv $(_tmpnw)

$(PROJECT).pdf: $(PROJECT).tex  $(TEX_DEPS)
	$(PDFLATEX) $<
	$(PDFLATEX) $<
	$(PDFLATEX) $<

clean:
	rm -Rfv *.tex *.aux *.log *.out *.toc
	rm -Rfv $(TARG_SRC) $(TARG_PDF)

.PHONY: all clean pdf code
