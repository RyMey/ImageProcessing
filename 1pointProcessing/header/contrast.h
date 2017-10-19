Mat contrast(Mat source){
    Mat result;
    result = source.clone();
    int width = source.size().width;
    int height = source.size().height;
    int minContrast = 255;
    int maxContrast = 0;

    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            Vec3b temp = source.at<Vec3b>(i,j);
            for(int k=0;k<3;k++){
                int value = (int) source.at<Vec3b>(i,j).val[k];
                if(value<minContrast)
                    minContrast = value;
                else if(value>maxContrast)
                    maxContrast = value;
            }
        }
    }

    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            Vec3b temp = source.at<Vec3b>(i,j);
            for(int k=0;k<3;k++){
                int value = (int) source.at<Vec3b>(i,j).val[k];
                result.at<Vec3b>(i,j).val[k] = (value-minContrast)*(255/(maxContrast-minContrast));
            }
        }
    }

    return result;
}
