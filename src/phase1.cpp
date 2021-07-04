#include "phase1.hpp"

uint32_t Phase_1::getInd(const Cube& c) const
{
    // Generates 0..2047
	return
       c.edgeOrientation[0]  +
       c.edgeOrientation[1]  * 2 +
       c.edgeOrientation[2]  * 4 +
       c.edgeOrientation[3]  * 8 +
       c.edgeOrientation[4]  * 16 +
       c.edgeOrientation[5]  * 32 +
       c.edgeOrientation[6]  * 64 +
       c.edgeOrientation[7]  * 128 +
       c.edgeOrientation[8]  * 256 +
       c.edgeOrientation[9]  * 512 +
       c.edgeOrientation[10] * 1024;
}
