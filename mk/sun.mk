#
# sun.mk
#


CC = suncc
LD = suncc
CCNAME = suncc
FLAGS = -Wall -Wextra -pedantic  
LFLAGS = 
AR = ar
ARFLAGS = rcs
toclean =

RUNNER =
STD_WARNINGS = 
STD_INCLUDE = -Isrc/include -Isrc/structures -Isrc/tests
STD_DEFINES = -Dcompiler=$(CCNAME)  -Dno_c11
ALLFLAGS = $(FLAGS) $(STD_WARNINGS) $(STD_INCLUDE) $(STD_DEFINES)

# include mk/unix-standard.mk
