#include "brake.h"

const double Brake::NEUTRAL_PRESSURE = 500;

Brake::Brake( const std::string &fileName ) :
    prevLeverPos(NEUTRAL_LEVER)
{
    std::ifstream ifs(fileName);
    if (!ifs)
    {
        std::cerr << "Bad file name " << fileName << "\n";
        return;
    }
    ifs >> brakeWavePeriod;

    int posCount;
    ifs >> posCount;
    theBrakeVelocityByLever.init(ifs, posCount);
    theForceByBrakeVelocity.init(ifs);
}

double Brake::brakeVelocityByLever( int pos ) const
{
    return theBrakeVelocityByLever.get(pos);
}

double Brake::forceByBrakeVelocity( double pressure ) const
{
    return theForceByBrakeVelocity.get(pressure);
}

double Brake::forceByLever( int leverPos, int curTime, int wagonNo )
{
    auto curPressure = prevStablePressure +
            ((curTime - brakeStartTime - wagonNo * brakeWavePeriod) > 0) *
            brakeVelocityByLever(leverPos) *
            (curTime - brakeStartTime - wagonNo * brakeWavePeriod);

    if (leverPos != NEUTRAL_LEVER && prevLeverPos == NEUTRAL_LEVER)
    {
        brakeStartTime = curTime;
        prevStablePressure = curPressure;
    }

    if (leverPos == NEUTRAL_LEVER && prevLeverPos != NEUTRAL_LEVER)
    {
        prevStablePressure = curPressure;
    }

    prevLeverPos = leverPos;

    return forceByBrakeVelocity(curPressure);
}
