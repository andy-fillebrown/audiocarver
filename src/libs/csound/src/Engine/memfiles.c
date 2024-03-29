/*
    memfiles.c:

    Copyright (C) 1991, 2001 Barry Vercoe, John ffitch, Richard Dobson
              (C) 2005 Istvan Varga

    This file is part of Csound.

    The Csound Library is free software; you can redistribute it
    and/or modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    Csound is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with Csound; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
    02111-1307 USA
*/

#include "csoundCore.h"     /*                              MEMFILES.C      */
#include "soundio.h"
#include "pvfileio.h"
#include "pstream.h"
#include "namedins.h"
#include <sndfile.h>
#include <string.h>

static int Load_File_(CSOUND *csound, const char *filnam,
                       char **allocp, int32 *len, int csFileType)
{
    FILE *f;
    *allocp = NULL;
    f = fopen(filnam, "rb");
    if (UNLIKELY(f == NULL))                    /* if cannot open the file */
      return 1;                                 /*    return 1             */
    /* notify the host if it asked */
    csoundNotifyFileOpened(csound, filnam, csFileType, 0, 0);
    fseek(f, 0L, SEEK_END);                     /* then get its length     */
    *len = (int32) ftell(f);
    fseek(f, 0L, SEEK_SET);
    if (UNLIKELY(*len < 1L))
      goto err_return;
    *allocp = mmalloc(csound, (size_t) (*len)); /*   alloc as reqd     */
    if (UNLIKELY(fread(*allocp, (size_t) 1,     /*   read file in      */
                       (size_t) (*len), f) != (size_t) (*len)))
      goto err_return;
    fclose(f);                                  /*   and close it      */
    return 0;                                   /*   return 0 for OK   */

 err_return:
    if (*allocp != NULL) {
      mfree(csound, *allocp);
      *allocp = NULL;
    }
    fclose(f);
    return 1;
}

/* Backwards-compatible wrapper for ldmemfile2().
   Please use ldmemfile2() or ldmemfile2withCB() in all new code instead. */
MEMFIL *ldmemfile(CSOUND *csound, const char *filnam)
{
    return ldmemfile2withCB(csound, filnam, CSFTYPE_UNKNOWN, NULL);
}

/* Takes an additional parameter specifying the type of the file being opened.
   The type constants are defined in the enumeration CSOUND_FILETYPES.
   Use ldmemfile2() to load file without additional processing.  */
MEMFIL *ldmemfile2(CSOUND *csound, const char *filnam, int csFileType)
{
    return ldmemfile2withCB(csound, filnam, csFileType, NULL);
}

/* This version of ldmemfile2 allows you to specify a callback procedure
   to process the file's data after it is loaded.  This method ensures that
   your procedure is only called once even if the file is "loaded" multiple
   times by several opcodes.  callback can be NULL.

   Callback signature:     int myfunc(CSOUND* csound, MEMFIL* mfp)
   Callback return value:  OK (0) or NOTOK (-1)
 */
MEMFIL *ldmemfile2withCB(CSOUND *csound, const char *filnam, int csFileType,
                         int (*callback)(CSOUND*, MEMFIL*))
{                               /* read an entire file into memory and log it */
    MEMFIL  *mfp, *last = NULL; /* share the file with all subsequent requests*/
    char    *allocp;            /* if not fullpath, look in current directory,*/
    int32    len;                /*   then SADIR (if defined).                 */
    char    *pathnam;           /* Used by adsyn, pvoc, and lpread            */

    mfp = csound->memfiles;
    while (mfp != NULL) {                               /* Checking chain */
      if (strcmp(mfp->filename, filnam) == 0)           /*   if match     */
        return mfp;                                     /*   we have it   */
      last = mfp;
      mfp = mfp->next;
    }
    /* Add new file description */
    mfp = (MEMFIL*) mcalloc(csound, sizeof(MEMFIL));
    if (last != NULL)
      last->next = mfp;
    else
      csound->memfiles = mfp;
    mfp->next = NULL;
    strcpy(mfp->filename, filnam); /* FIXME: will crash if filnam > 255 chars? */

    pathnam = csoundFindInputFile(csound, filnam, "SADIR");
    if (UNLIKELY(pathnam == NULL)) {
      csoundMessage(csound, Str("cannot load %s\n"), filnam);
      delete_memfile(csound, filnam);
      return NULL;
    }
    if (UNLIKELY(Load_File_(csound, pathnam, &allocp, &len, csFileType) != 0)) {
      /* loadfile */
      csoundMessage(csound, Str("cannot load %s, or SADIR undefined\n"),
                            pathnam);
      mfree(csound, pathnam);
      delete_memfile(csound, filnam);
      return NULL;
    }
    /* init the struct */
    mfp->beginp = allocp;
    mfp->endp = allocp + len;
    mfp->length = len;
    if (callback != NULL) {
      if (callback(csound, mfp) != OK) {
        csoundMessage(csound, Str("error processing file %s\n"), filnam);
        mfree(csound, pathnam);
        delete_memfile(csound, filnam);
        return NULL;
      }
    }
    csoundMessage(csound, Str("file %s (%ld bytes) loaded into memory\n"),
                          pathnam, len);
    mfree(csound, pathnam);
    return mfp;                                          /* rtn new slotadr */
}

