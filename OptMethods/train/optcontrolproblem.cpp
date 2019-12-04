#include <cmath>
#include "optcontrolproblem.h"

OptControlProblem::OptControlProblem() :
    curState({0, 2, 0}),
    prevState({0, 2, 0})
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
    curState({0, 2, 0}),
    prevState({0, 2, 0})
{
    mu = weather.getFrictionByHumidity(humidity);
}

void OptControlProblem::evaluateForces( double distance )
{
    static const double gravityConst = 9.81;
    auto trainInfo = train.staticInfo();
    auto wagonMass = train.wagonMass();

    for (int i = 0; i < trainInfo.wagonCount; i++)
    {
        auto curMass = wagonMass[size_t(i)];
        auto curAngle = stretch.sector(distance - trainInfo.wagonLength * i).angle;
        auto
                tractionForce = curState.tractionPercent * trainInfo.tractionForceMax / 100.0, //kN
                frictionForce = - mu * curMass * cos(curAngle), // kN = tonn * m/s^2
                brakeForce = brake.forceByLever(curState.brakeLever, curState.time, i),
                gravityForce = - curMass * gravityConst * sin(curAngle);


        train.setForce(i, tractionForce + frictionForce + brakeForce + gravityForce);
    }
}

double OptControlProblem::evaluateVelocity( double prevVelocity, int timeElapsed ) const
{
    // Left rect method
    return prevVelocity + timeElapsed * train.wagonForce(0) / train.wagonForce(0);
}

double OptControlProblem::evaluateDistance( double prevDistance, double velocity, int timeElapsed ) const
{
    return prevDistance + velocity * timeElapsed;
}

bool OptControlProblem::simulateSector(
        double incomingVelocity,
        int sectorNo,
        const Solution &sectorSolution )
{
    static const double TOLLERANCE_PRESSURE = 0.3;
    static const double TOLLERANCE_VELOCITY = 5;
    static const double TOLLERANCE_DISTANCE = 1;

    double distFromStrBeg = stretch.distanceFromStart(sectorNo);
    double distance = 0;
    double velocity = incomingVelocity;
    int step = sectorSolution.step;
    double deltaPressure = 0;

    for (int stepNo = 0; stepNo < sectorSolution.stepsCount; stepNo++)
    {
        // kinematics
        evaluateForces(distFromStrBeg + distance);
        velocity = evaluateVelocity(velocity, step);
        distance = evaluateDistance(distance, velocity, step);

        // brake
        auto brakeVel = brake.brakeVelocityByLever(sectorSolution.brake[size_t(stepNo)]);
        deltaPressure += brakeVel * step;

        if (!checkForces())
            return false;

        if (sectorSolution.traction[size_t(stepNo)] * brakeVel > 0)
            return false;

        if (sectorSolution.traction[size_t(stepNo)] < train.staticInfo().tractionForceMax)
            return false;
    }

    if (std::abs(deltaPressure) > TOLLERANCE_PRESSURE)
        return false;

    if (std::abs(velocity - stretch.profile()[size_t(sectorNo + 1)].maxVelocity) >
            TOLLERANCE_VELOCITY)
        return false;

    if (std::abs(distance - stretch.profile()[size_t(sectorNo)].length) >
            TOLLERANCE_DISTANCE)
        return false;

    return true;
}

bool OptControlProblem::checkForces() const
{
    auto trainForce = train.wagonForce();

    auto info = train.staticInfo();

    for (size_t i = 1; i < size_t(info.wagonCount); i++)
        if (std::abs(trainForce[i] - trainForce[i - 1]) > info.couplerForceMax)
            return false;

    return true;
}
