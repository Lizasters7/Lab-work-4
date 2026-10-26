#include "generator.h"
#include <iostream>
#include "timer.h"
#include <filesystem>
#include <iomanip>

int main() {
    const std::string dir = "tests";

    if (!std::filesystem::exists(dir)) {            
        Generator gen(1200000, dir);
        gen.generateScenario("a", {10, 5, 50, 10, 25});
        gen.generateScenario("b", {20, 20, 20, 20, 20});
        gen.generateScenario("c", {5, 40, 5, 40, 10});
    }

    Timer timer(dir, 10);                      

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Average time, ms\n";
    std::cout << "file   1 thread   2 threads   3 threads\n";
    for (const char* s : {"a", "b", "c"}) {
        std::cout << s << "   ";
        for (int t = 1; t <= 3; ++t)
            std::cout << std::setw(10) << timer.calculate(s, t) << "  ";
        std::cout << "\n";
    }
    std::cout << "Checksum: " << timer.calculateChecksum() << "\n";
}