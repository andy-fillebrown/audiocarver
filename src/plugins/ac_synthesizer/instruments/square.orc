
#include "aci/track-control.aci"

instr 2
#include "aci/instrument-control.aci"
    a_out vco2 k_volume, k_cps, 10
    out a_out
endin
