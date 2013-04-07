//
//  Camera.cpp
//  WebcamDrummer
//
//  Created by Mark Govea on 4/6/13.
//

#include "Camera.hpp"

using namespace cv;

// keep these allocated (should be faster)
Mat imgProcessed;

Camera::Camera(int cameraSource) : cap(cameraSource)
{
    if(!cap.isOpened())  // check if we succeeded
        throw "Camera failed to initialize!";
}

point2d Camera::getSize()
{
    point2d result;
    result.x = (float) cap.get(CV_CAP_PROP_FRAME_WIDTH);
    result.y = (float) cap.get(CV_CAP_PROP_FRAME_HEIGHT);
    return result;
}

processedFrame Camera::nextFrame()
{
    Mat frame;
    Mat drawing;
    
    // get a new frame from camera
    cap >> frame;
    
    // start drawing the output - flip the frame
    flip(frame, drawing, 1);
    
    // smoothing
    blur(drawing, imgProcessed, Size(3,3), Point(-1,-1), BORDER_DEFAULT);
    //GaussianBlur(drawing, imgHSV, Size(5,5), 1, 1);
    
    // convert to hsv for thresholding
    cvtColor(imgProcessed, imgProcessed, CV_BGR2HSV);
    
    // green thresholding
    inRange(imgProcessed, Scalar(32, 88, 60), Scalar(44, 180, 230), imgProcessed);
    
    
    // detect "green" blobs in binary image
    
    // blob detection parameters
    SimpleBlobDetector::Params params;
    params.minDistBetweenBlobs = 30;
    params.filterByInertia = false;
    params.filterByConvexity = false;
    params.filterByColor = false;
    params.filterByCircularity = false;
    params.filterByArea = true;
    params.minArea = 80;
    params.maxArea = 20000;
    
    // set up detector using the parameters
    Ptr<cv::FeatureDetector> blob_detector = new SimpleBlobDetector(params);
    blob_detector->create("SimpleBlob");
    
    // detect blobs!
    vector<cv::KeyPoint> keypoints;
    blob_detector->detect(imgProcessed, keypoints);
    
    
    // prepare for return
    processedFrame result;
    result.points = new point2d[keypoints.size()];
    
    // loop over blob keypoints
    for (int i=0; i<keypoints.size(); i++){
        
        // extract the x y coordinates of the blob keypoint
        float X=keypoints[i].pt.x; 
        float Y=keypoints[i].pt.y;
        
        // draw keypoint on image
        circle(drawing, Point(X,Y), 15, Scalar(0, 20, 255), -1, 8, 0);
        
        // add point to return result
        result.points[i].x = X;
        result.points[i].y = Y;
    }
    
    // convert Mat (drawing) to texture
    GLuint texture[1];
    glGenTextures(1, &texture[0]);
    glBindTexture(GL_TEXTURE_2D, texture[0]);               
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); 
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); 
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S , GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    glTexImage2D(GL_TEXTURE_2D, 0, 3, drawing.cols, drawing.rows, 0, GL_RGB, GL_UNSIGNED_BYTE, drawing.data);
    
    // add image to return result
    result.image = texture;
    
    return result;
}