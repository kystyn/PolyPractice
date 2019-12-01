#include <iostream>
#include <fstream>
#include "stretch.h"

std::istream & operator>>( std::istream &iss, Stretch::Sector &s )
{
    iss >> s.maxVelocity;
    if (!iss)
    {
        s.maxVelocity = 0;
        return iss;
    }

    iss >> s.angle >> s.length;

    return iss;
}

Stretch::Stretch( std::string const &fileName )
{
    init(fileName);
}

void Stretch::init( const std::string &fileName )
{
    std::ifstream ifs(fileName);
    if (!ifs)
    {
        std::cerr << "Bad file name " << fileName << "\n";
        return;
    }

    Sector s;
    while (!ifs)
    {
        ifs >> s;
        if (std::abs(s.maxVelocity) < 1e-6)
            return;
        theProfile.push_back(s);
    }
}

const Stretch::Sector & Stretch::sector( double distance ) const
{
    double d = 0;

    for (auto const &s : theProfile)
        if (d + s.length > distance)
            return s;

    return theProfile.back();
}

double Stretch::distanceFromStart( int sectorNo ) const
{
    double dist = 0;
    for (size_t i = 0; i < size_t(sectorNo); i++)
        dist += theProfile[i].length;

    return dist;
}

const std::vector<Stretch::Sector> & Stretch::profile() const
{
    return theProfile;
}
