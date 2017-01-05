#include "algorithm.h"

algorithm::algorithm(QObject *parent) : QObject(parent)
{

}

void algorithm::bernsen(QObject *image) {
    /*Mat ret = Mat::zeros(gray.size(),gray.type());
    for(int i=0;i<gray.cols;i++ ) {
        for(int j=0;j<gray.rows;j++ ) {
            double mn=999,mx=0;
            int ti=0,tj=0;
            int tlx=i-ksize/2;
            int tly=j-ksize/2;
            int brx=i+ksize/2;
            int bry=j+ksize/2;
            if(tlx<0) tlx=0;
            if(tly<0) tly=0;
            if(brx>=gray.cols) brx=gray.cols-1;
            if(bry>=gray.rows) bry=gray.rows-1;

            //minMaxIdx(gray(Rect(Point(tlx,tly),Point(brx,bry))),&mn,&mx,0,0);

            for(int ik=-ksize/2;ik<=ksize/2;ik++)
            {
                for(int jk=-ksize/2;jk<=ksize/2;jk++)
                {
                    ti=i+ik;
                    tj=j+jk;
                    if(ti>0 && ti<gray.cols && tj>0 && tj<gray.rows)
                    {
                        uchar pix = gray.at<uchar>(tj,ti);
                        if(pix<mn) mn=pix;
                        if(pix>mx) mx=pix;
                    }
                }
            }
            int median = 0.5 * (mn+mx);
            if(median<contrast_limit) {
                ret.at<uchar>(j,i)=0;
            } else {
                uchar pix = gray.at<uchar>(j,i);
                ret.at<uchar>(j,i) = pix>median?255:0;
            }
        }
    }
    return ret;
}*/
}

void algorithm::laab(QObject *image) {
    image->setProperty("color", "green");
}

void algorithm::lines(QObject *image) {
    image->setProperty("color", "black");
}
