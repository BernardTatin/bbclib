#
# watcom.mk
#

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


STD_WARNINGS = -w4 -e25
STD_INCLUDE = -zq -i="$(WIN_WATCOM_BASE)/h;$(WIN_WATCOM_BASE)/h/nt;./include;./tests;./structures"
STD_DEFINES = -dcompiler=$(CCNAME) -dno_c11
ALLFLAGS = $(subst /,\,$(STD_INCLUDE)) $(STD_WARNINGS) $(DEBUG) $(MACHINE) $(STD_DEFINES)

