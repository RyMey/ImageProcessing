#include <iostream>
#include <cv.h>
#include <highgui.h>
#include<cmath>
using namespace std;
using namespace cv;

#include "header/utils.h"
#include "header/negative.h"
#include "header/contrast.h"
#include "header/threshold.h"
#include "header/crop.h"
#include "header/sobel.h"

int main(){
    Mat img,img2;
    int answer;
    do{
        cout<<"What do you want?\n\
        1. Face Detection\n\
        2. Negative Image\n\
        3. Change Contrast\n\
        4. Cropping\n\
        0. Quit\n";

        cin>>answer;

        if(answer==1){
            img = imread("picture/1.png");
            img2 = img.clone();
            printMat("Before",img);

            img = threshold(img);
            printMat("128",img);

            img2 = thresholdOtsu(img2);
            printMat("Otsu",img2);

            printMat("Sobel",sobel());
        }else if(answer==2){
            img = imread("picture/1.png");
            printMat("Before",img);

            img = negative(img);
            printMat("After",img);
        }else if(answer==3){
            img = imread("picture/3.jpg");
            printMat("Before",img);

            img = contrast(img);
            printMat("After",img);
        }else if(answer==4){
            Mat object = imread("picture/rya.jpg",0);
            img = imread("picture/4.jpg");
            img2 = img.clone();
            Mat img3;
            printMat("Before",img);

            img = cropSilhouette(img,object);
            printMat("Crop Silhouette",img);
            img3 = img.clone();

            img2 = cropSubtract(img2,object);
            printMat("Crop Substract",img2);

            printMat("Object",object);

            img3 = cropThreshold(img3,0);
            printMat("Crop Threshold",img3);
        }else{
            cout<<"Sorry, your answer in not in our list. Please select again."<<endl;

        }
        cout<<"Thank you"<<endl;
        img.release();
        img2.release();
        waitKey();
    }while (answer!=0);
    return 0;
}
