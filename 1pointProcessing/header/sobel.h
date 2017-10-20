/*
    Rya Meyvriska
    G64164008
    Ilmu Komputer IPB
*/

int xG(Mat source, int x, int y){
    return ((int)source.at<uchar>(y-1, x-1) + 2*(int)source.at<uchar>(y, x-1) + (int)source.at<uchar>(y+1, x-1))
            - ((int)source.at<uchar>(y-1, x+1) + (int)source.at<uchar>(y+1, x+1) + 2*(int)source.at<uchar>(y, x+1));
}

int yG(Mat source, int x, int y){
    return ((int)source.at<uchar>(y-1, x-1) + 2*(int)source.at<uchar>(y-1, x) + (int)source.at<uchar>(y-1, x+1))
            - ((int)source.at<uchar>(y+1, x-1)+2*(int)source.at<uchar>(y+1, x)+(int)source.at<uchar>(y+1, x+1));
}

Mat sobel(){
    Mat source = imread("picture/1.png", CV_LOAD_IMAGE_GRAYSCALE);
    Mat result;
//    if(source.channels()==1)
        result = source.clone();
//    else
//        cvtColor(source,result,CV_BGR2GRAY); //pixel from load and convert are different :(

    int gx,gy,sum;
    int width = source.size().width;
    int height = source.size().height;

    cout<<(int)source.at<uchar>(0,0);

    for(int i=1; i<height-1; i++){
            for(int j=1; j<width-1; j++){
                gx = xG(source, j, i);
                gy = yG(source, j, i);
                sum = abs(gx) + abs(gy);
                sum = sum > 255 ? 255:sum;
                sum = sum < 0 ? 0 : sum;
                result.at<uchar>(i,j) = sum;
            }
        }

    return result;
}

