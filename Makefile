# Makefile

_os = $(shell uname)

ifeq ($(compiler), clang)
    ifeq ($(OS), Windows_NT)
        CLANG_BASE = C:/Program Files (x86)/LLVM/bin
        CC = "$(CLANG_BASE)/clang.exe"
    else
        CC = clang
    endif
    LD = $(CC)
    CCNAME = clang
    FLAGS = 
    LFLAGS = -v
else
    CC = gcc
    LD = gcc
    CCNAME = gcc
    FLAGS = 
    LFLAGS = 
endif

ODIR = objs-$(CCNAME)


STD_WARNINGS = -Wall -Wextra -pedantic -std=c11
STD_INCLUDES = -Iinclude -Itests -Istructures
STD_DEFINES = -Dcompiler=$(CCNAME)

ifeq ($(OS), Windows_NT)
	_exe = .exe
else
	_exe =
endif

SOURCES = $(wildcard src/*.c) $(wildcard tests/*.c) $(wildcard structures/*.c)
_OBJS = $(patsubst %.c,%.o,$(notdir $(SOURCES)))
OBJS = $(addprefix $(ODIR)/, $(_OBJS))

EXE = bbclib-test.GNU.$(CCNAME)$(_exe)

_odir: $(ODIR)

$(ODIR):
	@echo "ODIR $(ODIR)"
	mkdir -p $@


$(ODIR)/%.o: src/%.c
	$(CC) $(STD_INCLUDES) $(STD_WARNINGS) $(FLAGS) -c $< -o $@

$(ODIR)/%.o: tests/%.c
	$(CC) $(STD_INCLUDES) $(STD_WARNINGS)  $(FLAGS) -c $< -o $@

$(ODIR)/%.o: structures/%.c
	$(CC) $(STD_INCLUDES) $(STD_WARNINGS)  $(FLAGS) -c $< -o $@

all: _odir $(EXE)
	@echo "ODIR $(ODIR) _os $(_os) OS $(OS) EXE $(EXE)"

clean:
	rm -fv $(OBJS) $(EXE)

$(EXE): $(OBJS)
	@echo "_os $(_os) OS $(OS) EXE $(EXE)"
	$(LD) $(LFLAGS) $(OBJS) -o $@

ref: all
		./$(EXE) --ref > ref.log

tests: all
		./$(EXE) --test > test.log
		diff test.log ref.log

analyze: _odir
	scan-build -analyze-headers -enable-checker alpha.security.ArrayBoundV2 -analyzer-config  stable-report-filename=true  -o analyze -stats --use-cc $(which clang)  --use-analyzer $(which clang) -v -v -v make compiler=clang clean all

.PHONY: _odir all clean tests analyze
