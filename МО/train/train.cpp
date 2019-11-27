#include "train.h"

void Train::init( const std::string &fileName )
{
    std::ifstream ifs(fileName);

    if (!ifs)
    {
        std::cerr << "Bad file name " << fileName << "\n";
        return;
    }

    // TRAIN:
    // couplerForceMax
    // tractionForceMax
    // brakeWavePeriod
    // wagonLength
    // wagonCount
    // wagonsMassTable

    ifs >> couplerForceMax >> tractionForceMax >>
           brakeWavePeriod >> wagonLength >>
           wagonCount;

    // key - from which wagon mass is value
    MapTable<int, int> massDistr(ifs, wagonCount);

    std::map<int, int> table = massDistr.getTable();

    table[wagonCount + 1] = 0;

    auto end = --table.end();

    wagonMass.clear();

    int curWagon = 0;
    for (auto i = table.begin(); i != end;)
    {
        auto
                cur = i,
                next = ++i;
        for (int j = 0; j < next->first - cur->first; j++)
            wagonMass[size_t(curWagon++)] = cur->second;
    }
}
