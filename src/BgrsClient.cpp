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
//    bool shouldTerminate= false;
    InputReader inputReader(connectionHandler);
    OutputWriter outputWriter(connectionHandler);
//    while (!shouldTerminate) {
//        int len=0;
//        const short bufsize = 1024;
//        char buf[bufsize];
//        std::cin.getline(buf, bufsize);
//        std::string line(buf);
//        inputReader.convertToBytes(line,buf,len);
//        convertToBytes(line, buf,len);
//        if (!connectionHandler.sendBytes(buf, len)) {
//            std::cout << "Disconnected. Exiting...\n" << std::endl;
//            break;
//        }
//        std::string answer="";
//        char ans[bufsize];
//        if (!connectionHandler.getLine(answer)) {
//            std::cout << "Disconnected. Exiting...\n" << std::endl;
//            break;
//        }
//        std::cout<<answer<<std::endl;
//            if(answer=="Ack 4"){
//                shouldTerminate= true;
//            }
//        }
    std::thread keyboard_thread(&InputReader::run, &inputReader);
    std::thread socket_thread(&OutputWriter::run, &outputWriter);
//    keyboard_thread.detach();
//    socket_thread.detach();
    keyboard_thread.join();
    socket_thread.join();
    std::cout<<"check";
    return 0;
}



