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

    // ATTENTION
    // remember that last sector is sector of new stretch
    // it is mentioned just for out velocity check
    // don't consider other conditions

    Stretch() {}

    Stretch( std::string const &fileName );

    void init( std::string const &fileName );

    // distance is distance from the beginning of the stretch
    Sector const & sector( double distance ) const;
    double distanceFromStart( int sectorNo ) const;
    std::vector<Sector> const & profile( void ) const;

private:

    std::vector<Sector> theProfile;
};

#endif // STRETCH_H
