# architecture

An openframeworks-based project attempting to recreate styles of architecture from other shapes and epochs using openCV and ofxDelaunay.

This branch is using ofxDelaunay to segment the image into triangles, based on Harris corner detection, which can then be easily compared based on angle, rotation, scale and position.

The image that will be overlaying these triangles can then be translated into the positions of the segments it matches. This will therefore be creating a new image based on geometric properties of the original image.