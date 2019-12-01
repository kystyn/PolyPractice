#include "brake.h"

const double Brake::NEUTRAL_PRESSURE = 4.5;

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
}

double Brake::velocityByLever( int pos ) const
{
    return theBrakeVelocityByLever.get(pos);
}

double Brake::forceByBrakePressure( double pressure ) const
{
    auto table = theBrakeVelocityByLever.getTable();
    std::pair<double, double> prev, next = {0, 0};

    for (auto t : table)
    {
        if (t.first < pressure)
            prev = t;
        else
        {
            next = t;
            break;
        }
    }

    if (std::abs(next.first) < 1e-6)
        return prev.second;

    auto l = (pressure - prev.first) / (next.first - prev.first);

    return (1 - l) * prev.second + l * prev.second;
}

double Brake::forceByLever( int leverPos, int curTime, int wagonNo )
{
    auto curPressure = prevStablePressure +
            ((curTime - brakeStartTime - wagonNo * brakeWavePeriod) > 0) *
            velocityByLever(leverPos) *
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

    return forceByBrakePressure(curPressure);
}
