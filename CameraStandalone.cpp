//
//  CameraStandalone.cpp
//  WebcamDrummer
//
//  Created by Mark Govea on 4/6/13.
//

#include <iostream>
#include "opencv2/opencv.hpp"

using namespace cv;

int main(int, char**)
{
    VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return -1;
    
    Mat drawing;
    Mat imgHSV;
    Mat imgGrn;
    namedWindow("Detected Regions",1);
    namedWindow("ComputerVision Output",2);
    
    for(;;)
    {
        Mat frame;
        
        // get a new frame from camera
        cap >> frame;
        
        // start drawing the output - flip the frame
        flip(frame, drawing, 1);
        
        // smoothing
        blur(drawing, imgHSV, Size(3,3), Point(-1,-1), BORDER_DEFAULT);
        //GaussianBlur(drawing, imgHSV, Size(5,5), 1, 1);
        
        // convert to hsv for thresholding
        cvtColor(imgHSV, imgHSV, CV_BGR2HSV);
        
        // green thresholding
        inRange(imgHSV, Scalar(32, 88, 60), Scalar(44, 180, 230), imgGrn);
        
        
        // detect "green" blobs in binary image
        
        // parameters
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
        
        // detect!
        vector<cv::KeyPoint> keypoints;
        blob_detector->detect(imgGrn, keypoints);
        
        // extract the x y coordinates of the blob keypoints:
        for (int i=0; i<keypoints.size(); i++){
            float X=keypoints[i].pt.x; 
            float Y=keypoints[i].pt.y;
            
            circle(drawing, Point(X,Y), 15, Scalar(0, 20, 255), -1, 8, 0);
        }
        
        
        // draw
        imshow("Detected Regions", imgGrn);
        imshow("ComputerVision Output", drawing); 
        if(waitKey(30) >= 0) break;
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}