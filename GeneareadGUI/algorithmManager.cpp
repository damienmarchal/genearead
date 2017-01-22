#include "algorithmManager.h"
#include <iostream>

AlgorithmManager::AlgorithmManager() {
    algorithms = Algorithms();
    algorithms.push_back(new Bernsen());

}

void AlgorithmManager::updateGrayLayer(Layer *RGBMatrix) {
    const int rows = RGBMatrix->rows;
    const int cols = RGBMatrix->cols;
    if(
            &grayInMatrix==NULL ||
            cols != grayInMatrix.cols ||
            rows != grayInMatrix.rows) {
        grayInMatrix = Layer(rows, cols, CV_8UC1);
        grayOutMatrix = Layer(rows, cols, CV_8UC1);
    }

    cvtColor(*RGBMatrix, grayInMatrix, CV_RGB2GRAY);
}

void AlgorithmManager::RGBToGray(Layer* RGBMatrix, Layer* grayMatrix) {
    cvtColor(*RGBMatrix, *grayMatrix, CV_RGB2GRAY);
}

void AlgorithmManager::GrayToRGB(Layer* grayMatrix, Layer* RGBMatrix) {
    cvtColor(*grayMatrix, *RGBMatrix, CV_GRAY2RGB);
}

Algorithm* AlgorithmManager::getAlgorithm(QString name) {
    Algorithm* a;
    qDebug() << "!   searching through" << algorithms.size() << "algorithm(s)";
    for(unsigned i=0; i<algorithms.size(); ++i) {
        qDebug() << " -> testing number" << i;
        a = algorithms[i];
        qDebug() << "    looking for" << name << ". Got" << a->getName();
        if(a->getName() == name)
            return a;
    }
    return NULL;
}

void AlgorithmManager::binarize(Layer* RGBMatrix, Layer* mask, QObject* parameters) {

    qDebug() << "--- applying binary";
    qDebug() << "--- --- reading algorithm name";
    QVariant v;
    if((v = parameters->property("name")).isNull())
        return;
    qDebug() << "--- [V] reading algorithm name";

    const QString name = v.toString();
    qDebug() << "--- --- fetching algorithm :" << name;
    Algorithm* algo = getAlgorithm(name);
    if(algo == NULL) {
        qDebug() << "--- --- <X> fetching algorithm :" << name;
        return;
    }
    qDebug() << "--- [V] fetching algorithm :" << name;

    qDebug() << "--- --- setting parameters";
    algo->setParameters(parameters);
    qDebug() << "--- [V] setting parameters";

    qDebug() << "--- --- update gray buffers";
    updateGrayLayer(RGBMatrix);
    qDebug() << "--- [V] update gray buffers";


    qDebug() << "--- --- converting RGB to Gray";
    RGBToGray(RGBMatrix, &grayInMatrix);
    qDebug() << "--- [V] converting RGB to Gray";


    qDebug() << "--- --- binarizing";
    algo->apply(&grayInMatrix, &grayOutMatrix, mask);
    qDebug() << "--- [V] binarizing";

    qDebug() << "--- --- converting Gray to RGB";
    GrayToRGB(&grayOutMatrix, RGBMatrix);
    qDebug() << "--- [V] converting Gray to RGB";

    qDebug() << "[V] applying binary";
}

Layer* AlgorithmManager::bernsen(Layer* image) {
    const int ksize = 3;
    const double contrast_limit = 0.5;
    Layer ret = Layer::zeros(image->size(),image->type());
    for(int i=0;i<image->cols;i++ ) {
        for(int j=0;j<image->rows;j++ ) {
            double mn=999,mx=0;
            int ti=0,tj=0;
            int tlx=i-ksize/2;
            int tly=j-ksize/2;
            int brx=i+ksize/2;
            int bry=j+ksize/2;
            if(tlx<0) tlx=0;
            if(tly<0) tly=0;
            if(brx>=image->cols) brx=image->cols-1;
            if(bry>=image->rows) bry=image->rows-1;

            //minMaxIdx(image(Rect(Point(tlx,tly),Point(brx,bry))),&mn,&mx,0,0);

            for(int ik=-ksize/2;ik<=ksize/2;ik++)
            {
                for(int jk=-ksize/2;jk<=ksize/2;jk++)
                {
                    ti=i+ik;
                    tj=j+jk;
                    if(ti>0 && ti<image->cols && tj>0 && tj<image->rows)
                    {
                        uchar pix = image->at<uchar>(tj,ti);
                        if(pix<mn) mn=pix;
                        if(pix>mx) mx=pix;
                    }
                }
            }
            int median = 0.5 * (mn+mx);
            if(median<contrast_limit) {
                ret.at<uchar>(j,i)=0;
            } else {
                uchar pix = image->at<uchar>(j,i);
                ret.at<uchar>(j,i) = pix>median?255:0;
            }
        }
    }
    return &ret;
}

Layer* AlgorithmManager::laab(Layer *image) {
    //image->setProperty("color", "green");
    return image;
}

Layer* AlgorithmManager::lines(Layer *image) {
    //image->setProperty("color", "black");
    return image;
}



