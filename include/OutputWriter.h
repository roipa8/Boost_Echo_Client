#include "../include/connectionHandler.h"
#include "string"
#include <atomic>

#ifndef BOOST_ECHO_CLIENT_OUTPUTWRITER_H
#define BOOST_ECHO_CLIENT_OUTPUTWRITER_H


class OutputWriter {
public:
    void run();
    OutputWriter(ConnectionHandler &connectionHandler,bool &shouldTerminate, bool &canProceed);

private:
    ConnectionHandler& connectionHandler;
//    std::atomic<bool> &shouldTerminate;
    bool& shouldTerminate;
    bool &canProceed;
    std::string answer;
};


#endif //BOOST_ECHO_CLIENT_OUTPUTWRITER_H
