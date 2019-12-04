#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>

#include "solution.h"
#include "brake.h"

Solution::Solution( const Train &train ) : train(train)
{

}

void Solution::setTimeUniformDistribution( int h, int N )
{
    step = h;
    stepsCount = N;
    traction.resize(size_t(N));
    brake.resize(size_t(N));
}

void Solution::output( const std::string &fileName )
{
    std::ofstream ofs(fileName);

    if (!ofs)
        std::cerr << "Couldn't open file " + fileName + " for writing!\n";

    for (size_t i = 0; i < brake.size(); i++)
        ofs << traction[i] << ' ' << brake[i] << "\n";
}

Solution Solution::operator*( double F ) const
{
    Solution newSol = *this;
    for (size_t i = 0; i < brake.size(); i++)
    {
        if (newSol.brake[i] > Brake::NEUTRAL_LEVER)
            newSol.brake[i]--;

        if (newSol.brake[i] <= Brake::NEUTRAL_LEVER)
            newSol.traction[i] = std::min(std::max(0.0, newSol.traction[i] * F), train.staticInfo().tractionForceMax);
    }

    return newSol;
}

Solution Solution::operator+( const Solution &sol ) const
{
    Solution newSol = *this;

    for (size_t i = 0; i < brake.size(); i++)
    {
        newSol.brake[i] = (sol.brake[i] + brake[i]) / 2;
        newSol.traction[i] = (sol.traction[i] + traction[i]) / 2;
    }

    return newSol;
}

Solution Solution::operator-( const Solution &sol ) const
{
    Solution newSol = *this;

    for (size_t i = 0; i < brake.size(); i++)
    {
        newSol.brake[i] = sol.brake[i] - brake[i];
        newSol.traction[i] = sol.traction[i] - traction[i];
    }

    return newSol;
}
