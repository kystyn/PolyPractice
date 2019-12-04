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
    double brakeVelocityByLever( int pos ) const;
    double forceByBrakeVelocity( double pressure ) const;
    double forceByLever( int leverPos,
                         int curTime,
                         int wagonNo );

    static const int NEUTRAL_LEVER = 2;
    static const int STAFF_LEVE = 5;
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
        theForceByBrakeVelocity;
};

#endif /* __BRAKE_H_ */
