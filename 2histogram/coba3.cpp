#include<iostream>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

void originalHistogram(Mat image){
     // alokasi memori untuk menyimpan histogram dengan index 0-255
    int histogram[256];

    // inisialisasi semua nilai 0
    for(int i = 0; i < 255; i++){
        histogram[i] = 0;
    }

    // menambahkan index sesuai frekuensi yang ada
    int width = image.size().width;
    int height = image.size().height;

    for(int y = 0; y < height; y++)
        for(int x = 0; x < width; x++)
            histogram[(int)image.at<uchar>(y,x)]++;

    // menemukan maxHist untuk menentkan tinggi
    int maxHist = histogram[0];
    for(int i = 1; i < 256; i++){
        if(maxHist < histogram[i]){
            maxHist = histogram[i];
        }
    }

    // menggambar histogram
    int hist_w = 512; int hist_h = maxHist+5; //deklarasi panjang dan lebar histogram yang akan di cetak
    int bin_w = cvRound((double) hist_w/256); //hanya untuk memperlebar jarak sehingga full dan terlihat

    Mat histImage(hist_h, hist_w, CV_8UC1, Scalar(255, 255, 255));

    // menggambar line
    for(int i = 0; i < 255; i++){
        line(histImage, Point(bin_w*(i), hist_h), Point(bin_w*(i), hist_h - histogram[i]),Scalar(0,0,0), 1, 8, 0);
    }

    // menampilkan
    namedWindow("Original Histogram", CV_WINDOW_AUTOSIZE);
    imshow("Original Histogram", histImage);
}

void normalizeScaleHistogram(Mat image){
    // alokasi memori untuk menyimpan histogram dengan index 0-255
    int histogram[256];

    // inisialisasi semua nilai 0
    for(int i = 0; i < 255; i++){
        histogram[i] = 0;
    }

   // menambahkan index sesuai frekuensi yang ada
    int width = image.size().width;
    int height = image.size().height;

    for(int y = 0; y < height; y++)
        for(int x = 0; x < width; x++)
            histogram[(int)image.at<uchar>(y,x)]++;

    // menggambar histogram
    int hist_w = 512; int hist_h = 110; //deklarasi panjang dan lebar histogram yang akan di cetak
    int bin_w = cvRound((double) hist_w/256); //hanya untuk memperlebar jarak sehingga full dan terlihat

    Mat histImage(hist_h, hist_w, CV_8UC1, Scalar(255, 255, 255));

    // menemukan maxHist untuk normalisasi
    int maxHist = histogram[0];
    for(int i = 1; i < 256; i++){
        if(maxHist < histogram[i]){
            maxHist = histogram[i];
        }
    }
     // menormalisasi, disini saya normalisasi agar matrixnya jadi 0-100 (karena kalau 0-1 jadi terlalu kecil)
     //normalisasi disini dengan max nilai di histogram (agar yg max 100), karena jika normalisasi row*col hasilnya akan banyak yang sangat kecil
    for(int i = 0; i < 255; i++){
        double temp = ((double)histogram[i]/maxHist)*100;
        histogram[i] = (int) temp;
    }

    // menggambar line
    for(int i = 0; i < 255; i++){
        line(histImage, Point(bin_w*(i), hist_h), Point(bin_w*(i), hist_h - histogram[i]),Scalar(0,0,0), 1, 8, 0);
    }

    // menampilkan
    namedWindow("Normalisasi Histogram", CV_WINDOW_AUTOSIZE);
    imshow("Normalisasi Histogram", histImage);
}

void accumulateHistogram(Mat image){
    // alokasi memori untuk menyimpan histogram dengan index 0-255
    int histogram[256];

    // inisialisasi semua nilai 0
    for(int i = 0; i < 255; i++){
        histogram[i] = 0;
    }

   // menambahkan index sesuai frekuensi yang ada
    int width = image.size().width;
    int height = image.size().height;

    for(int y = 0; y < height; y++)
        for(int x = 0; x < width; x++)
            histogram[(int)image.at<uchar>(y,x)]++;

     // menemukan maxHist untuk normalisasi
    int maxHist = histogram[0];
    for(int i = 1; i < 256; i++){
        if(maxHist < histogram[i]){
            maxHist = histogram[i];
        }
    }
     // menormalisasi, disini saya normalisasi agar matrixnya jadi 0-100 (karena kalau 0-1 jadi terlalu kecil)
     //normalisasi disini dengan max nilai di histogram (agar yg max 100), karena jika normalisasi row*col hasilnya akan banyak yang sangat kecil
    for(int i = 0; i < 255; i++){
        double temp = ((double)histogram[i]/maxHist)*10;
        histogram[i] = (int) temp;
    }

    // mengakumulasi histogram
    for(int i = 1; i < 255; i++){
        histogram[i] += histogram[i-1];
    }

    // menemukan maxHist lagi untuk menentkan tinggi
    maxHist = histogram[0];
    for(int i = 1; i < 256; i++){
        if(maxHist < histogram[i]){
            maxHist = histogram[i];
        }
    }

    // menggambar histogram
    int hist_w = 512; int hist_h = maxHist+5; //deklarasi panjang dan lebar histogram yang akan di cetak
    int bin_w = cvRound((double) hist_w/256); //hanya untuk memperlebar jarak sehingga full dan terlihat

    Mat histImage(hist_h, hist_w, CV_8UC1, Scalar(255, 255, 255));

    // menggambar line
    for(int i = 0; i < 255; i++){
        line(histImage, Point(bin_w*(i), hist_h), Point(bin_w*(i), hist_h - histogram[i]),Scalar(0,0,0), 1, 8, 0);
    }

    // menampilkan
    namedWindow("Accumulate Histogram", CV_WINDOW_AUTOSIZE);
    imshow("Accumulate Histogram", histImage);
}

void equalizeHistogram(Mat image){
   // alokasi memori untuk menyimpan histogram dengan index 0-255
    int histogram[256];
    int akumulasi[256];
    int C[256];

    // inisialisasi semua nilai 0
    for(int i = 0; i < 255; i++){
        histogram[i] = 0;
    }

   // menambahkan index sesuai frekuensi yang ada
    int width = image.size().width;
    int height = image.size().height;

    for(int y = 0; y < height; y++)
        for(int x = 0; x < width; x++)
            histogram[(int)image.at<uchar>(y,x)]++;

    // mengisi nilai akumulasi
    akumulasi[0] = histogram[0];
    for(int i = 1; i < 255; i++){
        akumulasi[i] += histogram[i-1];
    }

     // menemukan maxHist untuk normalisasi
    int maxHist = histogram[0];
    for(int i = 1; i < 256; i++){
        if(maxHist < histogram[i]){
            maxHist = histogram[i];
        }
    }

     //normalisasi disini dengan max nilai di histogram (agar yg max 100), karena jika normalisasi row*col hasilnya akan banyak yang sangat kecil
    for(int i = 0; i < 255; i++){
        double temp = ((double)akumulasi[i]/maxHist)*100;
        C[i] = (int) temp;
    }

    for(int y = 0; y < height; y++)
        for(int x = 0; x < width; x++)
            image.at<uchar>(y,x) = C[image.at<uchar>(y,x)];

    normalizeScaleHistogram(image);
}
int main()
{
    Mat image = imread("picture/2.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    namedWindow("Image", CV_WINDOW_AUTOSIZE);
    imshow("Image", image);
    originalHistogram(image);
   // normalizeScaleHistogram(image);
    accumulateHistogram(image);
    equalizeHistogram(image);

    waitKey();
    return 0;
}
