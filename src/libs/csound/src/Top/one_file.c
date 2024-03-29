/*
    one_file.c:

    Copyright (C) 1998 John ffitch

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

#include "csoundCore.h"
#include <stdlib.h>
int mkstemp(char *);
#include <ctype.h>
#include <errno.h>
#include <stdlib.h>
#include "corfile.h"

#if defined(LINUX) || defined(__MACH__) || defined(WIN32)
#  include <sys/types.h>
#  include <sys/stat.h>
#endif

#define CSD_MAX_LINE_LEN    4096
#define CSD_MAX_ARGS        100

#  undef L_tmpnam
#  define L_tmpnam (200)

#ifndef TRUE
#  define TRUE  (1)
#endif
#ifndef FALSE
#  define FALSE (0)
#endif

/* These are used to set/clear bits in csound->tempStatus.
   If the bit is set, it indicates that the given file is
   a temporary. */
const uint32_t csOrcMask     = 1;
const uint32_t csScoInMask   = 2;
const uint32_t csScoSortMask = 4;
const uint32_t csMidiScoMask = 8;
const uint32_t csPlayScoMask = 16;

typedef struct namelst {
  char           *name;
  struct namelst *next;
} NAMELST;

typedef struct {
    NAMELST *toremove;
    char    orcname[L_tmpnam + 4];
    char    sconame[L_tmpnam + 4];
    char    midname[L_tmpnam + 4];
    int     midiSet;
    int     csdlinecount;
    char    *orcstr;
    char    *scostr;
} ONE_FILE_GLOBALS;

#define ST(x)   (((ONE_FILE_GLOBALS*) csound->oneFileGlobals)->x)

#if !defined(WIN32)
char *mytmpnam(char *name)
{
    int fd;
    char *tmpdir = getenv("TMPDIR");
    sprintf(name, "%s/csound-XXXXXX",  (tmpdir!=NULL ? tmpdir :"/tmp"));
    umask(0077); /* ensure exclusive access on buggy implementations of mkstemp */
    fd = mkstemp(name);
    close(fd);
    unlink(name);
    return (fd<0 ? NULL : name);
}
#endif


CS_NOINLINE char *csoundTmpFileName(CSOUND *csound, char *buf, const char *ext)
{
    size_t  nBytes = L_tmpnam+4;
    if (buf == NULL) {
      nBytes = (size_t) (L_tmpnam);
      if (ext != NULL && ext[0] != (char) 0)
        nBytes += strlen(ext);
      buf = csound->Malloc(csound, nBytes);
    }
    {
#if defined(LINUX) || defined(__MACH__)
      struct stat tmp;
      do {
#elif defined(WIN32)
      struct _stat tmp;
      do {
#endif
#ifndef WIN32
        //        if (UNLIKELY(mytmpnam(buf) == NULL))
        //          csound->Die(csound, Str(" *** cannot create temporary file"));
        int fd;
        char *tmpdir = getenv("TMPDIR");
        if (tmpdir != NULL && tmpdir[0] != '\0')
          snprintf(buf, nBytes, "%s/csound-XXXXXX", tmpdir);
        else
          strcpy(buf, "/tmp/csound-XXXXXX");
        umask(0077); /* ensure exclusive access on buggy i
                        mplementations of mkstemp */
        if (UNLIKELY((fd = mkstemp(buf)) < 0))
          csound->Die(csound, Str(" *** cannot create temporary file"));
        close(fd);
        unlink(buf);
#else
        {
          char  *s = (char*) csoundGetEnv(csound, "SFDIR");
          if (s == NULL)
            s = (char*) csoundGetEnv(csound, "HOME");
          s = _tempnam(s, "cs");
          if (UNLIKELY(s == NULL))
            csound->Die(csound, Str(" *** cannot create temporary file"));
          strncpy(buf, s, nBytes);
          free(s);
        }
#endif
        if (ext != NULL && ext[0] != (char) 0) {
#if !defined(LINUX) && !defined(__MACH__) && !defined(WIN32)
          char  *p;
          /* remove original extension (does not work on OS X */
          /* and may be a bad idea) */
          if ((p = strrchr(buf, '.')) != NULL)
            *p = '\0';
#endif
          strncat(buf, ext, nBytes);
        }
#ifdef __MACH__
        /* on MacOS X, store temporary files in /tmp instead of /var/tmp */
        /* (suggested by Matt Ingalls) */
        if (strncmp(buf, "/var/tmp/", 9) == 0) {
          int i = 3;
          do {
            i++;
            buf[i - 4] = buf[i];
          } while (buf[i] != (char) 0);
        }
#endif
#if defined(LINUX) || defined(__MACH__)
        /* if the file already exists, try again */
      } while (stat(buf, &tmp) == 0);
#elif defined(WIN32)
      } while (_stat(buf, &tmp) == 0);
#endif
    }

    return buf;
}

