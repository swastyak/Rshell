#!/bin/sh
a=("(echo A && echo B) || (echo C && echo D)")
../rshell ${a[0]}
b=("((echo Hello && echo Bye) && echo What) || echo wontoutput")
../rshell ${b[0]}
c=("(false && echo B) || (echo C && echo D)")
../rshell ${c[0]}
d=("(false && echo B) && (echo C && echo D); echo \"only this should output\"")
../rshell ${d[0]}
e=("(mkdir directory_should_not_make")
../rshell ${e[0]}
f=("(echo 1 && echo 2)")
../rshell ${f[0]}
g=("(echo 1 || echo 2)")
../rshell ${g[0]}
h=("([ ../test ] && echo \"test exists\") || echo \"test does not exist\"")
../rshell ${h[0]}
i=("(echo)")
../rshell ${i[0]}
j=("((echo a || ls) && (echo a || ls)) || (echo a || ls) && (echo a || ls) && (echo a || ls) && (echo a || ls) && (echo a || ls) && (echo a || ls) && (echo a || ls) && (echo a || ls)")
../rshell ${j[0]}
