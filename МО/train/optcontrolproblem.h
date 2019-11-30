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

    // distance from the stretch beginning
    void evaluateForces( double distance );

private:
    Brake brake;
    Train train;
    Stretch stretch;
    Weather weather;
    Solution solution;

    double mu;

    int
        curTraction,
        curBrakeLever;
    bool isBrakeWaveDistributing;

    int brakeStartedTime;
    int currentTime;
};

#endif // OPTCONTROLPROBLEM_H
