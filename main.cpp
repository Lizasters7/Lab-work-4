#include "generator.h"
#include <iostream>

int main() {
    Generator gen(1200000, "tests");      

    gen.generateScenario("a", {10, 5, 50, 10, 25});   
    gen.generateScenario("b", {20, 20, 20, 20, 20});  
    gen.generateScenario("c", {5, 40, 5, 40, 10});    

    std::cout << "Files generated\n";
}