# Makefile

_os = $(shell uname)
compiler ?= gcc

ifeq ($(compiler), clang)
    ifeq ($(OS), Windows_NT)
        CLANG_BASE = C:/Program Files (x86)/LLVM/bin
        CC = "$(CLANG_BASE)/clang.exe"
    else
        CC = clang
    endif
    LD = $(CC)
    CCNAME = clang
    FLAGS = -Weverything
    LFLAGS = 
    AR = ar
    ARFLAGS = rcs
endif  

ifeq ($(compiler), watcom)
    WATCOM_BASE = ~/.wine/drive_c/WATCOM/binnt
    CC = wine $(WATCOM_BASE)/wcc386.exe
    LD = wine $(WATCOM_BASE)/wlink.exe
    CCNAME = watcom
    FLAGS = -w4 -e25 -od -d2 -db -en -6r -bt=nt -fo=.obj -mf
endif

ifeq ($(compiler), gcc)
    CC = gcc
    LD = gcc
    CCNAME = gcc
    FLAGS = -Wall -Wextra -pedantic  
    LFLAGS = 
    AR = ar
    ARFLAGS = rcs
endif

ODIR = objs-$(CCNAME)



ifneq ($(compiler), watcom)
STD_WARNINGS = -std=c11
STD_INCLUDES = -Iinclude -Istructures -Itests
STD_DEFINES = -Dcompiler=$(CCNAME)
else
STD_WARNINGS = 
STD_INCLUDE = $(WATCOM_BASE)/h;$(WATCOM_BASE)/h/nt;./include;./tests;./structures
STD_DEFINES =
endif

ifeq ($(OS), Windows_NT)
	_exe = .exe
else
	_exe =
endif

LSOURCES = $(wildcard src/*.c) $(wildcard structures/*.c)
_LOBJS = $(patsubst %.c,%.o,$(notdir $(LSOURCES)))
LOBJS = $(addprefix $(ODIR)/, $(_LOBJS))

SOURCES = $(wildcard tests/*.c)
_OBJS = $(patsubst %.c,%.o,$(notdir $(SOURCES)))
OBJS = $(addprefix $(ODIR)/, $(_OBJS))

EXE = bbclib-test.GNU.$(CCNAME)$(_exe)
_LIB = bbclib.GNU.$(CCNAME)
LIB = lib$(_LIB).a

all: _odir $(LIB) $(EXE)
https://youtu.be/KisHhIRihMY
$(ODIR)/%.o: src/%.c
	$(CC) $(STD_INCLUDES) $(STD_WARNINGS) $(FLAGS) -c $< -o $@

$(ODIR)/%.o: tests/%.c
	$(CC) $(STD_INCLUDES) $(STD_WARNINGS)  $(FLAGS) -c $< -o $@

$(ODIR)/%.o: structures/%.c
	$(CC) $(STD_INCLUDES) $(STD_WARNINGS)  $(FLAGS) -c $< -o $@

_odir: $(ODIR)

$(ODIR):
	mkdir -p $@


clean:
	rm -fv $(LOBJS) $(OBJS) $(EXE)

$(LIB): $(LOBJS)
	$(AR) $(ARFLAGS) $@ $(LOBJS)
	
$(EXE): $(OBJS)
	$(LD) $(LFLAGS) $(OBJS) -L. -l$(_LIB) -o $@

ref: all
	./$(EXE) --ref > ref.log

tests: all
	./$(EXE) --queue
	./$(EXE) --test > test.log
	diff test.log ref.log

analyze: _odir
	scan-build -analyze-headers -enable-checker alpha.security.ArrayBoundV2 -analyzer-config  stable-report-filename=true  -o analyze -stats --use-cc /usr/bin/clang  --use-analyzer /usr/bin/clang -v -v -v $(MAKE) compiler=clang clean all

.PHONY: _odir all clean tests analyze
