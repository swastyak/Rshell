#!/bin/bash

INPUTS=("echo 1 #comment && exit")
../rshell ${INPUTS[0]}
I=("exit")
../rshell ${I[0]}
II=("ls -a; exit")
../rshell ${II[0]}
III=("exit; ls")
../rshell ${III[0]}
IIII=("gibberish || exit")
../rshell ${IIII[0]}
IIIII=("gibberish && exit")
../rshell ${IIIII[0]}
IIIIII=("gibberish; exit")
../rshell ${IIIIII[0]}
IIIIIII=("ls -la; exit; echo shouldnotbeecho")
../rshell ${IIIIIII[0]}
