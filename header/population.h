#include <iostream>
#include <vector>
#include <array>
#include <iterator>
#include <algorithm>
#include <random>

#include "individual.h"
#include "rouletteselect.h"

#ifndef POPULATION
#define POPULATION

#define POPULATION_SIZE 200
#define PAIR_SIZE 250
#define ELITE_RATE 0.2
#define GENERATION_COUNT 1000

class Population {
   private:
    std::array<Individual, POPULATION_SIZE> individuals;
    std::vector< std::array<int, 2> > defaultPairs;
    std::vector<Individual> crossover();
    std::vector<Individual> eliteSelect(
        std::vector<Individual> hugeIndividuals);

   public:
    Population();
    Individual calculate();
    void setIndividual(Individual individual, int index);
};

#endif
