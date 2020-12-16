#include "../header/individual.h"

int Individual::nodes[][2] = {
    {23, 39}, {8, 44}, {34, 36}, {12, 30}, {42, 37}, {6, 35},  {1, 15},
    {12, 25}, {4, 39}, {13, 42}, {23, 13}, {7, 39},  {11, 5},  {6, 44},
    {28, 45}, {10, 7}, {3, 16},  {4, 19},  {3, 39},  {0, 2},   {19, 21},
    {5, 43},  {8, 34}, {20, 39}, {2, 50},  {20, 26}, {16, 36}, {24, 30},
    {9, 40},  {5, 22}, {30, 35}, {2, 0},   {21, 36}, {22, 28}, {3, 33},
    {11, 36}, {14, 34}};

Individual::Individual() {
    this->setRandomGene();
    this->score = this->calcScore();
}

Individual::Individual(Individual mother, Individual father, int division) {
    this->orderCrossover(mother, father, division);
    std::random_device seed;
    std::mt19937 rand(seed());
    std::uniform_int_distribution<double> distribution(0, 1);
    if (distribution(rand) < MUTATION_RATE) {
        this->spontaneousMutation();
    }
    this->score = this->calcScore();
}

void Individual::setRandomGene() {
    std::vector<int> numbers(NODE_COUNT);
    for (int i = 0; i < NODE_COUNT; i++) {
        numbers[i] = i;
    }
    std::random_device seed;
    std::mt19937 rand(seed());
    for (int i = 0; i < NODE_COUNT; i++) {
        std::uniform_int_distribution<int> distribution(0, numbers.size() - 1);
        int r = distribution(rand);
        this->chromosome[i] = numbers[r];
        numbers.erase(numbers.begin() + r);
    }
}

void Individual::orderCrossover(Individual mother, Individual father,
                                int division) {
    for (int i = 0; i < division; i++) {
        this->chromosome[i] = mother.chromosome[i];
    }
    int geneIndex = division;
    for (int i = 0; i < NODE_COUNT; i++) {
        int value = father.chromosome[i];
        bool including = false;
        for (int formerIndex = 0; formerIndex < division; formerIndex++) {
            if (value == this->chromosome[formerIndex]) {
                including = true;
                break;
            }
        }
        if (including) {
            continue;
        }
        this->chromosome[geneIndex++] = value;
        if (geneIndex == NODE_COUNT) {
            break;
        }
    }
}

void Individual::spontaneousMutation() {
    std::random_device seed;
    std::mt19937 rand(seed());
    std::uniform_int_distribution<int> distribution(0, NODE_COUNT - 1);
    int a, b;
    a = b = distribution(rand);
    while (a == b) {
        b = distribution(rand);
    }
    int index1 = a < b ? a : b;
    int index2 = a < b ? b : a;
    int copy[NODE_COUNT];
    for (int i = 0; i < NODE_COUNT; i++) {
        copy[i] = this->chromosome[i];
    }
    for (int i = 0; i < NODE_COUNT; i++) {
        int mutateIndex = index1 <= i && i <= index2 ? index1 + index2 - i : i;
        this->chromosome[i] = copy[mutateIndex];
    }
}

void Individual::output() {
    std::cout << "遺伝子配列: [";
    for (int i = 0; i < NODE_COUNT; i++) {
        if (i % 10 == 0) {
            std::cout << "\n    ";
        }
        std::cout << this->chromosome[i] << ", ";
    }
    std::cout << "\n]\n経路長: " << this->score << std::endl;
}

double Individual::calcScore() {
    double score = 0;
    for (int i = 0; i < NODE_COUNT; i++) {
        int gene1 = this->chromosome[i];
        int gene2 = this->chromosome[i < NODE_COUNT - 1 ? i + 1 : 0];
        score += Individual::calcDistance(gene1, gene2);
    }
    return score;
}

double Individual::calcDistance(int gene1, int gene2) {
    int x = Individual::nodes[gene1][0] - Individual::nodes[gene2][0];
    int y = Individual::nodes[gene1][1] - Individual::nodes[gene2][1];
    return sqrt(x * x + y * y);
}
