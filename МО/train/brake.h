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
    double velocityByLever( int pos ) const;
    double forceByBrakePressure( double pressure ) const;
    double forceByLever( int leverPos,
                         int curTime,
                         int wagonNo );

    static const int NEUTRAL_LEVER = 2;
    static const double NEUTRAL_PRESSURE;
private:
    int prevLeverPos;
    // stable == in neutral position
    double prevStablePressure;

    int brakeStartTime;
    double brakeWavePeriod;

    MapTable<int, double>
        theBrakeVelocityByLever;
    MapTable<double, double>
        theForceByBrakePressure;
};

#endif /* __BRAKE_H_ */