/* clear the memfile array, & free all allocated space */

void rlsmemfiles(CSOUND *csound)
{
    MEMFIL  *mfp = csound->memfiles, *nxt;

    while (mfp != NULL) {
      nxt = mfp->next;
      mfree(csound, mfp->beginp);       /*   free the space */
      mfree(csound, mfp);
      mfp = nxt;
    }
    csound->memfiles = NULL;
}

int delete_memfile(CSOUND *csound, const char *filnam)
{
    MEMFIL  *mfp, *prv;

    prv = NULL;
    mfp = csound->memfiles;
    while (mfp != NULL) {
      if (strcmp(mfp->filename, filnam) == 0)
        break;
      prv = mfp;
      mfp = mfp->next;
    }
    if (mfp == NULL)
      return -1;
    if (prv == NULL)
      csound->memfiles = mfp->next;
    else
      prv->next = mfp->next;
    mfree(csound, mfp->beginp);
    mfree(csound, mfp);
    return 0;
}

 /* ------------------------------------------------------------------------ */

/*  despite basic parity in analysis and synthesis,
    we still have to rescale the amplitudes
    by 32768 to fit Csound's notion of 0dBFS.
    Note we do NOT try to rescale to match the old .pv format.
*/

/* custom version of ldmemfile();
   enables pvfileio funcs to apply byte-reversal if needed.
   NB: filename size in MEMFIL struct was only 64; now 256...
*/

/* RWD NB PVOCEX format always 32bit, so no MYFLTs here! */

static int pvx_err_msg(CSOUND *csound, const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    csound->ErrMsgV(csound, Str("PVOCEX_LoadFile(): error:\n    "), fmt, args);
    va_end(args);
    return -1;
}

