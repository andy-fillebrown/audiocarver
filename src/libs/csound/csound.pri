TARGET = csound
TEMPLATE = lib

useDoubles {
    DEFINES *= USE_DOUBLE
    TARGET = $${TARGET}64
}

load(../../library.prf)

win32 {
    load(../pthreads/pthreads.prf)
    load(../sndfile/sndfile.prf)
}

CONFIG -= qt
CONFIG *= warn_off

CONFIG(debug|release, release) {
    QMAKE_CFLAGS += \
        -fomit-frame-pointer \
        -freorder-blocks \

    QMAKE_CXXFLAGS += \
        -fomit-frame-pointer \
        -freorder-blocks \
}

DEFINES -= \
    UNICODE \

DEFINES *= \
    __BUILDING_LIBCSOUND \
    ENABLE_NEW_PARSER \
    HAVE_DIRENT_H \
    HAVE_FCNTL_H \
    HAVE_IO_H \
    HAVE_LIBSNDFILE=1017 \
    HAVE_PTHREAD_BARRIER_INIT \
    HAVE_SOCKETS \
    HAVE_STDINT_H \
    HAVE_SYS_TIME_H \
    HAVE_SYS_TYPES_H \
    HAVE_UNISTD_H \
    HAVE_VALUES_H \
    PIPES \

CONFIG(debug|release, release) {
    DEFINES *= \
        _CSOUND_RELEASE_ \
}

INCLUDEPATH *= \
    ../src \
    ../src/H \

