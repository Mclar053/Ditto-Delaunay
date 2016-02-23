#!/bin/sh

# First, clear the image output dir if already populated
if [ "$(ls "./bin/data/seg"*)" ]; then
  echo "cleaning up old segments..."
  rm -r ./bin/data/seg*
fi

# Run either the command line app or make and make run.
if [ "$1" = "c" ]; then
  echo "Running command line project with default images..."
  open -n ./bin/./creativeProject.app/ --args http://www.tekuto.com/wp-content/themes/tekuto2nd/images/topmain/toruso01.jpg?=20151006 long.jpg
else
  make && make run
fi
