#include <iostream>
#include <vector>
#include <cmath>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

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

// menormalisasi data menjadi 0 - maxValue
void normalize(int array[], int length, int maxValue) {
    int maxElement = findMaxElement(array, length);
    for (int i = 0; i < length; i++) {
        double temp = ((double) array[i] / maxElement) * maxValue;
        array[i] = (int) temp;
    }
}

// mengubah isi array menjadi akumulasi nilai-nilai sebelum i
void transformToAccumulatedFrequency(int frequencyTable[], int length) {
    for (int i = 1; i < length; i++) {
        frequencyTable[i] += frequencyTable[i - 1];
    }
}

// untuk membuat gambar histogram
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

Mat originalHistogram(Mat &image) {
    // alokasi memori untuk menyimpan tabel frekuensi dengan index 0-255
    int frequencyTable[256] = {0};
    calculateIntensityFrequency(image, frequencyTable);

    // menemukan frekuensi terbanyak untuk menentukan tinggi
    int maxFrequency = findMaxElement(frequencyTable, 256);

    return createHistogram(frequencyTable, 512, maxFrequency + 5);
}

Mat normalizeScaleHistogram(Mat &image) {
    // alokasi memori untuk menyimpan tabel frekuensi dengan index 0-255
    int frequencyTable[256] = {0};
    calculateIntensityFrequency(image, frequencyTable);

    // menormalisasi, disini saya normalisasi agar matrixnya jadi 0-100 (karena kalau 0-1 jadi terlalu kecil)
    // normalisasi disini dengan max nilai di histogram (agar yg max 100),
    // karena jika normalisasi row*col hasilnya akan banyak yang sangat kecil
    normalize(frequencyTable, 256, 100);

    return createHistogram(frequencyTable, 512, 110);
}

Mat accumulateHistogram(Mat &image) {
    // alokasi memori untuk menyimpan tabel frekuensi dengan index 0-255
    int frequencyTable[256] = {0};
    calculateIntensityFrequency(image, frequencyTable);

    // mengakumulasi frekuensi
    transformToAccumulatedFrequency(frequencyTable, 256);

    // menormalisasi, disini saya normalisasi agar matrixnya jadi 0-100 (karena kalau 0-1 jadi terlalu kecil)
    // normalisasi disini dengan max nilai di histogram (agar yg max 100)
    // karena jika normalisasi row*col hasilnya akan banyak yang sangat kecil
    normalize(frequencyTable, 256, 100);

    return createHistogram(frequencyTable, 512, 110);
}

Mat equalizeImage(Mat &image) {
    // alokasi memori untuk menyimpan tabel frekuensi dengan index 0-255
    int frequencyTable[256] = {0};
    calculateIntensityFrequency(image, frequencyTable);

    transformToAccumulatedFrequency(frequencyTable, 256);

    int minFrequency = findMinElement(frequencyTable, 256);
    int width = image.size().width;
    int height = image.size().height;
    int size = width * height;

    // buat gambar baru dengan melakukan normalisasi grey scale nya
    Mat newImage(height, width, CV_8UC1);
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            double intensity =
                    ((double) frequencyTable[image.at<uchar>(y, x)] - minFrequency) / (double(size - 1)) * 255.0;
            newImage.at<uchar>(y, x) = (uchar) cvRound(intensity);
        }
    }

    return newImage;
}

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

    normalize(hist, hist, 0, 100, NORM_MINMAX, -1, Mat());

    return createHistogram(hist, 512, 110);
}

double minkowskiDistance(Mat &image1, Mat &image2, int p) {
    int frequencyTable1[256] = {0};
    calculateIntensityFrequency(image1, frequencyTable1);
    normalize(frequencyTable1, 256, 100);

    int frequencyTable2[256] = {0};
    calculateIntensityFrequency(image2, frequencyTable2);
    normalize(frequencyTable2, 256, 100);

    double sum = 0;
    for (int i = 0; i < 256; i++) {
        sum += pow(abs(frequencyTable1[i] - frequencyTable2[i]), p);
    }

    return pow(sum, 1.0 / p);
}

int main() {
    Mat image = imread("picture/2.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    showWindow("Image", image);

    showWindow("Original Histogram", originalHistogram(image));
    showWindow("OpenCV Original Histogram", openCvOriginalHistogram(image));

    showWindow("Normalized Histogram", normalizeScaleHistogram(image));
    showWindow("OpenCV Normalized Histogram", openCvNormalizeScaleHistogram(image));

    showWindow("Accumulated Histogram", accumulateHistogram(image));

    Mat equalizedImage = equalizeImage(image);
    showWindow("Equalized Image", equalizedImage);
    showWindow("Equalized Histogram", normalizeScaleHistogram(equalizedImage));

    Mat openCvEqualizedImage = openCvEqualizeImage(image);
    showWindow("OpenCV Equalized Image", openCvEqualizedImage);
    showWindow("OpenCV Equalized Histogram", normalizeScaleHistogram(openCvEqualizedImage));

    cout << minkowskiDistance(image, equalizedImage, 2) << "\n";

    waitKey();
    return 0;
}
