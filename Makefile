# Makefile

_os = $(shell uname)
ifeq ($(compiler), clang)
include mk/clang.mk
else
CC = gcc
LD = gcc
CCNAME = gcc
endif

ODIR = objs


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

$(ODIR)/%.o: src/%.c
	$(CC) $(STD_INCLUDES) $(STD_WARNINGS) -c $< -o $@

$(ODIR)/%.o: tests/%.c
	$(CC) $(STD_INCLUDES) $(STD_WARNINGS) -c $< -o $@

$(ODIR)/%.o: structures/%.c
	$(CC) $(STD_INCLUDES) $(STD_WARNINGS) -c $< -o $@

all: _odir $(EXE)

clean:
	rm -fv $(OBJS) $(EXE) *.log

_odir: $(ODIR)

$(ODIR):
	mkdir -p $@

$(EXE): $(OBJS)
	@echo "_os $(_os) OS $(OS) EXE $(EXE)"
	@$(CC) --version
	$(LD) $(OBJS) -o $@

tests: $(EXE)
		./$(EXE) --ref > ref.log
		./$(EXE) --test > test.log
		./$(EXE) --bin
		diff test.log ref.log

.PHONY: _odir all clean tests
