#ifndef __MAP_TABLE_H_
#define __MAP_TABLE_H_

#include <fstream>
#include <map>
#include <string>
#include <iostream>

template<typename KeyT, typename ValT>
class MapTable
{
public:
    MapTable() {}

    MapTable( std::string const &fileName )
    {
        init(fileName);
    }

    MapTable( std::ifstream &ifs, int count = 0 )
    {
        init(ifs, count);
    }

    void init( std::ifstream &ifs, int count = 0 )
    {
        KeyT key;
        ValT val;
        int i = 0;

        while (count != 0 ? i < count : !ifs)
        {
            ifs >> key;
            if (!ifs)
                break;
            ifs >> val;
            table[key] = val;
            i++;
        }
    }

    void init( std::string const &fileName )
    {
        std::ifstream ifs(fileName);
        if (!ifs)
        {
            std::cerr << "Bad file name " << fileName << "\n";
            return;
        }

        init(ifs);
    }

    ValT get( KeyT key ) const
    {
        auto it = table.find(key);
        if (it != table.end())
            return table.at(key);
        return ValT();
    }

    std::map<KeyT, ValT> const & getTable( void ) const
    {
        return table;
    }

private:
    std::map<KeyT, ValT> table;
};

#endif /* __MAP_TABLE_H_ */
