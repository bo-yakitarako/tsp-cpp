#include "../header/rouletteselect.h"

RouletteSelect::RouletteSelect(std::vector<Individual> remain) {
    this->remain = remain;
    this->fitnesses = this->convertToFitness();
}

std::vector<double> RouletteSelect::convertToFitness() {
    const double MIN_SCORE = this->remain[this->remain.size() - 1].score;
    const double DIFF = this->remain[0].score - MIN_SCORE;
    const int MAX = 10, MIN = 1;
    std::vector<double> fitnesses(this->remain.size());
    this->fitnessSum = 0;
    for (int i = 0; i < fitnesses.size(); i++) {
        fitnesses[i] =
            ((this->remain[i].score - MIN_SCORE) / DIFF) * (MAX - MIN) + MIN;
        this->fitnessSum += fitnesses[i];
    }
    return fitnesses;
}

void RouletteSelect::select(Population *population) {
    const int ELITE_COUNT = (int)(POPULATION_SIZE * ELITE_RATE);
    for (int index = ELITE_COUNT; index < POPULATION_SIZE; index++) {
        int selectIndex = this->getSelectIndex();
        this->fitnessSum -= this->fitnesses[selectIndex];
        Individual selectedIndividual = this->remain[selectIndex];
        this->fitnesses.erase(this->fitnesses.begin() + selectIndex);
        this->remain.erase(this->remain.begin() + selectIndex);
        population->setIndividual(selectedIndividual, index);
    }
}

int RouletteSelect::getSelectIndex() {
    std::random_device seed;
    std::mt19937 rand(seed());
    std::uniform_int_distribution<double> distribution(0, this->fitnessSum);
    double randomValue = distribution(rand);
    double currentSum = 0;
    for (int i = 0; i < this->fitnesses.size(); i++) {
        double preSum = currentSum;
        currentSum += this->fitnesses[i];
        if (preSum <= randomValue && randomValue < currentSum) {
            return i;
        }
    }
    return this->fitnesses.size() - 1;
}
