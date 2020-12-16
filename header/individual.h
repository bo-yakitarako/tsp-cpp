#include <iostream>
#include <random>
#include <vector>
#include <math.h>

#ifndef INDIVIDUAL
#define INDIVIDUAL

#define NODE_COUNT 37
#define MUTATION_RATE 0.03

class Individual {
   private:
    void setRandomGene();
    void orderCrossover(Individual mother, Individual father, int division);
    void spontaneousMutation();
    double calcScore();
    static double calcDistance(int gene1, int gene2);

   public:
    int chromosome[NODE_COUNT];
    double score;
    static int nodes[NODE_COUNT][2];
    Individual();
    Individual(Individual mother, Individual father, int division);
    void output();
};

#endif
