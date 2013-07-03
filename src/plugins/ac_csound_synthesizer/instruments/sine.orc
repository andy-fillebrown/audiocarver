
#define START_VOLUME   #0.000#
#define ATTACK_TIME    #0.005#
#define ATTACK_VOLUME  #1.000#
#define DECAY_TIME     #0.000#
#define SUSTAIN_VOLUME #1.000#
#define RELEASE_TIME   #0.005#
#define END_VOLUME     #0.000#

gi_sine ftgen 0, 0, 65536, 10, 1

#include "aci/track-control.aci"

instr 2
#include "aci/instrument-control.aci"
#include "aci/volume-envelope.aci"
    a_out poscil3 k_volume, k_cps, gi_sine
    out a_out
endin
