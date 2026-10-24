#pragma once
#include <shared_mutex>
#include <string>

class Data {
public:
    static constexpr int M = 2;         
    int get(int i) const;
    void set(int i, int v);
    operator std::string() const;

private:
    struct alignas(64) Field {
        int value = 0;
        mutable std::shared_mutex m;
    };
    Field fields[M];                    
};