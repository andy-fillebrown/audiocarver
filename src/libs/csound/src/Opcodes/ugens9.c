/*
    ugens9.c:

    Copyright (C) 1996 Greg Sullivan, 2004 ma++ ingalls

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

#include "csdl.h"   /*                                      UGENS9.C        */
#include <math.h>
#include "convolve.h"
#include "ugens9.h"
#include "soundio.h"
#include "oload.h"

static int cvset(CSOUND *csound, CONVOLVE *p)
{
    char     cvfilnam[MAXNAME];
    MEMFIL   *mfp;
    MYFLT *fltp;
    CVSTRUCT *cvh;
    int siz;
    int32     Hlenpadded = 1, obufsiz, Hlen;
    int      nchanls;

    if (UNLIKELY(csound->oparms->odebug))
      csound->Message(csound, CONVOLVE_VERSION_STRING);

    csound->strarg2name(csound, cvfilnam, p->ifilno, "convolve.", p->XSTRCODE);
    if ((mfp = p->mfp) == NULL || strcmp(mfp->filename, cvfilnam) != 0) {
      /* if file not already readin */
      if (UNLIKELY((mfp = csound->ldmemfile2(csound, cvfilnam, CSFTYPE_CVANAL))
                   == NULL)) {
        return csound->InitError(csound,
                                 Str("CONVOLVE cannot load %s"), cvfilnam);
      }
    }
    cvh = (CVSTRUCT *)mfp->beginp;
    if (UNLIKELY(cvh->magic != CVMAGIC)) {
      return csound->InitError(csound,
                               Str("%s not a CONVOLVE file (magic %ld)"),
                               cvfilnam, cvh->magic);
    }

    nchanls = (cvh->channel == ALLCHNLS ? cvh->src_chnls : 1);

    if (*p->channel == FL(0.0)) {
      if (LIKELY(p->OUTOCOUNT == nchanls))
        p->nchanls = nchanls;
      else {
        return csound->InitError(csound,
                                 Str("CONVOLVE: output channels not equal "
                                     "to number of channels in source"));
      }
    }
    else {
      if (*p->channel <= nchanls) {
        if (UNLIKELY(p->OUTOCOUNT != 1)) {
          return csound->InitError(csound,
                                   Str("CONVOLVE: output channels not equal "
                                        "to number of channels in source"));
        }
        else
          p->nchanls = 1;
      }
      else {
        return csound->InitError(csound,
                                 Str("CONVOLVE: channel number greater than "
                                     "number of channels in source"));
      }
    }
    Hlen = p->Hlen = cvh->Hlen;
    while (Hlenpadded < 2*Hlen-1)
      Hlenpadded <<= 1;
    p->Hlenpadded = Hlenpadded;
    p->H = (MYFLT *) ((char *)cvh+cvh->headBsize);
    if ((p->nchanls == 1) && (*p->channel > 0))
      p->H += (Hlenpadded + 2) * (int)(*p->channel - 1);

    if (UNLIKELY(cvh->samplingRate != csound->esr)) {
      /* & chk the data */
      csound->Warning(csound, Str("%s's srate = %8.0f, orch's srate = %8.0f"),
                              cvfilnam, cvh->samplingRate, csound->esr);
    }
    if (UNLIKELY(cvh->dataFormat != CVMYFLT)) {
      return csound->InitError(csound,
                               Str("unsupported CONVOLVE data "
                                   "format %ld in %s"),
                               cvh->dataFormat, cvfilnam);
    }

    /* Determine size of circular output buffer */
    if (Hlen >= csound->ksmps)
      obufsiz = (int32) CEIL((MYFLT) Hlen / csound->ksmps)
                * csound->ksmps;
    else
      obufsiz = (int32) CEIL(csound->ksmps / (MYFLT) Hlen) * Hlen;

    siz = ((Hlenpadded + 2) + p->nchanls * ((Hlen - 1) + obufsiz)
              + (p->nchanls > 1 ? (Hlenpadded + 2) : 0));
    if (p->auxch.auxp == NULL || p->auxch.size < siz*sizeof(MYFLT)) {
      /* if no buffers yet, alloc now */
      csound->AuxAlloc(csound, (size_t) siz*sizeof(MYFLT), &p->auxch);
      fltp = (MYFLT *) p->auxch.auxp;
      p->fftbuf = fltp;   fltp += (Hlenpadded + 2); /* and insert addresses */
      p->olap = fltp;     fltp += p->nchanls*(Hlen - 1);
      p->outbuf = fltp;   fltp += p->nchanls*obufsiz;
      p->X  = fltp;
    }
    else {
      fltp = (MYFLT *) p->auxch.auxp;
      memset(fltp, 0, sizeof(MYFLT)*siz);
    /* for(i=0; i < siz; i++) fltp[i] = FL(0.0); */
    }
    p->obufsiz = obufsiz;
    p->outcnt = obufsiz;
    p->incount = 0;
    p->obufend = p->outbuf + obufsiz - 1;
    p->outhead = p->outail = p->outbuf;
    return OK;
}

