#include <iostream>
#include <random>
#include "header/population.h"

int main(void) {
    Population population;
    Individual result = population.calculate();
    std::cout << "最終世代" << std::endl;
    result.output();
    return 0;
}
