/*  ifd.c pvsifd

(c) Victor Lazzarini, 2005

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

/* PVSIFD

Instantaneous Frequency Distribution analysis, plus magnitude
and phase output.

ffrs, fphs pvsifd ain, ifftsize, ihopsize, iwintype[,iscal]

ffrs - AMP_FREQ signal
fphs - AMP_PHASE signal (unwrapped phase)

ain - input
ifftsize - fftsize (must be integer multiple of hopsize)
ihopsize - hopsize
iwintype - O:hamming; 1: hanning,
iscal - magnitude scaling (defaults to 0)

*/

#include "csdl.h"
#include "pstream.h"

typedef struct _ifd {
    OPDS    h;
/* outputs */
    PVSDAT *fout1, *fout2;
/* inputs */
    MYFLT  *in, *size, *hop, *type, *scal;
/* data */
    AUXCH   sigframe, diffsig, win, diffwin;
    AUXCH   counter;
    int     fftsize, hopsize, wintype, frames, cnt;
    double  fund, factor;
    MYFLT   norm, g;
} IFD;

static int ifd_init(CSOUND * csound, IFD * p)
{

    int     fftsize, hopsize, frames;
    int    *counter, wintype, i;
    MYFLT  *winf, *dwinf;
    double  alpha = 0.0, fac;

    p->cnt = 0;
    fftsize = p->fftsize = (int) *p->size;
    hopsize = p->hopsize = (int) *p->hop;
    p->g = *p->scal;
    wintype = p->wintype = (int) *p->type;
    frames = fftsize / hopsize;

    if (UNLIKELY((frames - (float) fftsize / hopsize) != 0.0f))
      csound->Die(csound, Str("pvsifd: fftsize should "
                              "be an integral multiple of hopsize"));

    if (UNLIKELY((fftsize & (fftsize - 1))))
      csound->Die(csound, Str("pvsifd: fftsize should be power-of-two"));

    p->frames = frames;

    if (p->sigframe.auxp == NULL ||
        frames * fftsize * sizeof(MYFLT) > (unsigned int) p->sigframe.size)
      csound->AuxAlloc(csound, frames * fftsize * sizeof(MYFLT), &p->sigframe);
    else
      memset(p->sigframe.auxp, 0, sizeof(MYFLT) * fftsize * frames);
    if (p->diffsig.auxp == NULL ||
        fftsize * sizeof(MYFLT) > (unsigned int) p->diffsig.size)
      csound->AuxAlloc(csound, fftsize * sizeof(MYFLT), &p->diffsig);
    else
      memset(p->diffsig.auxp, 0, sizeof(MYFLT) * fftsize);
    if (p->diffwin.auxp == NULL ||
        fftsize * sizeof(MYFLT) > (unsigned int) p->diffwin.size)
      csound->AuxAlloc(csound, fftsize * sizeof(MYFLT), &p->diffwin);
    if (p->win.auxp == NULL ||
        fftsize * sizeof(MYFLT) > (unsigned int) p->win.size)
      csound->AuxAlloc(csound, fftsize * sizeof(MYFLT), &p->win);
    if (p->counter.auxp == NULL ||
        frames * sizeof(int) > (unsigned int) p->counter.size)
      csound->AuxAlloc(csound, frames * sizeof(int), &p->counter);
    if (p->fout1->frame.auxp == NULL ||
        (fftsize + 2) * sizeof(MYFLT) > (unsigned int) p->fout1->frame.size)
      csound->AuxAlloc(csound, (fftsize + 2) * sizeof(float), &p->fout1->frame);
    else
      memset(p->fout1->frame.auxp, 0, sizeof(MYFLT) * (fftsize + 2));
    if (p->fout2->frame.auxp == NULL ||
        (fftsize + 2) * sizeof(MYFLT) > (unsigned int) p->fout2->frame.size)
      csound->AuxAlloc(csound, (fftsize + 2) * sizeof(float), &p->fout2->frame);
    else
      memset(p->fout2->frame.auxp, 0, sizeof(MYFLT) * (fftsize + 2));
    p->fout1->N = fftsize;
    p->fout1->overlap = hopsize;
    p->fout1->winsize = fftsize;
    p->fout1->wintype = wintype;
    p->fout1->framecount = 1;
    p->fout1->format = PVS_AMP_FREQ;

    p->fout2->N = fftsize;
    p->fout2->overlap = hopsize;
    p->fout2->winsize = fftsize;
    p->fout2->wintype = wintype;
    p->fout2->framecount = 1;
    p->fout2->format = PVS_AMP_PHASE;

    counter = (int *) p->counter.auxp;
    for (i = 0; i < frames; i++)
      counter[i] = i * hopsize;

    winf = (MYFLT *) p->win.auxp;
    dwinf = (MYFLT *) p->diffwin.auxp;

    switch (wintype) {
    case PVS_WIN_HAMMING:
      alpha = 0.54;
      break;
    case PVS_WIN_HANN:
      alpha = 0.5;
      break;
    default:
      csound->Die(csound, Str("pvsifd: unsupported value for iwintype\n"));
      break;
    }
    fac = TWOPI / (fftsize - 1.0);

    for (i = 0; i < fftsize; i++)
      winf[i] = (MYFLT) (alpha - (1.0 - alpha) * cos(fac * i));

    p->norm = 0;
    for (i = 0; i < fftsize; i++) {
      dwinf[i] = winf[i] - (i + 1 < fftsize ? winf[i + 1] : FL(0.0));
      p->norm += winf[i];
    }

    p->factor = csound->esr / TWOPI_F;
    p->fund = csound->esr / fftsize;

    return OK;
}