static void alloc_globals(CSOUND *csound)
{
    if (UNLIKELY(csound->oneFileGlobals == NULL)) {
      csound->oneFileGlobals = mcalloc(csound, sizeof(ONE_FILE_GLOBALS));
      /* count lines from 0 so that it adds OK to orc/sco counts */
      ST(csdlinecount) = 0;
    }
}

char *get_sconame(CSOUND *csound)
{
    alloc_globals(csound);
    return ST(sconame);
}

static char *my_fgets(CSOUND *csound, char *s, int n, FILE *stream)
{
    char *a = s;
    if (UNLIKELY(n <= 1)) return NULL;        /* best of a bad deal */
    do {
      int ch = getc(stream);
      if (ch == EOF) {                       /* error or EOF       */
        if (s == a) return NULL;             /* no chars -> leave  */
        if (ferror(stream)) a = NULL;
        break; /* add NULL even if ferror(), spec says 'indeterminate' */
      }
      if (ch == '\n' || ch == '\r') {   /* end of line ? */
        ++(ST(csdlinecount));           /* count the lines */
        *(s++) = '\n';                  /* convert */
        if (ch == '\r') {
          ch = getc(stream);
          if (ch != '\n')               /* Mac format */
            ungetc(ch, stream);
        }
        break;
      }
      *(s++) = ch;
    } while (--n > 1);
    *s = '\0';
    return a;
}

void remove_tmpfiles(CSOUND *csound)            /* IV - Feb 03 2005 */
{                               /* use one fn to delete all temporary files */
    alloc_globals(csound);
    while (ST(toremove) != NULL) {
      NAMELST *nxt = ST(toremove)->next;
#ifdef BETA
      csoundMessage(csound, Str("Removing temporary file %s ...\n"),
                            ST(toremove)->name);
#endif
      if (remove(ST(toremove)->name))
        csoundMessage(csound, Str("WARNING: could not remove %s\n"),
                              ST(toremove)->name);
      mfree(csound, ST(toremove)->name);
      mfree(csound, ST(toremove));
      ST(toremove) = nxt;
    }
}

void add_tmpfile(CSOUND *csound, char *name)    /* IV - Feb 03 2005 */
{                               /* add temporary file to delete list */
    NAMELST *tmp;
    alloc_globals(csound);
    tmp = (NAMELST*) mmalloc(csound, sizeof(NAMELST));
    tmp->name = (char*) mmalloc(csound, strlen(name) + 1);
    strcpy(tmp->name, name);
    tmp->next = ST(toremove);
    ST(toremove) = tmp;
}

/* readingCsOptions should be non-zero when readOptions() is called
   while reading the <CsOptions> tag, but zero in other cases. */
