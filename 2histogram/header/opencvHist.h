Mat openCvEqualizeImage(Mat &image) {
    Mat newImage;
    equalizeHist(image, newImage);

    return newImage;
}

Mat openCvCalcHist(Mat &image) {
    int histSize = 256;
    float range[] = {0, 255};
    const float *ranges[] = {range};

    Mat hist;
    calcHist(&image, 1, 0, Mat(), hist, 1, &histSize, ranges, true, false);

    return hist;
}

Mat openCvOriginalHistogram(Mat &image) {
    Mat hist = openCvCalcHist(image);

    // menemukan frekuensi terbanyak untuk menentukan tinggi
    int maxFrequency = cvRound(findMaxElement(hist, 256));

    return createHistogram(hist, 512, maxFrequency + 5);
}

Mat openCvNormalizeScaleHistogram(Mat &image) {
    Mat hist = openCvCalcHist(image);

    /*
    src – input array.
    dst – output array of the same size as src .
    alpha – norm value to normalize to or the lower range boundary in case of the range normalization.
    beta – upper range boundary in case of the range normalization; it is not used for the norm normalization.
    normType – normalization type.
    dtype – when negative, the output array has the same type as src; otherwise, it has the same number of channels as src and the depth =CV_MAT_DEPTH(dtype).
    mask – optional operation mask.
    */
    normalize(hist, hist, 0, 100, NORM_MINMAX, -1, Mat());

    return createHistogram(hist, 512, 110);
}

