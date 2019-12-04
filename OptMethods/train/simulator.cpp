#include <cmath>

#include "simulator.h"

Simulator::Simulator() :
    curState({0, Brake::NEUTRAL_LEVER, 0}),
    prevState({0, Brake::NEUTRAL_LEVER, 0})
{

}

Simulator::Simulator( const std::string &brakeFName,
                      const std::string &trainFName,
                      const std::string &weatherFName,
                      const std::string &stretchFName,
                      int humidity ) :
    brake(brakeFName),
    theTrain(trainFName),
    theStretch(stretchFName),
    weather(weatherFName),
    curState({0, Brake::NEUTRAL_LEVER, 0}),
    prevState({0, Brake::NEUTRAL_LEVER, 0})
{
    mu = weather.getFrictionByHumidity(humidity);
}

void Simulator::evaluateForces( double distance )
{
    static const double gravityConst = 9.81;
    auto trainInfo = theTrain.staticInfo();
    auto wagonMass = theTrain.wagonMass();

    for (int i = 0; i < trainInfo.wagonCount; i++)
    {
        auto curMass = wagonMass[size_t(i)];
        auto curAngle = theStretch.sector(distance - trainInfo.wagonLength * i).angle;
        auto
                tractionForce = curState.tractionPercent * trainInfo.tractionForceMax / 100.0, //kN
                frictionForce = - mu * curMass * cos(curAngle), // kN = tonn * m/s^2
                brakeForce = brake.forceByLever(curState.brakeLever, curState.time, i),
                gravityForce = - curMass * gravityConst * sin(curAngle);


        theTrain.setForce(i, tractionForce + frictionForce + brakeForce + gravityForce);
    }
}

double Simulator::evaluateVelocity( double prevVelocity, int timeElapsed ) const
{
    // Left rect method
    return prevVelocity + timeElapsed * theTrain.wagonForce(0) / theTrain.wagonForce(0);
}

double Simulator::evaluateDistance( double prevDistance, double velocity, int timeElapsed ) const
{
    return prevDistance + velocity * timeElapsed;
}

bool Simulator::simulateSector(
        double incomingVelocity,
        int sectorNo,
        const Solution &sectorSolution )
{
    static const double TOLLERANCE_PRESSURE = 0.3;
    static const double TOLLERANCE_VELOCITY = 5;
    static const double TOLLERANCE_DISTANCE = 1;

    double distFromStrBeg = theStretch.distanceFromStart(sectorNo);
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

        if (sectorSolution.traction[size_t(stepNo)] < theTrain.staticInfo().tractionForceMax)
            return false;
    }

    if (std::abs(deltaPressure) > TOLLERANCE_PRESSURE)
        return false;

    if (std::abs(velocity - theStretch.profile()[size_t(sectorNo + 1)].maxVelocity) >
            TOLLERANCE_VELOCITY)
        return false;

    if (std::abs(distance - theStretch.profile()[size_t(sectorNo)].length) >
            TOLLERANCE_DISTANCE)
        return false;

    return true;
}

const Train &Simulator::train() const
{
    return theTrain;
}

const Stretch &Simulator::stretch() const
{
    return theStretch;
}

bool Simulator::checkForces() const
{
    auto trainForce = theTrain.wagonForce();

    auto info = theTrain.staticInfo();

    for (size_t i = 1; i < size_t(info.wagonCount); i++)
        if (std::abs(trainForce[i] - trainForce[i - 1]) > info.couplerForceMax)
            return false;

    return true;
}

