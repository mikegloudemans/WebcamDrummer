//
//  ImageConversion.hpp
//  WebcamDrummer
//
//  Created by Mark Govea on 4/7/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#ifndef WebcamDrummer_ImageConversion_hpp
#define WebcamDrummer_ImageConversion_hpp

#include <iostream>
#include <OpenGL/gl.h>
#include "opencv2/opencv.hpp"

GLuint matToTexture(cv::Mat &mat, GLenum minFilter, GLenum magFilter, GLenum wrapFilter);

#endif
