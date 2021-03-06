# Makefile

_os = $(shell uname)
compiler ?= gcc

include mk/$(compiler).mk

ifeq ($(OS), Windows_NT)
	_exe = .exe
endif


ODIR = objs$(CCNAME)


LSOURCES = $(wildcard src/*.c) $(wildcard src/structures/*.c)
_LOBJS = $(patsubst %.c,%.o,$(notdir $(LSOURCES)))
LOBJS = $(addprefix $(ODIR)/, $(_LOBJS))

SOURCES = $(wildcard src/tests/*.c)
_OBJS = $(patsubst %.c,%.o,$(notdir $(SOURCES)))
OBJS = $(addprefix $(ODIR)/, $(_OBJS))

EXE = bbclib-test.GNU.$(CCNAME)$(_exe)
_LIB = bbclib.GNU.$(CCNAME)

all: _all

include mk/$(compiler)-rules.mk

lib: _odir $(LIB)

exe: lib $(EXE)


_all: _odir lib exe

_odir: $(ODIR)

$(ODIR):
	mkdir -p $@


clean:
	rm -fv $(LOBJS) $(OBJS) $(EXE) $(toclean) $(LIB)


ref: all
	$(RUNNER) ./$(EXE) --ref | tr -d '\r' > ref.log

tests: ref
	$(RUNNER) ./$(EXE) --queue
	$(RUNNER) ./$(EXE) --stack
	$(RUNNER) ./$(EXE) --test | tr -d '\r' > $(compiler).log
	diff  --suppress-common-lines -syW 132 $(compiler).log ref.log

analyze: _odir
	scan-build -analyze-headers -enable-checker alpha.security.ArrayBoundV2 -analyzer-config  stable-report-filename=true  -o analyze -stats --use-cc /usr/bin/clang  --use-analyzer /usr/bin/clang -v -v -v $(MAKE) compiler=clang clean all

.PHONY: _odir all _all clean tests analyze lib exe
