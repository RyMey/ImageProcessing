#include <iostream>
#include <cv.h>
#include <highgui.h>
using namespace std;
using namespace cv;

#include "negative.h"

int main(){
    Mat img;
    img = imread("picture/0.png",CV_LOAD_IMAGE_COLOR);

    img = negative(img);
    namedWindow("Hasil",CV_WINDOW_AUTOSIZE);
    imshow("Hasil", img);
    waitKey();
    return 0;
}