int readOptions(CSOUND *csound, FILE *unf, int readingCsOptions)
{
    char  *p;
    int   argc = 0;
    char  *argv[CSD_MAX_ARGS];
    char    buffer[CSD_MAX_LINE_LEN];

    alloc_globals(csound);
    while (my_fgets(csound, buffer, CSD_MAX_LINE_LEN, unf) != NULL) {
      p = buffer;
      /* Remove trailing spaces; rather heavy handed */
      {
        int len = strlen(p)-2;
        while (len>0 && (p[len]==' ' || p[len]=='\t')) len--;
        p[len+1] = '\n'; p[len+2] = '\0';
      }
      while (*p == ' ' || *p == '\t') p++;
      if (readingCsOptions && strstr(p, "</CsOptions>") == p) {
        return TRUE;
      }
      /**
       * Allow command options in unified CSD files
       * to begin with the Csound command, so that
       * the command line arguments can be exactly the same in unified files
       * as for regular command line invocation.
       */
      if (*p==';' || *p=='#' || *p=='\n') continue; /* empty or comment line? */
      argc = 0;
      argv[0] = p;
      while (*p==' ' || *p=='\t') p++;  /* Ignore leading space */
      if (*p=='-') {        /* Deal with case where no command name is given */
        argv[0] = "csound";
        argv[1] = p;
        argc++;
      }
      while (*p != '\0') {
        if (*p==' ' || *p=='\t') {
          *p++ = '\0';
#ifdef _DEBUG
          csoundMessage(csound, "argc=%d argv[%d]=%s\n",
                                argc, argc, argv[argc]);
#endif
          while (*p == ' ' || *p=='\t') p++;

          if (*p== '"') {
            if (argc == CSD_MAX_ARGS)
              csoundDie(csound, Str("More than %d arguments in <CsOptions>"),
                        CSD_MAX_ARGS);
            argv[++argc] = ++p;
            while (*p != '"' && *p != '\0') {
              if (*p == '\\' && *(p+1) != '\0')
                p++;
              p++;
            }
            if (*p == '"') {
              /* ETX char used to mark the limits of a string */
              *p = (isspace(*(p+1)) ? '\0' : 3);
            }
            break;
          }

          if (*p==';' ||
              *p=='#' ||
              (*p == '/' && *(p+1) == '/')) { /* Comment line? */
            *p = '\0'; break;
          }
          if (*p == '/' && *(p+1) == '*') {  /* Comment line? */
            p += 2;
          top:
            while (*p != '*' && *p != '\0') p++;
            if (*p == '*' && *(p+1)== '/') {
              p += 2; break;
            }
            if (*p=='*') {
              p++; goto top;
            }
            my_fgets(csound, buffer, CSD_MAX_LINE_LEN, unf);
            p = buffer; goto top;
          }
          if (UNLIKELY(argc == CSD_MAX_ARGS))
            csoundDie(csound, Str("More than %d arguments in <CsOptions>"),
                      CSD_MAX_ARGS);
          argv[++argc] = p;
        }
        else if (*p=='\n') {
          *p = '\0';
          break;
        }
        else if (*p=='"') {
          int is_escape = 0;
          char *old = NULL;
          *p=3; /* ETX char used to mark the limits of a string */
          while ((*p != '"' || is_escape) && *p != '\0') {
            if (is_escape)
              *old = 0x18; /* CAN char used to mark a removable character */
            is_escape = (*p == '\\' ? !is_escape : 0);
            old = p;
            p++;
          }
          if (*p == '"') {
            if (isspace(*(p+1))) {
              *p = '\0';
              break;
            }
            else {
              *p = 3;
            }
          }
        }
        p++;
      }
#ifdef _DEBUG
      csoundMessage(csound, "argc=%d argv[%d]=%s\n", argc, argc, argv[argc]);
#endif
      /*      argc++; */                  /* according to Nicola but wrong */
      /* Read an argv thing */
      if (UNLIKELY(argc == 0)) {
        if (readingCsOptions)
          csoundErrorMsg(csound, Str("Invalid arguments in <CsOptions>: %s"),
                         buffer);
        else csoundErrorMsg(csound,
                         Str("Invalid arguments in .csoundrc or -@ file: %s"),
                         buffer);
      }
      else argdecode(csound, argc, argv);
    }
    if (UNLIKELY(readingCsOptions))
      csoundErrorMsg(csound, Str("Missing end tag </CsOptions>"));
    else
      ST(csdlinecount) = 0;
 return FALSE;
}

static int createOrchestra(CSOUND *csound, FILE *unf)
{
    char  *p;
    /* FILE  *orcf; */
    /* void  *fd; */
    CORFIL *incore = corfile_create_w();
    char  buffer[CSD_MAX_LINE_LEN];

    csound->orcLineOffset = ST(csdlinecount)+1;
    while (my_fgets(csound, buffer, CSD_MAX_LINE_LEN, unf)!= NULL) {
      p = buffer;
      while (*p == ' ' || *p == '\t') p++;
      if (strstr(p, "</CsInstruments>") == p) {
        //corfile_flush(incore);
        //#ifdef ENABLE_NEW_PARSER
        if (csound->oparms->newParser) corfile_puts("\n#exit\n", incore);
        //#endif
        corfile_putc('\0', incore);
        corfile_putc('\0', incore);
        csound->orchstr = incore;
        return TRUE;
      }
      else
        corfile_puts(buffer, incore);
    }
    csoundErrorMsg(csound, Str("Missing end tag </CsInstruments>"));
    return FALSE;
}

