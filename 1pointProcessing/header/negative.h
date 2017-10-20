Mat negative(Mat source){
    Mat result;
    if(source.channels()==1)
        result = source.clone();
    else
        cvtColor(source,result,CV_BGR2GRAY);

    int width = result.size().width;
    int height = result.size().height;

    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            int value = (int) result.at<uchar>(i,j);
            result.at<uchar>(i,j) = 255 - value;
        }
    }

    return result;
}
