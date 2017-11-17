/*
    Rya Meyvriska
    G64164008
    Ilmu Komputer IPB
*/

// mengubah isi array menjadi akumulasi nilai-nilai sebelum i
void transformToAccumulatedFrequency(int frequencyTable[], int length) {
    for (int i = 1; i < length; i++) {
        frequencyTable[i] += frequencyTable[i - 1];
    }
}

Mat accumulateHistogram(Mat &image) {
    // alokasi memori untuk menyimpan tabel frekuensi dengan index 0-255
    int frequencyTable[256] = {0};
    calculateIntensityFrequency(image, frequencyTable);

    // mengakumulasi frekuensi
    transformToAccumulatedFrequency(frequencyTable, 256);

    // optional mau di normalize atau gk (disini di normalize agar tidak terlalu panjang
    normalize(frequencyTable, 256, 100);

    //110 dari normalize 100 +10 untuk space diatas
    return createHistogram(frequencyTable, 512, 110);
}

