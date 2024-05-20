export OPEN_SPIEL_HOME=${PWD}
export LD_LIBRARY_PATH=${OPEN_SPIEL_HOME}/build_sg
export PYTHONPATH=$PYTHONPATH:$OPEN_SPIEL_HOME:$OPEN_SPIEL_HOME/build_sg/python

export DBUILD_SHARED_LIB=ON
export CC=gcc-13
export CXX=g++-13
#export CC=clang-17
#export CXX=clang++-17

echo CC=$CC
echo CXX=$CXX

OS=$(uname)
if [ "$OS" = "Darwin" ]; then
echo "OS is Darwin(Mac)"
elif [ "$OS" = "Linux" ]; then
echo "OS is Linux"
else
echo "This OS is not supported"
fi