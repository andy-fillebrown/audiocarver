
#define START_VOLUME   #1.000#
#define ATTACK_TIME    #0.001#
#define ATTACK_VOLUME  #1.000#
#define DECAY_TIME     #0.000#
#define SUSTAIN_VOLUME #1.000#
#define RELEASE_TIME   #0.010#
#define END_VOLUME     #0.000#

#include "aci/track-control.aci"

instr 2
#include "aci/instrument-control.aci"
#include "aci/volume-envelope.aci"
    i_cps = cpsmidinn(i_pitch)
    a_out pluck k_volume, k_cps, i_cps, 0, 1
    out a_out
endin
