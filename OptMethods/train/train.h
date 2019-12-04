#ifndef TRAIN_H
#define TRAIN_H

#include <vector>
#include "map_table.h"

class Train
{
public:
    struct StaticInfo
    {
        double couplerForceMax; // kN
        double tractionForceMax; // kN
        int wagonCount;
        double wagonLength; // m
    };

    Train( void ) {}

    Train( std::string const &fileName );

    void setForce( int wagonNo, double force );

    void init( std::string const &fileName );

    StaticInfo const & staticInfo( void ) const;

    std::vector<int> const & wagonMass( void ) const;
    std::vector<double> const & wagonForce( void ) const;

    int wagonMass( int wagonNo ) const;
    double wagonForce( int wagonNo ) const;

    int trainLength( void ) const;

private:
    StaticInfo theStaticInfo;
    std::vector<int> theWagonMass;
    std::vector<double> theWagonForce;
};

#endif // TRAIN_H
