
#include "track-control.aci"

instr $INSTR
#include "instrument-control.aci"
	tigoto end
	i_cps = cpsmidinn(i_pitch)
	a_out pluck k_volume, k_cps, i_cps, 0, 1
	out a_out
end:
endin
