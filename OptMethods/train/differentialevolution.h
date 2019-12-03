#ifndef DIFFERENTIALEVOLUTION_H
#define DIFFERENTIALEVOLUTION_H

#include "abstractsolutiongenerator.h"

class DifferentialEvolution : public AbstractSolutionGenerator
{
public:
    DifferentialEvolution() = default;
    void generatePopulation() override;
    std::pair<Solution, Solution> parents() override;
    int childrenCount( void ) const override;
    // crossingover creates two new children
    std::pair<Solution, Solution> crossingover( std::pair<Solution, Solution> const &sols ) override;
    bool needMutate( Solution const &sol ) const override;
    // solution mutates in itself
    void mutate( Solution &sol ) const override;
    void select( void ) override;
    // returns true if has optimal solution. false otherwise
    bool findOptimal( Solution &optSolution ) const override;
    // returns true if finished.
    // should also consider case when do not have convergenct
    bool finished() const override;
};

#endif // DIFFERENTIALEVOLUTION_H
