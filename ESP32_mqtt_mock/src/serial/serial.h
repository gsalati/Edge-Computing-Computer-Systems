#ifndef SERIAL_H
#define SERIAL_H

#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <atomic>

class SerialCom {
public:
    SerialCom();
    ~SerialCom();
    // Initialize serial communication with the specified baud rate
    void begin(int baudRate);
    int writeBytes(const char* data, int length);
    int readBytes(char* buffer, int length);
    int available();
    void setPortName(const char* port) { portname = port; }
private:
    int fd; // File descriptor for the serial port
    const char* portname = "/dev/ttyACM0";
    std::atomic<int> bytesToRead = 0;
    std::thread readThread;
    std::queue<char> readBuffer;

    std::mutex bufferMtx;
    std::mutex bytesMtx;

    void readLoop(); // Thread function to continuously read from the serial port
};

#endif