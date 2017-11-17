/*
    Rya Meyvriska
    G64164008
    Ilmu Komputer IPB
*/

// helper method untuk menampilkan window
void showWindow(const String &name, const Mat &content) {
    namedWindow(name, CV_WINDOW_AUTOSIZE);
    imshow(name, content);
}

// untuk menghitung frekuensi intensitas grey scale di matrix
void calculateIntensityFrequency(Mat &image, int *result) {
    int width = image.size().width;
    int height = image.size().height;

    // menambahkan index sesuai frekuensi yang ada
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            result[(int) image.at<uchar>(y, x)]++;
        }
    }
}

// untuk membuat gambar histogram (untuk buatan sendiri)
Mat createHistogram(int frequencyTable[], int width, int height) {
    int bin_w = cvRound((double) width / 256); //hanya untuk memperlebar jarak sehingga full dan terlihat

    Mat histogram(height, width, CV_8UC1, Scalar(255, 255, 255));

    // menggambar line
    for (int i = 0; i < 256; i++) {
        line(histogram, Point(bin_w * (i), height), Point(bin_w * (i), height - frequencyTable[i]), Scalar(0, 0, 0), 1,
             8, 0);
    }

    return histogram;
}

//membuat histogram from Mat (untuk opencv)
Mat createHistogram(Mat &mat, int width, int height) {
    int bin_w = cvRound((double) width / 256); //hanya untuk memperlebar jarak sehingga full dan terlihat

    Mat histogram(height, width, CV_8UC1, Scalar(255, 255, 255));

    // menggambar line
    for (int i = 0; i < 256; i++) {
        line(histogram, Point(bin_w * (i), height), Point(bin_w * (i), height - cvRound(mat.at<float>(i))),
             Scalar(0, 0, 0), 1, 8, 0);
    }

    return histogram;
}

// mencari nilai minimum di dalam array yang bukan 0
int findMinElement(int array[], int length) {
    int min = 0;
    for (int i = 0; i < length; i++) {
        if (array[i] > 0) {
            if (min == 0) {
                min = array[i];
            } else if (array[i] < min) {
                min = array[i];

            }
        }
    }
    return min;
}

// mencari nilai maksimum di dalam array
int findMaxElement(int array[], int length) {
    int max = array[0];
    for (int i = 1; i < length; i++) {
        if (max < array[i]) {
            max = array[i];
        }
    }
    return max;
}

// mencari nilai maksimum di dalam matrix
float findMaxElement(Mat &mat, int length) {
    float max = mat.at<float>(0);
    for (int i = 1; i < length; i++) {
        if (max < mat.at<float>(i)) {
            max = mat.at<float>(i);
        }
    }
    return max;
}


