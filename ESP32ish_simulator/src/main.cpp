#include <cerrno>
#include <csignal>
#include <cstring>
#include <iostream>
#include <poll.h>
#include <stdexcept>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <memory.h>
#include "esp32.h"
using namespace std;

#include "serial/serial.h"

int main(int argc, char* argv[])
{
    std::ios_base::sync_with_stdio(false); // Unsychronize C++ streams from C stdio
    std::cin.tie(nullptr);                 // Untie cin from cout

    setup();
    
    while(true){loop();}

     std::cout << "\nEncerrado.\n";

    return 0;
}