static int createScore(CSOUND *csound, FILE *unf)
{
    char   *p;
    char   buffer[CSD_MAX_LINE_LEN];

    if (csound->scorestr == NULL)
      csound->scorestr = corfile_create_w();
    csound->scoLineOffset = ST(csdlinecount);
    while (my_fgets(csound, buffer, CSD_MAX_LINE_LEN, unf)!= NULL) {
      p = buffer;
      while (*p == ' ' || *p == '\t') p++;
      if (strstr(p, "</CsScore>") == p)
        return TRUE;
      else
        corfile_puts(buffer, csound->scorestr);
    }
    csoundErrorMsg(csound, Str("Missing end tag </CsScore>"));
    return FALSE;
}

static int createExScore(CSOUND *csound, char *p, FILE *unf)
{
    char    extname[L_tmpnam + 4];
    char *q;
    char prog[L_tmpnam + 4];
    void *fd;
    FILE  *scof;
    char    buffer[CSD_MAX_LINE_LEN];

    p = strstr(p, "bin=\"");
    if (UNLIKELY(p==NULL)) {
      csoundErrorMsg(csound, Str("Missing program in tag <CsScore>"));
      return FALSE;
    }
    q = strchr(p+5, '"');
    if (UNLIKELY(q==NULL)) {              /* No program given */
      csoundErrorMsg(csound, Str("Missing program in tag <CsScore>"));
      return FALSE;
    }
    *q = '\0';
    strcpy(prog, p+5); /* after "<CsExScore " */
    /* Generate score name */
    csoundTmpFileName(csound, ST(sconame), ".sco");
    csoundTmpFileName(csound, extname, ".ext");
    fd = csoundFileOpenWithType(csound, &scof, CSFILE_STD, extname, "w", NULL,
                                CSFTYPE_SCORE, 1);
    csound->tempStatus |= csScoInMask;
/* #ifdef _DEBUG */
    csoundMessage(csound, Str("Creating %s (%p)\n"), extname, scof);
/* #endif */
    if (UNLIKELY(fd == NULL))
      return FALSE;

    csound->scoLineOffset = ST(csdlinecount);
    while (my_fgets(csound, buffer, CSD_MAX_LINE_LEN, unf)!= NULL) {
      p = buffer;
      if (strstr(p, "</CsScore>") == p) {
        char sys[1024];
        csoundFileClose(csound, fd);
        sprintf(sys, "%s %s %s", prog, extname, ST(sconame));
        if (UNLIKELY(system(sys) != 0)) {
          csoundErrorMsg(csound, Str("External generation failed"));
          remove(extname);
          remove(ST(sconame));
          return FALSE;
        }
        remove(extname);
        if (csound->scorestr == NULL)
          csound->scorestr = corfile_create_w();
        fd = csoundFileOpen(csound, &scof, CSFILE_STD, ST(sconame), "r", NULL);
        if (UNLIKELY(fd == NULL)) {
          remove(ST(sconame));
          return FALSE;
        }
        while (my_fgets(csound, buffer, CSD_MAX_LINE_LEN, scof)!= NULL)
          corfile_puts(buffer, csound->scorestr);
        csoundFileClose(csound, fd);
        remove(ST(sconame));
        return TRUE;
      }
      else fputs(buffer, scof);
    }
    csoundErrorMsg(csound, Str("Missing end tag </CsScore>"));
    return FALSE;
}

static void read_base64(CSOUND *csound, FILE *in, FILE *out)
{
    int c;
    int n, nbits;

    n = nbits = 0;
    while ((c = getc(in)) != '=' && c != '<') {
      while (c == ' ' || c == '\t' || c == '\n' || c == '\r') {
        if (c == '\n') {               /* count lines */
          ++(ST(csdlinecount));
          c = getc(in);
        }
        else if (c == '\r') {
          ++(ST(csdlinecount));
          c = getc(in);
          if (c == '\n') c = getc(in); /* DOS format */
        }
        else c = getc(in);
      }
      if (c == '=' || c == '<' || c == EOF)
        break;
      n <<= 6;
      nbits += 6;
      if (isupper(c))
        c -= 'A';
      else if (islower(c))
        c -= ((int) 'a' - 26);
      else if (isdigit(c))
        c -= ((int) '0' - 52);
      else if (c == '+')
        c = 62;
      else if (c == '/')
        c = 63;
      else {
        csoundDie(csound, Str("Non base64 character %c(%2x)"), c, c);
      }
      n |= (c & 0x3F);
      if (nbits >= 8) {
        nbits -= 8;
        c = (n >> nbits) & 0xFF;
        n &= ((1 << nbits) - 1);
        putc(c, out);
      }
    }
    if (c == '<')
      ungetc(c, in);
    if (nbits >= 8) {
      nbits -= 8;
      c = (n >> nbits) & 0xFF;
      n &= ((1 << nbits) - 1);
      putc(c, out);
    }
    if (UNLIKELY(nbits > 0 && n != 0)) {
      csoundDie(csound, Str("Truncated byte at end of base64 stream"));
    }
}

