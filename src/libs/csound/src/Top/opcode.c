/*
    opcode.c:

    Copyright (C) 1997 John ffitch
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

                                /* OPCODE.C */
                                /* Print opcodes in system */

                                /* John ffitch -- 26 Jan 97 */
                                /*  4 april 02 -- ma++ */
                                /*  restructure to retrieve externally  */
#include "csoundCore.h"
#include <ctype.h>

static int opcode_cmp_func(const void *a, const void *b)
{
    opcodeListEntry *ep1 = (opcodeListEntry*) a;
    opcodeListEntry *ep2 = (opcodeListEntry*) b;
    int             retval;

    if ((retval = strcmp(ep1->opname, ep2->opname)) != 0)
      return retval;
    if ((retval = strcmp(ep1->outypes, ep2->outypes)) != 0)
      return retval;
    if ((retval = strcmp(ep1->intypes, ep2->intypes)) != 0)
      return retval;
    if (ep1 < ep2)
      return -1;
    if (ep1 > ep2)
      return 1;

    return 0;
}

/**
 * Gets an alphabetically sorted list of all opcodes.
 * Should be called after externals are loaded by csoundCompile().
 * Returns the number of opcodes, or a negative error code on failure.
 * Make sure to call csoundDisposeOpcodeList() when done with the list.
 */

PUBLIC int csoundNewOpcodeList(CSOUND *csound, opcodeListEntry **lstp)
{
    void    *lst;
    OENTRY  *ep;
    char    *s;
    size_t  nBytes = (size_t) 0;
    int     i, cnt = 0;

    (*lstp) = NULL;
    i = csoundLoadAllPluginOpcodes(csound);
    if (i != 0)
      return i;
    ep = (OENTRY*) csound->opcodlst;
    if (UNLIKELY(ep == NULL))
      return -1;
    /* count the number of opcodes, and bytes to allocate */
    for ( ; ep < (OENTRY*) csound->oplstend; ep++) {
      if (ep->opname != NULL &&
          ep->opname[0] != '\0' && isalpha(ep->opname[0]) &&
          ep->outypes != NULL && ep->intypes != NULL) {
        cnt++;
        nBytes += sizeof(opcodeListEntry);
        for (i = 0; ep->opname[i] != '\0' && ep->opname[i] != '.'; i++)
          ;
        nBytes += (size_t) i;
        nBytes += strlen(ep->outypes);
        nBytes += strlen(ep->intypes);
        nBytes += 3;    /* for null characters */
      }
    }
    nBytes += sizeof(opcodeListEntry);
    /* allocate memory for opcode list */
    lst = malloc(nBytes);
    if (UNLIKELY(lst == NULL))
      return CSOUND_MEMORY;
    (*lstp) = (opcodeListEntry*) lst;
    /* store opcodes in list */
    ep = (OENTRY*) csound->opcodlst;
    s = (char*) lst + ((int) sizeof(opcodeListEntry) * (cnt + 1));
    for (cnt = 0; ep < (OENTRY*) csound->oplstend; ep++) {
      if (ep->opname != NULL &&
          ep->opname[0] != '\0' && isalpha(ep->opname[0]) &&
          ep->outypes != NULL && ep->intypes != NULL) {
        for (i = 0; ep->opname[i] != '\0' && ep->opname[i] != '.'; i++)
          s[i] = ep->opname[i];
        s[i++] = '\0';
        ((opcodeListEntry*) lst)[cnt].opname = s;
        s += i;
        strcpy(s, ep->outypes);
        ((opcodeListEntry*) lst)[cnt].outypes = s;
        s += ((int) strlen(ep->outypes) + 1);
        strcpy(s, ep->intypes);
        ((opcodeListEntry*) lst)[cnt].intypes = s;
        s += ((int) strlen(ep->intypes) + 1);
        cnt++;
      }
    }
    ((opcodeListEntry*) lst)[cnt].opname = NULL;
    ((opcodeListEntry*) lst)[cnt].outypes = NULL;
    ((opcodeListEntry*) lst)[cnt].intypes = NULL;
    /* sort list */
    qsort(lst, (size_t) cnt, sizeof(opcodeListEntry), opcode_cmp_func);
    /* return the number of opcodes */
    return cnt;
}

PUBLIC void csoundDisposeOpcodeList(CSOUND *csound, opcodeListEntry *lst)
{
    (void) csound;
    free(lst);
}

void list_opcodes(CSOUND *csound, int level)
{
    opcodeListEntry *lst;
    const char      *sp = "                    ";   /* length should be 20 */
    int             j, k;
    int             cnt, len = 0, xlen = 0;

    cnt = csoundNewOpcodeList(csound, &lst);
    if (UNLIKELY(cnt <= 0)) {
      csound->ErrorMsg(csound, Str("Error creating opcode list"));
      return;
    }
    csound->Message(csound, Str("%d opcodes\n"), cnt);

    for (j = 0, k = -1; j < cnt; j++) {
      if (level == 0) {                         /* Print in 4 columns */
        if (j > 0 && strcmp(lst[j - 1].opname, lst[j].opname) == 0)
          continue;
        k++;
        xlen = 0;
        if (!(k & 3))
          csound->Message(csound, "\n");
        else {
          if (len > 19) {
            xlen = len - 19;
            len = 19;
          }
          csound->Message(csound, "%s", sp + len);
        }
        csound->Message(csound, "%s", lst[j].opname);
        len = (int) strlen(lst[j].opname) + xlen;
      }
      else {
        char *ans = lst[j].outypes, *arg = lst[j].intypes;
        csound->Message(csound, "%s", lst[j].opname);
        len = (int) strlen(lst[j].opname);
        if (len > 11) {
          xlen = len - 11;
          len = 11;
        }
        csound->Message(csound, "%s", sp + (len + 8));
        if (ans == NULL || *ans == '\0') ans = "(null)";
        if (arg == NULL || *arg == '\0') arg = "(null)";
        csound->Message(csound, "%s", ans);
        len = (int) strlen(ans) + xlen;
        len = (len < 11 ? len : 11);
        xlen = 0;
        csound->Message(csound, "%s", sp + (len + 8));
        csound->Message(csound, "%s\n", arg);
      }
    }
    csound->Message(csound, "\n");
    csoundDisposeOpcodeList(csound, lst);
}

