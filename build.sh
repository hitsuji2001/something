#!/bin/bash

CXX="${CXX:-g++}"
SRC_APP="./main.cpp ./opengl-template.cpp ./glad/src/glad.c"
CFLAGS="-Werror -Wall -Wextra -pedantic -ggdb"
OFLAGS="-lGL -lX11 -lpthread -lXrandr -lXi -ldl"
LIBS="opengl glfw3"
OUT="something"

set -xe

$($CXX $SRC_APP $CFLAGS $OFLAGS -o $OUT $(pkg-config --cflags --libs $LIBS))

if [[ $? -ne 0 ]]
then
    echo "ERROR: Compile failed!"
    exit 1
else
    echo "Compile succesfully!"
    exit 0
fi
