
#define START_VOLUME   #0.000#
#define ATTACK_TIME    #0.005#
#define ATTACK_VOLUME  #1.000#
#define DECAY_TIME     #0.000#
#define SUSTAIN_VOLUME #1.000#
#define RELEASE_TIME   #0.005#
#define END_VOLUME     #0.000#

gi_sine = 0

#include "aci/track-control.aci"

instr 2
#include "aci/instrument-control.aci"
#include "aci/volume-envelope.aci"
    if (0 == gi_sine) then
        gi_sine ftgen 0, 0, 128, 10, 1
    endif
    a_out wgbow 0.6 * k_volume, k_cps, 0, 0.127236, 0, 0, gi_sine, 50
    out a_out
endin
