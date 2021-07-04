#include "phase2.hpp"

uint32_t Phase_2::getInd(const Cube& c) const
{
    array<uint8_t, 4> E_Comb;

	for (uint8_t i = 0, j = 0; i < 12 && j < 4; ++i)
	{
		if (c.edgePosition[i] == 0 || c.edgePosition[i] == 2
			|| c.edgePosition[i] == 4 || c.edgePosition[i] == 6)
			E_Comb[j++] = i + 1;
	}
	uint32_t E_ind = CombIndex.getInd(E_Comb);	// edge
	uint32_t C_ind = 0;							// corner

	// treats corner orientations as ternay numbers and converts it to decimal
	C_ind += c.cornerOrientation[0] +
        c.cornerOrientation[1] * 3 +
        c.cornerOrientation[2] * 9 +
        c.cornerOrientation[3] * 27 +
        c.cornerOrientation[4] * 81 +
        c.cornerOrientation[5] * 243 +
        c.cornerOrientation[6] * 729;
	// (0..3^7 - 1) * 12C4 + (0..12C4 - 1) = 0..1082564
	return C_ind * 495 + E_ind;
}
