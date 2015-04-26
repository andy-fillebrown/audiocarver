TARGET = sndfile
TEMPLATE = lib

include(../../_.library.prf)

CONFIG -= qt

DEFINES -= \
    UNICODE \

INCLUDEPATH *= \
    src \

HEADERS = \
    src/chanmap.h \
    src/common.h \
    src/ima_oki_adpcm.h \
    src/ogg.h \
    src/sf_unistd.h \
    src/sfconfig.h \
    src/sfendian.h \
    src/sndfile.h \
    src/wav_w64.h \
    \
    src/G72x/g72x.h \
    src/G72x/g72x_priv.h \
    \
    src/GSM610/config.h \
    src/GSM610/gsm.h \
    src/GSM610/gsm610_priv.h \

SOURCES = \
    src/aiff.c \
    src/alaw.c \
    src/au.c \
    src/audio_detect.c \
    src/avr.c \
    src/broadcast.c \
    src/caf.c \
    src/chanmap.c \
    src/chunk.c \
    src/command.c \
    src/common.c \
    src/dither.c \
    src/double64.c \
    src/dwd.c \
    src/dwvw.c \
    src/file_io.c \
    src/flac.c \
    src/float32.c \
    src/g72x--top.c \
    src/gsm610--top.c \
    src/htk.c \
    src/id3.c \
    src/ima_adpcm.c \
    src/ima_oki_adpcm.c \
    src/interleave.c \
    src/ircam.c \
    src/macbinary3.c \
    src/macos.c \
    src/mat4.c \
    src/mat5.c \
    src/mpc2k.c \
    src/ms_adpcm.c \
    src/nist.c \
    src/ogg.c \
    src/ogg_pcm.c \
    src/ogg_speex.c \
    src/ogg_vorbis.c \
    src/paf.c \
    src/pcm.c \
    src/pvf.c \
    src/raw.c \
    src/rf64.c \
    src/rx2.c \
    src/sd2.c \
    src/sds.c \
    src/sndfile.c \
    src/strings.c \
    src/svx.c \
    src/txw.c \
    src/ulaw.c \
    src/voc.c \
    src/vox_adpcm.c \
    src/w64.c \
    src/wav.c \
    src/wav_w64.c \
    src/windows.c \
    src/wve.c \
    src/xi.c \
    \
    src/G72x/g72x.c \
    src/G72x/g721.c \
    src/G72x/g723_16.c \
    src/G72x/g723_24.c \
    src/G72x/g723_40.c \
    \
    src/GSM610/add.c \
    src/GSM610/code.c \
    src/GSM610/decode.c \
    src/GSM610/gsm_create.c \
    src/GSM610/gsm_decode.c \
    src/GSM610/gsm_destroy.c \
    src/GSM610/gsm_encode.c \
    src/GSM610/gsm_option.c \
    src/GSM610/long_term.c \
    src/GSM610/lpc.c \
    src/GSM610/preprocess.c \
    src/GSM610/rpe.c \
    src/GSM610/short_term.c \
    src/GSM610/table.c \

QMAKE_CFLAGS_WARN_ON *= -Wno-unused-const-variable

OTHER_FILES *= \
    _.sndfile.prf \
    AUTHORS \
    ChangeLog \
    COPYING \
    README \

macx {
    INCLUDEPATH *= config/macx-g++
    HEADERS *= config/macx-g++/config.h
}
win32-g++* {
    INCLUDEPATH *= config/win32-g++
    HEADERS *= config/win32-g++/config.h
}
