#ifndef SOLUTION_H
#define SOLUTION_H

#include <vector>
#include <string>

class Solution
{
public:
    void setTimeUniformDistribution( int h, int N );
    void output( std::string const &fileName );

    int step, stepsCount;
    // key - time, in secs
    // percentage of max traction
    std::vector<int> traction;
    // brake lever
    std::vector<int> brake;
};

#endif // SOLUTION_H
