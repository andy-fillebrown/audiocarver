/*
    window.c:

    Copyright (C) 1991 Barry Vercoe, John ffitch

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

#include "csoundCore.h"                         /*      WINDOW.C        */
#include "cwindow.h"                            /*  graph window mgr    */
#include "winEPS.h"                             /* PostSCript routines  */
#include "namedins.h"                           /*  dpwe 16may90        */

extern void MakeAscii(CSOUND *, WINDAT *, const char *);
extern void DrawAscii(CSOUND *, WINDAT *);
extern void KillAscii(CSOUND *, WINDAT *);

/* somewhere to invoke for no display */

static void DummyFn1(CSOUND *csound, WINDAT *p, const char *s)
{
    IGN(csound); IGN(p); IGN(s);
}

/* somewhere to invoke for no display */

static void DummyFn2(CSOUND *csound, WINDAT *p)
{
    IGN(csound); IGN(p);
}

/* somewhere to invoke that returns 1 (!) for dummy exit fn */
/* Used to be 1 but seems silly (MR/JPff) */

static int DummyFn3(CSOUND *csound)
{
    IGN(csound);
    return 0;
}

/* initial proportions */

static void MkXYDummy(CSOUND *csound, XYINDAT *wdptr, MYFLT x, MYFLT y)
{
    IGN(csound);
    wdptr->windid = 0;  /* xwin = MakeWindow(1);        */
    wdptr->down = 0;    /* by def released after Make */

    wdptr->m_x = 0;
    wdptr->m_y = 0;
    wdptr->x = x;
    wdptr->y = y;
}

static void RdXYDummy(CSOUND *csound, XYINDAT *wdptr)
{
    IGN(csound);
    IGN(wdptr);
}

/* called once on initialisation of program to */
/*  choose between teletype or bitmap graphics */

void dispinit(CSOUND *csound)
{
    OPARMS  *O = csound->oparms;

    if (O->displays && !(O->graphsoff || O->postscript)) {
      if (!csound->isGraphable_)
      find_opcode(csound, "FLrun");       /* load FLTK for displays */
      if (csound->isGraphable_)
        return;         /* provided by window driver: is this session able? */
    }
    if (!O->displays) {
      csound->Message(csound, Str("displays suppressed\n"));
      csound->csoundMakeGraphCallback_ = DummyFn1;
      csound->csoundDrawGraphCallback_ = DummyFn2;
      csound->csoundKillGraphCallback_ = DummyFn2;
    }
    else {
      csound->Message(csound, Str("graphics %s, ascii substituted\n"),
                      ((O->graphsoff || O->postscript) ?
                       Str("suppressed")
                       : Str("not supported on this terminal")));
      csound->csoundMakeGraphCallback_ = MakeAscii;
      csound->csoundDrawGraphCallback_ = DrawAscii;
      csound->csoundKillGraphCallback_ = KillAscii;
    }
    csound->csoundMakeXYinCallback_ = MkXYDummy;
    csound->csoundReadXYinCallback_ = RdXYDummy;
    csound->csoundKillXYinCallback_ = RdXYDummy;
    csound->csoundExitGraphCallback_ = DummyFn3;
}

void dispset(CSOUND *csound,            /* setup a new window       */
             WINDAT *wdptr,             /*   & init the data struct */
             MYFLT  *fdata,
             int32  npts,
             char   *caption,
             int    waitflg,
             char   *label)
{
    char *s = caption;
    char *t = wdptr->caption;
    char *tlim = t + CAPSIZE - 1;
    if (!csound->oparms->displays) return;    /* return if displays disabled */
    wdptr->fdata    = fdata;            /* init remainder of data structure   */
    wdptr->npts     = npts;
    while (*s != '\0' && t < tlim)
      *t++ = *s++;                      /*  (copy the caption) */
    *t = '\0';
    if (!wdptr->windid) {   /* if no window defined for this str, create one */
      csound->csoundMakeGraphCallback_(csound, wdptr, label);
      if (csound->oparms->postscript)
        PS_MakeGraph(csound, wdptr, label); /* open PS file + write header    */
    }

    wdptr->waitflg  = waitflg;
    wdptr->polarity = (int16)NOPOL;
    wdptr->max      = FL(0.0);
    wdptr->min      = FL(0.0);
    wdptr->absmax   = FL(0.0);
    wdptr->oabsmax  = FL(0.0);
    wdptr->danflag  = 0;
}

int dispexit(CSOUND *csound)
{
    if (csound->oparms->postscript)
      PS_ExitGraph(csound);     /* Write trailer to PostScript file  */
    /* prompt for exit from last active window */
    return csound->csoundExitGraphCallback_(csound);
}

void display(CSOUND *csound, WINDAT *wdptr)   /* prepare a MYFLT array, then  */
                                              /*   call the graphing fn       */
{
    MYFLT   *fp, *fplim;
    MYFLT   max, min, absmax, fval;
    int     pol;

    if (!csound->oparms->displays)  return;   /* displays disabled? return */
    fp = wdptr->fdata;
    fplim = fp + wdptr->npts;
    for (max = *fp++, min = max; fp < fplim; ) {  /* find max & min values */
      if ((fval = *fp++) > max)       max = fval;
      else if (fval < min)            min = fval;
    }
    absmax = (-min > max )? (-min):max;
    wdptr->max    = max;                 /* record most pos and most */
    wdptr->min    = min;                 /*  neg this array of data  */
    wdptr->absmax = absmax;              /* record absmax this data  */
    if (absmax > wdptr->oabsmax)
      wdptr->oabsmax = absmax;           /* & absmax over life of win */

    pol = wdptr->polarity;     /* adjust polarity flg for life of win */
    if (pol == (int16)NOPOL)  {
      if (max > FL(0.0) && min < FL(0.0))      pol = (int16)BIPOL;
      else if (max <= FL(0.0) && min <FL(0.0)) pol = (int16)NEGPOL;
      else                                     pol = (int16)POSPOL;
    }
    else if (pol == (int16)POSPOL && min < FL(0.0)) pol = (int16)BIPOL;
    else if (pol == (int16)NEGPOL && max > FL(0.0)) pol = (int16)BIPOL;
    wdptr->polarity = pol;

    /* now graph the function */
    csound->csoundDrawGraphCallback_(csound, wdptr);


    /* Write postscript code */
    if (csound->oparms->postscript)
      PS_DrawGraph(csound, wdptr);
}