/* Write from a circular buffer into a linear output buffer without
   clearing data
   UPDATES SOURCE & DESTINATION POINTERS TO REFLECT NEW POSITIONS */
static void writeFromCircBuf(
    MYFLT   **sce,
    MYFLT   **dst,              /* Circular source and linear destination */
    MYFLT   *sceStart,
    MYFLT   *sceEnd,            /* Address of start & end of source buffer */
    int32    numToDo)            /* How many points to write (<= circBufSize) */
{
    MYFLT   *srcindex = *sce;
    MYFLT   *dstindex = *dst;
    int32    breakPoint;     /* how many points to add before having to wrap */

    breakPoint = sceEnd - srcindex + 1;
    if (numToDo >= breakPoint) { /*  we will do 2 in 1st loop, rest in 2nd. */
      numToDo -= breakPoint;
      for (; breakPoint > 0; --breakPoint) {
        *dstindex++ = *srcindex++;
      }
      srcindex = sceStart;
    }
    for (; numToDo > 0; --numToDo) {
      *dstindex++ = *srcindex++;
    }
    *sce = srcindex;
    *dst = dstindex;
    return;
}

static int convolve(CSOUND *csound, CONVOLVE *p)
{
    int    nsmpso=csound->ksmps,nsmpsi=csound->ksmps,nsmpso_sav,outcnt_sav;
    int    nchm1 = p->nchanls - 1,chn;
    int32  i,j;
    MYFLT  *ar[4];
    MYFLT  *ai = p->ain;
    MYFLT  *fftbufind;
    int32  outcnt = p->outcnt;
    int32  incount=p->incount;
    int32  Hlen = p->Hlen;
    int32  Hlenm1 = Hlen - 1;
    int32  obufsiz = p->obufsiz;
    MYFLT  *outhead = NULL;
    MYFLT  *outail = p->outail;
    MYFLT  *olap;
    MYFLT  *X;
    int32  Hlenpadded = p->Hlenpadded;
    MYFLT  scaleFac;

    scaleFac = csound->GetInverseRealFFTScale(csound, (int) Hlenpadded);
    ar[0] = p->ar1;
    ar[1] = p->ar2;
    ar[2] = p->ar3;
    ar[3] = p->ar4;

    if (p->auxch.auxp==NULL) goto err1;
  /* First dump as much pre-existing audio in output buffer as possible */
    if (outcnt > 0) {
      if (outcnt <= csound->ksmps)
        i = outcnt;
      else
        i = csound->ksmps;
      nsmpso -= i; outcnt -= i;
      for (chn = nchm1;chn >= 0;chn--) {
        outhead = p->outhead + chn*obufsiz;
        writeFromCircBuf(&outhead,&ar[chn],p->outbuf+chn*obufsiz,
                         p->obufend+chn*obufsiz,i);
      }
      p->outhead = outhead;
    }
    while (nsmpsi > 0) {
      /* Read input audio and place into work buffer. */

      fftbufind = p->fftbuf + incount;
      if ((incount + nsmpsi) <= Hlen)
        i = nsmpsi;
      else
        i = Hlen - incount;
      nsmpsi -= i;
      incount += i;
      while (i--)
        *fftbufind++ = scaleFac * *ai++;
      if (incount == Hlen) {
        /* We have enough audio for a convolution. */
        incount = 0;
        /* FFT the input (to create X) */
        /*csound->Message(csound, "CONVOLVE: ABOUT TO FFT\n"); */
        csound->RealFFT(csound, p->fftbuf, (int) Hlenpadded);
        p->fftbuf[Hlenpadded] = p->fftbuf[1];
        p->fftbuf[1] = p->fftbuf[Hlenpadded + 1L] = FL(0.0);
        /* save the result if multi-channel */
        if (nchm1) {
          fftbufind = p->fftbuf;
          X = p->X;
          for (i = Hlenpadded + 2;i > 0;i--)
            *X++ = *fftbufind++;
        }
        nsmpso_sav = nsmpso;
        outcnt_sav = outcnt;
        for (chn = nchm1;chn >= 0;chn--) {
          outhead = p->outhead + chn*obufsiz;
          outail = p->outail + chn*obufsiz;
          olap = p->olap + chn*Hlenm1;
          if (chn < nchm1) {
            fftbufind = p->fftbuf;
            X = p->X;
            for (i = Hlenpadded + 2;i> 0;i--)
              *fftbufind++ = *X++;
          }
          /*csound->Message(csound, "CONVOLVE: ABOUT TO MULTIPLY\n");  */
          /* Multiply H * X, point for point */

          {
            MYFLT *a, *b, re, im;
            int   i;
            a = (MYFLT*) p->H + (int) (chn * (Hlenpadded + 2));
            b = (MYFLT*) p->fftbuf;
            for (i = 0; i <= (int) Hlenpadded; i += 2) {
              re = a[i + 0] * b[i + 0] - a[i + 1] * b[i + 1];
              im = a[i + 0] * b[i + 1] + a[i + 1] * b[i + 0];
              b[i + 0] = re;
              b[i + 1] = im;
            }
          }

          /*csound->Message(csound, "CONVOLVE: ABOUT TO IFFT\n"); */
          /* Perform inverse FFT on X */

          p->fftbuf[1] = p->fftbuf[Hlenpadded];
          p->fftbuf[Hlenpadded] = p->fftbuf[Hlenpadded + 1L] = FL(0.0);
          csound->InverseRealFFT(csound, p->fftbuf, (int) Hlenpadded);

          /* Take the first Hlen output samples and output them to
             either the real audio output buffer or the local circular
             buffer */
          nsmpso = nsmpso_sav;
          outcnt = outcnt_sav;
          fftbufind = p->fftbuf;
          if ( (nsmpso > 0)&&(outcnt == 0) ) {
      /*    csound->Message(csound, "Outputting to audio buffer proper\n");*/
            /* space left in output buffer, and nothing currently in circular
               buffer, so write as much as possible to output buffer first */
            if (nsmpso >= Hlenm1) {
              nsmpso -= Hlenm1;
              for (i=Hlenm1;i > 0;--i)
                *ar[chn]++ = *fftbufind++ + *olap++;
              if (nsmpso > 0) {
                *ar[chn]++ = *fftbufind++;
                --nsmpso;
              }
            }
            else {
              for (;nsmpso > 0;--nsmpso)
                *ar[chn]++ = *fftbufind++ + *olap++;
            }
          }
/* Any remaining output must go into circular buffer */
/*csound->Message(csound, "Outputting to circ. buffer\n");*/
          i = Hlen - (fftbufind - p->fftbuf);
          outcnt += i;
          i--; /* do first Hlen -1 samples with overlap */
          j = p->obufend+chn*obufsiz - outail + 1;
          if (i >= j) {
            i -= j;
            for (;j > 0;--j)
              *outail++ = *fftbufind++ + *olap++;
            outail = p->outbuf+chn*obufsiz;
          }
          for (;i > 0;--i)
            *outail++ = *fftbufind++ + *olap++;
/*  just need to do sample at Hlen now */
          *outail++ = *fftbufind++;
          if (outail > p->obufend+chn*obufsiz)
            outail = p->outbuf+chn*obufsiz;

/*  Pad the rest to zero, and save first remaining (Hlen - 1) to overlap
    buffer */
          olap = p->olap+chn*Hlenm1;
          for (i = Hlenm1;i > 0;--i) {
            *olap++ = *fftbufind;
            *fftbufind++ = FL(0.0);
          }
          olap = p->olap+chn*Hlenm1;
    /* Now pad the rest to zero as well. In theory, this shouldn't be
       necessary, however it's conceivable that rounding errors may
       creep in, and these cells won't be exactly zero. So, let's
       make absolutely sure */
          for (i = Hlenpadded - (Hlen+Hlenm1);i > 0;--i)
            *fftbufind++ = FL(0.0);
        } /* end main for loop */
        p->outhead = outhead;
        p->outail = outail;
      }
    } /* end while */

/* update state in p */
    p->incount = incount;
    p->outcnt = outcnt;
    p->outhead = outhead;
    p->outail = outail;
    return OK;
 err1:
    return csound->PerfError(csound, Str("convolve: not initialised"));
}

