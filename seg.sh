#!/bin/sh

# First, clear the image output dir if already populated
if [ "$(ls "./bin/data/seg"*)" ]; then
  echo "cleaning up old segments..."
  rm -r ./bin/data/seg*
fi

make && make run