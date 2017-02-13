#ifndef PROJECTREADER_H
#define PROJECTREADER_H

#include <iostream>
#include <fstream>

#include <QString>

#include <opencv2/core.hpp>

class ProjectReader {

public:
    ProjectReader();

    /**
     * @brief open
     * Opens a std::ifstream to <code>filename</code>
     * @param filename the local file name
     * @return true if the stream was not already open. False otherwise.
     */
    bool open(std::string filename);

    /**
     * @brief close
     * Closes a previously opened std::ifstream
     * @return true if the stream was open. False otherwise.
     */
    bool close();

    /**
     * @brief isReading
     * @return true if the std::ifstream is open. False otherwise.
     */
    bool isReading();

    /**
     * @brief parseInt
     * Parses an int (4 bytes) from the opened std::ifstream.
     * @deprecated use readInt instead
     * @return the int value read.
     */
    int parseInt();

    /**
     * @brief nextLine
     * Reads a line from the opened std::ifstream into std::string <code>line</code>
     */
    void nextLine();

    /**
     * @brief readInt
     * Parses an int from the opened std::ifstream.
     * @param size the number of bytes to read.
     * @return the int value read.
     */
    int readInt(size_t size = 4);

    /**
     * @brief readChar
     * Parses an char (1 byte) from the opened std::ifstream.
     * @return the char value read.
     */
    char readChar();

    /**
     * @brief readUchar
     * Parses an uchar (1 byte) from the opened std::ifstream.
     * @return the uchar value read.
     */
    uchar readUchar();

    /**
     * @brief readString
     * Parses an std::string from the opened std::ifstream.
     * Stops parsing when <code>size</code> bytes are read of when character <code>delim</code> is encountered.
     * @param size the maximum number of bytes to read.
     * @param delim a characters that stops the parsing when encountered.
     * @return the std::string value read.
     */
    std::string readString(std::streamsize size = 1024, char delim = '\0');

    /**
     * @brief readMat
     * Parses an cv::Mat from the opened std::ifstream.
     * @return a pointer to the cv::Mat value read.
     */
    cv::Mat* readMat();

protected:

private:
    std::ifstream reader;
    bool reading;
    std::string line;
};

#endif // PROJECTREADER_H
