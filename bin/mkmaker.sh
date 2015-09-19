#!/bin/sh

# =================================================================
# globals

# static variables
scriptname=$(basename $0)
version="0.0.1"

# these variables depends of command line options 
PROJECT=
TARGET=Makefile
SOUCES='.'
INCLUDES=
LIBS=
LIBSDIR=
COMPILER=gcc

# these globals are computed after the previous are filled
cc=
ld=
cflags=
ldflags=
incs=
defs=

# =================================================================
# functions

# this function shows usage
dohelp() {
	local exitcode=0

	[ $# -ne 0 ] && exitcode=1 && errmsg=$1 && echo "ERROR $errmsg"
cat << DOHELP
${scriptname} version ${version}
${scriptname} [--help] : this text
${scriptname} PROJECT  [OPTIONS]
	PROJECT is the project name
OPTIONS :
    --target TARGET : the name of the Makefile (default: Makefile)
    --sources SOURCES : directories where are the source files (default : '.')
	--includes INCLUDES : directories of header files
	--libs LIBS : list of libs
	--libsdir LIBSDIR : directories of libraries
	--compiler COMPILER : one of gcc|clang|watcom|bc5, gcc is the default

NOTE :	
Each list of directories or files is a semi-colons separated list as PATH
DOHELP

	exit $exitcode
}

# this fonction compute includes options 
computeincs() {
	local prefix=
	local sep=
	local method=
	
	case $COMPILER in
		gcc|clang)
			prefix='-I'
			;;
		*)
			onerror "$COMPILER not implemented"
			;;
	esac
	echo $INCLUDES | sed "s/^/$prefix/g" | sed "s/:/ $prefix/g" 
}

# called when en arror occurs
onerror() {
	local errmsg="unknown error"
	[ $# -ne 0 ] && errmsg="" && while [ $# -ne 0 ]
	do
		errmsg="$errmsg $1"
		shift
	done
	dohelp "$errmsg"
}

# no arguments, we show help
[ $# -eq 0 ] && dohelp

# first argument is the project name
PROJECT=$1
shift

# computes globals from command line
while [ $# -ne 0 ]
do
	case $1 in
		--target)
			shift
			$TARGET=$1
			;;
		--sources)
			shift
			SOURCES=$1
			;;
		--includes)
			shift
			INCLUDES=$1
			;;
		--libs)
			shift
			LIBS=$1
			;;
		--libsdir)
			shift
			LIBSDIR=$1
			;;
		--compiler)
			shift
			COMPILER=$1
			;;
	esac
	shift
done

# verify globals
[ "$TARGET" = "" ] && onerror "You must supply a target Makefile"
[ "$SOURCES" = "" ] && onerror "You must supply a source directory"
[ "$INCLUDES" = "" ] && INCLUDES='.'
case $COMPILER in
	watcom|bc5)
		onerror "$COMPILER not implemented"
		;;
	clang)
		cc=$COMPILER
		ld=$COMPILER
		cflags="-Weverything -std=c11"
		ldflags=
		defs="-Dcompiler=$COMPILER"
		incs=$(computeincs)
		;;
	gcc)
		cc=$COMPILER
		ld=$COMPILER
		cflags="-Wall -Wextra -pedantic -std=c11"
		ldflags=
		defs="-Dcompiler=$COMPILER"
		incs=$(computeincs)
		;;
	*)
		onerror "Unknown compiler ($COMPILER)"
		;;
esac

# creating the Makefile
cat > $TARGET << EOTARGET
#
# $(basename $TARGET)
# created on $(date)
# by $USER

CC=$cc
LD=$ld
PROJECT=$PROJECT

ALLCFLAGS = $cflags $incs $defs
ALLLDFLAGS = 

_os = \$(shell uname)
ODIR = objs_$COMPILER
SOURCES = \$(wildcard $SOURCES/*.c)
_OBJS = \$(patsubst %.c,%.o,\$(notdir \$(SOURCES)))
OBJS = \$(addprefix \$(ODIR)/, \$(_OBJS))

ifeq (\$(OS), Windows_NT)
	_exe = .exe
endif

EXE = \$(PROJECT).$COMPILER\$(_exe)

all: _all

\$(ODIR)/%.o: $SOURCES/%.c
	\$(CC) \$(ALLCFLAGS) -c \$< -o \$@

exe: \$(EXE)

\$(EXE): \$(OBJS)
	\$(LD) \$(ALLLDFLAGS) \$(OBJS) -o \$@

_all: _odir exe

_odir: \$(ODIR)

\$(ODIR):
	mkdir -p \$@


clean:
	rm -fv \$(OBJS) \$(EXE)



.PHONY: _odir all _all clean exe
EOTARGET

# test
cat << TEST
TARGET='$TARGET'
SOURCES='$SOURCES'
INCLUDES='$INCLUDES'
LIBS='$LIBS'
LIBSDIR='$LIBSDIR'
COMPILER='$COMPILER'

cflags='$cflags'
ldflags='$ldflags'
defs='$defs'
incs='$incs'
TEST

cat $TARGET