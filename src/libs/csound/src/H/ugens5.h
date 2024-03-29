/*
    ugens5.h:

    Copyright (C) 1991 Barry Vercoe, John ffitch, Gabriel Maldonado

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

#include "lpc.h"        /*                                              UGENS5.H        */

typedef struct {
        OPDS    h;
        MYFLT   *kr, *ksig, *ihtim, *isig;
        double   c1, c2, yt1;
} PORT;

typedef struct {
        OPDS    h;
        MYFLT   *ar, *asig, *khp, *istor;
        double  c1, c2, yt1, prvhp;
} TONE;

typedef struct {
        OPDS    h;
        MYFLT   *ar, *asig, *kcf, *kbw, *iscl, *istor;
        int     scale;
        double  c1, c2, c3, yt1, yt2, cosf, prvcf, prvbw;
} RESON;

typedef struct {
        OPDS    h;
        MYFLT   *ar, *asig, *khp, *ord, *istor;
        double  c1, c2, *yt1, prvhp;
        int loop;
        AUXCH   aux;
} TONEX;

typedef struct {
        OPDS    h;
        MYFLT   *ar, *asig, *kcf, *kbw, *ord, *iscl, *istor;
        int     scale, loop;
        double  c1, c2, c3, *yt1, *yt2, cosf, prvcf, prvbw;
        AUXCH   aux;
} RESONX;

typedef struct {
        OPDS    h;
        MYFLT   *krmr, *krmo, *kerr, *kcps, *ktimpt, *ifilno, *inpoles, *ifrmrate;
        int32   headlen, npoles, nvals, lastfram16, lastmsg;
        MYFLT   kcoefs[MAXPOLES*2], framrat16;
        int     storePoles ;
        MEMFIL  *mfp;
} LPREAD;

typedef struct {
        OPDS    h;
        MYFLT   *ar, *asig;
        MYFLT   circbuf[MAXPOLES<<1], *circjp, *jp2lim;
        LPREAD  *lpread;
} LPRESON;

typedef struct {
        OPDS    h;
        MYFLT   *kcf,*kbw, *kfor;
        LPREAD  *lpread;
} LPFORM;

typedef struct {
        OPDS    h;
        MYFLT   *ar, *asig, *kfrqratio;
        MYFLT   past[MAXPOLES], prvratio, d, prvout;
        LPREAD  *lpread;
} LPFRESON;

typedef struct {
        OPDS    h;
        MYFLT   *kr, *asig, *ihp, *istor;
        double   c1, c2, prvq;
} RMS;

typedef struct {
        OPDS    h;
        MYFLT   *ar, *asig, *krms, *ihp, *istor;
        double  c1, c2, prvq, prva;
} GAIN;

typedef struct {
        OPDS    h;
        MYFLT   *ar, *asig, *csig, *ihp, *istor;
        double  c1, c2, prvq, prvr, prva;
} BALANCE;

typedef struct {
        OPDS    h;
        MYFLT   *islotnum ; /* Assume sizeof(int)== sizeof(MYFLT) */
} LPSLOT ;

typedef struct {
        OPDS    h;
        MYFLT   *islot1 ;
        MYFLT   *islot2 ; /* Assume sizeof(pointer)== sizeof(MYFLT) */
        MYFLT   *kmix  ;
        MYFLT   *fpad[5]; /* Pad for kcoef correctly put (Mighty dangerous) */
        int32    lpad,npoles ;
        LPREAD  *lp1,*lp2 ;
        int32    lastmsg;
        MYFLT   kcoefs[MAXPOLES*2], framrat16;
        int             storePoles ;
} LPINTERPOL ;
