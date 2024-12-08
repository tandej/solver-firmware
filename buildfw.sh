#!/bin/sh

# give argument of directory name to build firmware from

if [ $# -lt 1 ]
then
    echo "did not specify which directory to build firmware from!"
    return 1
fi

if [ $1 != "motor-sequencer" ] && true
then
    echo "unrecognized firmware to build!"
    return 1
fi

echo "building $1 firmware..."
echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
echo

cd $1
cmake .
make