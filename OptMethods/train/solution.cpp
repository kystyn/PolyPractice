#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>

#include "solution.h"
#include "brake.h"

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
    output(ofs);
}

void Solution::output( std::ofstream &ofs )
{
    for (size_t i = 0; i < brake.size(); i++)
        ofs << traction[i] << ' ' << brake[i] << "\n";
}


Solution & Solution::operator=( const Solution &s )
{
    step = s.step;
    stepsCount = s.stepsCount;
    traction = s.traction;
    brake = s.brake;

    for (auto &x : traction)
        x = std::max(0, std::min(x, 100));

    for (auto &x : brake)
        x = std::max(1, std::min(x, 5));

    return *this;
}

