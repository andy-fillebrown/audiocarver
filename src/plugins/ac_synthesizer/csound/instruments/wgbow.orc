
gi_sine = 0

#include "track-control.aci"

instr $INSTR
#include "instrument-control.aci"
	tigoto end
	if (gi_sine == 0) then
		gi_sine ftgen 0, 0, 128, 10, 1
	endif
	a_out wgbow k_volume, k_cps, 0, 0.127236, 0, 0, gi_sine, 50
	out a_out
end:
endin
