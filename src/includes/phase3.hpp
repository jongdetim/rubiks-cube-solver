#ifndef PHASE_3
#define PHASE_3

#include "indexing.hpp"
#include "cube.hpp"

struct Phase_3
{
    public:
        uint32_t getInd(const Cube& cube) const;
    private:
        CombinationIndexer<4> CombIndex;
};

#endif