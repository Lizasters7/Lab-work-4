#include "generator.h"
#include <filesystem>
#include <fstream>

Generator::Generator(int total, std::string dir, unsigned seed): total(total), dir(std::move(dir)), seed(seed) {
    std::filesystem::create_directory(this->dir);
}

const char* Generator::opLine(int op) {
    switch (op) {
        case 0:  return "read 0\n";
        case 1:  return "write 0 1\n";
        case 2:  return "read 1\n";
        case 3:  return "write 1 1\n";
        default: return "string\n";
    }
}

void Generator::generateFile(const std::string& path, int count, std::discrete_distribution<int> dist) {
    std::mt19937 gen(seed++);           
    std::ofstream out(path);
    for (int i = 0; i < count; ++i)
        out << opLine(dist(gen));
}

void Generator::generateScenario(const std::string& name, std::discrete_distribution<int> dist) {
    for (int threads = 1; threads <= 3; ++threads) {
        int perThread = total / threads;
        for (int i = 0; i < threads; ++i) {
            std::string path = dir + "/" + name + "_" + std::to_string(threads)
                             + "t_" + std::to_string(i) + ".txt";
            generateFile(path, perThread, dist);
        }
    }
}