/*
    Rya Meyvriska
    G64164008
    Ilmu Komputer IPB
*/

// menormalisasi data menjadi 0 - maxValue
void normalize(int array[], int length, int maxValue) {
    int maxElement = findMaxElement(array, length);
    for (int i = 0; i < length; i++) {
        //dibagi max element to normalize and cross by maxvalue so the range is 0-maxValue, not 0-1 (excep macvalue is 1 of course
        double temp = ((double) array[i] / maxElement) * maxValue;
        array[i] = (int) temp;
    }
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
