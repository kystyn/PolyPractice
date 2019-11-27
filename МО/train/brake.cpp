#include "brake.h"

Brake::Brake(const std::string &fileName)
{
    std::ifstream ifs(fileName);
    if (!ifs)
    {
        std::cerr << "Bad file name " << fileName << "\n";
        return;
    }

    int posCount;
    ifs >> posCount;
    breakVelocityByLever.init(ifs, posCount);
}

double Brake::getVelocityByLever(int pos) const
{
    return breakVelocityByLever.get(pos);
}

double Brake::getForceByVelocity(double pos) const
{
    return forceByBreakVelocity.get(pos);
}

double Brake::getForceByLever(int pos) const
{
    return getForceByVelocity(getVelocityByLever(pos));
}
