#ifndef SOLUTION_H
#define SOLUTION_H

#include <vector>
#include <string>

#include "train.h"

class Solution
{
public:
    Solution( const Train &train );
    void setTimeUniformDistribution( int h, int N );
    void output( std::string const &fileName );

    Solution operator*( double F ) const;
    Solution operator+( Solution const &sol ) const;
    Solution operator-( Solution const &sol ) const;

    int step, stepsCount;
    // key - time, in secs
    // percentage of max traction
    std::vector<int> traction;
    // brake lever
    std::vector<int> brake;

private:
    const Train &train;
};

#endif // SOLUTION_H
