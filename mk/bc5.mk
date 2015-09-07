#
# bc5.mk
#

BC5_BASE = ~/.wine/drive_c/Borland/bc5
WIN_BC5_BASE = C:\Borland\bc5
CC = wine $(BC5_BASE)/bin/bcc32.exe
LD = wine $(BC5_BASE)/bin/tlink32.exe
CCNAME = bc5
DEBUG = 
MACHINE = -4
AR = wine $(BC5_BASE)/bin/tlib.exe
_exe = .exe
toclean = *.map $(compiler).lk1 *.BAK

STD_WARNINGS = 
STD_INCLUDE = -Iinclude -Iinclude\_compat -Itests -Istructures -I$(WIN_BC5_BASE)\include
STD_DEFINES = -Dcompiler=$(CCNAME) -Dno_c11 -Dno_inline
ALLFLAGS = $(subst /,\,$(STD_INCLUDE)) $(STD_WARNINGS) $(DEBUG) $(MACHINE) $(STD_DEFINES)

