Mat cropSilhouette(Mat source,Mat object){
    Mat result;
    result = source.clone();
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

Mat cropSubtract(Mat source, Mat object){
    Mat result;
    result = source.clone();
    int width = source.size().width;
    int height = source.size().height;

    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            Vec3b value = object.at<uchar>(i,j);
            for(int k=0;k<3;k++){
                int temp = result.at<Vec3b>(i, j).val[k]-value.val[k];
                if(temp>255)
                    result.at<Vec3b>(i, j).val[k]=255;
                else if(temp<0)
                    result.at<Vec3b>(i, j).val[k]=0;
                else
                    result.at<Vec3b>(i, j).val[k] = temp;
            }
        }
    }

    return result;
}
