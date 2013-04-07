//
//  Camera.hpp
//  WebcamDrummer
//
//  Created by Mark Govea on 4/7/13.
//

#ifndef WebcamDrummer_Camera_hpp
#define WebcamDrummer_Camera_hpp

#include <iostream>
#include "opencv2/opencv.hpp"

struct point2d {
    float x;
    float y;
};

struct processedFrame {
    cv::Mat image;
    point2d* points;
};

class Camera
{
private:
    cv::VideoCapture cap;
public:
	Camera(int cameraSource = 0);
    point2d getSize();
	processedFrame nextFrame();
};

#endif
