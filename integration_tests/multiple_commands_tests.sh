#!/bin/bash
EXAMPLEFROMSPECS=("ls -a; echo hello && mkdir test || echo world; git status")
../rshell ${EXAMPLEFROMSPECS[0]}
SIMPLE=("echo 1; ls; echo 2")
../rshell ${SIMPLE[0]}
SIMPLEII=("echo hello; mkdir test; ls -a")
../rshell ${SIMPLEII[0]}
ALLCONNECT=("echo hello && mkdir test || ls -a") #
../rshell ${ALLCONNECT[0]}
CONNECT=("echo 1 || echo 2 && echo 3; echo 4")
../rshell ${CONNECT[0]}
SIMPLEAND=("echo 1 && echo 2")
../rshell ${SIMPLEAND[0]}
SIMPLEPIPE=("echo 1 || echo 2")
../rshell ${SIMPLEPIPE[0]}
SIMPLESCOLON=("echo 1; echo 2")
../rshell ${SIMPLESCOLON[0]}
INPUTTWO=("(exit 1); echo 1; echo 2") #this breaks
../rshell ${INPUTTWO[0]}

I3=("mkdir test; echo test; ls -la")
../rshell ${I3}
INPUTSONE=("echo hi && echo \"testing || && echo with connectors\"") #
../rshell ${INPUTSONE[0]}

II=("ls -a && echo 2 || echo 3; echo 4")
../rshell ${II[0]}
III=("fghbtrtyuj -a && echo should_not_output || echo should_output; echo always_output")
../rshell ${III[0]}
IIII=("echo always_outputs && echo should_output || echo should_not_output; echo always_out")
../rshell ${IIII[0]}
I5=("mkdir test2; ls -a && echo \"hello world\"")
../rshell ${I5[0]}



#../rshell lsssss -la; echo 3
#../rshell NULL
#../rshell echo 1; ls
#../rshell echo hello; ls -a; echo world
