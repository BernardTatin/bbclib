#
# bc5.mk
#

BC5_BASE = ~/.wine/drive_c/Borland/bc5
WIN_BC5_BASE = C:\Borland\bc5
CC = wine $(BC5_BASE)/bin/bcc32.exe
LD = wine $(BC5_BASE)/bin/tlink32.exe
CCNAME = borlandc5
DEBUG = 
MACHINE = -4
AR = wine $(BC5_BASE)/bin/tlib.exe


STD_WARNINGS = 
STD_INCLUDE = -Iinclude -Iinclude\_compat -Itests -Istructures -I$(WIN_BC5_BASE)\include
STD_DEFINES = -Dcompiler=$(CCNAME)
ALLFLAGS = $(subst /,\,$(STD_INCLUDE)) $(STD_WARNINGS) $(DEBUG) $(MACHINE) $(STD_DEFINES)

