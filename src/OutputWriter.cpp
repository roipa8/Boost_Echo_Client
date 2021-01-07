#include "../include/OutputWriter.h"
#include "string"

OutputWriter::OutputWriter(ConnectionHandler &_connectionHandler, bool &_shouldTerminate, bool &_canProceed): connectionHandler(_connectionHandler), shouldTerminate(_shouldTerminate), canProceed(_canProceed) {}
void OutputWriter::run() {
    while (!shouldTerminate) {
        answer="";
        if (!connectionHandler.getLine(answer)) {
            std::cout << "Disconnected. Exiting...\n" << std::endl;
            break;
        }
        std::cout << answer << std::endl;
        if(answer=="ACK 4"){
            shouldTerminate=true;
            canProceed= true;
        }
        if(answer=="ERROR 4"){
            canProceed= true;
        }
    }
}

//void OutputWriter::run() {
//    while (!shouldTerminate){
//        std::string answer="";
//        if (!connectionHandler.getLine(answer)) {
//            std::cout << "Disconnected. Exiting...\n" << std::endl;
//            break;
//        }
//        std::cout <<answer <<std::endl;
//        int len=answer.length();
//        if(answer.at(len)=='\0'){
//            answer.resize(len-1);
//            std::cout <<answer <<std::endl;
//            if(answer=="Ack 4"){
//                shouldTerminate= true;
//            }
//        }
//        answer.resize(len-1);
//        std::cout << "Reply: " << answer << " " << len << " bytes " << std::endl << std::endl;
//        if (answer == "bye") {
//            std::cout << "Exiting...\n" << std::endl;
//            break;
//        }
//    }
//}

