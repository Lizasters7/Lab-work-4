#include "Data.h"
#include <thread>
#include <iostream>

int main() {
    Data d;
    auto work = [&] {
        for (int k = 0; k < 100000; ++k) {
            d.set(k % 2, k);
            d.get(1);
            std::string s = d;
        }
    };
    std::thread t1(work), t2(work), t3(work);
    t1.join(); t2.join(); t3.join();
    std::cout << std::string(d) << "\n";
}