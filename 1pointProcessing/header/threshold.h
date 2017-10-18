
Mat thresholdOtsu(Mat source){
    int histogram[256];
    for(int i=0; i<256; i++) histogram[i] = 0;

    float sum=0,sumB=0;
    int q1=0,q2=0;
    float m1=0,m2=0,var=0,var_max=0;
    int th=0;

    Mat result;
    cvtColor(source,result,CV_BGR2GRAY);
    result = contrast(result);
    int width = result.size().width;
    int height = result.size().height;
    int N = width*height;

    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            int value = result.at<uchar>(i,j);
            histogram[value]++;
        }
    }

    for(int i=0;i<256;i++){
        sum += i*histogram[i];
    }
    for(int i=0;i<256;i++){
        q1 += histogram[i];
        if (q1!=0){
            q2 = N-q1;

            if (q2 == 0)
                break;

            sumB += (float) i*histogram[i];
            m1 = sumB/q1;
            m2 = (sum -sumB)/q2;

            var = (float) q1*q2*(m1-m2)*(m1-m2);

            if(var>var_max){
                th = i;
                var_max = var;
            }
        }
    }

    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            int value = result.at<uchar>(i,j);
            if(value<th)
                result.at<uchar>(i,j) = 0;
            else
                result.at<uchar>(i,j) = 255;
        }
    }
    return result;
}

Mat threshold(Mat source){
    Mat result;
    cvtColor(source,result,CV_BGR2GRAY);
    result = contrast(result);
    int width = result.size().width;
    int height = result.size().height;
    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            int value = result.at<uchar>(i,j);
            if(value<128)
                result.at<uchar>(i,j) = 0;
            else
                result.at<uchar>(i,j) = 255;
        }
    }
    return result;
}
