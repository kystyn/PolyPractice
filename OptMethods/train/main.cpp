#include <iostream>

#include "optcontrolproblem.h"

using namespace std;

int main( void )
{
    OptControlProblem p("../train/dat/brake.dat",
                        "../train/dat/train.dat",
                        "../train/dat/weather.dat",
                        "../train/dat/stretch.dat",
                        50);

    p.solve("../train/results/result.txt");

    cout << "Hello World!" << endl;
    return 0;
}
