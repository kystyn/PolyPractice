#ifndef OPTCONTROLPROBLEM_H
#define OPTCONTROLPROBLEM_H

#include "brake.h"
#include "stretch.h"
#include "train.h"
#include "weather.h"
#include "solution.h"

class OptControlProblem
{
public:
    OptControlProblem();

    OptControlProblem( std::string const & brakeFName,
                       std::string const & trainFName,
                       std::string const & weatherFName,
                       std::string const & stretchFName,
                       int humidity);

    bool simulateSector(
            double incomingVelocity,
            int sectorNo,
            Solution const &sectorSolution );

private:
    // distance from the stretch beginning
    void evaluateForces( double distance );
    double evaluateVelocity( double prevVelocity, int timeElapsed ) const;
    double evaluateDistance( double prevDistance, double velocity, int timeElapsed ) const;
    bool checkForces( void ) const;

    struct DynamicState
    {
        std::vector<double>
            &force;
        double velocity;
    };

    struct ControlState
    {
        // time in secs
        int
            tractionPercent,
            brakeLever,
            time;
    };

    Brake brake;
    Train train;
    Stretch stretch;
    Weather weather;
    Solution stretchSolution;

    double mu;

    ControlState
        curState,
        prevState;
};

#endif // OPTCONTROLPROBLEM_H
