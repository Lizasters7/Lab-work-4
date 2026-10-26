#pragma once
#include "data.h"
#include <string>
#include <vector>

struct Operation {
    enum class Type { Read, Write, String };
    Type type;
    int field = 0;
    int value = 0;
};

class Timer {
public:
    Timer(std::string dir, int repeats);
    double calculate(const std::string& scenario, int threads);
    long long calculateChecksum() const;

private:
    std::string dir;
    int repeats;
    long long checksum = 0;
    static std::vector<Operation> loadFile(const std::string& path);
    static long long executeOperations(Data& data, const std::vector<Operation>& ops);
    double runOnce(const std::vector<std::vector<Operation>>& perThread);
};