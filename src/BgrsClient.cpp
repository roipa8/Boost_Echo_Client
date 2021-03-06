#include <stdlib.h>
#include <connectionHandler.h>
#include <iostream>
#include "../include/InputReader.h"
#include "../include/OutputWriter.h"
#include <mutex>
#include <thread>

int main (int argc, char *argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " host port" << std::endl << std::endl;
        return -1;
    }
    std::string host = argv[1];
    short port = atoi(argv[2]);
    ConnectionHandler connectionHandler(host, port);
    if (!connectionHandler.connect()) {
        std::cerr << "Cannot connect to " << host << ":" << port << std::endl;
        return 1;
    }
    bool shouldTerminate=false;
    bool canProceed= false;
//    std::atomic<bool> shouldTerminate(false);
    InputReader inputReader(connectionHandler, shouldTerminate, canProceed);
    OutputWriter outputWriter(connectionHandler, shouldTerminate, canProceed);
    std::thread socket_thread(&OutputWriter::run,&outputWriter);
    std::thread keyboard_thread(&InputReader::run, &inputReader);
//    std::thread socket_thread(&OutputWriter::run(&shouldTerminate), &outputWriter);
//    keyboard_thread.detach();
//    socket_thread.detach();
    keyboard_thread.join();
    socket_thread.join();
    return 0;
}



