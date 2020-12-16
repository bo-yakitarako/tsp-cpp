#include <iostream>
#include <vector>
#include <random>

#ifndef ROULETTE_SELECT
#define ROULETTE_SELECT

#include "population.h"

class RouletteSelect {
   private:
    std::vector<Individual> remain;
    std::vector<double> fitnesses;
    double fitnessSum;
    std::vector<double> convertToFitness();
    int getSelectIndex();

   public:
    RouletteSelect(std::vector<Individual> remain);
    void select(Population *population);
};

#endif