static int createMIDI2(CSOUND *csound, FILE *unf)
{
    char  *p;
    FILE  *midf;
    void  *fd;
    char  buffer[CSD_MAX_LINE_LEN];

    /* Generate MIDI file name */
    csoundTmpFileName(csound, ST(midname), ".mid");
    fd = csoundFileOpenWithType(csound, &midf, CSFILE_STD, ST(midname), "wb", NULL,
                                CSFTYPE_STD_MIDI, 1);
    if (UNLIKELY(fd == NULL)) {
      csoundDie(csound, Str("Cannot open temporary file (%s) for MIDI subfile"),
                        ST(midname));
    }
    csound->tempStatus |= csMidiScoMask;
    read_base64(csound, unf, midf);
    csoundFileClose(csound, fd);
    add_tmpfile(csound, ST(midname));               /* IV - Feb 03 2005 */
    ST(midiSet) = TRUE;
    while (TRUE) {
      if (my_fgets(csound, buffer, CSD_MAX_LINE_LEN, unf)!= NULL) {
        p = buffer;
        while (*p == ' ' || *p == '\t') p++;
        if (strstr(p, "</CsMidifileB>") == p) {
          return TRUE;
        }
      }
    }
    csoundErrorMsg(csound, Str("Missing end tag </CsMidifileB>"));
    return FALSE;
}

static int createSample(CSOUND *csound, char *buffer, FILE *unf)
{
    int   num;
    FILE  *smpf;
    void  *fd;
    char  sampname[256];
    /* char  buffer[CSD_MAX_LINE_LEN]; */

    sscanf(buffer, "<CsSampleB filename=\"%d\">", &num);
    sprintf(sampname, "soundin.%d", num);
    if (UNLIKELY((smpf = fopen(sampname, "rb")) != NULL)) {
      fclose(smpf);
      csoundDie(csound, Str("File %s already exists"), sampname);
    }
    fd = csoundFileOpenWithType(csound, &smpf, CSFILE_STD, sampname, "wb", NULL,
                                CSFTYPE_UNKNOWN_AUDIO, 1);
    if (UNLIKELY(fd == NULL)) {
      csoundDie(csound, Str("Cannot open sample file (%s) subfile"), sampname);
    }
    read_base64(csound, unf, smpf);
    csoundFileClose(csound, fd);
    add_tmpfile(csound, sampname);              /* IV - Feb 03 2005 */
    while (TRUE) {
      if (my_fgets(csound, buffer, CSD_MAX_LINE_LEN, unf)!= NULL) {
        char *p = buffer;
        while (*p == ' ' || *p == '\t') p++;
        if (strstr(p, "</CsSampleB>") == p) {
          return TRUE;
        }
      }
    }
    csoundErrorMsg(csound, Str("Missing end tag </CsSampleB>"));
    return FALSE;
}

