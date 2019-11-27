#ifndef WEATHER_H
#define WEATHER_H

#include "map_table.h"

// int - percentage humidity
// double - mu
class Weather : MapTable<int, double>
{
public:
    using MapTable<int, double>::MapTable;

    double getFrictionByHumidity( int hum ) const
    {
        return get(hum);
    }
};

#endif // WEATHER_H
