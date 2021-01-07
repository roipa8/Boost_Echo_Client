#include "../include/connectionHandler.h"
#include "string"
#include <atomic>

#ifndef BOOST_ECHO_CLIENT_INPUTREADER_H
#define BOOST_ECHO_CLIENT_INPUTREADER_H


class InputReader {
public:
    InputReader(ConnectionHandler &connectionHandler, std::atomic<bool> &shouldTerminate);
    void run();
    void convertToBytes(const std::string& input, char bytes[], int &len);
    void shortToBytes(short num, char bytesArr[], int& len);
//    int numberOfSpaces(std::string string);
    short getOptcode(std::string command);
    void convertByUserAndPassword(const std::string& input, const std::string& command, char bytesArr[], int& len);
    void convertByCourseNumber(const std::string& input, const std::string& command, char bytesArr[], int& len);

private:
    ConnectionHandler &connectionHandler;
    short optcode;
    std::atomic<bool> &shouldTerminate;
//    bool &shouldTerminate;
    int len;

};


#endif //BOOST_ECHO_CLIENT_INPUTREADER_H
