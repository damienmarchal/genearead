#include "bernsen.h"

Bernsen::Bernsen() {

}

QString Bernsen::getName() {
    return "bernsen";
}

void Bernsen::setParameters(QObject* parameters) {
    QVariant v;
    if(!(v = parameters->property("k")).isNull())
        this->k = v.toInt();

}

void Bernsen::apply(Layer* in, Layer* out, Layer* mask) {
    const int ksize = 3;
    const double contrast_limit = 0.5;

    for(int i=0;i<in->cols;i++ ) {
        for(int j=0;j<in->rows;j++ ) {
            double mn=999,mx=0;
            int ti=0,tj=0;
            int tlx=i-ksize/2;
            int tly=j-ksize/2;
            int brx=i+ksize/2;
            int bry=j+ksize/2;
            if(tlx<0) tlx=0;
            if(tly<0) tly=0;
            if(brx>=in->cols) brx=in->cols-1;
            if(bry>=in->rows) bry=in->rows-1;

            //minMaxIdx(image(Rect(Point(tlx,tly),Point(brx,bry))),&mn,&mx,0,0);

            for(int ik=-ksize/2;ik<=ksize/2;ik++)
            {
                for(int jk=-ksize/2;jk<=ksize/2;jk++)
                {
                    ti=i+ik;
                    tj=j+jk;
                    if(ti>0 && ti<in->cols && tj>0 && tj<in->rows)
                    {
                        uchar pix = in->at<uchar>(tj,ti);
                        if(pix<mn) mn=pix;
                        if(pix>mx) mx=pix;
                    }
                }
            }
            int median = 0.5 * (mn+mx);
            if(median<contrast_limit) {
                out->at<uchar>(j,i)=0;
            } else {
                uchar pix = in->at<uchar>(j,i);
                out->at<uchar>(j,i) = pix>median?255:0;
            }
        }
    }
}
