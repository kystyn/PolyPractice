#include <cmath>
#include "optcontrolproblem.h"

OptControlProblem::OptControlProblem(
        const std::string &brakeFName,
        const std::string &trainFName,
        const std::string &weatherFName,
        const std::string &stretchFName,
        int humidity ) : simulator(brakeFName, trainFName, weatherFName, stretchFName, humidity)
{
}
