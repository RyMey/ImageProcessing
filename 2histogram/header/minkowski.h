/*
    Rya Meyvriska
    G64164008
    Ilmu Komputer IPB
*/

//p=1 manhattan, p=2 euclidea
double minkowskiDistance(Mat &image1, Mat &image2, int p) {
    int frequencyTable1[256] = {0};
    calculateIntensityFrequency(image1, frequencyTable1);
    normalize(frequencyTable1, 256, 100);

    int frequencyTable2[256] = {0};
    calculateIntensityFrequency(image2, frequencyTable2);
    normalize(frequencyTable2, 256, 100);

    double sum = 0;
    double temp;
    for (int i = 0; i < 256; i++) {
        sum += pow(abs(frequencyTable1[i] - frequencyTable2[i]), p);
    }

    return pow(sum, 1.0 / p);
}
