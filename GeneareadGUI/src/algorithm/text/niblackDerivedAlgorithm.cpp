#include <header/algorithm/text/niblackDerivedAlgorithm.h>

#include "qdebug.h"

NiblackDerivedAlgorithm::NiblackDerivedAlgorithm()
    : winx(15), winy(15)
{

}

void NiblackDerivedAlgorithm::apply(Layer* in, Layer* out, Layer* mask) {

    qDebug() << "apply niblack";
    qDebug() << winx << winy;

    double m, s, max_s;
    double th=0;
    double min_I, max_I;
    int wxh	= winx/2;
    int wyh	= winy/2;
    int x_firstth= wxh;
    int x_lastth = in->cols-wxh-1;
    int y_lastth = in->rows-wyh-1;
    int y_firstth= wyh;

    // Create local statistics and store them in a double Layerrices
    Layer map_m = Layer::zeros (in->rows, in->cols, CV_32F);
    Layer map_s = Layer::zeros (in->rows, in->cols, CV_32F);
    max_s = calcLocalStats(in, &map_m, &map_s, mask);

    cv::minMaxLoc(*in, &min_I, &max_I);

    Layer thsurf (in->rows, in->cols, CV_32F);


    // Create the threshold surface, including border processing
    // ----------------------------------------------------

    for	(int j = y_firstth ; j<=y_lastth; j++) {

        // NORMAL, NON-BORDER AREA IN THE MIDDLE OF THE WINDOW:
        for	(int i=0 ; i <= in->cols-winx; i++) {

            m  = map_m.at<float>(j, i+wxh);
            s  = map_s.at<float>(j, i+wxh);

            // Calculate the threshold
            th = threshold(m, s, min_I, max_I, max_s);
            /*switch (version) {
            case NIBLACK:
                th = m + k*s;
                break;
            case SAUVOLA:
                th = m * (1 + k*(s/dR-1));
                break;
            case WOLFJOLION:
                th = m + k * (s/max_s-1) * (m-min_I);
                break;
            default:
                cerr << "Unknown threshold type in ImageThresholder::surfaceNiblackImproved()\n";
                exit (1);
            }*/

            thsurf.at<float>(j, i+wxh) = th;

            if (i==0) {
                // LEFT BORDER
                for (int i=0; i<=x_firstth; ++i)
                    thsurf.at<float>(j, i) = th;

                // LEFT-UPPER CORNER
                if (j==y_firstth)
                    for (int u=0; u<y_firstth; ++u)
                        for (int i=0; i<=x_firstth; ++i)
                            thsurf.at<float>(u, i) = th;

                // LEFT-LOWER CORNER
                if (j==y_lastth)
                    for (int u=y_lastth+1; u<in->rows; ++u)
                        for (int i=0; i<=x_firstth; ++i)
                            thsurf.at<float>(u, i) = th;
            }

            // UPPER BORDER
            if (j==y_firstth)
                for (int u=0; u<y_firstth; ++u)
                    thsurf.at<float>(u, i+wxh) = th;

            // LOWER BORDER
            if (j==y_lastth)
                for (int u=y_lastth+1; u<in->rows; ++u)
                    thsurf.at<float>(u, i+wxh) = th;
        }

        // RIGHT BORDER
        for (int i=x_lastth; i<in->cols; ++i)
            thsurf.at<float>(j, i) = th;

        // RIGHT-UPPER CORNER
        if (j==y_firstth)
            for (int u=0; u<y_firstth; ++u)
                for (int i=x_lastth; i<in->cols; ++i)
                    thsurf.at<float>(u, i) = th;

        // RIGHT-LOWER CORNER
        if (j==y_lastth)
            for (int u=y_lastth+1; u<in->rows; ++u)
                for (int i=x_lastth; i<in->cols; ++i)
                    thsurf.at<float>(u, i) = th;
    }

    cv::Vec3b vec;
    for	(int y=0; y<in->rows; ++y) {
        //std::cout << y << std::endl;
        for	(int x=0; x<in->cols; ++x) {

            vec = mask->at<cv::Vec3b>(y, x);
            if(vec[0] || vec[1] || vec[2]) {
            //if(true) {
                if (in->at<uc>(y, x) >= thsurf.at<float>(y, x)) {
                    out->at<uc>(y, x) = 255;
                } else {
                    out->at<uc>(y, x) = 0;
                }
            } else {
                out->at<uc>(y, x) = in->at<uc>(y, x);
            }
        }
    }

    qDebug() << "ok here";
    //std::cout << *out << std::endl;

}

double NiblackDerivedAlgorithm::calcLocalStats(Layer* in, Layer* out_m, Layer* out_s, Layer* mask) {

    double m,s,max_s, sum, sum_sq, foo;
    int wxh	= winx/2;
    int wyh	= winy/2;
    int x_firstth= wxh;
    int y_lastth = in->rows-wyh-1;
    int y_firstth= wyh;
    double winarea = winx*winy;

    max_s = 0;
    for	(int j = y_firstth ; j<=y_lastth; j++) {
        // Calculate the initial window at the beginning of the line
        sum = sum_sq = 0;
        for	(int wy=0 ; wy<winy; wy++) {
            for	(int wx=0 ; wx<winx; wx++) {
                foo = in->at<uc>(j-wyh+wy, wx);
                sum    += foo;
                sum_sq += foo*foo;
            }
        }
        m  = sum / winarea;
        s  = sqrt ((sum_sq - (sum*sum)/winarea)/winarea);
        if (s > max_s)
            max_s = s;

        out_m->at<float>(j, x_firstth) = m;
        out_s->at<float>(j, x_firstth) = s;

        // Shift the window, add and remove	new/old values to the histogram
        for	(int i=1 ; i <= in->cols-winx; i++) {

            // Remove the left old column and add the right new column
            for (int wy=0; wy<winy; ++wy) {
                foo = in->at<uc>(j-wyh+wy, i-1);
                sum    -= foo;
                sum_sq -= foo*foo;

                foo = in->at<uc>(j-wyh+wy, i+winx-1);
                sum    += foo;
                sum_sq += foo*foo;
            }
            m  = sum / winarea;
            s  = sqrt ((sum_sq - (sum*sum)/winarea)/winarea);
            if (s > max_s)
                max_s = s;
            out_m->at<float>(j, i+wxh) = m;
            out_s->at<float>(j, i+wxh) = s;
        }
    }

    return max_s;
}
