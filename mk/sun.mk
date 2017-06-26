#
# sun.mk
#

dev_studio_home = /usr/local/tools/DevStudio/developerstudio12.5

CC = cc
LD = cc
CCNAME = cc
FLAGS = -Wall -Wextra -gnone -m64 -xCC -std=c11
LFLAGS = -m64
CINCLUDES = -I$(dev_studio_home)/lib/compilers/rtlibs/usr/include -I$(dev_studio_home)/lib/compilers/include/cc -I/usr/include/x86_64-linux-gnu 

AR = ar
ARFLAGS = rcs
toclean =

RUNNER =
STD_WARNINGS = 
STD_INCLUDE = -I- $(CINCLUDES) -Isrc -Isrc/include -Isrc/structures -Isrc/tests
STD_DEFINES = -Dcompiler=$(CCNAME) 
ALLFLAGS = $(FLAGS) $(STD_WARNINGS) $(STD_INCLUDE) $(STD_DEFINES)