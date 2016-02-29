#!/bin/sh

# First, clear the image output dir if already populated
if [ "$(ls "./bin/data/seg"*)" ]; then
  echo "cleaning up old segments..."
  rm -r ./bin/data/seg*
fi

# Run either the command line app or make and make run.
if [ "$1" = "default" ]; then
  echo "Running command line project with default images..."
  open -n ./bin/./creativeProject.app/ --args $2 http://www.tekuto.com/wp-content/themes/tekuto2nd/images/topmain/toruso01.jpg?=20151006 long.jpg
elif [ "$1" = "interior" ]; then
  echo "Running command line project with interior images..."
  open -n ./bin/./creativeProject.app/ --args $2 https://s-media-cache-ak0.pinimg.com/564x/aa/d0/7c/aad07c449f29e9e106b62395e044250b.jpg https://s-media-cache-ak0.pinimg.com/564x/67/8a/ed/678aed334b030344482dc84f24063552.jpg https://s-media-cache-ak0.pinimg.com/564x/70/42/62/704262ee8e41c319f39da5ccb76d83b0.jpg
else
  make && make run
fi
