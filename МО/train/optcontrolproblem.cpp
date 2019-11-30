#include "optcontrolproblem.h"

OptControlProblem::OptControlProblem() :
    curTraction(0),
    curBrakeLever(2),
    isBrakeWaveDistributing(false),
    currentTime(0)
{

}

OptControlProblem::OptControlProblem( const std::string &brakeFName,
                                      const std::string &trainFName,
                                      const std::string &weatherFName,
                                      const std::string &stretchFName,
                                      int humidity ) :
    brake(brakeFName),
    train(trainFName),
    stretch(stretchFName),
    weather(weatherFName),
    curTraction(0),
    curBrakeLever(2),
    isBrakeWaveDistributing(false),
    currentTime(0)
{
    mu = weather.getFrictionByHumidity(humidity);
}

void OptControlProblem::evaluateForces( double distance )
{
}
