#ifndef __BRAKE_H_
#define __BRAKE_H_

#include "map_table.h"

// key - brake lever
// value - dP/dt
class Brake
{
public:
    Brake( std::string const &fileName );
    double getVelocityByLever( int pos ) const;
    double getForceByVelocity( double pos ) const;
    double getForceByLever( int pos ) const;

private:
    MapTable<int, double>
        breakVelocityByLever;
    MapTable<double, double>
        forceByBreakVelocity;
};

#endif /* __BRAKE_H_ */
