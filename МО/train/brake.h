#ifndef __BRAKE_H_
#define __BRAKE_H_

#include "map_table.h"

// key - brake lever
// value - dP/dt
class Brake
{
public:
    Brake() {}
    Brake( std::string const &fileName );
    double getVelocityByLever( int pos ) const;
    double getForceByBreakPressure( double pressure ) const;
    double getForceByLever( int leverPos,
                            double prevPressure,
                            int elapsedFromBrakeStart,
                            int wagonNo ) const;

private:
    double brakeWavePeriod;
    MapTable<int, double>
        breakVelocityByLever;
    MapTable<double, double>
        forceByBrakePressure;
};

#endif /* __BRAKE_H_ */
