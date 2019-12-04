#ifndef SOLUTION_H
#define SOLUTION_H

#include <vector>
#include <string>

class Solution
{
public:
    Solution( void ) = default;
    void setTimeUniformDistribution( int h, int N );
    void output( std::string const &fileName );
    void output( std::ofstream &ofs );

    Solution operator*( double F ) const;
    Solution operator+( Solution const &sol ) const;
    Solution operator-( Solution const &sol ) const;

    Solution & operator=( Solution const &s )
    {
        traction = std::move(s.traction);
        brake = std::move(s.traction);

        return *this;
    }

    int step, stepsCount;
    // key - time, in secs
    // percentage of max traction
    std::vector<int> traction;
    // brake lever
    std::vector<int> brake;
};

#endif // SOLUTION_H
