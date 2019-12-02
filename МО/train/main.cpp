#include <iostream>

#include "optcontrolproblem.h"

using namespace std;

int main( void )
{
    OptControlProblem p("dat/brake.dat",
                        "dat/train.dat",
                        "dat/weather.dat",
                        "dat/stretch.dat",
                        50);
    cout << "Hello World!" << endl;
    return 0;
}
