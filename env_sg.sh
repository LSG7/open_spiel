export OPEN_SPIEL_HOME=${PWD}
export LD_LIBRARY_PATH=${OPEN_SPIEL_HOME}/build_sg
export PYTHONPATH=$PYTHONPATH:$OPEN_SPIEL_HOME:$OPEN_SPIEL_HOME/build_sg/python

OS=$(uname)
if [ "$OS" = "Darwin" ]; then



else

fi