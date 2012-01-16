
gi_sine = 0

#include "track-control.aci"

instr $INSTR
#include "instrument-control.aci"
	tigoto end
	if (gi_sine == 0) then
		gi_sine ftgen 0, 0, 16384, 10, 1
	endif
	a_out poscil k_volume, k_cps, gi_sine
	out a_out
end:
endin