HEADERS = \
    ../src/Engine/*.h* \
    ../src/H/*.h* \
    ../src/InOut/*.h* \
    ../src/InOut/libmpadec/*.h* \
    ../src/OOps/*.h* \
    ../src/Opcodes/*.h* \
    ../src/Opcodes/gab/*.h* \
    ../src/Top/*.h* \

SOURCES = \
    ../src/Engine/auxfd.c \
    ../src/Engine/cfgvar.c \
    ../src/Engine/corfiles.c \
    ../src/Engine/csound_orc_semantics.c \
    ../src/Engine/csound_orc_expressions.c \
    ../src/Engine/csound_orc_optimize.c \
    ../src/Engine/csound_orc_compile.c \
    ../src/Engine/csound_orclex.c \
    ../src/Engine/csound_orcparse.c \
    ../src/Engine/entry1.c \
    ../src/Engine/envvar.c \
    ../src/Engine/express.c \
    ../src/Engine/extract.c \
    ../src/Engine/fgens.c \
    ../src/Engine/insert.c \
    ../src/Engine/linevent.c \
    ../src/Engine/memalloc.c \
    ../src/Engine/memfiles.c \
    ../src/Engine/musmon.c \
    ../src/Engine/namedins.c \
    ../src/Engine/new_orc_parser.c \
    ../src/Engine/otran.c \
    ../src/Engine/rdorch.c \
    ../src/Engine/rdscor.c \
    ../src/Engine/scsort.c \
    ../src/Engine/scxtract.c \
    ../src/Engine/sort.c \
    ../src/Engine/sread.c \
    ../src/Engine/swrite.c \
    ../src/Engine/swritestr.c \
    ../src/Engine/symbtab.c \
    ../src/Engine/twarp.c \
    \
    ../src/InOut/libsnd.c \
    ../src/InOut/libsnd_u.c \
    ../src/InOut/midifile.c \
    ../src/InOut/midirecv.c \
    ../src/InOut/midisend.c \
    ../src/InOut/winascii.c \
    ../src/InOut/windin.c \
    ../src/InOut/window.c \
    ../src/InOut/winEPS.c \
    \
    ../src/InOut/libmpadec/layer1.c \
    ../src/InOut/libmpadec/layer2.c \
    ../src/InOut/libmpadec/layer3.c \
    ../src/InOut/libmpadec/mp3dec.c \
    ../src/InOut/libmpadec/mpadec.c \
    ../src/InOut/libmpadec/synth.c \
    ../src/InOut/libmpadec/tables.c \
    \
    ../src/OOps/aops.c \
    ../src/OOps/bus.c \
    ../src/OOps/cmath.c \
    ../src/OOps/diskin.c \
    ../src/OOps/diskin2.c \
    ../src/OOps/disprep.c \
    ../src/OOps/dumpf.c \
    ../src/OOps/fftlib.c \
    ../src/OOps/goto_ops.c \
    ../src/OOps/midiinterop.c \
    ../src/OOps/midiops.c \
    ../src/OOps/midiout.c \
    ../src/OOps/mxfft.c \
    ../src/OOps/oscils.c \
    ../src/OOps/pstream.c \
    ../src/OOps/pvfileio.c \
    ../src/OOps/pvsanal.c \
    ../src/OOps/random.c \
    ../src/OOps/remote.c \
    ../src/OOps/schedule.c \
    ../src/OOps/sndinfUG.c \
    ../src/OOps/str_ops.c \
    ../src/OOps/ugens1.c \
    ../src/OOps/ugens2.c \
    ../src/OOps/ugens3.c \
    ../src/OOps/ugens4.c \
    ../src/OOps/ugens5.c \
    ../src/OOps/ugens6.c \
    ../src/OOps/ugrw1.c \
    ../src/OOps/ugrw2.c \
    ../src/OOps/vdelay.c \
    \
    ../src/Opcodes/ambicode.c \
    ../src/Opcodes/ambicode1.c \
    ../src/Opcodes/babo.c \
    ../src/Opcodes/bbcut.c \
    ../src/Opcodes/bilbar.c \
    ../src/Opcodes/biquad.c \
    ../src/Opcodes/bowedbar.c \
    ../src/Opcodes/butter.c \
    ../src/Opcodes/clfilt.c \
    ../src/Opcodes/compress.c \
    ../src/Opcodes/cross2.c \
    ../src/Opcodes/crossfm.c \
    ../src/Opcodes/dam.c \
    ../src/Opcodes/dcblockr.c \
    ../src/Opcodes/dsputil.c \
    ../src/Opcodes/eqfil.c \
    ../src/Opcodes/fareyseq.c \
    ../src/Opcodes/filter.c \
    ../src/Opcodes/flanger.c \
    ../src/Opcodes/fm4op.c \
    ../src/Opcodes/follow.c \
    ../src/Opcodes/fout.c \
    ../src/Opcodes/freeverb.c \
    ../src/Opcodes/ftconv.c \
    ../src/Opcodes/ftest.c \
    ../src/Opcodes/ftgen.c \
    ../src/Opcodes/grain.c \
    ../src/Opcodes/grain4.c \
    ../src/Opcodes/harmon.c \
    ../src/Opcodes/hrtfearly.c \
    ../src/Opcodes/hrtferX.c \
    ../src/Opcodes/hrtfopcodes.c \
    ../src/Opcodes/hrtfreverb.c \
    ../src/Opcodes/ifd.c \
    ../src/Opcodes/locsig.c \
    ../src/Opcodes/loscilx.c \
    ../src/Opcodes/lowpassr.c \
    ../src/Opcodes/mandolin.c \
    ../src/Opcodes/metro.c \
    ../src/Opcodes/midiops2.c \
    ../src/Opcodes/midiops3.c \
    ../src/Opcodes/minmax.c \
    ../src/Opcodes/modal4.c \
    ../src/Opcodes/modmatrix.c \
    ../src/Opcodes/moog1.c \
    ../src/Opcodes/mp3in.c \
    ../src/Opcodes/newfils.c \
    ../src/Opcodes/nlfilt.c \
    ../src/Opcodes/oscbnk.c \
    ../src/Opcodes/pan2.c \
    ../src/Opcodes/partials.c \
    ../src/Opcodes/partikkel.c \
    ../src/Opcodes/phisem.c \
    ../src/Opcodes/physmod.c \
    ../src/Opcodes/physutil.c \
    ../src/Opcodes/pitch.c \
    ../src/Opcodes/pitch0.c \
    ../src/Opcodes/pitchtrack.c \
    ../src/Opcodes/psynth.c \
    ../src/Opcodes/pvadd.c \
    ../src/Opcodes/pvinterp.c \
    ../src/Opcodes/pvlock.c \
    ../src/Opcodes/pvoc.c \
    ../src/Opcodes/pvocext.c \
    ../src/Opcodes/pvread.c \
    ../src/Opcodes/pvsbasic.c \
    ../src/Opcodes/pvsbuffer.c \
    ../src/Opcodes/pvscent.c \
    ../src/Opcodes/pvsdemix.c \
    ../src/Opcodes/pvsband.c \
    ../src/Opcodes/pluck.c \
    ../src/Opcodes/pvs_ops.c \
    ../src/Opcodes/repluck.c \
    ../src/Opcodes/reverbsc.c \
    ../src/Opcodes/scoreline.c \
    ../src/Opcodes/seqtime.c \
    ../src/Opcodes/sfont.c \
    ../src/Opcodes/shaker.c \
    ../src/Opcodes/shape.c \
    ../src/Opcodes/singwave.c \
    ../src/Opcodes/sndloop.c \
    ../src/Opcodes/sndwarp.c \
    ../src/Opcodes/space.c \
    ../src/Opcodes/spat3d.c \
    ../src/Opcodes/spectra.c \
    ../src/Opcodes/stackops.c \
    ../src/Opcodes/stdopcod.c \
    ../src/Opcodes/syncgrain.c \
    ../src/Opcodes/tabsum.c \
    ../src/Opcodes/tabvars.c \
    ../src/Opcodes/ugakbari.c \
    ../src/Opcodes/ugens7.c \
    ../src/Opcodes/ugens8.c \
    ../src/Opcodes/ugens9.c \
    ../src/Opcodes/ugensa.c \
    ../src/Opcodes/uggab.c \
    ../src/Opcodes/ugmoss.c \
    ../src/Opcodes/ugnorman.c \
    ../src/Opcodes/ugsc.c \
    ../src/Opcodes/vaops.c \
    ../src/Opcodes/vbap.c \
    ../src/Opcodes/vbap_eight.c \
    ../src/Opcodes/vbap_four.c \
    ../src/Opcodes/vbap_sixteen.c \
    ../src/Opcodes/vbap_zak.c \
    ../src/Opcodes/Vosim.c \
    ../src/Opcodes/vpvoc.c \
    ../src/Opcodes/wave-terrain.c \
    \
    ../src/Opcodes/gab/gab.c \
    ../src/Opcodes/gab/hvs.c \
    ../src/Opcodes/gab/newgabopc.c \
    ../src/Opcodes/gab/sliderTable.c \
    ../src/Opcodes/gab/tabmorph.c \
    ../src/Opcodes/gab/vectorial.c \
    \
    ../src/Top/argdecode.c \
    ../src/Top/cscore_internal.c \
    ../src/Top/cscorfns.c \
    ../src/Top/csmodule.c \
    ../src/Top/csound.c \
    ../src/Top/getstring.c \
    ../src/Top/main.c \
    ../src/Top/new_opts.c \
    ../src/Top/one_file.c \
    ../src/Top/opcode.c \
    ../src/Top/threads.c \
    ../src/Top/utility.c

OTHER_FILES *= \
    ../src/AUTHORS \
    ../src/ChangeLog \
    ../src/COPYING \
    ../src/LICENSE.random \
    ../src/readme.txt \
    ../src/readme-parser.txt \

unix: !macx: !freebsd* {
    INCLUDEPATH *= \
        ../../sndfile/src \

    LIBS *= \
        -ldl \
        -lpthread \
        /usr/lib/libsndfile.so.1 \
}

win32 {
    QMAKE_CFLAGS *= \
        -mthreads \

    QMAKE_CXXFLAGS *= \
        -mthreads \

    DEFINES *= \
        OS_IS_WIN32 \
        _WIN32 \
        WIN32 \

    LIBS *= \
        -lwsock32 \
}
