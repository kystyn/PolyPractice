#include <algorithm>
#include <cmath>
#include "differentialevolution.h"

DifferentialEvolution::DifferentialEvolution( const Stretch::Sector &sector ) :
    mutantShift(0),
    sector(sector)
{
}

void DifferentialEvolution::generatePopulation()
{
    double minVelocity = sector.maxVelocity / 10;
    population.resize(populationSize);

    for (size_t i = 0; i < populationSize; i++)
    {
        Solution sol;
        double velocity = (minVelocity + (sector.maxVelocity - sector.maxVelocity) * i / populationSize) / 3.6;
        int time = int(std::ceil(sector.length / velocity));
        int stepsCount = time / step + 1;
        sol.setTimeUniformDistribution(step, stepsCount);

        sol.traction.resize(size_t(stepsCount));
        sol.brake.resize(size_t(stepsCount));
        if (i < populationSize / 2)
            for (size_t s = 0; s < size_t(stepsCount); s++)
            {
                sol.brake[s] = 1 + rand() % 6;
                sol.traction[s] = 0;
            }
        else
            for (size_t s = 0; s < size_t(stepsCount); s++)
            {
                sol.brake[s] = 0;
                sol.traction[s] = 1 + rand() % 100;
            }

        population[i] = sol;
    }
}

std::pair<Solution, Solution> DifferentialEvolution::parents()
{
    size_t
            n1 = size_t(rand()) % population.size(),
            n2 = size_t(rand()) % population.size();

    return std::make_pair(population[n1], population[n2]);
}

int DifferentialEvolution::childrenCount() const
{
    return int(population.size());
}

std::pair<Solution, Solution> DifferentialEvolution::crossingover( const std::pair<Solution, Solution> &sols )
{
    auto lessSize = std::min(sols.first.traction.size(), sols.second.traction.size());

    auto newSol = sols;

    for (size_t i = 0; i < lessSize / 3; i++)
    {
        std::swap(newSol.first.brake[i], newSol.second.brake[i]);
        std::swap(newSol.first.traction[i], newSol.second.traction[i]);
    }

    for (size_t i = lessSize * 2 / 3; i < lessSize; i++)
    {
        std::swap(newSol.first.brake[i], newSol.second.brake[i]);
        std::swap(newSol.first.traction[i], newSol.second.traction[i]);
    }

    return newSol;
}

bool DifferentialEvolution::needMutate( const Solution &sol )
{
    mutantShift = (mutantShift + 1) % mutateFrequency;

    return mutantShift != 0;
}

void DifferentialEvolution::mutate( Solution &sol ) const
{

}
