#include <algorithm>
#include <cmath>
#include "concretegenerator.h"
#include "simulator.h"


ConcreteSolutionGenerator::ConcreteSolutionGenerator(
        Simulator &simulator, double incomingVelocity,
        int sectorNo, int passTime ) :
    iterationsCount(0),
    passTime(passTime),
    simulator(simulator),
    train(simulator.train()),
    mutantShift(0),
    incomingVelocity(incomingVelocity),
    sectorNo(sectorNo),
    sector(simulator.stretch().profile()[size_t(sectorNo)])
{
}

void ConcreteSolutionGenerator::generatePopulation()
{
    population.resize(populationSize);

    for (size_t i = 0; i < populationSize; i++)
    {
        // m / s
        int stepsCount = passTime / step + 1;
        population[i].setTimeUniformDistribution(step, stepsCount);

        population[i].traction.resize(size_t(stepsCount));
        population[i].brake.resize(size_t(stepsCount));

        population[i].stepsCount = stepsCount;
        population[i].step = step;

        for (size_t s = 0; s < size_t(stepsCount);)
            if (rand() % 2)
                // -1 cause last position is emergency
                for (int j = 0;
                     s < size_t(stepsCount) &&
                     j < std::max(int(simulator.brake().brakeWavePeriod() * simulator.train().staticInfo().wagonCount) / step, stepsCount / 30);
                     j++)
                {
                    population[i].brake[s] = 1 + rand() % (simulator.brake().leverPositions() - 1);
                    population[i].traction[s++] = 0;
                }
            else
                for (int j = 0;
                     s < size_t(stepsCount) &&
                     j < std::max(int(simulator.brake().brakeWavePeriod() * simulator.train().staticInfo().wagonCount) / step, stepsCount / 30);
                     j++)
                {
                    population[i].brake[s] = 0;
                    population[i].traction[s++] = 1 + rand() % 100;
                }
    }
}

std::pair<Solution, Solution> ConcreteSolutionGenerator::parents()
{
    size_t
            n1 = size_t(rand()) % population.size(),
            n2 = size_t(rand()) % population.size();

    return std::make_pair(population[n1], population[n2]);
}

int ConcreteSolutionGenerator::childrenCount()
{
    return int(population.size());
}

std::pair<Solution, Solution> ConcreteSolutionGenerator::crossingover( const std::pair<Solution, Solution> &sols )
{
    auto lessSize = std::min(sols.first.traction.size(), sols.second.traction.size());

    auto newSol = sols;

    size_t
            s1 = size_t(rand()) % lessSize,
            s2 = size_t(rand()) % lessSize;

    for (size_t i = 0; i < std::min(s1, s2)/*lessSize / 3*/; i++)
    {
        std::swap(newSol.first.brake[i], newSol.second.brake[i]);
        std::swap(newSol.first.traction[i], newSol.second.traction[i]);
    }

    for (size_t i = std::max(s1, s2)/*2 * lessSize / 3*/; i < lessSize; i++)
    {
        std::swap(newSol.first.brake[i], newSol.second.brake[i]);
        std::swap(newSol.first.traction[i], newSol.second.traction[i]);
    }

    return newSol;
}

bool ConcreteSolutionGenerator::needMutate( const Solution & )
{
    mutantShift = (mutantShift + 1) % mutateFrequency;

    return mutantShift == 0;
}

void ConcreteSolutionGenerator::mutate( Solution &sol )
{
    int position = rand() % int(sol.traction.size());
    bool isTraction = (sol.traction[size_t(position)] != 0);
    auto startPos = position;
    for (; startPos >= 0; startPos--)
        if ((isTraction && sol.traction[size_t(startPos)] == 0) ||
            (!isTraction && sol.traction[size_t(startPos)] != 0))
        {
            startPos++;
            break;
        }

    for (; (sol.traction[size_t(startPos)] != 0) == isTraction &&
           startPos < sol.stepsCount; startPos++)
    {
        sol.brake[size_t(startPos)] = isTraction * (1 + rand() % (simulator.brake().leverPositions() - 1));
        sol.traction[size_t(startPos)] = !isTraction * (1 + rand() % 100);
    }
}

void ConcreteSolutionGenerator::select()
{
    int selectionSteps = populationSize * 2;
    int curSteps = 0;
    // Clever select
    while (populationSize > population.size() * 3 / 2 && curSteps++ < selectionSteps)
    {
        size_t i = size_t(rand()) % population.size() - 1;
        double vel;
        while (simulator.simulateSector(incomingVelocity, sectorNo, population[(++i )], vel))
            ;
        population.erase(population.begin() + int(i % population.size()));
    }

    // Random select
    while (populationSize > population.size())
        population.erase(population.begin() + rand() % int(population.size()));
}

bool ConcreteSolutionGenerator::findOptimal( Solution &optSolution )
{
    double vel;
    for (auto &sol : population)
        if (simulator.simulateSector(incomingVelocity, sectorNo, sol, vel))
        {
            optSolution = sol;
            return true;
        }

    return false;
}

bool ConcreteSolutionGenerator::finished()
{
    Solution s;
    if (iterationsCount++ >= maxIterCount)
        return false;
    return findOptimal(s);
}
