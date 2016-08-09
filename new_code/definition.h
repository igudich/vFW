#ifndef DEFINITION_H
#define DEFINITION_H
#include <chrono>

//#define TEST_MODE

#define TIME_MEASURE(some) \
    auto start = std::chrono::high_resolution_clock::now(); \
    some \
    auto diff = std::chrono::high_resolution_clock::now() - start;\
    auto t1 = std::chrono::duration_cast<std::chrono::milliseconds>(diff);\
    std::cout << "Time: " << t1.count() << std::endl;

#endif // DEFINITION_H

