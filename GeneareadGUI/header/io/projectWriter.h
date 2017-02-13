#ifndef PROJECTWRITER_H
#define PROJECTWRITER_H

#include <iostream>
#include <fstream>

#include <QString>
#include <QDebug>

#include <opencv2/core.hpp>

class ImageManager;

class ProjectWriter {

public:
    ProjectWriter();

    /**
     * @brief open
     * Opens a std::ofstream to <code>filename</code>
     * @param filename the local file name
     * @return true if the stream was not already open. False otherwise.
     */
    bool open(std::string filename);

    /**
     * @brief close
     * Closes a previously opened std::ofstream
     * @return true if the stream was open. False otherwise.
     */
    bool close();

    /**
     * @brief isWriting
     * @return true if the std::ofstream is open. False otherwise.
     */
    bool isWriting();

    /**
     * @brief writeInt
     * Adds an int to the opened std::ofstream.
     * @param var the value to add to the stream.
     * @param size the number of bytes to write.
     */
    void writeInt(int var, size_t size = 4);

    /**
     * @brief writeChar
     * Adds a char (1 byte) to the opened std::ofstream.
     * @param var the value to add to the stream.
     */
    void writeChar(char var);

    /**
     * @brief writeUchar
     * Adds a uchar (1 byte) to the opened std::ofstream.
     * @param var the value to add to the stream.
     */
    void writeUchar(uchar var);

    /**
     * @brief writeString
     * Adds an std::string to the opened std::ofstream.
     * Stops adding characters when '/0' is encountered.
     * @param var the value to add to the stream.
     */
    void writeString(std::string var);

    /**
     * @brief writeMat
     * Adds a cv::Mat to the opened std::ofstream.
     * @param a pointer to the cv::Mat  to add to the stream.
     */
    void writeMat(cv::Mat* mat);

protected:

private:
    std::ofstream writer;
    bool writing;
};

#endif // PROJECTREADER_H
