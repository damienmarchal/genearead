#include <header/io/projectWriter.h>

#include <string>
#include <functional>

ProjectWriter::ProjectWriter() {
    writer = std::ofstream();
}

bool ProjectWriter::isWriting() {
    return writing;
}

bool ProjectWriter::open(std::string filename) {
    if(isWriting())
        return false;
    writer.open(filename, std::ios_base::out);
    writing = true;
    return true;
}

bool ProjectWriter::close() {
    if(!isWriting())
        return false;
    writer.flush();
    writer.close();
    writing = false;
    return true;
}

void ProjectWriter::writeInt(int var, size_t size) {
    int v = 0;
    int cur;
    for(size_t i=0; i<size; ++i) {
        cur = ((var >> ((size-i-1)*8)) & 0xFF);
        v |= cur << (i*8);
        writeUchar((unsigned char)cur);
    }
}

void ProjectWriter::writeChar(char c) {
    writer.put(c);
}

void ProjectWriter::writeUchar(uchar c) {
    writer.put(c);
}

void ProjectWriter::writeString(std::string var) {
    writer.write(var.data(), var.size());
}

void ProjectWriter::writeMat(cv::Mat* mat) {

    int type = mat->type();
    int chan = mat->channels();
    int height = mat->rows;
    int width = mat->cols;
    int size = width * height * chan;
    uchar* l = mat->ptr();
    std::function<void(int)> writePixel;


    switch(type) {

    case CV_8UC3 :
        writePixel = [&] (int i) {
            writeUchar(l[i  ]);
            writeUchar(l[i+1]);
            writeUchar(l[i+2]);
        };
        break;

    case CV_8UC4 :
        writePixel = [&] (int i) {
            writeUchar(l[i  ]);
            writeUchar(l[i+1]);
            writeUchar(l[i+2]);
            writeUchar(l[i+3]);
        };
        break;

    default :
        qDebug() << "error";
        return;
    }

    writeInt(height);
    writeInt(width);
    writeInt(type);

    for(int i=0; i<size; i+=chan) {
        writePixel(i);
    }

}
