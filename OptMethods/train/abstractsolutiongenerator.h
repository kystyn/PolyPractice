#ifndef SOLUTIONGENERATOR_H
#define SOLUTIONGENERATOR_H

#include "solution.h"

class AbstractSolutionGenerator
{
public:
    AbstractSolutionGenerator() = default;

    bool solve( Solution &optSolution );
protected:
    virtual void generatePopulation() = 0;
    virtual std::pair<Solution, Solution> parents() = 0;
    virtual int childrenCount( void ) const = 0;
    // crossingover creates two new children
    virtual std::pair<Solution, Solution> crossingover( std::pair<Solution, Solution> const &sols ) = 0;
    virtual bool needMutate( Solution const &sol ) = 0;
    // solution mutates in itself
    virtual void mutate( Solution &sol ) const = 0;
    virtual void select( void ) = 0;
    // returns true if has optimal solution. false otherwise
    virtual bool findOptimal( Solution &optSolution ) const = 0;
    // returns true if finished.
    // should also consider case when do not have convergenct
    virtual bool finished() const = 0;

    std::vector<Solution> population;

private:
    void breeding( int chuildrenCount );
};

#endif // SOLUTIONGENERATOR_H
