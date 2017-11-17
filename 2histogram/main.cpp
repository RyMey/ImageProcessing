/*
    Rya Meyvriska
    G64164008
    Ilmu Komputer IPB
*/

#include <iostream>
#include <vector>
#include <cmath>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

#include "header/utility.h"
#include "header/opencvHist.h"
#include "header/original.h"
#include "header/normalize.h"
#include "header/accumulate.h"
#include "header/equalize.h"
#include "header/minkowski.h"

int main() {
    Mat image;
    int answer;
    do{
        cout<<"What do you want?\n\
        1. Original Histogram\n\
        2. Normalize Histogram\n\
        3. Accumulate Histogram\n\
        4. Equalize Histogram\n\
        5. Minkowski distance\n\
        0. Quit\n";

        cin>>answer;
        image = imread("picture/2.jpg", CV_LOAD_IMAGE_GRAYSCALE);
        showWindow("Original Image", image);

        if(answer==1){
            showWindow("Original Histogram", originalHistogram(image));
            showWindow("OpenCV Original Histogram", openCvOriginalHistogram(image));
        }else if(answer==2){
            showWindow("Normalized Histogram", normalizeScaleHistogram(image));
            showWindow("OpenCV Normalized Histogram", openCvNormalizeScaleHistogram(image));
        }else if(answer==3){
            showWindow("Accumulated Histogram", accumulateHistogram(image));
        }else if(answer==4){
            Mat equalizedImage = equalizeImage(image);
            showWindow("Equalized Image", equalizedImage);
            showWindow("Equalized Histogram", normalizeScaleHistogram(equalizedImage));

            Mat openCvEqualizedImage = openCvEqualizeImage(image);
            showWindow("OpenCV Equalized Image", openCvEqualizedImage);
            showWindow("OpenCV Equalized Histogram", normalizeScaleHistogram(openCvEqualizedImage));
        }else if(answer==5){
            Mat equalizedImage = equalizeImage(image);
            showWindow("Equalized Image", equalizedImage);

            Mat openCvEqualizedImage = openCvEqualizeImage(image);
            showWindow("OpenCV Equalized Image", openCvEqualizedImage);
            cout << "Old image vs New Image: "<<minkowskiDistance(image, equalizedImage, 2) << "\n";
            cout << "Manual vs openCV: "<<minkowskiDistance(openCvEqualizedImage, equalizedImage, 2) << "\n";
        }else if(answer==0){
            break;
        }else{
            cout<<"Sorry, your answer in not in our list. Please select again."<<endl;
        }
        cout<<"Thank you"<<endl;
        waitKey();
        destroyWindow("Original Image");
        image.release();
    }while (answer!=0);
    return 0;
}
