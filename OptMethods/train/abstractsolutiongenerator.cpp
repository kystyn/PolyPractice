#include "abstractsolutiongenerator.h"

void AbstractSolutionGenerator::breeding( int chuildrenCount )
{
    std::vector<Solution> children;
    for (int i = 0; i < chuildrenCount / 2; i++)
    {
        auto curChildren = crossingover(parents());
        children.push_back(curChildren.first);
        children.push_back(curChildren.second);
    }
}

bool AbstractSolutionGenerator::solve( Solution &optSolution )
{
    generatePopulation();
    int chCount = childrenCount();

    while (!finished())
    {
        breeding(chCount);
        for (auto s : population)
            if (needMutate(s))
                mutate(s);
        select();
    }
    return findOptimal(optSolution);
}
