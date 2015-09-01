#
# clang.mk
#

ifeq ($(OS), Windows_NT)
CLANG_BASE = C:/Program Files (x86)/LLVM/bin

CC = "$(CLANG_BASE)/clang.exe"
else
CC = clang
endif
LD = $(CC)