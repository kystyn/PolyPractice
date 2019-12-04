#ifndef OPTCONTROLPROBLEM_H
#define OPTCONTROLPROBLEM_H

#include <memory>
#include "simulator.h"
#include "abstractsolutiongenerator.h"

class OptControlProblem
{
public:
    OptControlProblem() = default;

    OptControlProblem( std::string const & brakeFName,
                       std::string const & trainFName,
                       std::string const & weatherFName,
                       std::string const & stretchFName,
                       int humidity );

    void solve();//bin search
private:
    Simulator simulator;
    std::shared_ptr<AbstractSolutionGenerator> generator;
};

#endif // OPTCONTROLPROBLEM_H
