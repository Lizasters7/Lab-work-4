#include "timer.h"
#include <chrono>
#include <fstream>
#include <stdexcept>
#include <thread>

Timer::Timer(std::string dir, int repeats): dir(std::move(dir)), repeats(repeats) {}

long long Timer::calculateChecksum() const {
    return checksum;
}

std::vector<Operation> Timer::loadFile(const std::string& path) {
    std::ifstream in(path);
    if (!in)
        throw std::runtime_error("Cannot open " + path);

    std::vector<Operation> ops;
    std::string cmd;
    while (in >> cmd) {
        Operation op;
        if (cmd == "read") {
            op.type = Operation::Type::Read;
            in >> op.field;
        } else if (cmd == "write") {
            op.type = Operation::Type::Write;
            in >> op.field >> op.value;
        } else {
            op.type = Operation::Type::String;
        }
        ops.push_back(op);
    }
    return ops;
}

long long Timer::executeOperations(Data& data, const std::vector<Operation>& ops) {
    long long sink = 0;
    for (const Operation& op : ops) {
        if (op.type == Operation::Type::Read)
            sink += data.get(op.field);
        else if (op.type == Operation::Type::Write)
            data.set(op.field, op.value);
        else
            sink += std::string(data).size();
    }
    return sink;
}

double Timer::runOnce(const std::vector<std::vector<Operation>>& perThread) {
    Data data;                                      
    std::vector<long long> sinks(perThread.size());
    std::vector<std::thread> threads;

    auto start = std::chrono::steady_clock::now();
    for (size_t t = 0; t < perThread.size(); ++t)
        threads.emplace_back([&, t] { sinks[t] = executeOperations(data, perThread[t]); });
    for (std::thread& th : threads)
        th.join();
    auto end = std::chrono::steady_clock::now();

    for (long long s : sinks)
        checksum += s;
    return std::chrono::duration<double, std::milli>(end - start).count();
}

double Timer::calculate(const std::string& scenario, int threads) {
    std::vector<std::vector<Operation>> perThread;
    for (int i = 0; i < threads; ++i)
        perThread.push_back(loadFile(dir + "/" + scenario + "_"
                                     + std::to_string(threads) + "t_"
                                     + std::to_string(i) + ".txt"));

    double total = 0;
    for (int i = 0; i < repeats; ++i)
        total += runOnce(perThread);
    return total / repeats;
}