/* partitioned (low latency) overlap-save convolution.
   we break up the IR into separate blocks, then perform
   an FFT on each partition.  For this reason we ONLY accept
   soundfiles as input, and do all of the traditional 'cvanal'
   processing at i-time.  it would be nice to eventually
   have cvanal create a partitioned format, which in turn would
   allow this opcode to accept .con files.
   -ma++ april 2004 */

static int pconvset(CSOUND *csound, PCONVOLVE *p)
{
    int     channel = (*(p->channel) <= 0 ? ALLCHNLS : (int) *(p->channel));
    SNDFILE *infd;
    SOUNDIN IRfile;
    MYFLT   *inbuf, *fp1,*fp2;
    int32    i, j, read_in, part;
    MYFLT   *IRblock;
    MYFLT   ainput_dur, scaleFac;
    MYFLT   partitionSize;

    /* IV - 2005-04-06: fixed bug: was uninitialised */
    memset(&IRfile, 0, sizeof(SOUNDIN));
    /* open impulse response soundfile [code derived from SAsndgetset()] */
    IRfile.skiptime = FL(0.0);
    csound->strarg2name(csound, IRfile.sfname, p->ifilno, "soundin.",
                                p->XSTRCODE);
    IRfile.sr = 0;
    if (UNLIKELY(channel < 1 || ((channel > 4) && (channel != ALLCHNLS)))) {
      return csound->InitError(csound, Str("channel request %d illegal"), channel);
    }
    IRfile.channel = channel;
    IRfile.analonly = 1;
    if (UNLIKELY((infd = csound->sndgetset(csound, &IRfile)) == NULL)) {
      return csound->InitError(csound, Str("pconvolve: error while impulse file"));
    }

    if (UNLIKELY(IRfile.framesrem < 0)) {
      csound->Warning(csound, Str("undetermined file length, "
                                  "will attempt requested duration"));
      ainput_dur = FL(0.0);     /* This is probably wrong -- JPff */
    }
    else {
        IRfile.getframes = IRfile.framesrem;
        ainput_dur = (MYFLT) IRfile.getframes / IRfile.sr;
      }

    csound->Warning(csound, Str("analyzing %ld sample frames (%3.1f secs)\n"),
                            (long) IRfile.getframes, ainput_dur);

    p->nchanls = (channel != ALLCHNLS ? 1 : IRfile.nchanls);
    if (UNLIKELY(p->nchanls != p->OUTOCOUNT)) {
      return csound->InitError(csound, Str("PCONVOLVE: number of output channels "
                                           "not equal to input channels"));
    }

    if (UNLIKELY(IRfile.sr != csound->esr)) {
      /* ## RWD suggests performing sr conversion here! */
      csound->Warning(csound, "IR srate != orch's srate");
    }

    /* make sure the partition size is nonzero and a power of 2  */
    if (*p->partitionSize <= 0)
      partitionSize = csound->oparms->outbufsamps / csound->nchnls;
    else
      partitionSize = *p->partitionSize;

    p->Hlen = 1;
    while (p->Hlen < partitionSize)
      p->Hlen <<= 1;

    p->Hlenpadded = 2*p->Hlen;

    /* determine the number of partitions */
    p->numPartitions = CEIL((MYFLT)(IRfile.getframes) / (MYFLT)p->Hlen);

    /* set up FFT tables */
    inbuf = (MYFLT *) csound->Malloc(csound,
                                     p->Hlen * p->nchanls * sizeof(MYFLT));
    csound->AuxAlloc(csound, p->numPartitions * (p->Hlenpadded + 2) *
             sizeof(MYFLT) * p->nchanls, &p->H);
    IRblock = (MYFLT *)p->H.auxp;

    /* form each partition and take its FFT */
    for (part = 0; part < p->numPartitions; part++) {
      /* get the block of input samples and normalize -- soundin code
         handles finding the right channel */
      if (UNLIKELY((read_in = csound->getsndin(csound, infd, inbuf,
                                               p->Hlen*p->nchanls, &IRfile)) <= 0))
        csound->Die(csound, Str("PCONVOLVE: less sound than expected!"));

      /* take FFT of each channel */
      scaleFac = csound->dbfs_to_float
                 * csound->GetInverseRealFFTScale(csound, (int) p->Hlenpadded);
      for (i = 0; i < p->nchanls; i++) {
        fp1 = inbuf + i;
        fp2 = IRblock;
        for (j = 0; j < read_in/p->nchanls; j++) {
          *fp2++ = *fp1 * scaleFac;
          fp1 += p->nchanls;
        }
        csound->RealFFT(csound, IRblock, (int) p->Hlenpadded);
        IRblock[p->Hlenpadded] = IRblock[1];
        IRblock[1] = IRblock[p->Hlenpadded + 1L] = FL(0.0);
        IRblock += (p->Hlenpadded + 2);
      }
    }

    csound->Free(csound, inbuf);
    csound->FileClose(csound, IRfile.fd);

    /* allocate the buffer saving recent input samples */
    csound->AuxAlloc(csound, p->Hlen * sizeof(MYFLT), &p->savedInput);
    p->inCount = 0;

    /* allocate the convolution work buffer */
    csound->AuxAlloc(csound, (p->Hlenpadded+2) * sizeof(MYFLT), &p->workBuf);
    p->workWrite = (MYFLT *)p->workBuf.auxp + p->Hlen;

    /* allocate the buffer holding recent past convolutions */
    csound->AuxAlloc(csound, (p->Hlenpadded+2) * p->numPartitions
             * p->nchanls * sizeof(MYFLT), &p->convBuf);
    p->curPart = 0;

    /* allocate circular output sample buffer */
    p->outBufSiz = sizeof(MYFLT) * p->nchanls *
      (p->Hlen >= csound->ksmps ? p->Hlenpadded : 2*csound->ksmps);
    csound->AuxAlloc(csound, p->outBufSiz, &p->output);
    p->outRead = (MYFLT *)p->output.auxp;

    /* if ksmps < hlen, we have to pad initial output to prevent a possible
       empty ksmps pass after a few initial generated buffers.  There is
       probably an equation to figure this out to reduce the delay, but
       I can't seem to figure it out */
    if (p->Hlen > csound->ksmps) {
      p->outCount = p->Hlen + csound->ksmps;
      p->outWrite = p->outRead + (p->nchanls * p->outCount);
    }
    else {
      p->outCount = 0;
      p->outWrite = p->outRead;
    }
    return OK;
}

