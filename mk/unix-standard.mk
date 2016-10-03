#
# unix-standard.mk
#

RUNNER =
STD_WARNINGS = -std=c11
STD_INCLUDE = -Isrc/include -Isrc/structures -Isrc/tests
STD_DEFINES = -Dcompiler=$(CCNAME)
ALLFLAGS = $(FLAGS) $(STD_WARNINGS) $(STD_INCLUDE) $(STD_DEFINES)