/*
    Rya Meyvriska
    G64164008
    Ilmu Komputer IPB
*/

bool R1(int R, int G, int B) {
    bool e1 = (R>95) && (G>40) && (B>20) && ((max(R,max(G,B)) - min(R, min(G,B)))>15) && (abs(R-G)>15) && (R>G) && (R>B);
    bool e2 = (R>220) && (G>210) && (B>170) && (abs(R-G)<=15) && (R>B) && (G>B);
    return (e1||e2);
}

bool R2(float Y, float Cr, float Cb) {
    bool e3 = Cr <= 1.5862*Cb+20;
    bool e4 = Cr >= 0.3448*Cb+76.2069;
    bool e5 = Cr >= -4.5652*Cb+234.5652;
    bool e6 = Cr <= -1.15*Cb+301.75;
    bool e7 = Cr <= -2.2857*Cb+432.85;
    return e3 && e4 && e5 && e6 && e7;
}

bool R3(float H, float S, float V) {
    return (H<25) || (H > 230);
}


Mat GetSkin(Mat source) {
    Mat result = source.clone();

    Vec3b cwhite = Vec3b::all(255);
    Vec3b cblack = Vec3b::all(0);

    Mat source_ycrcb, source_hsv;
    cvtColor(source, source_ycrcb, CV_BGR2YCrCb);

    source.convertTo(source_hsv, CV_32FC3);
    cvtColor(source_hsv, source_hsv, CV_BGR2HSV);

    normalize(source_hsv, source_hsv, 0.0, 255.0, NORM_MINMAX, CV_32FC3);

    int width = source.size().width;
    int height = source.size().height;

    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {

            Vec3b pix_bgr = source.ptr<Vec3b>(i)[j];
            int B = pix_bgr.val[0];
            int G = pix_bgr.val[1];
            int R = pix_bgr.val[2];
            bool a = R1(R,G,B);

            Vec3b pix_ycrcb = source_ycrcb.ptr<Vec3b>(i)[j];
            int Y = pix_ycrcb.val[0];
            int Cr = pix_ycrcb.val[1];
            int Cb = pix_ycrcb.val[2];
            bool b = R2(Y,Cr,Cb);

            Vec3f pix_hsv = source_hsv.ptr<Vec3f>(i)[j];
            float H = pix_hsv.val[0];
            float S = pix_hsv.val[1];
            float V = pix_hsv.val[2];
            bool c = R3(H,S,V);

            if(!(a&&b&&c))
                result.ptr<Vec3b>(i)[j] = cblack;
        }
    }
    return result;
}
