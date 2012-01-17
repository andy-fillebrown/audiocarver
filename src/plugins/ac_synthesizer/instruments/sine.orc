
#include "aci/track-control.aci"

instr 2
#include "aci/instrument-control.aci"
    i_sine ftgenonce 0, 0, 16384, 10, 1
    a_out poscil k_volume, k_cps, i_sine
    out a_out
endin
