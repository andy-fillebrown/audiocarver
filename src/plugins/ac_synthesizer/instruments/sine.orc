
gi_sine = 0

#include "aci/track-control.aci"

instr 2
#include "aci/instrument-control.aci"
	if (0 == gi_sine) then
		gi_sine ftgen 0, 0, 16384, 10, 1
	endif
    a_out poscil k_volume, k_cps, gi_sine
    out a_out
endin
