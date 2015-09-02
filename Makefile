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
    WATCOM_BASE = ~/.wine/drive_c/WATCOM
    WIN_WATCOM_BASE = C:\WATCOM
    CC = wine $(WATCOM_BASE)/binnt/wcc386.exe
    LD = wine $(WATCOM_BASE)/binnt/wlink.exe
    CC = wine wcc386.exe
    LD = wine wlink.exe
    CCNAME = watcom
    DEBUG = -od -d2 -db -en
    MACHINE = -6r -bt=nt -mf
    AR = wine wlib.exe
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
STD_INCLUDE = -Iinclude -Istructures -Itests
STD_DEFINES = -Dcompiler=$(CCNAME)
ALLFLAGS = $(FLAGS) $(STD_WARNINGS) $(STD_INCLUDE) $(STD_DEFINES)
else
STD_WARNINGS = -w4 -e25
STD_INCLUDE = -zq -i="$(WIN_WATCOM_BASE)/h;$(WIN_WATCOM_BASE)/h/nt;./include;./tests;./structures"
STD_DEFINES = -dcompiler=$(CCNAME)
ALLFLAGS = $(subst /,\,$(STD_INCLUDE)) $(STD_WARNINGS) $(DEBUG) $(MACHINE) $(STD_DEFINES)
endif


ifeq ($(OS), Windows_NT)
	_exe = .exe
else
ifneq ($(compiler), watcom)
	_exe =
else
	_exe = .exe
endif	
endif

LSOURCES = $(wildcard src/*.c) $(wildcard structures/*.c)
_LOBJS = $(patsubst %.c,%.o,$(notdir $(LSOURCES)))
LOBJS = $(addprefix $(ODIR)/, $(_LOBJS))

SOURCES = $(wildcard tests/*.c)
_OBJS = $(patsubst %.c,%.o,$(notdir $(SOURCES)))
OBJS = $(addprefix $(ODIR)/, $(_OBJS))

EXE = bbclib-test.GNU.$(CCNAME)$(_exe)
_LIB = bbclib.GNU.$(CCNAME)
ifneq ($(compiler), watcom)
LIB = lib$(_LIB).a
else
LIB = $(_LIB).lib
endif

all: _odir $(LIB) $(EXE)

$(ODIR)/%.o: src/%.c
ifneq ($(compiler), watcom)
	$(CC) $(ALLFLAGS) -c $< -o $@
else
	$(CC) $(subst /,\\,$<) $(ALLFLAGS) -fo=$(subst /,\\,$@)
endif

$(ODIR)/%.o: tests/%.c
ifneq ($(compiler), watcom)
	$(CC) $(ALLFLAGS) -c $< -o $@
else
	$(CC) $(subst /,\\,$<) $(ALLFLAGS) -fo=$(subst /,\\,$@)
endif

$(ODIR)/%.o: structures/%.c
ifneq ($(compiler), watcom)
	$(CC) $(ALLFLAGS) -c $< -o $@
else
	$(CC) $(subst /,\\,$<) $(ALLFLAGS) -fo=$(subst /,\\,$@)
endif

_odir: $(ODIR)

$(ODIR):
	mkdir -p $@


clean:
	rm -fv $(LOBJS) $(OBJS) $(EXE)

$(LIB): $(LOBJS)
ifneq ($(compiler), watcom)
	$(AR) $(ARFLAGS) $@ $(LOBJS)
else
	$(AR) $@ $(subst $(ODIR)/,-+$(ODIR)\\,$(LOBJS))
endif
	
$(EXE): $(OBJS)
ifneq ($(compiler), watcom)
	$(LD) $(LFLAGS) $(OBJS) -L. -l$(_LIB) -o $@
else
	echo "NAME $@" > watcom.lk1
	echo "SYSTEM nt" >> watcom.lk1
	echo "FILE {$(OBJS)}" >> watcom.lk1
	echo "LIBFILE $(LIB)" >> watcom.lk1
	$(LD) d all op m op maxe=25 op symf @watcom.lk1
endif

ref: all
	./$(EXE) --ref > ref.log

tests: all
	./$(EXE) --queue
	./$(EXE) --test > test.log
	diff test.log ref.log

analyze: _odir
	scan-build -analyze-headers -enable-checker alpha.security.ArrayBoundV2 -analyzer-config  stable-report-filename=true  -o analyze -stats --use-cc /usr/bin/clang  --use-analyzer /usr/bin/clang -v -v -v $(MAKE) compiler=clang clean all

.PHONY: _odir all clean tests analyze
