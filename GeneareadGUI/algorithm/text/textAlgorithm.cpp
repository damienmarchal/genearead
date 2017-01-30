#include "textAlgorithm.h"

void TextAlgorithm::applyMask(Layer* in, Layer* out, Layer* mask) {
    uchar* m = mask->ptr();
    uchar* o = out->ptr();
    uchar* i = in->ptr();
    int chan = mask->channels();
    int width = mask->cols * chan;
    int height = mask->rows;
    int size = width*height;
    int y = 0;

    for(int x=0; x<size; x+=chan) {
        if(!(m[x] | m[x+1] | m[x+2])) {
            o[y] = i[y];
        }
        ++y;
    }

}

