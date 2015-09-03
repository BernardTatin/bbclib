#
# unix-standard.mk
#

STD_WARNINGS = -std=c11
STD_INCLUDE = -Iinclude -Istructures -Itests
STD_DEFINES = -Dcompiler=$(CCNAME)
ALLFLAGS = $(FLAGS) $(STD_WARNINGS) $(STD_INCLUDE) $(STD_DEFINES)