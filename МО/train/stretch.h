#ifndef STRETCH_H
#define STRETCH_H

#include <vector>

class Stretch
{
public:
    struct Sector
    {
        double maxVelocity;
        double angle;
        double length;
    };

    Stretch() {}

    Stretch( std::string const &fileName );

    void init( std::string const &fileName );

    // distance is distance from the beginning of the stretch
    Sector const & getSector( double distance ) const;

private:

    std::vector<Sector> profile;
};

#endif // STRETCH_H
