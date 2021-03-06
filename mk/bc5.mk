#
# bc5.mk
#

BC5_BASE = ~/.wine/drive_c/BC5
WIN_BC5_BASE = C:/BC5
CC = wine $(BC5_BASE)/bin/bcc32.exe
LD = wine $(BC5_BASE)/bin/tlink32.exe
TDUMP = wine $(BC5_BASE)/bin/tdump.exe

CCNAME = bc5
DEBUG =
MACHINE = -5 -O2 -p -a -Oc -Oi -OS -wcln -wsig -wucp -wbbf -wpin -wnak -wdef -wnod -wamb -wuse -wstv -wasm -wamp -wobs -wpch -WC -H-
AR = wine $(BC5_BASE)/bin/tlib.exe
_exe = .exe
toclean = *.map $(compiler).lk1 *.BAK

RUNNER = wine
STD_WARNINGS =
STD_INCLUDE = -Isrc/include -Isrc/tests -Isrc/structures -Isrc -I$(WIN_BC5_BASE)/include
STD_DEFINES = -Dcompiler=$(CCNAME) -Dno_c11
ALLFLAGS = $(subst /,\\,$(STD_INCLUDE)) $(STD_WARNINGS) $(DEBUG) $(MACHINE) $(STD_DEFINES)

