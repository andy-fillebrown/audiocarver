
#define START_VOLUME   #0#
#define ATTACK_TIME    #0.005#
#define ATTACK_VOLUME  #1#
#define DECAY_TIME     #0#
#define SUSTAIN_VOLUME #1#
#define RELEASE_TIME   #0.005#
#define END_VOLUME     #0#

#define GRAIN_FREQUENCY_RANDOM_VARIATION       #0#    ; kfmd
#define GRAIN_DURATION                         #0.25# ; kgdur
#define GRAIN_OVERLAP_COUNT                    #10#   ; iovrlp
#define GRAIN_FREQUENCY_DISTRIBUTION_VARIATION #0#    ; [irpow]
#define GRAIN_SEED                             #0#    ; [iseed]
#define GRAIN_MODE                             #0#    ; [imode]

gi_buzz_waveform_table ftgen 0, 0, 2048, 11, 30, 1, 0.8
gi_grain_envelope_hanning_window_function ftgen 0, 0, 512, 20, 2

#include "aci/track-control.aci"

instr 2
#include "aci/instrument-control.aci"
#include "aci/volume-envelope.aci"
    a_out grain2 \
        k_cps, \
        $GRAIN_FREQUENCY_RANDOM_VARIATION, \
        $GRAIN_DURATION, \
        $GRAIN_OVERLAP_COUNT, \
        gi_buzz_waveform_table, \
        gi_grain_envelope_hanning_window_function, \
        $GRAIN_FREQUENCY_DISTRIBUTION_VARIATION, \
        $GRAIN_SEED, \
        $GRAIN_MODE
    out 0.25 * k_volume * a_out
endin
