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
MACHINE = -6r -bt=nt -mf -ze
AR = wine wlib.exe
_exe = .exe
toclean = *.map *.err $(compiler).lk1 *.sym


RUNNER = wine
STD_WARNINGS = -w4 -e25
STD_INCLUDE = -zq -i="$(WIN_WATCOM_BASE)/h;$(WIN_WATCOM_BASE)/h/nt;./src/include;./src/tests;./src/structures"
STD_DEFINES = -dcompiler=$(CCNAME)
ALLFLAGS = $(subst /,\,$(STD_INCLUDE)) $(STD_WARNINGS) $(DEBUG) $(MACHINE) $(STD_DEFINES)

