/*
    Rya Meyvriska
    G64164008
    Ilmu Komputer IPB
*/

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
#include "header/rgbhcbcr.h"

void faceDetection(){
    int ans;
    Mat img;
    img = imread("picture/1.png");
    do{
        cout<<"What do you want?\n\
        1. 128-Threshold\n\
        2. Otsu-Threshold\n\
        3. Sobel (Edge detection)\n\
        4. RGB-H-CbCr (Skin detection)\n\
        5. All\n\
        0. Back to Home\n";

        cin>>ans;

        if(ans==1){
            printMat("Before",img);
            printMat("128",threshold(img));
        }else if(ans==2){
            printMat("Before",img);
            printMat("Otsu",thresholdOtsu(img));
        }else if(ans==3){
            printMat("Before",img);
            printMat("Sobel",sobel());
        }else if(ans==4){
            printMat("Before",img);
            printMat("RGB-H-CbCr",GetSkin(img));
        }else if(ans==5){
            printMat("Before",img);
            printMat("128",threshold(img));
            printMat("Otsu",thresholdOtsu(img));
            printMat("Sobel",sobel());
            printMat("RGB-H-CbCr",GetSkin(img));
        }else if(ans==0){
            break;
        }else{
            cout<<"Sorry, your answer in not in our list. Please select again."<<endl;
        }
        waitKey();
    }while(ans!=0);
    img.release();
}

void negativeImage(){
    Mat img = imread("picture/1.png");
    printMat("Before",img);
    printMat("After",negative(img));
    waitKey();
    img.release();
}

void changeContrast(){
    Mat img = imread("picture/3.jpg");
    printMat("Before",img);
    printMat("After",contrast(img));
    waitKey();
    img.release();
}

void cropping(){
    int ans;
    Mat img,object;
    img = imread("picture/4.jpg");
    object = imread("picture/rya.jpg",0);
    do{
        cout<<"What do you want?\n\
        1. Crop with Silhouette\n\
        2. Pixrl Subtract\n\
        3. Crop Size with Threshold\n\
        4. All\n\
        0. Back to Home\n";

        cin>>ans;

        if(ans==1){
            printMat("Before",img);
            printMat("Object",object);
            printMat("Crop Silhouette",cropSilhouette(img,object));
        }else if(ans==2){
            printMat("Before",img);
            printMat("Object",object);
            printMat("Crop Substract",cropSubtract(img,object));
        }else if(ans==3){
            printMat("Before",img);
            printMat("Object",object);
            printMat("Crop Threshold",cropThreshold(cropSilhouette(img,object),0));
        }else if(ans==4){
            printMat("Before",img);
            printMat("Object",object);
            printMat("Crop Silhouette",cropSilhouette(img,object));
            printMat("Crop Substract",cropSubtract(img,object));
            printMat("Crop Threshold",cropThreshold(cropSilhouette(img,object),0));
        }else if(ans==0){
            break;
        }else{
            cout<<"Sorry, your answer in not in our list. Please select again."<<endl;
        }
        waitKey();
    }while(ans!=0);

    img.release();
    object.release();
}

int main(){
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
            faceDetection();
        }else if(answer==2){
            negativeImage();
        }else if(answer==3){
            changeContrast();
        }else if(answer==4){
           cropping();
        }else{
            cout<<"Sorry, your answer in not in our list. Please select again."<<endl;

        }
        cout<<"Thank you"<<endl;
    }while (answer!=0);
    return 0;
}
