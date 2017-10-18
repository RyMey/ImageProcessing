Mat negative(Mat source){
    Mat result;
    cvtColor(source,result,CV_BGR2GRAY);
    int width = result.size().width;
    int height = result.size().height;

    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            Vec3b temp = result.at<Vec3b>(i,j);
            for(int k=0;k<3;k++){
                result.at<Vec3b>(i, j).val[k] = 255 - (int) temp.val[k];
            }
        }
    }

    return result;
}