static int pconvolve(CSOUND *csound, PCONVOLVE *p)
{
    int    nsmpsi = csound->ksmps;
    MYFLT  *ai = p->ain;
    MYFLT  *buf;
    MYFLT  *input = (MYFLT*) p->savedInput.auxp, *workWrite = p->workWrite;
    MYFLT  *a1 = p->ar1, *a2 = p->ar2, *a3 = p->ar3, *a4 = p->ar4;
    int32  i, j, count = p->inCount;
    int32  hlenpaddedplus2 = p->Hlenpadded+2;

    while (nsmpsi-- > 0) {
      /* Read input audio and place into buffer. */
      input[count++] = *workWrite++ = *ai++;

      /* We have enough audio for a convolution. */
      if (count == p->Hlen) {
        MYFLT *dest = (MYFLT*) p->convBuf.auxp
                      + p->curPart * (p->Hlenpadded + 2) * p->nchanls;
        MYFLT *h = (MYFLT*) p->H.auxp;
        MYFLT *workBuf = (MYFLT*) p->workBuf.auxp;

        /* FFT the input (to create X) */
        *workWrite = FL(0.0); /* zero out nyquist bin from last fft result
                           - maybe is ignored for input(?) but just in case.. */
        csound->RealFFT(csound, workBuf, (int) p->Hlenpadded);
        workBuf[p->Hlenpadded] = workBuf[1];
        workBuf[1] = workBuf[p->Hlenpadded + 1L] = FL(0.0);

        /* for every IR partition convolve and add to previous convolves */
        for (i = 0; i < p->numPartitions*p->nchanls; i++) {
          MYFLT *src = workBuf;
          int n;
          for (n = 0; n <= (int) p->Hlenpadded; n += 2) {
            dest[n + 0] += (h[n + 0] * src[n + 0]) - (h[n + 1] * src[n + 1]);
            dest[n + 1] += (h[n + 1] * src[n + 0]) + (h[n + 0] * src[n + 1]);
          }
          h += n; dest += n;
          if (dest == (MYFLT*)p->convBuf.endp)
            dest = (MYFLT*)p->convBuf.auxp;
        }

        /* Perform inverse FFT of the ondeck partion block */
        buf = (MYFLT*) p->convBuf.auxp
              + p->curPart * p->nchanls * hlenpaddedplus2;
        for (i = 0; i < p->nchanls; i++) {
          MYFLT *bufp;
          bufp = buf + i * hlenpaddedplus2;
          bufp[1] = bufp[p->Hlenpadded];
          bufp[p->Hlenpadded] = bufp[p->Hlenpadded + 1L] = FL(0.0);
          csound->InverseRealFFT(csound, bufp, (int) p->Hlenpadded);
        }
        /* We only take only the last Hlen output samples so we first zero out
           the first half for next time, then we copy the rest to output buffer
         */
        for (j = 0; j < p->nchanls; j++) {
          MYFLT *outp = p->outWrite + j;
          for (i = 0; i < p->Hlen; i++)
            *buf++ = FL(0.0);
          for (i = 0; i < p->Hlen; i++) {
            *outp = *buf;
            *buf++ = FL(0.0);
            outp += p->nchanls;
            if (outp >= (MYFLT *)p->output.endp)
              outp = (MYFLT *)p->output.auxp + j;
          }
          buf += 2;
        }
        p->outWrite += p->Hlen*p->nchanls;
        if (p->outWrite >= (MYFLT *)p->output.endp)
          p->outWrite -= p->outBufSiz/sizeof(MYFLT);
        p->outCount += p->Hlen;
        if (++p->curPart == p->numPartitions)
          /* advance to the next partition */
          p->curPart = 0;
        /* copy the saved input into the work buffer for next time around */
        memcpy(p->workBuf.auxp, input, p->Hlen * sizeof(MYFLT));
        count = 0;
        workWrite = (MYFLT *)p->workBuf.auxp + p->Hlen;
      }
    } /* end while */

    /* copy to output if we have enough samples [we always should
       except the first Hlen samples] */
    if (p->outCount >= csound->ksmps) {
      int n;
      p->outCount -= csound->ksmps;
      for (n=0; n < csound->ksmps; n++) {
        switch (p->nchanls) {
        case 1:
          *a1++ = *p->outRead++;
          break;
        case 2:
          *a1++ = *p->outRead++;
          *a2++ = *p->outRead++;
          break;
        case 3:
          *a1++ = *p->outRead++;
          *a2++ = *p->outRead++;
          *a3++ = *p->outRead++;
          break;
        case 4:
          *a1++ = *p->outRead++;
          *a2++ = *p->outRead++;
          *a3++ = *p->outRead++;
          *a4++ = *p->outRead++;
          break;
        }
        if (p->outRead == p->output.endp)
          p->outRead = p->output.auxp;
      }
    }

    /* update struct */
    p->inCount = count;
    p->workWrite = workWrite;
    return OK;
}

static OENTRY localops[] = {
    { "convolve", sizeof(CONVOLVE),   5, "mmmm", "aTo",
            (SUBR) cvset,     (SUBR) NULL,    (SUBR) convolve   },
    { "convle",   sizeof(CONVOLVE),   5, "mmmm", "aTo",
            (SUBR) cvset,     (SUBR) NULL,    (SUBR) convolve   },
    { "pconvolve",sizeof(PCONVOLVE),  5, "mmmm", "aToo",
            (SUBR) pconvset,  (SUBR) NULL,    (SUBR) pconvolve  }
};

int ugens9_init_(CSOUND *csound)
{
    return csound->AppendOpcodes(csound, &(localops[0]),
                                 (int) (sizeof(localops) / sizeof(OENTRY)));
}

