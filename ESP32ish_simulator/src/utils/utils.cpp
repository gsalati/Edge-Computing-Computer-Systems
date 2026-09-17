#include "utils.h"
#include <chrono>
#include <iostream>

void delay(int ms){
 std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

unsigned long millis(){
    static bool first;
    static std::chrono::_V2::steady_clock::time_point firstMilli;

    if(!first){
        firstMilli = std::chrono::steady_clock::now();
        first = true;
        return 0;
    }

    auto timeNow =  std::chrono::steady_clock::now();
    auto millis2return = std::chrono::duration_cast<std::chrono::milliseconds>(timeNow - firstMilli).count();

    return static_cast<unsigned long> (millis2return);
}