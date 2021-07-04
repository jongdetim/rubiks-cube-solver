#ifndef PHASE_2
#define PHASE_2

#include "indexing.hpp"
#include "cube.hpp"

struct Phase_2
{
    public:
        uint32_t getInd(const Cube& cube) const;
    private:
        CombinationIndexer<4> CombIndex;
};

#endif