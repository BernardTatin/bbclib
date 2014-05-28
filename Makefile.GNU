# Makefile



CC = gcc
LD = gcc

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

EXE = bbclib-test$(_exe)

$(ODIR)/%.o: src/%.c
	$(CC) $(STD_INCLUDES) $(STD_WARNINGS) -c $< -o $@

$(ODIR)/%.o: tests/%.c
	$(CC) $(STD_INCLUDES) $(STD_WARNINGS) -c $< -o $@

all: _odir $(EXE)
	@echo "_os $(_os) OS $(OS) EXE $(EXE)"

clean:
	rm -fv $(OBJS) $(EXE) *.log

_odir: $(ODIR)

$(ODIR):
	mkdir -p $@

$(EXE): $(OBJS)
	$(LD) $(OBJS) -o $@

tests: $(EXE)
		./$(EXE) --ref > ref.log
		./$(EXE) --test > test.log
		diff test.log ref.log

.PHONY: _odir all clean tests