
#include "aci/track-control.aci"

instr 2
#include "aci/instrument-control.aci"
    gi_sine ftgenonce 0, 0, 128, 10, 1
    a_out wgbow k_volume, k_cps, 0, 0.127236, 0, 0, i_sine, 50
    out a_out
endin
