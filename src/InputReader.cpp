#include "../include/connectionHandler.h"
#include "../include/InputReader.h"
#include <boost/lexical_cast.hpp>
using namespace std;

InputReader::InputReader(ConnectionHandler &_connectionHandler, std::atomic<bool> &_shouldTerminate): connectionHandler(_connectionHandler), optcode(),shouldTerminate(_shouldTerminate), len(0) {}
void InputReader::run() {
    while (!shouldTerminate) {
        const short bufsize = 1024;
        char buf[bufsize];
        std::cin.getline(buf, bufsize);
        std::string line(buf);
        convertToBytes(line, buf,len);
        if (!connectionHandler.sendBytes(buf, len)) {
            std::cout << "Disconnected. Exiting...\n" << std::endl;
            break;
        }
        if(line=="LOGOUT"){ //To make sure that the thread won't enter the final iteration in case that the logout command is valid
            sleep(1);
        }
        len=0;
    }
}
//void InputReader::run(bool &shouldTerminate) {
//    while (!shouldTerminate) {
//        const short bufsize = 1024;
//        char buf[bufsize];
//        std::cin.getline(buf, bufsize);
//        std::string line(buf);
//        convertToBytes(line, buf,len);
//        if (!connectionHandler.sendBytes(buf, len)) {
//            std::cout << "Disconnected. Exiting...\n" << std::endl;
//            break;
//        }
//        len=0;
//    }
//}
//
void InputReader::convertToBytes(const std::string &input, char *bytes, int &len) {
    std::string command=input.substr(0, input.find_first_of(' ', 0));
    optcode=getOptcode(command);
    shortToBytes(optcode, bytes, len);
//    if(optcode==1 || optcode==2 || optcode==3 || optcode==8){
//        convertByUserAndPassword(input,command,bytes,len);
//    } else{
//      if(optcode==4){
//          shouldTerminate= true;
//      } else{
//          if(optcode==5 || optcode==6 || optcode==7 || optcode==9 || optcode==10){
//              convertByCourseNumber(input,command,bytes,len);
//          }
//      }
//    }
    switch (optcode) {
        case 1:
        case 2:
        case 3:
        case 8:
            convertByUserAndPassword(input,command,bytes,len);
            break;
        case 4:
        case 11:
            bytes[len++]='\0';
            break;
        case 5:
        case 6:
        case 7:
        case 9:
        case 10:
            convertByCourseNumber(input,command,bytes,len);

    }

}

//int InputReader::numberOfSpaces(std::string string) {
//    int numberOfSpaces = 0;
//    for (int i = 0; i < string.length(); i++) {
//        if (string.at(i) == ' ') {
//            numberOfSpaces = numberOfSpaces + 1;
//        }
//    }
//    return numberOfSpaces;
//}

short InputReader::getOptcode(std::string command) {
    if (command == "ADMINREG"){
        optcode=1;
    } else {
        if (command == "STUDENTREG") {
            optcode = 2;
        } else {
            if (command == "LOGIN") {
                optcode = 3;
            } else {
                if (command == "LOGOUT"){
                    optcode=4;
                } else{
                    if(command=="COURSEREG"){
                        optcode=5;
                    } else{
                        if(command=="KDAMCHECK"){
                            optcode=6;
                        } else{
                            if(command=="COURSESTAT"){
                                optcode=7;
                            } else{
                                if(command=="STUDENTSTAT"){
                                    optcode=8;
                                } else{
                                    if(command=="ISREGISTERED"){
                                        optcode=9;
                                    } else{
                                        if(command=="UNREGISTER"){
                                            optcode=10;
                                        } else{
                                            if(command=="MYCOURSES"){
                                                optcode=11;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }

            }
        }
    }
    return optcode;
}

void InputReader::shortToBytes(short num, char *bytesArr, int& len) {
    bytesArr[len++] = ((num >> 8) & 0xFF);
//    cout<<bytesArr[len-1]<<endl;
    bytesArr[len++] = (num & 0xFF);
//    cout<<bytesArr[len-1]<<endl;
}

void InputReader::convertByUserAndPassword(const std::string& input, const std::string& command, char *bytesArr, int &len) {
    int inputLength=input.length();
    for(int i=command.length()+1; i<inputLength; i++){
        if(input.at(i)==' '){
            bytesArr[len++]='\0';
        }
        else{
            bytesArr[len++]=input.at(i);
        }
    }
    bytesArr[len++]='\0';
}

void InputReader::convertByCourseNumber(const std::string& input, const std::string& command, char *bytesArr, int &len) {
    std::string courseNumByString=input.substr(command.length()+1,input.length());
    short courseNumByShort=boost::lexical_cast<short>(courseNumByString);
    shortToBytes(courseNumByShort,bytesArr,len);
}


