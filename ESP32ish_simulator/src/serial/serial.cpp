#include "serial.h"
#include <cerrno>
#include <csignal>
#include <cstring>
#include <iostream>
#include <poll.h>
#include <stdexcept>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

using namespace std;

SerialCom::SerialCom(){
}

SerialCom::~SerialCom() {
    
}

void SerialCom::begin(int baudRate) {
    speed_t speed;

    switch (baudRate) {
        case 1200: speed = B1200; break;
        case 2400: speed = B2400; break;
        case 4800: speed = B4800; break;
        case 9600: speed = B9600; break;
        case 19200: speed = B19200; break;
        case 38400: speed = B38400; break;
        case 57600: speed = B57600; break;
        case 115200: speed = B115200; break;
        default:
            std::cerr << "Unsupported baud rate: " << baudRate << endl;
            exit(1);
    }

    fd = open(portname, O_RDWR | O_NOCTTY | O_SYNC);

    if (fd < 0) {
        std::cerr << "Error opening " << portname << ": "
             << strerror(errno) << endl;
        exit(1);
    }
    
    // Configura o terminal serial
    termios tty{};

    if (tcgetattr(fd, &tty) != 0) {
        std::cerr << "tcgetattr(): "
                  << std::strerror(errno) << '\n';
        close(fd);
        exit(1);
    }

    cfsetospeed(&tty, speed);
    cfsetispeed(&tty, speed);

   // 8N1
    tty.c_cflag &= ~PARENB; // sem paridade
    tty.c_cflag &= ~CSTOPB; // 1 stop bit
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8;     // 8 bits

    // Sem controle de fluxo
    tty.c_cflag &= ~CRTSCTS;

    // Habilita receptor
    tty.c_cflag |= CREAD | CLOCAL;

    // Modo raw
    tty.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    tty.c_iflag &= ~(IXON | IXOFF | IXANY);
    tty.c_iflag &= ~(IGNBRK | BRKINT | PARMRK |
                     ISTRIP | INLCR | IGNCR | ICRNL);
    tty.c_oflag &= ~OPOST;

    // Não queremos que read() fique bloqueado.
    tty.c_cc[VMIN]  = 0;
    tty.c_cc[VTIME] = 0;

    if (tcsetattr(fd, TCSANOW, &tty) != 0) {
        std::cerr << "tcsetattr(): "
                  << std::strerror(errno) << '\n';
        close(fd);
        exit(1);
    }

    cout << "Porta Serial iniciada. Device: " << portname << endl;
    readThread = std::thread(&SerialCom::readLoop, this);
}

void SerialCom::readLoop(){
    pollfd pfd{};
    pfd.fd = fd;
    pfd.events = POLLIN;
    ssize_t n = 0;
    ssize_t i = 0;
    char buffer[256];
   
    while(true){
        int poll_result = poll(&pfd, 1, 1000); // 1 second timeout

        if(poll_result < 0){
            if(errno == EINTR)
                continue;

            std::cerr << "poll(): "
            << std::strerror(errno) << '\n';
            
            break; 
        }

        if (poll_result == 0){
            // Time out
            continue;
        }

        if(pfd.revents & POLLIN)
        {
            n = read(fd, buffer, sizeof(buffer));
            //cout.write(buffer, n);
            //cout.flush();
            if(n > 0)
            {
                {
                    std::lock_guard<std::mutex> lock(bufferMtx);          
                    for(i = 0;  i < n; i++)
                    {
                        readBuffer.push(buffer[i]);
                    }
                }
                bytesToRead+=n;              
            }
            else if(n == 0)
            {
                continue;
            }
            else
            {
                std::cerr << "read(): "
                << std::strerror(errno) << '\n';
                break;
            }
        }

        // Erro no dispositivo
        if (pfd.revents & (POLLERR | POLLHUP | POLLNVAL)) {
            std::cerr << "\nErro/desconexão do dispositivo.\n";
            break;
        }
    }

    close(fd);
    std::cout << "Conexão serial terminada." << std::endl;
}

int SerialCom::available()
{
    int r;
    std::lock_guard<std::mutex> lock(bytesMtx);          
    r = bytesToRead.load();
    return r;
}

int SerialCom::readBytes(char* buffer, int length)
{
    int i = 0;
    int bytesReady = bytesToRead;
    int bytesRead = 0;

    std::lock_guard<std::mutex> lock1(bytesMtx);
    std::lock_guard<std::mutex> lock2(bufferMtx);

    if(readBuffer.empty()){
        cout << "ueh";
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
    cout << "3?" << endl;
    return bytesRead;
}

int SerialCom::writeBytes(const char* data, int length)
{
   int totalToWrite = length;
   int totalWritten = 0;
   int bytesWritten = 0;

   if(length <=0)
   {
        cerr << "Tentativa de escrever 0 btyes" << endl;
        return 0;
   }

   while (totalWritten < length)
   {
        bytesWritten = write(fd, data + totalWritten, length - totalWritten);
        if(bytesWritten < 0)
        {
            cerr << "Erro na escrita" << endl;
            return 0;
        }
        totalWritten += bytesWritten;
   }

   return totalWritten;
}