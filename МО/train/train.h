#ifndef TRAIN_H
#define TRAIN_H

#include <vector>
#include "map_table.h"

class Train
{
public:
    struct StaticInfo
    {
        double couplerForceMax;
        double tractionForceMax;
        int wagonCount;
        int wagonLength;
    };

    Train( void ) {}

    Train( std::string const &fileName );

    void setActualForce( int wagonNo, double force );
    double getActualForce( int wagonNo ) const;

    void init( std::string const &fileName );

    StaticInfo const & staticInfo( void ) const;

private:
//    double couplerForceMax;
//    double tractionForceMax;
//    int wagonCount;
//    int wagonLength;
//    double brakeWavePeriod;
    StaticInfo theStaticInfo;
    std::vector<int> wagonMass;
    std::vector<double> wagonForce;
};

#endif // TRAIN_H