int PVOCEX_LoadFile(CSOUND *csound, const char *fname, PVOCEX_MEMFILE *p)
{
    PVOCDATA      pvdata;
    WAVEFORMATEX  fmt;
    PVOCEX_MEMFILE  *pp;
    int           i, j, rc = 0, pvx_id, hdr_size, name_size;
    int32          mem_wanted;
    int32          totalframes, framelen;
    float         *pFrame;

    if (UNLIKELY(fname == NULL || fname[0] == '\0')) {
      memset(p, 0, sizeof(PVOCEX_MEMFILE));
      return pvx_err_msg(csound, Str("Empty or NULL file name"));
    }
    /* is this file already loaded ? */
    pp = csound->pvx_memfiles;
    while (pp != NULL && strcmp(pp->filename, fname) != 0)
      pp = pp->nxt;
    if (pp != NULL) {
      memcpy(p, pp, sizeof(PVOCEX_MEMFILE));
      return 0;
    }

    hdr_size = ((int) sizeof(PVOCEX_MEMFILE) + 7) & (~7);
    name_size = ((int) strlen(fname) + 8) & (~7);
    memset(p, 0, sizeof(PVOCEX_MEMFILE));
    memset(&pvdata, 0, sizeof(PVOCDATA));
    memset(&fmt, 0, sizeof(WAVEFORMATEX));
    pvx_id = csound->PVOC_OpenFile(csound, fname, &pvdata, &fmt);
    if (UNLIKELY(pvx_id < 0)) {
      return pvx_err_msg(csound, Str("unable to open pvocex file %s: %s"),
                                 fname, csound->PVOC_ErrorString(csound));
    }
    framelen = 2 * pvdata.nAnalysisBins;
    /* also, accept only 32bit floats for now */
    if (UNLIKELY(pvdata.wWordFormat != PVOC_IEEE_FLOAT)) {
      return pvx_err_msg(csound, Str("pvoc-ex file %s is not 32bit floats"),
                                 fname);
    }
    /* FOR NOW, accept only PVOC_AMP_FREQ: later, we can convert */
    /* NB Csound knows no other: frameFormat is not read anywhere! */
    if (UNLIKELY(pvdata.wAnalFormat != PVOC_AMP_FREQ)) {
      return pvx_err_msg(csound, Str("pvoc-ex file %s not in AMP_FREQ format"),
                                 fname);
    }
    /* ignore the window spec until we can use it! */
    totalframes = csound->PVOC_FrameCount(csound, pvx_id);
    if (UNLIKELY(totalframes <= 0)) {
      return pvx_err_msg(csound, Str("pvoc-ex file %s is empty!"), fname);
    }
    mem_wanted = totalframes * 2 * pvdata.nAnalysisBins * sizeof(float);
    /* try for the big block first! */
    pp = (PVOCEX_MEMFILE*) mmalloc(csound, (size_t) (hdr_size + name_size)
                                           + (size_t) mem_wanted);
    memset((void*) pp, 0, (size_t) (hdr_size + name_size));
    pp->filename = (char*) ((uintptr_t) pp + (uintptr_t) hdr_size);
    pp->nxt = csound->pvx_memfiles;
    pp->data = (float*) ((uintptr_t) pp + (uintptr_t) (hdr_size + name_size));
    strcpy(pp->filename, fname);
    /* despite using pvocex infile, and pvocex-style resynth, we ~still~
       have to rescale to Csound's internal range! This is because all pvocex
       calculations assume +-1 floatsam i/o.
       It seems preferable to do this here, rather than force the user
       to do so. Csound might change one day...
     */
    for (pFrame = pp->data, i = 0; i < totalframes; i++) {
      rc = csound->PVOC_GetFrames(csound, pvx_id, pFrame, 1);
      if (UNLIKELY(rc != 1))
        break;          /* read error, but may still have something to use */
      /* scale amps to Csound range, to fit fsig */
      for (j = 0; j < framelen; j += 2) {
        pFrame[j] *= (float) csound->e0dbfs;
      }
      pFrame += framelen;
    }
    csound->PVOC_CloseFile(csound, pvx_id);
    if (UNLIKELY(rc < 0)) {
      mfree(csound, pp);
      return pvx_err_msg(csound, Str("error reading pvoc-ex file %s"), fname);
    }
    if (UNLIKELY(i < totalframes)) {
      mfree(csound, pp);
      return pvx_err_msg(csound, Str("error reading pvoc-ex file %s "
                                     "after %d frames"), fname, i);
    }
    pp->srate = (MYFLT) fmt.nSamplesPerSec;
    if (pp->srate != csound->esr) {             /* & chk the data */
      csound->Warning(csound, Str("%s's srate = %8.0f, orch's srate = %8.0f"),
                              fname, pp->srate, csound->esr);
    }
    pp->nframes = (uint32) totalframes;
    pp->format  = PVS_AMP_FREQ;
    pp->fftsize = 2 * (pvdata.nAnalysisBins - 1);
    pp->overlap = pvdata.dwOverlap;
    pp->winsize = pvdata.dwWinlen;
    pp->chans   = fmt.nChannels;
    switch ((pv_wtype) pvdata.wWindowType) {
      case PVOC_DEFAULT:
      case PVOC_HAMMING:
        pp->wintype = PVS_WIN_HAMMING;
        break;
      case PVOC_HANN:
        pp->wintype = PVS_WIN_HANN;
        break;
      case PVOC_KAISER:
        pp->wintype = PVS_WIN_KAISER;
        break;
      default:
        /* deal with all other possibilities later! */
        pp->wintype = PVS_WIN_HAMMING;
        break;
    }

    /* link into PVOC-EX memfile chain */
    csound->pvx_memfiles = pp;
    csound->Message(csound, Str("file %s (%ld bytes) loaded into memory\n"),
                            fname, (int32) mem_wanted);

    memcpy(p, pp, sizeof(PVOCEX_MEMFILE));
    return 0;
}

 /* ------------------------------------------------------------------------ */

/**
 * Load an entire sound file into memory.
 * 'fileName' is the file name (searched in the current directory first,
 * then search path defined by SSDIR, then SFDIR), and sfinfo (optional,
 * may be NULL) stores the default parameters for opening a raw file.
 * On success, a pointer to an SNDMEMFILE structure (see csoundCore.h) is
 * returned, and sound file parameters are stored in sfinfo (assuming that
 * it is not NULL).
 * Multiple calls of csoundLoadSoundFile() with the same file name will
 * share the same SNDMEMFILE structure, and the file is loaded only once
 * from disk.
 * The return value is NULL if an error occurs (the contents of sfinfo may
 * be undefined in this case).
 */

