
; Adapted from an example by Iain McCurdy

#include "aci/track-control.aci"

instr 2

#include "aci/instrument-control.aci"

    ; A noise source sound: pink noise.
    aInput pinkish 1

    ; Cutoff frequencies for low and highpass filters.
    kLPF_CF = 13
    kHPF_CF = 5

    ; Filter input sound with low and highpass filters, in series.
    ; Do this twice per filter to sharpen cutoff slopes.
    aInput butlp aInput, cpsoct(kLPF_CF)
    aInput butlp aInput, cpsoct(kLPF_CF)
    aInput buthp aInput, cpsoct(kHPF_CF)
    aInput buthp aInput, cpsoct(kHPF_CF)

    ; Bandwidth for each filter is created individually as a random spline function.
    kbw1 = 0.0625
    kbw2 = 0.1250
    kbw3 = 0.2500
    kbw4 = 0.5000
    kbw5 = 1.0000
    kbw6 = 2.0000
    kbw7 = 4.0000
    kbw8 = 8.0000

    ; Amplitude balancing method used by the reson filters.
    imode = 0

    a1 resonz aInput, k_cps * 1.0000000000000, kbw1, imode
    a2 resonz aInput, k_cps * 1.7936737804878, kbw2, imode
    a3 resonz aInput, k_cps * 2.5201981707317, kbw3, imode
    a4 resonz aInput, k_cps * 2.9907012195122, kbw4, imode
    a5 resonz aInput, k_cps * 3.7855182926829, kbw5, imode
    a6 resonz aInput, k_cps * 4.5689024390244, kbw6, imode
    a7 resonz aInput, k_cps * 5.0296493902439, kbw7, imode
    a8 resonz aInput, k_cps * 6.0759908536585, kbw8, imode

    ; Amplitude control for each filter output.
    kAmp1 = 1.0
    kAmp2 = 0.9
    kAmp3 = 0.8
    kAmp4 = 0.7
    kAmp5 = 0.6
    kAmp6 = 0.5
    kAmp7 = 0.4
    kAmp8 = 0.3

    ; Mix the resonators.
    aMix sum a1 * kAmp1, a2 * kAmp2, a3 * kAmp3, a4 * kAmp4, a5 * kAmp5, a6 * kAmp6, a7 * kAmp7, a8 * kAmp8

    ; Global amplitude envelope.
    kEnv linseg 0, p3 * 0.5, 1, p3 * 0.5, 0, 1, 0

    ; Send audio to output.
    out 0.01 * k_volume * kEnv * aMix
endin
