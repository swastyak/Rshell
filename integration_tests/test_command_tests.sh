#!/bin/sh
a=("test -e ../test ")
../rshell ${a[0]}
aa=("test ../test ")
../rshell ${aa[0]}
aaa=("test -f ../names.txt")
../rshell ${aaa[0]}
#b=("test -e test/file/path && echo \"path exists\"")
#../rshell ${b[0]}
c=("test ../test && echo \"path exists\"")
../rshell ${c[0]}
d=("test ../testt  || echo \"path should not exist so this should execute\"")
../rshell ${d[0]}
e=("test -d ../test && echo \"path exists and is a directory\"")
../rshell ${e[0]}
f=("test -f ../test || echo \"path may or may not exist, but is not a file\"")
../rshell ${f[0]}
g=("test -f ../names.txt && echo \"file exists\"")
../rshell ${g[0]}
h=("test -d ../names.txt || echo \"path may or may not exist, but is not a directory\"")
../rshell ${h[0]}
i=("test -d ../names.txt &&  echo \"file exists\" || echo \"may or may not exist but is not a directory\"")
../rshell ${i[0]}
j=("test -f ../names.txt &&  echo \"file exists\" || echo \"something went wrong\"")
../rshell ${j[0]}
k=("test -d ../names.txt #making sure everything else is ignored here")
../rshell ${k[0]}
l=("test -d ../names.txt#making sure sharp sign next to argument won't break program if you read this it's broken")
../rshell ${;[0]}
m=("test -d ../names.txt &&  echo 1 || echo \"should echo this and not 1\"")
../rshell ${m[0]}
