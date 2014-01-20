#ifndef _V4L2_CAP_
#define _V4L2_CAP_
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/background_segm.hpp>
using namespace cv;

VideoCapture v4l2cap(int device, int width, int height, int fps);

#endif
