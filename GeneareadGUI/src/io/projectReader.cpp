#include <header/io/projectReader.h>

#include <string>
#include <functional>

#include <QDebug>

/*
 * ////////////////////////////////////
 * GeneaRead1.0\n        //version
 * 11102122121200110\n   //timestamp
 * PROJECT_NAME\n        //project name
 * FILENAME\n            //filename of the base image
 * ////////////////////////////////////
 * BACK_MAT_DATA\n         //data for base image
 * 5\n                     //id for binarisation method
 * MAIN_MAT_DATA\n         //data for binary image
 * 3\n                     //number of layers
 * LAYER1_DATA\n           //data for layer 1
 * LAYER2_DATA\n           //data for layer 2
 * LAYER3_DATA\n           //data for layer 3
 * ////////////////////////////////////
 */
ProjectReader::ProjectReader() {
    reader = std::ifstream();
}

bool ProjectReader::isReading() {
    return reading;
}

void ProjectReader::nextLine() {
    std::getline(reader, line);
}

int ProjectReader::parseInt() {
    return std::stoi(line);
}

int ProjectReader::readInt(size_t size) {
    int num = 0;
    int v;
    unsigned int c;
    for(size_t i=0; i<size; ++i) {
        c = readUchar();
        v = c << ((size-1-i)*8);
        num |= v;
    }
    return num;
}

std::string ProjectReader::readString(std::streamsize size, char delim) {
    char* c = (char*)malloc(size);
    reader.get(c, size, delim);
    std::string str(c);
    reader.ignore(1);
    return str;
}

char ProjectReader::readChar() {
    char c = reader.get();
    return c;
}

uchar ProjectReader::readUchar() {
    return (uchar)readChar();
}

cv::Mat* ProjectReader::readMat() {
    int rows = readInt();
    int cols = readInt();
    int type = readInt();
    cv::Mat* mat = new cv::Mat(rows, cols, type);

    int chan = mat->channels();
    int size = cols * rows * chan;
    uchar* l = mat->ptr();

    std::function<void(int)> readPixel;

    switch(type) {

    case CV_8UC3 :
        readPixel = [&] (int i) {
            l[i  ] = readUchar();
            l[i+1] = readUchar();
            l[i+2] = readUchar();
        };
        break;

    case CV_8UC4 :
        readPixel = [&] (int i) {
            l[i  ] = readUchar();
            l[i+1] = readUchar();
            l[i+2] = readUchar();
            l[i+3] = readUchar();
        };
        break;

    default : return mat;
    }

    for(int i=0; i<size; i+=chan) {
        readPixel(i);
    }

    return mat;
}

bool ProjectReader::open(std::string filename) {
    if(isReading())
        return false;
    reader.open(filename.data(), std::ios_base::in | std::ios_base::binary);
    reading = true;
    return true;
}

bool ProjectReader::close() {
    if(!isReading())
        return false;
    reader.close();
    reading = false;
    return true;
}



