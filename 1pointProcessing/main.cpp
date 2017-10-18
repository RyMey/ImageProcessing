#include <iostream>
#include <cv.h>
#include <highgui.h>
using namespace std;
using namespace cv;

#include "header/negative.h"
#include "header/contrast.h"
#include "header/threshold.h"
#include "header/crop.h"

printBefore(Mat img){
    namedWindow("Before",CV_WINDOW_AUTOSIZE);
    imshow("Before", img);
}

printAfter(Mat img){
    namedWindow("After",CV_WINDOW_AUTOSIZE);
    imshow("After", img);
}

int main(){
    Mat img;

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
            Mat img2 = img;
            printBefore(img);

            img = threshold(img);
            namedWindow("128",CV_WINDOW_AUTOSIZE);
            imshow("128", img);

            img2 = thresholdOtsu(img2);
            namedWindow("Otsu",CV_WINDOW_AUTOSIZE);
            imshow("Otsu", img2);

            cout<<"Thank you"<<endl;
        }else if(answer==2){
            img = imread("picture/1.png");
            printBefore(img);

            img = negative(img);
            printAfter(img);
            cout<<"Thank you"<<endl;
        }else if(answer==3){
            img = imread("picture/3.jpg");
            printBefore(img);

            img = contrast(img);
            printAfter(img);
            cout<<"Thank you"<<endl;
        }else if(answer==4){
            img = imread("picture/4.jpg");
            printBefore(img);

            img = crop(img);
            printAfter(img);
            cout<<"Thank you"<<endl;
        }
        waitKey();
    }while (answer!=0);
    return 0;
}
