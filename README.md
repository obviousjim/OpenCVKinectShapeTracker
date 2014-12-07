OpenCVKinectShapeTracker
========================

**Kinect 2 and OpenCV Shape Detection**

This example shows how to detect sphere like objects from the Kinect using a series of OpenCV steps

# Open a Kinect 2 color and depth stream
# Map the color information onto the depth information
# Segment the color frame using EGS image segmentation algorithm and ofxImageSegmentation
# Run contour tracking to determine geometric properties of each segment
# Filter out small, oversides, and oddly shaped segments
# Sense depth positions of the valid segments to find their 3D positions in space

