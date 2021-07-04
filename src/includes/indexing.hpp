#ifndef INDEXING_HPP
#define INDEXING_HPP

#include "main.hpp"

template<uint8_t K>
struct CombinationIndexer
{
    // 0!.....12! (longest possible combination has 12 values: 12 edges > 8 corners)
    const array<uint32_t, 13> factorial = { 1,1,2,6,24,120,720,5040,40320,362880,3628800,39916800,479001600 };

    // calculate nCm = n! / (m!(n - k)!)
    uint32_t nCm(uint8_t n, uint8_t m) const
    {
        if (n < m) return 0;
        if (n == m) return 1;
        return factorial[n] / (factorial[m] * factorial[n - m]);
    }

    // combinations are always assumed to be in a descending order
    uint32_t getInd(const array<uint8_t, K>& comb) const
    {
        // www.jaapsch.net/puzzles/compindx.htm
        // an edge combination is ranked based on the amount of possible smaller edge combinations
        // because there is no repetition or regard to order, nCk is used assuming the positions
        // permutations are always in a decending order (p = position: p[0]> p[1] > p[2] > p[3])
        // index = p[0]-1C4 + p[1]-1C3 + p[2]-1C2 + p[3]-1C1

        uint32_t index = 0;

        for (uint8_t n = K, m = K; m > 0; --n, --m)
            index += nCm(comb[n - 1] - 1, m);
        return index;
    }
};

#endif