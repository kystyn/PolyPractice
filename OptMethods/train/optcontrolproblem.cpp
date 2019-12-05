#include <cmath>
#include "optcontrolproblem.h"
#include "concretegenerator.h"

OptControlProblem::OptControlProblem(
        const std::string &brakeFName,
        const std::string &trainFName,
        const std::string &weatherFName,
        const std::string &stretchFName,
        int humidity ) :
    simulator(brakeFName, trainFName, weatherFName, stretchFName, humidity)
{
    srand(uint(time(nullptr)));
}

void OptControlProblem::solve( std::string const &outFName )
{
    std::shared_ptr<AbstractSolutionGenerator> generator;

    auto profile = simulator.stretch().profile();
    double outcomingVelocity = 0;

    std::ofstream ofs(outFName);

    if (!ofs)
        std::cerr << "Bad output file " + outFName << std::endl;

    // last profile element is always fake
    for (size_t i = 0; i < profile.size() - 1; i++)
    {
        int
                left_T0 = 0,
                right_T0 = 3000,
                T0 = right_T0,
                prevSuccessT0 = T0;
        Solution
                prevOptSectoralSol,
                optSectoralSol;

        while (right_T0 - left_T0 > 60)
        {
            T0 = (left_T0 + right_T0) / 2;
            generator = std::make_shared<ConcreteSolutionGenerator>(simulator, outcomingVelocity, i, T0);

            bool res = generator->solve(optSectoralSol);
            if (res)
            {
                prevSuccessT0 = T0;
                prevOptSectoralSol = optSectoralSol;
                left_T0 = T0;
            }
            else
                right_T0 = T0;
        }
        ofs << "STRETCH " << i << ": TIME " << prevSuccessT0 << "\n";
        prevOptSectoralSol.output(ofs);
    }
}
