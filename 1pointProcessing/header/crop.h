Mat cropSilhouette(Mat source,Mat object){
    Mat result = source.clone();
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

Mat cropSubtract(Mat source,Mat object){
    Mat result=source.clone();
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

Mat cropRectangle(Mat source){
    Mat result;
    int width = source.size().width;
    int height = source.size().height;
    int minX=width,maxX=0,minY=height,maxY=0;
    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            Scalar temp = source.at<uchar>(i,j);
            if(temp.val[0]!=0 && j<minX){
                minX = j;
            }else if(temp.val[0]!=0 && j>maxX ){
                maxX = j;
            }else if(temp.val[0]!=0 && i<minY){
                minY = i;
            }else if(temp.val[0]!=0 && i>maxY){
                maxY = i;
            }
        }
    }
    cout<<minX<<" "<<maxX<<" "<<minY<<" "<<maxY<<endl;
    cout<<width<<" "<<height<<" "<<source.size()<<endl;

    result = Mat(maxY,maxX, CV_64F, double(0));

    for(int i=minY;i<=maxY;i++){
        for(int j=minX;j<=maxX;j++){
             for(int k=0;k<3;k++){
                result.at<Vec3b>(i,j)[k]=source.at<Vec3b>(i,j)[k];
             }
        }
    }

    return result;
}