static int createFile(CSOUND *csound, char *buffer, FILE *unf)
{
    FILE  *smpf;
    void  *fd;
    char  filename[256];
    /* char  buffer[CSD_MAX_LINE_LEN]; */
    char *p = buffer, *q;

    filename[0] = '\0';

    p += 18;    /* 18== strlen("<CsFileB filename=  ") */
    if (*p=='"') {
      p++; q = strchr(p, '"');
    }
    else
      q = strchr(p, '>');
    if (q) *q='\0';
    strcpy(filename, p);
    if (UNLIKELY((smpf = fopen(filename, "rb")) != NULL)) {
      fclose(smpf);
      csoundDie(csound, Str("File %s already exists"), filename);
    }
    fd = csoundFileOpenWithType(csound, &smpf, CSFILE_STD, filename, "wb", NULL,
                                CSFTYPE_UNKNOWN, 1);
    if (UNLIKELY(fd == NULL)) {
      csoundDie(csound, Str("Cannot open file (%s) subfile"), filename);
    }
    read_base64(csound, unf, smpf);
    csoundFileClose(csound, fd);
    add_tmpfile(csound, filename);              /* IV - Feb 03 2005 */

    while (TRUE) {
      if (my_fgets(csound, buffer, CSD_MAX_LINE_LEN, unf)!= NULL) {
        char *p = buffer;
        while (*p == ' ' || *p == '\t') p++;
        if (strstr(p, "</CsFileB>") == p) {
          return TRUE;
        }
      }
    }
    csoundErrorMsg(csound, Str("Missing end tag </CsFileB>"));
    return FALSE;
}

static int checkVersion(CSOUND *csound, FILE *unf)
{
    char  *p;
    int   major = 0, minor = 0;
    int   result = TRUE;
    int   version = csoundGetVersion();
    char  buffer[CSD_MAX_LINE_LEN];

    while (my_fgets(csound, buffer, CSD_MAX_LINE_LEN, unf) != NULL) {
      p = buffer;
      while (*p == ' ' || *p == '\t') p++;
      if (strstr(p, "</CsVersion>") != NULL)
        return result;
      if (strstr(p, "Before") != NULL) {
        sscanf(p, "Before %d.%d", &major, &minor);
        if (UNLIKELY(version >= ((major * 1000) + (minor*10)))) {
          csoundDie(csound, Str("This CSD file requires a version of "
                                 "Csound before %d.%02d"), major, minor);
          result = FALSE;
        }
      }
      else if (strstr(p, "After") != NULL) {
        sscanf(p, "After %d.%d", &major, &minor);
        if (UNLIKELY(version <= ((major * 1000) + (minor*10)))) {
          csoundDie(csound, Str("This CSD file requires a version of "
                                 "Csound after %d.%02d"), major, minor);
          result = FALSE;
        }
      }
      else if (sscanf(p, "%d.%d", &major, &minor) == 2) {
        if (UNLIKELY(version <= ((major * 1000) + (minor*10)))) {
          csoundDie(csound, Str("This CSD file requires a version of "
                                "Csound after %d.%02d"), major, minor);
          result = FALSE;
        }
      }
    }
    csoundErrorMsg(csound, Str("Missing end tag </CsVersion>"));
    return FALSE;
}

static int checkLicence(CSOUND *csound, FILE *unf)
{
    char  *p, *licence;
    int   len = 1;
    char  buffer[CSD_MAX_LINE_LEN];

    csoundMessage(csound, Str("**** Licence Information ****\n"));
    licence = (char*) mcalloc(csound, len);
    while (my_fgets(csound, buffer, CSD_MAX_LINE_LEN, unf) != NULL) {
      p = buffer;
      if (strstr(p, "</CsLicence>") != NULL ||
          strstr(p, "</CsLicense>") != NULL) {
        csoundMessage(csound, Str("**** End of Licence Information ****\n"));
        mfree(csound, csound->SF_csd_licence);
        csound->SF_csd_licence = licence;
        return TRUE;
      }
      csoundMessage(csound, "%s", p);
      len += strlen(p);
      licence = mrealloc(csound, licence, len);
      strncat(licence, p, len);
    }
    mfree(csound, licence);
    csoundErrorMsg(csound, Str("Missing end tag </CsLicence>"));
    return FALSE;
}

static int blank_buffer(CSOUND *csound, char *buffer)
{
    const char *s;
    for (s = &(buffer[0]); *s != '\0' && *s != '\n'; s++) {
      if (*s == ';')
        return TRUE;
      if (*s != ' ' && *s != '\t')
        return FALSE;
    }
    return TRUE;
}

