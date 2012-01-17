
#include "aci/track-control.aci"

instr 2
#include "aci/instrument-control.aci"
    i_cps = cpsmidinn(i_pitch)
    a_out pluck k_volume, k_cps, i_cps, 0, 1
    out a_out
endin
