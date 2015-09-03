# Makefile

_os = $(shell uname)
compiler ?= gcc

include mk/$(compiler).mk

ifeq ($(OS), Windows_NT)
	_exe = .exe
else
ifneq ($(compiler), watcom)
	_exe =
else
	_exe = .exe
endif	
endif


ODIR = objs-$(CCNAME)


LSOURCES = $(wildcard src/*.c) $(wildcard structures/*.c)
_LOBJS = $(patsubst %.c,%.o,$(notdir $(LSOURCES)))
LOBJS = $(addprefix $(ODIR)/, $(_LOBJS))

SOURCES = $(wildcard tests/*.c)
_OBJS = $(patsubst %.c,%.o,$(notdir $(SOURCES)))
OBJS = $(addprefix $(ODIR)/, $(_OBJS))

EXE = bbclib-test.GNU.$(CCNAME)$(_exe)
_LIB = bbclib.GNU.$(CCNAME)

all: _all

include mk/$(compiler)-rules.mk

_all: _odir $(LIB) $(EXE)

_odir: $(ODIR)

$(ODIR):
	mkdir -p $@


clean:
	rm -fv $(LOBJS) $(OBJS) $(EXE)


ref: all
	./$(EXE) --ref > ref.log

tests: all
	./$(EXE) --queue
	./$(EXE) --test > test.log
	diff test.log ref.log

analyze: _odir
	scan-build -analyze-headers -enable-checker alpha.security.ArrayBoundV2 -analyzer-config  stable-report-filename=true  -o analyze -stats --use-cc /usr/bin/clang  --use-analyzer /usr/bin/clang -v -v -v $(MAKE) compiler=clang clean all

.PHONY: _odir all _all clean tests analyze