int read_unified_file(CSOUND *csound, char **pname, char **score)
{
    char  *name = *pname;
    FILE  *unf;
    void  *fd;
    int   result = TRUE;
    int   started = FALSE;
    int   r;
    char    buffer[CSD_MAX_LINE_LEN];

    /* Need to open in binary to deal with MIDI and the like. */
    fd = csoundFileOpenWithType(csound, &unf, CSFILE_STD, name, "rb", NULL,
                                CSFTYPE_UNIFIED_CSD, 0);
    /* RWD 3:2000 fopen can fail... */
    if (UNLIKELY(fd == NULL)) {
      csound->ErrorMsg(csound, Str("Failed to open csd file: %s"),
                               strerror(errno));
      return 0;
    }
    alloc_globals(csound);
    ST(orcname)[0] = ST(sconame)[0] = ST(midname)[0] = '\0';
    ST(midiSet) = FALSE;
#ifdef _DEBUG
    csoundMessage(csound, "Calling unified file system with %s\n", name);
#endif
    while (my_fgets(csound, buffer, CSD_MAX_LINE_LEN, unf)) {
      char *p = buffer;
      while (*p == ' ' || *p == '\t') p++;
      if (strstr(p, "<CsoundSynthesizer>") == p ||
          strstr(p, "<CsoundSynthesiser>") == p) {
        csoundDebugMsg(csound, Str("STARTING FILE\n"));
        started = TRUE;
      }
      else if (strstr(p, "</CsoundSynthesizer>") == p ||
               strstr(p, "</CsoundSynthesiser>") == p) {
        if (csound->scorestr != NULL)
          corfile_flush(csound->scorestr);
        *pname = ST(orcname);
        *score = ST(sconame);
        if (ST(midiSet)) {
          csound->oparms->FMidiname = ST(midname);
          csound->oparms->FMidiin = 1;
        }
        csoundFileClose(csound, fd);
        return result;
      }
      else if (strstr(p, "<CsOptions>") == p) {
        if (!csound->disable_csd_options) {
          csoundMessage(csound, Str("Creating options\n"));
          csound->orchname = NULL;  /* allow orchestra/score name in CSD file */
          r = readOptions(csound, unf, 1);
          result = r && result;
        }
        else {
          csoundMessage(csound, Str("Skipping <CsOptions>\n"));
          do {
            if (UNLIKELY(my_fgets(csound, buffer,
                                  CSD_MAX_LINE_LEN, unf) == NULL)) {
              csoundErrorMsg(csound, Str("Missing end tag </CsOptions>"));
              result = FALSE;
              break;
            }
            p = buffer;
            while (*p == ' ' || *p == '\t') p++;
          } while (strstr(p, "</CsOptions>") != p);
        }
      }
      else if (strstr(p, "<CsInstruments>") == p) {
        csoundMessage(csound, Str("Creating orchestra\n"));
        r = createOrchestra(csound, unf);
        result = r && result;
      }
      else if (strstr(p, "<CsScore") == p) {
        csoundMessage(csound, Str("Creating score\n"));
        if (strstr(p, "<CsScore>") == p)
          r = createScore(csound, unf);
        else
          r = createExScore(csound, p, unf);
        result = r && result;
      }
      /* else if (strstr(p, "<CsMidifile>") == p) { */
      /*   r = createMIDI(csound, unf); */
      /*   result = r && result; */
      /* } */
      else if (strstr(p, "<CsMidifileB>") == p) {
        r = createMIDI2(csound, unf);
        result = r && result;
      }
      else if (strstr(p, "<CsSampleB filename=") == p) {
        r = createSample(csound, buffer,unf);
        result = r && result;
      }
      else if (strstr(p, "<CsFileB filename=") == p) {
        r = createFile(csound, buffer, unf);
        result = r && result;
      }
      else if (strstr(p, "<CsVersion>") == p) {
        r = checkVersion(csound, unf);
        result = r && result;
      }
      else if (strstr(p, "<CsLicence>") == p ||
               strstr(p, "<CsLicense>") == p) {
        r = checkLicence(csound, unf);
        result = r && result;
      }
      else if (blank_buffer(csound, buffer)) continue;
      else if (started && strchr(p, '<') == buffer){
        csoundMessage(csound, Str("unknown CSD tag: %s\n"), buffer);
      }
    }
      if (UNLIKELY(!started)) {
      csoundMessage(csound,
                    Str("Could not find <CsoundSynthesizer> tag in CSD file.\n"));
      result = FALSE;
    }
    *pname = ST(orcname);
    *score = ST(sconame);
    if (ST(midiSet)) {
      csound->oparms->FMidiname = ST(midname);
      csound->oparms->FMidiin = 1;
    }
    csoundFileClose(csound, fd);
    return result;
}
