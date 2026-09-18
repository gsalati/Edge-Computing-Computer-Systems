#include "serialMock.h"
#include <cerrno>
#include <csignal>
#include <cstring>
#include <iostream>
#include <poll.h>
#include <stdexcept>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <string_view>
#include <ranges>
#include <cctype>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <algorithm>

using namespace std;

SerialMock::SerialMock(){
}

SerialMock::~SerialMock() {
    
}

/**
 * @brief Inicia uma "serial mock"
 * 
 * @param msgType Tipo de dado que será transmito/recebidp
 * h -> hexadecimal; s -> strings de texto
 */
void SerialMock::begin(char msgType) {    
    if(msgType ==  'h')
    {
        t = "Hexadecimal";
        type = 0;
    }else
    {
        t = "Texto";
        type = 1;
    }   

    cout << "Porta Serial iniciada. Tipo de dado: " << t << endl;

    std::cout << "Digite o que será enviado ao ESP32 no formato " << t << endl;
    readThread = std::thread(&SerialMock::readLoop, this);
}

void SerialMock::readLoop(){
    char buffer[256];
    int i, n;
    std::string in, rx;
   
    while(true){
        std::cin >> in;
        uint8_t r;
        int b;
        rx = trim(in);
        n = rx.length();
        b = n;

        if(!isValidHex(rx))
        {
            cerr << "Hex string inválida!" << endl;
            continue;
        }



        if(n > 0)
        {
            {
                std::lock_guard<std::mutex> lock(bufferMtx);
                if(type == 0)
                {
                    if(n%2 != 0){
                        cerr << "Hex string deve ter tamanho par" << endl;
                        continue;
                    }

                    b = n/2;
                    for(i = 0; i < n; i+= 2)
                    {
                        std::string byteString = rx.substr(i, 2);

                        uint8_t byte = static_cast<uint8_t>(std::stoul(byteString, nullptr, 16));
                        readBuffer.push(byte);
                    }   
                }
                else
                {     
                    b = n;     
                    for(i = 0;  i < n; i++)
                    {
            
                        readBuffer.push(rx.c_str()[i]);
                    }
                }
            }  
            bytesToRead+=b;              
        } 

        /*
        cout << "bytes to read: " << bytesToRead << endl;
        cout.flush();
        */
    }

}

int SerialMock::available()
{
    int r;
    std::lock_guard<std::mutex> lock(bytesMtx);          
    r = bytesToRead.load();
    return r;
}

int SerialMock::readBytes(char* buffer, int length)
{
    int i = 0;
    int bytesReady = bytesToRead;
    int bytesRead = 0;

    std::lock_guard<std::mutex> lock1(bytesMtx);
    std::lock_guard<std::mutex> lock2(bufferMtx);

    if(readBuffer.empty()){
        return 0;
    }
    for(i = 0; i <= length; i++)
    {
        buffer[i] = readBuffer.front();
        readBuffer.pop();
        
        bytesToRead--;
        bytesRead++;

        if(readBuffer.empty()){
            return bytesRead;
        }
    }
    return bytesRead;
}

int SerialMock::writeBytes(char* data, int length)
{
    cout << "TX ESP32: ";
    if(type == 0)
    {
        std::ostringstream oss;
        oss << std::uppercase << std::hex << std::setfill('0');

        for (int i = 0; i < length; i++) {
            oss << std::setw(2)
                << static_cast<unsigned int>(static_cast<unsigned char>(data[i]));
        }

        cout << oss.str();
    }
    else
    {
        cout.write(data, length);
    }

    cout << endl;

    return length;
}

bool SerialMock::isValidHex(std::string_view s) {
    if (s.empty()) return false;
        
    return !s.empty() && std::ranges::all_of(s, [](unsigned char c) {
        return std::isxdigit(c);
    });
}