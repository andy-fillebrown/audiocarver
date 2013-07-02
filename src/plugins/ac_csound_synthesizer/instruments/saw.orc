
#define START_VOLUME   #0.000#
#define ATTACK_TIME    #0.005#
#define ATTACK_VOLUME  #1.000#
#define DECAY_TIME     #0.000#
#define SUSTAIN_VOLUME #1.000#
#define RELEASE_TIME   #0.005#
#define END_VOLUME     #0.000#

#include "aci/track-control.aci"

instr 2
#include "aci/instrument-control.aci"
#include "aci/volume-envelope.aci"
    a_out vco2 k_volume, k_cps, 8
    out a_out
endin
