
** Kinect 2 and OpenCV Shape Detection

This example shows how to detect sphere like objects from the Kinect using a series of OpenCV steps

1) Open a Kinect 2 color and depth stream
2) Map the color information onto the depth information
3) Segment the color frame using EGS image segmentation algorithm and ofxImageSegmentation
4) Run contour tracking to determine geometric properties of each segment
5) Filter out small, oversides, and oddly shaped segments
6) Sense depth positions of the valid segments to find their 3D positions in space

