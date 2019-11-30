#include "brake.h"

Brake::Brake(const std::string &fileName)
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
    breakVelocityByLever.init(ifs, posCount);
}

double Brake::getVelocityByLever(int pos) const
{
    return breakVelocityByLever.get(pos);
}

double Brake::getForceByBreakPressure( double pressure ) const
{
    auto table = forceByBrakePressure.getTable();
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

double Brake::getForceByLever( int leverPos,
              double prevPressure,
              int elapsedFromBrakeStart,
              int wagonNo ) const
{
    return getForceByBreakPressure(
                prevPressure +
                ((elapsedFromBrakeStart - wagonNo * brakeWavePeriod) > 0) *
                getVelocityByLever(leverPos) *
                (elapsedFromBrakeStart - wagonNo * brakeWavePeriod));
}
