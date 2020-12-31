#!/bin/sh
a=("[ -e ../test ]")
../rshell ${a[0]}
#b=("[ -e test/file/path ] && echo \"path exists\"")
#../rshell ${b[0]}
c=("[ ../test ] && echo \"path exists\"")
../rshell ${c[0]}
d=("[ ../testt ] || echo \"path should not exist so this should execute\"")
../rshell ${d[0]}
e=("[ -d ../test ] && echo \"path exists and is a directory\"")
../rshell ${e[0]}
f=("[ -f ../test ] || echo \"path may or may not exist, but is not a file\"")
../rshell ${f[0]}
g=("[ -f ../names.txt ] && echo \"file exists\"")
../rshell ${g[0]}
h=("[ -d ../names.txt ] || echo \"path may or may not exist, but is not a directory\"")
../rshell ${h[0]}
i=("[ -d ../names.txt ] &&  echo \"file exists\" || echo \"is not a directory\"")
../rshell ${i[0]}
j=("[ -f ../names.txt ] &&  echo \"file exists\" || echo \"something went wrong\"")
../rshell ${j[0]}
k=("[ -d ../names.txt ] #making sure everything else is ignored here")
../rshell ${k[0]}
l=("[ -d ../names.txt ]#making sure sharp sign next to bracket won't break program if you read this it's broken")
../rshell ${;[0]}
m=("[ -d ../names.txt ] &&  echo 1 || echo \"should echo this and not 1\"")
../rshell ${m[0]}
