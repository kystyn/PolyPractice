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

void Train::setForce( int wagonNo, double force )
{
    theWagonForce[size_t(wagonNo)] = force;
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
    // couplerForceMax, kN
    // tractionForceMax, kN
    // wagonLength, m
    // wagonsMassTable, tonn

    ifs >> theStaticInfo;

    // key - from which wagon mass is value
    MapTable<int, int> massDistr(ifs);

    std::map<int, int> table = massDistr.getTable();

    theStaticInfo.wagonCount = (--table.end())->first;

    auto end = --table.end();

    theWagonMass.clear();
    theWagonMass.resize(size_t(end->first));

    int curWagon = 0;
    for (auto i = table.begin(); i != end;)
    {
        auto
                cur = i,
                next = ++i;
        for (int j = 0; j < next->first - cur->first; j++)
            theWagonMass[size_t(curWagon++)] = cur->second;
    }
    theWagonMass.back() = theWagonMass[theWagonMass.size() - 2];
}

const Train::StaticInfo & Train::staticInfo() const
{
    return theStaticInfo;
}

const std::vector<int> & Train::wagonMass() const
{
    return theWagonMass;
}

const std::vector<double> & Train::wagonForce() const
{
    return theWagonForce;
}

int Train::wagonMass( int wagonNo ) const
{
    return theWagonMass[size_t(wagonNo)];
}

double Train::wagonForce( int wagonNo ) const
{
    return theWagonForce[size_t(wagonNo)];
}

int Train::trainLength() const
{
    return staticInfo().wagonCount * staticInfo().wagonLength;
}
