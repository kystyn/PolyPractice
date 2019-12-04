#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "brake.h"
#include "stretch.h"
#include "train.h"
#include "weather.h"
#include "solution.h"

class Simulator
{
public:
    Simulator();
    Simulator( const std::string &brakeFName,
              const std::string &trainFName,
              const std::string &weatherFName,
              const std::string &stretchFName,
              int humidity );

    bool simulateSector(
            double incomingVelocity,
            int sectorNo,
            Solution const &sectorSolution,
            double &outcomingVelocity );

    Train const & train() const;
    Stretch const & stretch() const;

private:
    // distance from the stretch beginning
    void evaluateForces( double distance );
    double evaluateVelocity( double prevVelocity, int timeElapsed ) const;
    double evaluateDistance( double prevDistance, double velocity, int timeElapsed ) const;
    bool checkForces( void ) const;

    Brake brake;
    Train theTrain;
    Stretch theStretch;
    Weather weather;

    double mu;

    struct ControlState
    {
        // time in secs
        int
            tractionPercent,
            brakeLever,
            time;
    };

    ControlState
        curState,
        prevState;
};

#endif // SIMULATOR_H
