
gi_sine = 0

#include "aci/track-control.aci"

instr 2
#include "aci/instrument-control.aci"
    if (0 == gi_sine) then
        gi_sine ftgen 0, 0, 16384, 10, 1
    endif
    i_half_duration = p3 / 2
    k_current_time timeinsts
    k_volume_envelope init 0
    if (k_current_time < i_half_duration) then
        k_volume_envelope = k_current_time / i_half_duration
    else
        k_volume_envelope = 1 - ((k_current_time - i_half_duration) / i_half_duration)
    endif
    a_out poscil k_volume * k_volume_envelope, k_cps, gi_sine
    out a_out
endin
