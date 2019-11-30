#include <string>
#include <fstream>
#include <iostream>

#include "solution.h"

Solution::Solution()
{

}

void Solution::setTimeUniformDistribution( int h, int N )
{
    this->h = h;
    traction.resize(size_t(N));
    brake.resize(size_t(N));
}

void Solution::output( const std::string &fileName )
{
    std::ofstream ofs(fileName);

    if (!ofs)
        std::cerr << "Couldn't open file " + fileName + " for writing!\n";

    for (size_t i = 0; i < brake.size(); i++)
        ofs << traction[i] << brake[i] << "\n";
}
