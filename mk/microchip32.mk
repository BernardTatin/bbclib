
CC = xc32-gcc
LD = xc32-gcc
CCNAME = xc32
FLAGS = -Wall -Wextra -pedantic  
LFLAGS = 
AR = ar
ARFLAGS = rcs
toclean =
PROCESSOR ?= 32MX360F512L

RUNNER =
STD_WARNINGS = 
STD_INCLUDE = -Isrc/include -Isrc/structures -Isrc/tests
STD_DEFINES = -Dcompiler=$(CCNAME)
ALLFLAGS = $(FLAGS) $(STD_WARNINGS) $(STD_INCLUDE) $(STD_DEFINES) -mprocessor=$(PROCESSOR)
