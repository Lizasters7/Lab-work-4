#include "Data.h"
#include <mutex>

int Data::get(int i) const {
    std::shared_lock lk(fields[i].m);        
    return fields[i].value;
}

void Data::set(int i, int v) {
    std::unique_lock lk(fields[i].m);        
    fields[i].value = v;
}

Data::operator std::string() const {
    int a, b;
    {
        std::shared_lock l0(fields[0].m);
        std::shared_lock l1(fields[1].m);
        a = fields[0].value;
        b = fields[1].value;
    }
    return std::to_string(a) + " " + std::to_string(b);
}