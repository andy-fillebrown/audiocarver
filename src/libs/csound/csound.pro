TARGET = csound
TEMPLATE = lib

load(../../library.prf)
load(../libsndfile/libsndfile.prf)

CONFIG -= qt
CONFIG *= warn_off

QMAKE_CFLAGS += \
	-fomit-frame-pointer \
	-freorder-blocks \
	-mthreads \

QMAKE_CXXFLAGS += \
	-fomit-frame-pointer \
	-freorder-blocks \
	-mthreads \

DEFINES -= UNICODE
DEFINES *= USE_DOUBLE

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

windows {
	DEFINES *= \
		OS_IS_WIN32 \
		_WIN32 \
		WIN32 \
}

INCLUDEPATH *= \
	H \

HEADERS += \
	Engine/*.h* \
	H/*.h* \
	InOut/*.h* \
	OOps/*.h* \
	Opcodes/*.h* \
	Opcodes/gab/*.h* \
	Top/*.h* \

SOURCES += \
	Engine/auxfd.c \
	Engine/cfgvar.c \
	Engine/corfiles.c \
	Engine/csound_orc_semantics.c \
	Engine/csound_orc_expressions.c \
	Engine/csound_orc_optimize.c \
	Engine/csound_orc_compile.c \
	Engine/csound_orclex.c \
	Engine/csound_orcparse.c \
	Engine/entry1.c \
	Engine/envvar.c \
	Engine/express.c \
	Engine/extract.c \
	Engine/fgens.c \
	Engine/insert.c \
	Engine/linevent.c \
	Engine/memalloc.c \
	Engine/memfiles.c \
	Engine/musmon.c \
	Engine/namedins.c \
	Engine/new_orc_parser.c \
	Engine/otran.c \
	Engine/rdorch.c \
	Engine/rdscor.c \
	Engine/scsort.c \
	Engine/scxtract.c \
	Engine/sort.c \
	Engine/sread.c \
	Engine/swrite.c \
	Engine/swritestr.c \
	Engine/symbtab.c \
	Engine/twarp.c \
	\
	InOut/libsnd.c \
	InOut/libsnd_u.c \
	InOut/midifile.c \
	InOut/midirecv.c \
	InOut/midisend.c \
	InOut/winascii.c \
	InOut/windin.c \
	InOut/window.c \
	InOut/winEPS.c \
	\
	OOps/aops.c \
	OOps/bus.c \
	OOps/cmath.c \
	OOps/diskin.c \
	OOps/diskin2.c \
	OOps/disprep.c \
	OOps/dumpf.c \
	OOps/fftlib.c \
	OOps/goto_ops.c \
	OOps/midiinterop.c \
	OOps/midiops.c \
	OOps/midiout.c \
	OOps/mxfft.c \
	OOps/oscils.c \
	OOps/pstream.c \
	OOps/pvfileio.c \
	OOps/pvsanal.c \
	OOps/random.c \
	OOps/remote.c \
	OOps/schedule.c \
	OOps/sndinfUG.c \
	OOps/str_ops.c \
	OOps/ugens1.c \
	OOps/ugens2.c \
	OOps/ugens3.c \
	OOps/ugens4.c \
	OOps/ugens5.c \
	OOps/ugens6.c \
	OOps/ugrw1.c \
	OOps/ugrw2.c \
	OOps/vdelay.c \
	\
	Opcodes/ambicode.c \
	Opcodes/ambicode1.c \
	Opcodes/babo.c \
	Opcodes/bbcut.c \
	Opcodes/bilbar.c \
	Opcodes/biquad.c \
	Opcodes/bowedbar.c \
	Opcodes/butter.c \
	Opcodes/clfilt.c \
	Opcodes/compress.c \
	Opcodes/cpumeter.c \
	Opcodes/cross2.c \
	Opcodes/crossfm.c \
	Opcodes/dam.c \
	Opcodes/dcblockr.c \
	Opcodes/dsputil.c \
	Opcodes/eqfil.c \
	Opcodes/fareyseq.c \
	Opcodes/filter.c \
	Opcodes/flanger.c \
	Opcodes/fm4op.c \
	Opcodes/follow.c \
	Opcodes/fout.c \
	Opcodes/freeverb.c \
	Opcodes/ftconv.c \
	Opcodes/ftest.c \
	Opcodes/ftgen.c \
	Opcodes/grain.c \
	Opcodes/grain4.c \
	Opcodes/harmon.c \
	Opcodes/hrtfearly.c \
	Opcodes/hrtferX.c \
	Opcodes/hrtfopcodes.c \
	Opcodes/hrtfreverb.c \
	Opcodes/ifd.c \
	Opcodes/locsig.c \
	Opcodes/loscilx.c \
	Opcodes/lowpassr.c \
	Opcodes/mandolin.c \
	Opcodes/metro.c \
	Opcodes/midiops2.c \
	Opcodes/midiops3.c \
	Opcodes/minmax.c \
	Opcodes/modal4.c \
	Opcodes/modmatrix.c \
	Opcodes/moog1.c \
	Opcodes/newfils.c \
	Opcodes/nlfilt.c \
	Opcodes/oscbnk.c \
	Opcodes/pan2.c \
	Opcodes/partials.c \
	Opcodes/partikkel.c \
	Opcodes/phisem.c \
	Opcodes/physmod.c \
	Opcodes/physutil.c \
	Opcodes/pitch.c \
	Opcodes/pitch0.c \
	Opcodes/pitchtrack.c \
	Opcodes/psynth.c \
	Opcodes/pvadd.c \
	Opcodes/pvinterp.c \
	Opcodes/pvlock.c \
	Opcodes/pvoc.c \
	Opcodes/pvocext.c \
	Opcodes/pvread.c \
	Opcodes/pvsbasic.c \
	Opcodes/pvsbuffer.c \
	Opcodes/pvscent.c \
	Opcodes/pvsdemix.c \
	Opcodes/pvsband.c \
	Opcodes/pluck.c \
	Opcodes/pvs_ops.c \
	Opcodes/repluck.c \
	Opcodes/reverbsc.c \
	Opcodes/scoreline.c \
	Opcodes/seqtime.c \
	Opcodes/sfont.c \
	Opcodes/shaker.c \
	Opcodes/shape.c \
	Opcodes/singwave.c \
	Opcodes/sndloop.c \
	Opcodes/sndwarp.c \
	Opcodes/space.c \
	Opcodes/spat3d.c \
	Opcodes/spectra.c \
	Opcodes/stackops.c \
	Opcodes/stdopcod.c \
	Opcodes/syncgrain.c \
	Opcodes/tabsum.c \
	Opcodes/tabvars.c \
	Opcodes/ugakbari.c \
	Opcodes/ugens7.c \
	Opcodes/ugens8.c \
	Opcodes/ugens9.c \
	Opcodes/ugensa.c \
	Opcodes/uggab.c \
	Opcodes/ugmoss.c \
	Opcodes/ugnorman.c \
	Opcodes/ugsc.c \
	Opcodes/vbap.c \
	Opcodes/vbap_eight.c \
	Opcodes/vbap_four.c \
	Opcodes/vbap_sixteen.c \
	Opcodes/vbap_zak.c \
	Opcodes/Vosim.c \
	Opcodes/vpvoc.c \
	Opcodes/wave-terrain.c \
	\
	Opcodes/gab/gab.c \
	Opcodes/gab/hvs.c \
	Opcodes/gab/newgabopc.c \
	Opcodes/gab/sliderTable.c \
	Opcodes/gab/tabmorph.c \
	Opcodes/gab/vectorial.c \
	\
	Top/argdecode.c \
	Top/cscore_internal.c \
	Top/cscorfns.c \
	Top/csmodule.c \
	Top/csound.c \
	Top/getstring.c \
	Top/main.c \
	Top/new_opts.c \
	Top/one_file.c \
	Top/opcode.c \
	Top/threads.c \
	Top/utility.c

LIBS *= -lpthread

windows {
	LIBS *= -lwsock32
}

OTHER_FILES *= \
	readme-parser.txt \
