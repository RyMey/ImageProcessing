Mat crop(Mat source){
    Mat result,object;
    object = imread("picture/rya.jpg",0);

    result = source;
    int width = source.size().width;
    int height = source.size().height;

    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            int value = (int) object.at<uchar>(i,j);
            if(value>=128)
                result.at<Vec3b>(i, j) = 0;
        }
    }

    return result;
}
