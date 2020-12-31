#!/bin/sh
#INPUTS=("echo \"this is a         really || && stupid test \"")
#../rshell ${INPUTS[0]}


INPUTS=("echo tay keith; exit")
../rshell ${INPUTS[0]}
I=("echo hello; exit")
../rshell ${I[0]}
a=("echo \"&&\"; exit")
../rshell ${a[0]}
b=("echo \"||\"; exit")
../rshell ${b[0]}
II=("false; exit")
../rshell ${II[0]}
III=("echo \"this is a really || && () long test to make sure connectors and pipes show up as arguments test\"; exit")
../rshell ${III[0]}
IIII=("mkdir test; exit")
../rshell ${IIII[0]}
aaa=("ls; exit")
../rshell ${aaa[0]}
IIIII=("echo \"test && ||\"; exit")
../rshell ${IIIII[0]}
aa=("ls; exit")
../rshell ${aa[0]}
