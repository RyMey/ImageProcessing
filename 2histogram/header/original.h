//membuat histogram from array
Mat originalHistogram(Mat &image) {
    // alokasi memori untuk menyimpan tabel frekuensi dengan index 0-255
    int frequencyTable[256] = {0};
    calculateIntensityFrequency(image, frequencyTable);

    // menemukan frekuensi terbanyak untuk menentukan tinggi
    int maxFrequency = findMaxElement(frequencyTable, 256);

    return createHistogram(frequencyTable, 512, maxFrequency + 5);
}
