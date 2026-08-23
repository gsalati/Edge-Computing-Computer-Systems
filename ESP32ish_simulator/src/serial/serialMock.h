#ifndef SERIAL_MOCK_H
#define SERIAL_MOCK_H

#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <string_view>
#include <ranges>
#include <cctype>

inline constexpr const char* toTrim = " \t\n\r\f\v";

// trim from end of string (right)
inline std::string& rtrim(std::string& s, const char* t = toTrim)
{
    s.erase(s.find_last_not_of(t) + 1);
    return s;
}

// trim from beginning of string (left)
inline std::string& ltrim(std::string& s, const char* t = toTrim)
{
    s.erase(0, s.find_first_not_of(t));
    return s;
}

// trim from both ends of string (right then left)
inline std::string& trim(std::string& s, const char* t = toTrim)
{
    return ltrim(rtrim(s, t), t);
}


class SerialMock {
public:
    SerialMock();
    ~SerialMock();
    // Initialize serial communication with the specified baud rate
    void begin(char msgType);
    int writeBytes(char* data, int length);
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

    uint8_t type = 0; // 0 -> hexa, 1 -> string
    std::string t;

    void readLoop(); // Thread function to continuously read from the serial port
    bool isValidHex(std::string_view s);
};

#endif