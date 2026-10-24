#pragma once
#include <random>
#include <string>

class Generator {
public:
    Generator(int total, std::string dir, unsigned seed = 1);
    void generateScenario(const std::string& name, std::discrete_distribution<int> dist);

private:
    int total;          
    std::string dir;    
    unsigned seed;      
    static const char* opLine(int op);
    void generateFile(const std::string& path, int count, std::discrete_distribution<int> dist);
};