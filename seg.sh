#!/bin/sh

# First, clear the image output dir if already populated
if [ "$(ls "./bin/data/seg/")" ]; then
  echo "cleaning up old segments..."
  rm ./bin/data/seg/*.png
fi

make && make run