/**************************************************************
 * Binarization with several methods
 * (0) Niblacks method
 * (1) Sauvola & Co.
 *     ICDAR 1997, pp 147-152
 * (2) by myself - Christian Wolf
 *     Research notebook 19.4.2001, page 129
 * (3) by myself - Christian Wolf
 *     20.4.2007
 *
 * See also:
 * Research notebook 24.4.2001, page 132 (Calculation of s)
 **************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include <iostream>

using namespace std;
using namespace cv;

enum NiblackVersion
{
    NIBLACK=0,
    SAUVOLA,
    WOLFJOLION,
};

#define BINARIZEWOLF_VERSION	"2.3 (February 26th, 2013)"

#define uget(x,y)    at<unsigned char>(y,x)
#define uset(x,y,v)  at<unsigned char>(y,x)=v;
#define fget(x,y)    at<float>(y,x)
#define fset(x,y,v)  at<float>(y,x)=v;

/**********************************************************
 * Usage
 **********************************************************/

static void usage (char *com) {
    cerr << "usage: " << com << " [ -x <winx> -y <winy> -k <parameter> ] [ version ] <inputimage> <outputimage>\n\n"
         << "version: n   Niblack (1986)         needs white text on black background\n"
         << "         s   Sauvola et al. (1997)  needs black text on white background\n"
         << "         w   Wolf et al. (2001)     needs black text on white background\n"
         << "\n"
         << "Default version: w (Wolf et al. 2001)\n"
         << "\n"
         << "example:\n"
         << "       " << com << " w in.pgm out.pgm\n"
         << "       " << com << " in.pgm out.pgm\n"
         << "       " << com << " s -x 50 -y 50 -k 0.6 in.pgm out.pgm\n";
}

// *************************************************************
// glide a window across the image and
// create two maps: mean and standard deviation.
// *************************************************************


double calcLocalStats (Layer &im, Layer &map_m, Layer &map_s, int winx, int winy) {

    double m,s,max_s, sum, sum_sq, foo;
    int wxh	= winx/2;
    int wyh	= winy/2;
    int x_firstth= wxh;
    int y_lastth = im.rows-wyh-1;
    int y_firstth= wyh;
    double winarea = winx*winy;

    max_s = 0;
    for	(int j = y_firstth ; j<=y_lastth; j++)
    {
        // Calculate the initial window at the beginning of the line
        sum = sum_sq = 0;
        for	(int wy=0 ; wy<winy; wy++)
            for	(int wx=0 ; wx<winx; wx++) {
                foo = im.uget(wx,j-wyh+wy);
                sum    += foo;
                sum_sq += foo*foo;
            }
        m  = sum / winarea;
        s  = sqrt ((sum_sq - (sum*sum)/winarea)/winarea);
        if (s > max_s)
            max_s = s;
        map_m.fset(x_firstth, j, m);
        map_s.fset(x_firstth, j, s);

        // Shift the window, add and remove	new/old values to the histogram
        for	(int i=1 ; i <= im.cols-winx; i++) {

            // Remove the left old column and add the right new column
            for (int wy=0; wy<winy; ++wy) {
                foo = im.uget(i-1,j-wyh+wy);
                sum    -= foo;
                sum_sq -= foo*foo;
                foo = im.uget(i+winx-1,j-wyh+wy);
                sum    += foo;
                sum_sq += foo*foo;
            }
            m  = sum / winarea;
            s  = sqrt ((sum_sq - (sum*sum)/winarea)/winarea);
            if (s > max_s)
                max_s = s;
            map_m.fset(i+wxh, j, m);
            map_s.fset(i+wxh, j, s);
        }
    }

    return max_s;
}


/**********************************************************
 * The binarization routine
 **********************************************************/


