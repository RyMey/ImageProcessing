/*
    Rya Meyvriska
    G64164008
    Ilmu Komputer IPB
*/

//references : https://en.wikipedia.org/wiki/Histogram_equalization
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
