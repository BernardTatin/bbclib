# Makefile

ifeq ($(compiler), clang)
include mk/clang.mk
else
CC = gcc48
LD = gcc48
endif

ODIR = objs


STD_WARNINGS = -Wall -Wextra -pedantic -std=c11
STD_INCLUDES = -Iinclude -Itests

_os = $(shell uname)
ifeq ($(OS), Windows_NT)
	_exe = .exe
else
	_exe =
endif

SOURCES = $(wildcard src/*.c) $(wildcard tests/*.c)
_OBJS = $(patsubst %.c,%.o,$(notdir $(SOURCES)))
OBJS = $(addprefix $(ODIR)/, $(_OBJS))

EXE = bbclib-test$(_exe).GNU

$(ODIR)/%.o: src/%.c
	$(CC) $(STD_INCLUDES) $(STD_WARNINGS) -c $< -o $@

$(ODIR)/%.o: tests/%.c
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