void NiblackSauvolaWolfJolion (Layer im, Layer output, NiblackVersion version,
                               int winx, int winy, double k, double dR) {


    double m, s, max_s;
    double th=0;
    double min_I, max_I;
    int wxh	= winx/2;
    int wyh	= winy/2;
    int x_firstth= wxh;
    int x_lastth = im.cols-wxh-1;
    int y_lastth = im.rows-wyh-1;
    int y_firstth= wyh;
    int mx, my;

    // Create local statistics and store them in a double Layerrices
    Layer map_m = Layer::zeros (im.rows, im.cols, CV_32F);
    Layer map_s = Layer::zeros (im.rows, im.cols, CV_32F);
    max_s = calcLocalStats (im, map_m, map_s, winx, winy);

    minMaxLoc(im, &min_I, &max_I);

    Layer thsurf (im.rows, im.cols, CV_32F);

    // Create the threshold surface, including border processing
    // ----------------------------------------------------

    for	(int j = y_firstth ; j<=y_lastth; j++) {

        // NORMAL, NON-BORDER AREA IN THE MIDDLE OF THE WINDOW:
        for	(int i=0 ; i <= im.cols-winx; i++) {

            m  = map_m.fget(i+wxh, j);
            s  = map_s.fget(i+wxh, j);

            // Calculate the threshold
            switch (version) {

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
            }

            thsurf.fset(i+wxh,j,th);

            if (i==0) {
                // LEFT BORDER
                for (int i=0; i<=x_firstth; ++i)
                    thsurf.fset(i,j,th);

                // LEFT-UPPER CORNER
                if (j==y_firstth)
                    for (int u=0; u<y_firstth; ++u)
                        for (int i=0; i<=x_firstth; ++i)
                            thsurf.fset(i,u,th);

                // LEFT-LOWER CORNER
                if (j==y_lastth)
                    for (int u=y_lastth+1; u<im.rows; ++u)
                        for (int i=0; i<=x_firstth; ++i)
                            thsurf.fset(i,u,th);
            }

            // UPPER BORDER
            if (j==y_firstth)
                for (int u=0; u<y_firstth; ++u)
                    thsurf.fset(i+wxh,u,th);

            // LOWER BORDER
            if (j==y_lastth)
                for (int u=y_lastth+1; u<im.rows; ++u)
                    thsurf.fset(i+wxh,u,th);
        }

        // RIGHT BORDER
        for (int i=x_lastth; i<im.cols; ++i)
            thsurf.fset(i,j,th);

        // RIGHT-UPPER CORNER
        if (j==y_firstth)
            for (int u=0; u<y_firstth; ++u)
                for (int i=x_lastth; i<im.cols; ++i)
                    thsurf.fset(i,u,th);

        // RIGHT-LOWER CORNER
        if (j==y_lastth)
            for (int u=y_lastth+1; u<im.rows; ++u)
                for (int i=x_lastth; i<im.cols; ++i)
                    thsurf.fset(i,u,th);
    }
    cerr << "surface created" << endl;


    for	(int y=0; y<im.rows; ++y)
        for	(int x=0; x<im.cols; ++x)
        {
            if (im.uget(x,y) >= thsurf.fget(x,y))
            {
                output.uset(x,y,255);
            }
            else
            {
                output.uset(x,y,0);
            }
        }
}

/**********************************************************
 * The main function
 **********************************************************/

int maina (int argc, char **argv)
{
    char version;
    int c;
    int winx=0, winy=0;
    float optK=0.5;
    bool didSpecifyK=false;
    NiblackVersion versionCode;
    char *inputname, *outputname, *versionstring;

    cerr << "===========================================================\n"
         << "Christian Wolf, LIRIS Laboratory, Lyon, France.\n"
         << "christian.wolf@liris.cnrs.fr\n"
         << "Version " << BINARIZEWOLF_VERSION << endl
         << "===========================================================\n";

    // Argument processing
    while ((c =	getopt (argc, argv,	"x:y:k:")) != EOF) {

        switch (c) {

        case 'x':
            winx = atof(optarg);
            break;

        case 'y':
            winy = atof(optarg);
            break;

        case 'k':
            optK = atof(optarg);
            didSpecifyK = true;
            break;

        case '?':
            usage (*argv);
            cerr << "\nProblem parsing the options!\n\n";
            exit (1);
        }
    }

    switch(argc-optind)
    {
    case 3:
        versionstring=argv[optind];
        inputname=argv[optind+1];
        outputname=argv[optind+2];
        break;

    case 2:
        versionstring=(char *) "w";
        inputname=argv[optind];
        outputname=argv[optind+1];
        break;

    default:
        usage (*argv);
        exit (1);
    }

    cerr << "Adaptive binarization\n"
         << "Threshold calculation: ";

    // Determine the method
    version = versionstring[0];
    switch (version)
    {
    case 'n':
        versionCode = NIBLACK;
        cerr << "Niblack (1986)\n";
        break;

    case 's':
        versionCode = SAUVOLA;
        cerr << "Sauvola et al. (1997)\n";
        break;

    case 'w':
        versionCode = WOLFJOLION;
        cerr << "Wolf and Jolion (2001)\n";
        break;

    default:
        usage (*argv);
        cerr  << "\nInvalid version: '" << version << "'!";
    }


    cerr << "parameter k=" << optK << endl;

    if (!didSpecifyK)
        cerr << "Setting k to default value " << optK << endl;


    // Load the image in grayscale mode
    Layer input = imread(inputname, IMREAD_GRAYSCALE);


    if ((input.rows<=0) || (input.cols<=0)) {
        cerr << "*** ERROR: Couldn't read input image " << inputname << endl;
        exit(1);
    }


    // Treat the window size
    if (winx==0||winy==0) {
        cerr << "Input size: " << input.cols << "x" << input.rows << endl;
        winy = (int) (2.0 * input.rows-1)/3;
        winx = (int) input.cols-1 < winy ? input.cols-1 : winy;
        // if the window is too big, than we asume that the image
        // is not a single text box, but a document page: set
        // the window size to a fixed constant.
        if (winx > 100)
            winx = winy = 40;
        cerr << "Setting window size to [" << winx
             << "," << winy << "].\n";
    }

    // Threshold
    Layer output (input.rows, input.cols, CV_8U);
    NiblackSauvolaWolfJolion (input, output, versionCode, winx, winy, optK, 128);

    // Write the tresholded file
    cerr << "Writing binarized image to file '" << outputname << "'.\n";
    imwrite (outputname, output);

    return 0;
}
