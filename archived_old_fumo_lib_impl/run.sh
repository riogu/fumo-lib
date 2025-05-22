DIR="build/"
project_name="${PWD##*/}"
BIN="${DIR}${project_name}"

cd $DIR
ninja && cd .. && ./$BIN
