#!/bin/sh

scriptname=$(basename $0)
version="0.0.1"

dohelp() {
	local exitcode=0

	[ $# -ne 0 ] && exitcode=$1	
cat << DOHELP
${scriptname} version ${version}
${scriptname} [--help] : this text
${scriptname} TARGET --sources SOURCES [OPTIONS]
TARGET : the name of the Makefile
SOURCES : directories where are the source files
OPTIONS :
--includes INCLUDES : directories of header files
	--libs LIBS : list of libs
	--libsdir LIBSDIR : directories of libraries
	
NOTE :	
Each list of directories or files is a semi-colons separated list as PATH
DOHELP

	exit $exitcode
}


	dohelp 