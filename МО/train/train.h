#ifndef TRAIN_H
#define TRAIN_H

#include <vector>
#include "map_table.h"

class Train
{
public:
    Train( void ) {}

    void init( std::string const &fileName );

private:
    double couplerForceMax;
    double tractionForceMax;
    int wagonCount;
    int wagonLength;
    double brakeWavePeriod;
    std::vector<int> wagonMass;
};

#endif // TRAIN_H
