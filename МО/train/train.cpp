#include "train.h"

std::istream & operator>>( std::istream &is, Train::StaticInfo &i )
{
    is >> i.couplerForceMax >> i.tractionForceMax >> i.wagonLength;
    return is;
}

Train::Train( const std::string &fileName )
{
    init(fileName);
}

void Train::setActualForce( int wagonNo, double force )
{
    wagonForce[size_t(wagonNo)] = force;
}

double Train::getActualForce( int wagonNo ) const
{
    return wagonForce.at(size_t(wagonNo));
}

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
    // wagonsMassTable

    ifs >> theStaticInfo;

    // key - from which wagon mass is value
    MapTable<int, int> massDistr(ifs);

    std::map<int, int> table = massDistr.getTable();
    theStaticInfo.wagonCount = int(table.size());

    table[theStaticInfo.wagonCount + 1] = 0;

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

const Train::StaticInfo & Train::staticInfo() const
{
    return theStaticInfo;
}
