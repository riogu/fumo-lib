DIR="build/"
if [ ! -d "$DIR" ]; then
    mkdir ${DIR}
fi
project_name="${PWD##*/}"
EPIC="${project_name}"
cd $DIR
cmake .. -G Ninja -DCMAKE_EXPORT_COMPILE_COMMANDS=On -DCMAKE_BUILD_TYPE=Debug

BIN="${DIR}${project_name}"
ninja && cd .. && ./$BIN