static void IFAnalysis(CSOUND * csound, IFD * p, MYFLT * signal)
{

    double  powerspec, da, db, a, b, ph, d, factor = p->factor, fund = p->fund;
    MYFLT   scl = p->g / p->norm;
    int     i2, i, fftsize = p->fftsize, hsize = p->fftsize / 2;
    MYFLT   tmp1, tmp2, *diffwin = (MYFLT *) p->diffwin.auxp;
    MYFLT  *win = (MYFLT *) p->win.auxp;
    MYFLT  *diffsig = (MYFLT *) p->diffsig.auxp;
    float  *output = (float *) p->fout1->frame.auxp;
    float  *outphases = (float *) p->fout2->frame.auxp;

    for (i = 0; i < fftsize; i++) {
      diffsig[i] = signal[i] * diffwin[i];
      signal[i] = signal[i] * win[i];
    }

    for (i = 0; i < hsize; i++) {
      tmp1 = diffsig[i + hsize];
      tmp2 = diffsig[i];
      diffsig[i] = tmp1;
      diffsig[i + hsize] = tmp2;

      tmp1 = signal[i + hsize];
      tmp2 = signal[i];
      signal[i] = tmp1;
      signal[i + hsize] = tmp2;
    }

    csound->RealFFT(csound, signal, fftsize);
    csound->RealFFT(csound, diffsig, fftsize);

    for (i = 2; i < fftsize; i += 2) {

      i2 = i / 2;
      a = signal[i] * scl;
      b = signal[i + 1] * scl;
      da = diffsig[i] * scl;
      db = diffsig[i + 1] * scl;
      powerspec = a * a + b * b;

      if ((outphases[i] = output[i] = (float) sqrt(powerspec)) != 0.0f) {
        output[i + 1] = ((a * db - b * da) / powerspec) * factor + i2 * fund;
        ph = (float) atan2(b, a);
        d = ph - outphases[i + 1];
        while (d > PI)
          d -= TWOPI;
        while (d < -PI)
          d += TWOPI;
        outphases[i + 1] += (float)d;
      }
      else {
        output[i + 1] = i2 * fund;
        outphases[i + 1] = 0.0f;
      }
    }
    output[0] = outphases[0] = signal[0] * scl;
    output[1] = outphases[1] = outphases[fftsize + 1] = 0.0f;
    output[fftsize] = outphases[fftsize] = signal[1] * scl;
    output[fftsize + 1] = csound->esr * FL(0.5);
    p->fout1->framecount++;
    p->fout2->framecount++;
}

static int ifd_process(CSOUND * csound, IFD * p)
{
    int     i, n;
    MYFLT  *sigin = p->in;
    MYFLT  *sigframe = (MYFLT *) p->sigframe.auxp;
    int     fftsize = p->fftsize;
    int    *counter = (int *) p->counter.auxp;
    int     ksmps = csound->ksmps;
    int     frames = p->frames;
    int     cnt = p->cnt;

    for (n = 0; n < ksmps; n++) {
      for (i = 0; i < frames; i++) {
        sigframe[i * fftsize + counter[i]] = sigin[n];
        counter[i]++;
        if (counter[i] == fftsize) {
          if (cnt < frames)
            cnt++;
          else
            IFAnalysis(csound, p, &sigframe[i * fftsize]);
          counter[i] = 0;
        }
      }
    }
    p->cnt = cnt;

    return OK;
}

static OENTRY localops[] =
  {
    { "pvsifd", sizeof(IFD), 5, "ff", "aiiip",
                                 (SUBR) ifd_init, 0, (SUBR) ifd_process}
  };

int ifd_init_(CSOUND *csound)
{
  return csound->AppendOpcodes(csound, &(localops[0]),
                               (int) (sizeof(localops) / sizeof(OENTRY)));
}

