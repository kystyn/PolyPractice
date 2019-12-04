#ifndef DIFFERENTIALEVOLUTION_H
#define DIFFERENTIALEVOLUTION_H

#include "abstractsolutiongenerator.h"
#include "simulator.h"

class Train;
class OptControlProblem;

class DifferentialEvolution : public AbstractSolutionGenerator
{
public:
    DifferentialEvolution( Simulator &simulator,
                           double incomingVelocity,
                           int sectorNo,
                           int passTime );

    void generatePopulation() override;
    std::pair<Solution, Solution> parents() override;
    int childrenCount( void ) override;
    // crossingover creates two new children
    std::pair<Solution, Solution> crossingover( std::pair<Solution, Solution> const &sols ) override;
    bool needMutate( Solution const &sol ) override;
    // solution mutates in itself
    void mutate( Solution &sol ) override;
    void select( void ) override;
    // returns true if has optimal solution. false otherwise
    bool findOptimal( Solution &optSolution ) override;
    // returns true if finished.
    // should also consider case when do not have convergenct
    bool finished() override;

private:
    int iterationsCount;
    int passTime;

    Simulator &simulator;
    Train const &train;
    int mutantShift;
    double incomingVelocity;
    int sectorNo;
    Stretch::Sector sector;   
    static const int populationSize = 2000;
    static const int step = 20;
    static const int mutateFrequency = populationSize / 10;
    static const int maxIterCount = 100000;
};

#endif // DIFFERENTIALEVOLUTION_H
