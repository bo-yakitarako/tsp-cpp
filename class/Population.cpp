#include "../header/population.h"

bool sort_callback(Individual& a, Individual& b) { return a.score < b.score; }

Population::Population() {
    for (int i = 0; i < POPULATION_SIZE; i++) {
        Individual individual;
        this->individuals[i] = individual;
    }
    for (int row = 0; row < POPULATION_SIZE - 1; row++) {
        for (int column = row + 1; column < POPULATION_SIZE; column++) {
            std::array<int, 2> pair = {row, column};
            this->defaultPairs.push_back(pair);
        }
    }
    bool (*callback)(Individual&, Individual&) = sort_callback;
    std::sort(this->individuals.begin(), this->individuals.end(), callback);
}

Individual Population::calculate() {
    for (int i = 0; i < GENERATION_COUNT - 1; i++) {
        std::cout << "第" << i + 1 << "世代" << std::endl;
        this->individuals[0].output();
        std::cout << std::endl;
        std::vector<Individual> hugeIndividuals = this->crossover();
        std::vector<Individual> remain = this->eliteSelect(hugeIndividuals);
        RouletteSelect rouletteSelect(remain);
        rouletteSelect.select(this);
    }
    return this->individuals[0];
}

void Population::setIndividual(Individual individual, int index) {
    this->individuals[index] = individual;
}

std::vector<Individual> Population::crossover() {
    std::vector<Individual> hugeIndividuals(POPULATION_SIZE + 2 * PAIR_SIZE);
    for (int i = 0; i < POPULATION_SIZE; i++) {
        hugeIndividuals[i] = this->individuals[i];
    }
    int childIndex = POPULATION_SIZE;
    std::vector<std::array<int, 2> > pairs;
    std::copy(this->defaultPairs.begin(), this->defaultPairs.end(),
              std::back_inserter(pairs));
    std::random_device seed;
    std::mt19937 rand(seed());
    for (int i = 0; i < PAIR_SIZE; i++) {
        std::uniform_int_distribution<int> pairDistribution(0,
                                                            pairs.size() - 1);
        int pairIndex = pairDistribution(rand);
        Individual parent1 = this->individuals[pairs[pairIndex][0]];
        Individual parent2 = this->individuals[pairs[pairIndex][1]];
        std::uniform_int_distribution<int> nodesDistribution(0, NODE_COUNT - 1);
        int division = nodesDistribution(rand);
        Individual child1(parent1, parent2, division);
        Individual child2(parent2, parent1, division);
        pairs.erase(pairs.begin() + pairIndex);
        hugeIndividuals[childIndex++] = child1;
        hugeIndividuals[childIndex++] = child2;
    }
    return hugeIndividuals;
}

std::vector<Individual> Population::eliteSelect(
    std::vector<Individual> hugeIndividuals) {
    const int ELITE_COUNT = POPULATION_SIZE * ELITE_RATE;
    bool (*callback)(Individual&, Individual&) = sort_callback;
    std::sort(hugeIndividuals.begin(), hugeIndividuals.end(), callback);
    for (int i = 0; i < ELITE_COUNT; i++) {
        this->individuals[i] = hugeIndividuals[i];
    }
    const int REMAIN_COUNT = POPULATION_SIZE - ELITE_COUNT;
    std::vector<Individual> remain(REMAIN_COUNT);
    for (int i = 0; i < REMAIN_COUNT; i++) {
        remain[i] = hugeIndividuals[i + ELITE_COUNT];
    }
    return remain;
}