SNDMEMFILE *csoundLoadSoundFile(CSOUND *csound, const char *fileName, void *sfi)
{
    SF_INFO       *sfinfo = sfi;
    SNDFILE       *sf;
    void          *fd;
    SNDMEMFILE    *p = NULL;
    SF_INFO       tmp;
    unsigned char h;


    if (UNLIKELY(fileName == NULL || fileName[0] == '\0'))
      return NULL;
    /* check if file is already loaded */
    h = name_hash_2(csound, fileName);
    if (csound->sndmemfiles != NULL) {
      p = ((SNDMEMFILE**) csound->sndmemfiles)[(int) h];
      while (p != NULL && sCmp(p->name, fileName) != 0)
        p = p->nxt;
    }
    else {
      int i;
      /* if no files loaded yet, allocate table */
      csound->sndmemfiles = csound->Malloc(csound, sizeof(SNDMEMFILE*) * 256);
      for (i = 0; i < 256; i++)
        ((SNDMEMFILE**) csound->sndmemfiles)[i] = NULL;
    }
    if (p != NULL) {
      /* if file was loaded earlier: */
      if (sfinfo != NULL) {
        memset(sfinfo, 0, sizeof(SF_INFO));
        sfinfo->frames = (sf_count_t) p->nFrames;
         sfinfo->samplerate = ((int) p->sampleRate + 0.5);
         sfinfo->channels = p->nChannels;
         sfinfo->format = FORMAT2SF(p->sampleFormat) | TYPE2SF(p->fileType);
      }
      return p;
    }
    /* open file */
    if (sfinfo == NULL) {
      memset(&tmp, 0, sizeof(SF_INFO));
      sfinfo = &tmp;
    }
    fd = csound->FileOpen2(csound, &sf, CSFILE_SND_R, fileName, sfinfo,
                            "SFDIR;SSDIR", CSFTYPE_UNKNOWN_AUDIO, 0);
    if (UNLIKELY(fd == NULL)) {
      csound->ErrorMsg(csound,
                       Str("csoundLoadSoundFile(): failed to open '%s'"),
                       fileName);
      return NULL;
    }
    p = (SNDMEMFILE*)
            csound->Malloc(csound, sizeof(SNDMEMFILE)
                           + (size_t)  sfinfo->frames * sizeof(float));
    /* set parameters */
    p->name = (char*) csound->Malloc(csound, strlen(fileName) + 1);
    strcpy(p->name, fileName);
    p->fullName = (char*) csound->Malloc(csound,
                                         strlen(csound->GetFileName(fd)) + 1);
    strcpy(p->fullName, csound->GetFileName(fd));
    p->sampleRate = (double) sfinfo->samplerate;
    p->nFrames = (size_t) sfinfo->frames;
    p->nChannels = sfinfo->channels;
    p->sampleFormat = SF2FORMAT(sfinfo->format);
    p->fileType = SF2TYPE(sfinfo->format);
    /* set defaults for sampler information */
    p->loopMode = 0;
    p->startOffs = 0.0;
    p->loopStart = 0.0;
    p->loopEnd = 0.0;
    p->baseFreq = 1.0;
    p->scaleFac = 1.0;
    {
      SF_INSTRUMENT lpd;
      if (sf_command(sf, SFC_GET_INSTRUMENT, &lpd, sizeof(SF_INSTRUMENT))
          != 0) {
        if (lpd.loop_count > 0 && lpd.loops[0].mode != SF_LOOP_NONE) {
          /* set loop mode and loop points */
          p->loopMode = (lpd.loops[0].mode == SF_LOOP_FORWARD ?
                         2 : (lpd.loops[0].mode == SF_LOOP_BACKWARD ? 3 : 4));
          p->loopStart = (double) lpd.loops[0].start;
          p->loopEnd = (double) lpd.loops[0].end;
        }
        else {
          /* loop mode: off */
          p->loopMode = 1;
        }
        p->baseFreq = pow(2.0, (double) (((int) lpd.basenote - 69) * 100
                                         + (int) lpd.detune) / 1200.0) * 440.0;
        p->scaleFac = pow(10.0, (double) lpd.gain * 0.05);
      }
    }
    p->nxt = ((SNDMEMFILE**) csound->sndmemfiles)[(int) h];
    if ((size_t) sf_readf_float(sf, &(p->data[0]), (sf_count_t) p->nFrames)
        != p->nFrames) {
      csound->FileClose(csound, fd);
      csound->Free(csound, p->name);
      csound->Free(csound, p->fullName);
      csound->Free(csound, p);
      csound->ErrorMsg(csound, Str("csoundLoadSoundFile(): error reading '%s'"),
                               fileName);
      return NULL;
    }
    p->data[p->nFrames] = 0.0f;
    csound->FileClose(csound, fd);
    csound->Message(csound, Str("File '%s' (sr = %d Hz, %d channel(s), %lu "
                                "sample frames) loaded into memory\n"),
                            p->fullName, (int) sfinfo->samplerate,
                            (int) sfinfo->channels,
                            (uint32) sfinfo->frames);
    /* link into database */
    ((SNDMEMFILE**) csound->sndmemfiles)[(int) h] = p;
    /* return with pointer to file structure */
    return p;
}
