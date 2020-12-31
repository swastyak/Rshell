#!/bin/bash

INPUTS=("echo 1 #comment")
../rshell ${INPUTS[0]}
INPU=("echo \"this string has a sharp #\ which should output\"")
../rshell ${INPU[0]}
I=("echo 2 #comment; echo 3 #anothercomment")
../rshell ${I[0]}
II=("ls #comment; exit")
../rshell ${II[0]}
II=("ls#comment; exit") #breaks when there is no space inbetween sharp and prev arg
../rshell ${II[0]}
