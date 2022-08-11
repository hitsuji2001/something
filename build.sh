#!/bin/bash

CXX="${CXX:-g++}"
SRC_APP="./src/*.cpp ./opengl-templates/src/*.cpp ./glad/src/glad.c"
CFLAGS="-Werror -Wall -Wextra -pedantic -lm -lstdc++"
OFLAGS="-lGL -lX11 -lpthread -lXrandr -lXi -ldl"
LIBS="opengl glfw3"
OUT="something"

set -xe

compile() {
    $($CXX $SRC_APP $CFLAGS $OFLAGS -o $OUT $(pkg-config --cflags --libs $LIBS))
    if [[ $? -ne 0 ]]
    then
	echo "ERROR: Compile failed!"
	exit 1
    else
	echo "Compile succesfully!"
    fi
}

run() {
    $(./$OUT)
}

list_option() {
    echo "--compile, -c : Compile the project."
    echo "--run, -r     : Run the project (WITHOUT recompiling)."
    echo "--compile-and-run, -car : Compile and run the project."
    echo "--list-option, -l : Display this list."
    echo "--help, -h : Display help/usage."
    exit 0
}

display_help() {
    echo "[USAGE]: $0 [flag]"
    echo "[HELP] : use '--list-option' or '-l' flag to list all options"
    exit 0
}

if [[ $# -lt 1 ]]
then
    display_help
else
    case "$1" in
	"--compile" | "-c")
	    compile
	    ;;
	"--run" | "-r")
	    run
	    ;;
	"--compile-and-run" | "-car")
	    compile
	    run
	    ;;
	"--list-option" | "-l")
	    list_option
	    ;;
	"--help" | "-h")
	    display_help
	    ;;
    esac
fi
