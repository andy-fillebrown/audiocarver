
#include "track-control.aci"

instr 2
#include "instrument-control.aci"
    tigoto end
    a_out vco2 k_volume, k_cps, 8
    out a_out
end:
endin
