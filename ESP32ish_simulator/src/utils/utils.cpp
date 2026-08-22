#include "utils.h"

void delay(int ms){
 std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}