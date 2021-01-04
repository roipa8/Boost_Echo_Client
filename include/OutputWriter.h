#include "../include/connectionHandler.h"
#include "string"

#ifndef BOOST_ECHO_CLIENT_OUTPUTWRITER_H
#define BOOST_ECHO_CLIENT_OUTPUTWRITER_H


class OutputWriter {
public:
    void run();
    OutputWriter(ConnectionHandler &connectionHandler);

private:
    ConnectionHandler& connectionHandler;
    bool shouldTerminate;
};


#endif //BOOST_ECHO_CLIENT_OUTPUTWRITER_H
