/* A Bison parser, made by GNU Bison 2.4.2.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2006, 2009-2010 Free Software
   Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0

/* Substitute the variable and function names.  */
#define yyparse         csound_orcparse
#define yylex           csound_orclex
#define yyerror         csound_orcerror
#define yylval          csound_orclval
#define yychar          csound_orcchar
#define yydebug         csound_orcdebug
#define yynerrs         csound_orcnerrs


/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 142 "csound_orc.y"

/* #define YYSTYPE ORCTOKEN* */
/* JPff thinks that line must be wrong and is trying this! */
#define YYSTYPE TREE*

#ifndef NULL
#define NULL 0L
#endif
#include "csoundCore.h"
#include <ctype.h>
#include "namedins.h"

#include "csound_orc.h"
#ifdef PARCS
#include "cs_par_base.h"
#include "cs_par_orc_semantics.h"
#endif
#include "parse_param.h"

    //int udoflag = -1; /* THIS NEEDS TO BE MADE NON-GLOBAL */
#define udoflag csound->parserUdoflag

   //int namedInstrFlag = 0; /* THIS NEEDS TO BE MADE NON-GLOBAL */
#define namedInstrFlag csound->parserNamedInstrFlag

extern TREE* appendToTree(CSOUND * csound, TREE *first, TREE *newlast);
extern int csound_orclex(TREE**, CSOUND *, void *);
extern void print_tree(CSOUND *, char *msg, TREE *);
extern void csound_orcerror(PARSE_PARM *, void *, CSOUND *, TREE*, const char*);
extern void add_udo_definition(CSOUND*, char *, char *, char *);
extern ORCTOKEN *lookup_token(CSOUND*,char*,void*);
#define LINE csound_orcget_lineno(scanner)
extern int csound_orcget_lineno(void *);


/* Line 189 of yacc.c  */
#line 116 "csound_orc.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     NEWLINE = 258,
     S_NEQ = 259,
     S_AND = 260,
     S_OR = 261,
     S_LT = 262,
     S_LE = 263,
     S_EQ = 264,
     S_TASSIGN = 265,
     S_TABREF = 266,
     S_GT = 267,
     S_GE = 268,
     S_BITSHIFT_LEFT = 269,
     S_BITSHIFT_RRIGHT = 270,
     LABEL_TOKEN = 271,
     IF_TOKEN = 272,
     T_OPCODE0 = 273,
     T_OPCODE = 274,
     UDO_TOKEN = 275,
     UDOSTART_DEFINITION = 276,
     UDOEND_TOKEN = 277,
     UDO_ANS_TOKEN = 278,
     UDO_ARGS_TOKEN = 279,
     T_ERROR = 280,
     T_FUNCTION = 281,
     INSTR_TOKEN = 282,
     ENDIN_TOKEN = 283,
     T_STRSET = 284,
     T_PSET = 285,
     T_CTRLINIT = 286,
     T_MASSIGN = 287,
     T_TURNON = 288,
     T_PREALLOC = 289,
     T_ZAKINIT = 290,
     T_FTGEN = 291,
     T_INIT = 292,
     GOTO_TOKEN = 293,
     KGOTO_TOKEN = 294,
     IGOTO_TOKEN = 295,
     SRATE_TOKEN = 296,
     KRATE_TOKEN = 297,
     KSMPS_TOKEN = 298,
     NCHNLS_TOKEN = 299,
     NCHNLSI_TOKEN = 300,
     ZERODBFS_TOKEN = 301,
     STRING_TOKEN = 302,
     T_IDENT = 303,
     T_IDENT_I = 304,
     T_IDENT_GI = 305,
     T_IDENT_K = 306,
     T_IDENT_GK = 307,
     T_IDENT_A = 308,
     T_IDENT_GA = 309,
     T_IDENT_W = 310,
     T_IDENT_GW = 311,
     T_IDENT_F = 312,
     T_IDENT_GF = 313,
     T_IDENT_S = 314,
     T_IDENT_GS = 315,
     T_IDENT_T = 316,
     T_IDENT_GT = 317,
     T_IDENT_P = 318,
     T_IDENT_B = 319,
     T_IDENT_b = 320,
     INTEGER_TOKEN = 321,
     NUMBER_TOKEN = 322,
     THEN_TOKEN = 323,
     ITHEN_TOKEN = 324,
     KTHEN_TOKEN = 325,
     ELSEIF_TOKEN = 326,
     ELSE_TOKEN = 327,
     ENDIF_TOKEN = 328,
     UNTIL_TOKEN = 329,
     DO_TOKEN = 330,
     OD_TOKEN = 331,
     T_INSTLIST = 332,
     S_BITSHIFT_RIGHT = 333,
     S_UNOT = 334,
     S_UMINUS = 335,
     S_ATAT = 336,
     S_AT = 337,
     S_GEQ = 338,
     S_LEQ = 339,
     S_GOTO = 340,
     T_HIGHEST = 341
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 244 "csound_orc.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  77
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   2116

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  106
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  36
/* YYNRULES -- Number of rules.  */
#define YYNRULES  168
/* YYNRULES -- Number of states.  */
#define YYNSTATES  287

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   341

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   104,     2,    86,     2,    82,    85,     2,
     102,   103,    80,    78,    98,    79,     2,    81,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   105,     2,
       2,    99,     2,    93,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   100,     2,   101,    83,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    84,     2,    88,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    87,    89,    90,    91,    92,    94,    95,
      96,    97
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     8,    11,    14,    16,    18,    20,
      24,    28,    30,    32,    33,    34,    43,    47,    48,    49,
      50,    51,    52,    68,    71,    72,    77,    79,    84,    89,
      97,   102,   106,   108,   112,   118,   120,   126,   128,   130,
     133,   137,   142,   150,   160,   169,   180,   183,   185,   191,
     193,   195,   197,   199,   201,   203,   205,   207,   209,   211,
     213,   215,   217,   219,   221,   223,   225,   227,   229,   231,
     233,   235,   237,   239,   243,   247,   251,   253,   255,   256,
     260,   264,   268,   272,   276,   280,   284,   288,   292,   296,
     300,   304,   308,   312,   316,   320,   324,   328,   332,   335,
     338,   344,   350,   355,   359,   361,   365,   369,   373,   377,
     379,   383,   387,   391,   395,   399,   403,   405,   407,   409,
     414,   417,   420,   424,   428,   432,   436,   440,   444,   447,
     450,   454,   458,   461,   466,   470,   472,   474,   476,   478,
     480,   482,   484,   486,   488,   490,   492,   494,   496,   498,
     500,   502,   504,   506,   508,   510,   512,   514,   516,   518,
     520,   522,   524,   526,   528,   530,   532,   534,   536
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     107,     0,    -1,   108,    -1,   108,   120,    -1,   108,   110,
      -1,   108,   113,    -1,   120,    -1,   110,    -1,   113,    -1,
      66,    98,   109,    -1,    48,    98,   109,    -1,    66,    -1,
      48,    -1,    -1,    -1,    27,   111,   109,     3,   112,   119,
      28,     3,    -1,    27,     3,     1,    -1,    -1,    -1,    -1,
      -1,    -1,    21,   114,    48,   115,    98,   116,    23,   117,
      98,    24,     3,   118,   119,    22,     3,    -1,   119,   121,
      -1,    -1,   136,    99,   131,     3,    -1,   121,    -1,   137,
      99,   131,     3,    -1,    61,    99,    61,     3,    -1,    61,
     100,   132,   101,    99,   131,     3,    -1,   122,   141,   129,
       3,    -1,   140,   129,     3,    -1,    16,    -1,   127,   128,
       3,    -1,    17,   130,   127,   128,     3,    -1,   123,    -1,
      74,   130,    75,   119,    76,    -1,     3,    -1,   137,    -1,
      48,     1,    -1,   122,    98,   137,    -1,   122,    98,    48,
       1,    -1,    17,   130,   126,     3,   119,    73,     3,    -1,
      17,   130,   126,     3,   119,    72,   119,    73,     3,    -1,
      17,   130,   126,     3,   119,   124,    73,     3,    -1,    17,
     130,   126,     3,   119,   124,    72,   119,    73,     3,    -1,
     124,   125,    -1,   125,    -1,    71,   130,   126,     3,   119,
      -1,    68,    -1,    70,    -1,    69,    -1,    38,    -1,    39,
      -1,    40,    -1,    19,    -1,    18,    -1,    63,    -1,    49,
      -1,    50,    -1,    51,    -1,    52,    -1,    53,    -1,    54,
      -1,    55,    -1,    56,    -1,    57,    -1,    58,    -1,    59,
      -1,    60,    -1,    61,    -1,    62,    -1,    48,    -1,   129,
      98,   131,    -1,   129,    98,   128,    -1,   129,    98,     1,
      -1,   131,    -1,    48,    -1,    -1,   102,   130,   103,    -1,
     131,     8,   131,    -1,   131,     8,     1,    -1,   131,    13,
     131,    -1,   131,    13,     1,    -1,   131,     4,   131,    -1,
     131,     4,     1,    -1,   131,     9,   131,    -1,   131,     9,
       1,    -1,   131,    99,   131,    -1,   131,    99,     1,    -1,
     131,    12,   131,    -1,   131,    12,     1,    -1,   131,     7,
     131,    -1,   131,     7,     1,    -1,   130,     5,   130,    -1,
     130,     5,     1,    -1,   130,     6,   130,    -1,   130,     6,
       1,    -1,   104,   130,    -1,   104,     1,    -1,   130,    93,
     131,   105,   131,    -1,   130,    93,   131,   105,     1,    -1,
     130,    93,   131,     1,    -1,   130,    93,     1,    -1,   132,
      -1,   132,    78,   133,    -1,   132,    78,     1,    -1,   132,
      79,   133,    -1,   132,    79,     1,    -1,   133,    -1,   133,
      80,   134,    -1,   133,    80,     1,    -1,   133,    81,   134,
      -1,   133,    81,     1,    -1,   133,    82,   134,    -1,   133,
      82,     1,    -1,   134,    -1,   137,    -1,   139,    -1,    61,
     100,   132,   101,    -1,    79,   134,    -1,    78,   134,    -1,
     134,    83,   134,    -1,   134,    84,   134,    -1,   134,    85,
     134,    -1,   134,    86,   134,    -1,   134,    14,   134,    -1,
     134,    87,   134,    -1,    88,   134,    -1,    79,     1,    -1,
     102,   131,   103,    -1,   102,   131,     1,    -1,   102,     1,
      -1,   135,   102,   129,   103,    -1,   135,   102,     1,    -1,
      26,    -1,    41,    -1,    42,    -1,    43,    -1,    44,    -1,
      45,    -1,    46,    -1,    49,    -1,    51,    -1,    57,    -1,
      55,    -1,    59,    -1,    61,    -1,    53,    -1,    63,    -1,
     138,    -1,    50,    -1,    52,    -1,    58,    -1,    56,    -1,
      60,    -1,    62,    -1,    54,    -1,    66,    -1,    67,    -1,
      47,    -1,    41,    -1,    42,    -1,    43,    -1,    44,    -1,
      45,    -1,    46,    -1,    18,    -1,    19,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   178,   178,   186,   190,   194,   198,   199,   200,   203,
     207,   215,   217,   221,   223,   220,   235,   246,   248,   250,
     252,   254,   245,   290,   294,   297,   308,   312,   327,   335,
     350,   364,   377,   381,   388,   395,   396,   402,   404,   405,
     411,   412,   420,   426,   435,   444,   466,   478,   481,   491,
     493,   495,   499,   501,   503,   508,   509,   510,   511,   512,
     513,   514,   515,   516,   517,   518,   519,   520,   521,   522,
     523,   524,   525,   529,   534,   541,   542,   543,   544,   547,
     548,   549,   550,   551,   552,   553,   554,   555,   556,   557,
     558,   559,   560,   561,   562,   563,   564,   565,   566,   568,
     571,   574,   575,   576,   577,   580,   581,   582,   583,   584,
     587,   588,   589,   590,   591,   592,   593,   596,   597,   598,
     604,   608,   612,   613,   614,   615,   616,   618,   620,   622,
     623,   624,   625,   626,   633,   636,   646,   648,   650,   652,
     654,   656,   660,   661,   662,   663,   664,   665,   666,   667,
     668,   671,   672,   673,   674,   675,   676,   677,   680,   682,
     684,   686,   688,   690,   692,   694,   696,   700,   709
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "NEWLINE", "S_NEQ", "S_AND", "S_OR",
  "S_LT", "S_LE", "S_EQ", "S_TASSIGN", "S_TABREF", "S_GT", "S_GE",
  "S_BITSHIFT_LEFT", "S_BITSHIFT_RRIGHT", "LABEL_TOKEN", "IF_TOKEN",
  "T_OPCODE0", "T_OPCODE", "UDO_TOKEN", "UDOSTART_DEFINITION",
  "UDOEND_TOKEN", "UDO_ANS_TOKEN", "UDO_ARGS_TOKEN", "T_ERROR",
  "T_FUNCTION", "INSTR_TOKEN", "ENDIN_TOKEN", "T_STRSET", "T_PSET",
  "T_CTRLINIT", "T_MASSIGN", "T_TURNON", "T_PREALLOC", "T_ZAKINIT",
  "T_FTGEN", "T_INIT", "GOTO_TOKEN", "KGOTO_TOKEN", "IGOTO_TOKEN",
  "SRATE_TOKEN", "KRATE_TOKEN", "KSMPS_TOKEN", "NCHNLS_TOKEN",
  "NCHNLSI_TOKEN", "ZERODBFS_TOKEN", "STRING_TOKEN", "T_IDENT",
  "T_IDENT_I", "T_IDENT_GI", "T_IDENT_K", "T_IDENT_GK", "T_IDENT_A",
  "T_IDENT_GA", "T_IDENT_W", "T_IDENT_GW", "T_IDENT_F", "T_IDENT_GF",
  "T_IDENT_S", "T_IDENT_GS", "T_IDENT_T", "T_IDENT_GT", "T_IDENT_P",
  "T_IDENT_B", "T_IDENT_b", "INTEGER_TOKEN", "NUMBER_TOKEN", "THEN_TOKEN",
  "ITHEN_TOKEN", "KTHEN_TOKEN", "ELSEIF_TOKEN", "ELSE_TOKEN",
  "ENDIF_TOKEN", "UNTIL_TOKEN", "DO_TOKEN", "OD_TOKEN", "T_INSTLIST",
  "'+'", "'-'", "'*'", "'/'", "'%'", "'^'", "'|'", "'&'", "'#'",
  "S_BITSHIFT_RIGHT", "'~'", "S_UNOT", "S_UMINUS", "S_ATAT", "S_AT", "'?'",
  "S_GEQ", "S_LEQ", "S_GOTO", "T_HIGHEST", "','", "'='", "'['", "']'",
  "'('", "')'", "'!'", "':'", "$accept", "orcfile", "rootstatement",
  "instlist", "instrdecl", "$@1", "$@2", "udodecl", "$@3", "$@4", "$@5",
  "$@6", "$@7", "statementlist", "topstatement", "statement", "ans",
  "ifthen", "elseiflist", "elseif", "then", "goto", "label", "exprlist",
  "bexpr", "expr", "iexp", "iterm", "ifac", "function", "rident", "ident",
  "gident", "constant", "opcode0", "opcode", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,    43,    45,
      42,    47,    37,    94,   124,    38,    35,   333,   126,   334,
     335,   336,   337,    63,   338,   339,   340,   341,    44,    61,
      91,    93,    40,    41,    33,    58
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   106,   107,   108,   108,   108,   108,   108,   108,   109,
     109,   109,   109,   111,   112,   110,   110,   114,   115,   116,
     117,   118,   113,   119,   119,   120,   120,   121,   121,   121,
     121,   121,   121,   121,   121,   121,   121,   121,   122,   122,
     122,   122,   123,   123,   123,   123,   124,   124,   125,   126,
     126,   126,   127,   127,   127,   128,   128,   128,   128,   128,
     128,   128,   128,   128,   128,   128,   128,   128,   128,   128,
     128,   128,   128,   129,   129,   129,   129,   129,   129,   130,
     130,   130,   130,   130,   130,   130,   130,   130,   130,   130,
     130,   130,   130,   130,   130,   130,   130,   130,   130,   130,
     131,   131,   131,   131,   131,   132,   132,   132,   132,   132,
     133,   133,   133,   133,   133,   133,   133,   134,   134,   134,
     134,   134,   134,   134,   134,   134,   134,   134,   134,   134,
     134,   134,   134,   134,   134,   135,   136,   136,   136,   136,
     136,   136,   137,   137,   137,   137,   137,   137,   137,   137,
     137,   138,   138,   138,   138,   138,   138,   138,   139,   139,
     139,   139,   139,   139,   139,   139,   139,   140,   141
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     2,     2,     1,     1,     1,     3,
       3,     1,     1,     0,     0,     8,     3,     0,     0,     0,
       0,     0,    15,     2,     0,     4,     1,     4,     4,     7,
       4,     3,     1,     3,     5,     1,     5,     1,     1,     2,
       3,     4,     7,     9,     8,    10,     2,     1,     5,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     3,     3,     1,     1,     0,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     2,     2,
       5,     5,     4,     3,     1,     3,     3,     3,     3,     1,
       3,     3,     3,     3,     3,     3,     1,     1,     1,     4,
       2,     2,     3,     3,     3,     3,     3,     3,     2,     2,
       3,     3,     2,     4,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    37,    32,     0,   167,    17,    13,    52,    53,    54,
     136,   137,   138,   139,   140,   141,     0,   142,   151,   143,
     152,   148,   157,   145,   154,   144,   153,   146,   155,   147,
     156,   149,     0,     0,     2,     7,     8,     6,    26,     0,
      35,     0,     0,    38,   150,    78,   135,   161,   162,   163,
     164,   165,   166,   160,   147,   158,   159,     0,     0,     0,
       0,     0,     0,     0,   104,   109,   116,     0,   117,   118,
       0,     0,     0,    39,     0,     0,     0,     1,     4,     5,
       3,   168,     0,    78,    56,    55,    72,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    57,     0,     0,     0,    77,     0,     0,    76,     0,
       0,   121,   129,   120,   128,   132,     0,     0,    99,    98,
       0,     0,    49,    51,    50,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    18,    16,    12,
      11,     0,     0,     0,    24,     0,   147,    40,     0,    33,
       0,     0,    31,     0,     0,    79,   131,   130,    95,    94,
      97,    96,   103,     0,    24,     0,    85,    84,    93,    92,
      81,    80,    87,    86,    91,    90,    83,    82,    89,    88,
     106,   105,   108,   107,   111,   110,   113,   112,   115,   114,
     126,   122,   123,   124,   125,   127,   134,     0,     0,     0,
       0,    14,    28,     0,     0,    41,    30,    25,    27,    75,
     142,   151,   143,   152,   148,   157,   145,   154,   144,   153,
     146,   155,   147,   156,   149,    74,    73,   119,   102,     0,
       0,    34,   133,    19,    10,     9,    24,     0,    36,    23,
     101,   100,     0,    24,     0,     0,    47,     0,     0,     0,
       0,     0,    42,    24,     0,    46,    20,     0,    29,     0,
       0,     0,    44,     0,    15,    24,    43,     0,     0,    48,
      45,     0,    21,    24,     0,     0,    22
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    33,    34,   151,    35,    72,   246,    36,    70,   208,
     257,   273,   283,   214,    37,   249,    39,    40,   255,   256,
     126,    41,   102,   106,   107,    63,    64,    65,    66,    67,
      42,    68,    44,    69,    45,    83
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -170
static const yytype_int16 yypact[] =
{
    1728,  -170,  -170,  1538,  -170,  -170,    16,  -170,  -170,  -170,
    -170,  -170,  -170,  -170,  -170,  -170,    42,  -170,  -170,  -170,
    -170,  -170,  -170,  -170,  -170,  -170,  -170,  -170,  -170,   -60,
    -170,  -170,  1538,    48,  1728,  -170,  -170,  -170,  -170,    19,
    -170,  2053,   -18,    -4,  -170,  1474,  -170,  -170,  -170,  -170,
    -170,  -170,  -170,  -170,   -35,  -170,  -170,  1602,  1076,  1602,
     244,   308,  1421,   240,   -28,   -26,   243,   -31,  -170,  -170,
      53,   104,    27,  -170,    46,  1602,   184,  -170,  -170,  -170,
    -170,  -170,  1760,  1474,  -170,  -170,  -170,  -170,  -170,  -170,
    -170,  -170,  -170,  -170,  -170,  -170,  -170,  -170,  -170,  -170,
    -170,  -170,   117,  1538,  1538,  -170,    -1,   179,   240,  1602,
     244,  -170,  -170,  -170,  -170,  -170,   173,    13,  -170,    31,
     372,   436,  -170,  -170,  -170,   500,   119,  2053,   564,   628,
     692,   756,   820,   884,   948,  1139,  1202,  1265,  1328,  1391,
    1602,  1602,  1602,  1602,  1602,  1602,    84,  -170,  -170,    51,
      58,   155,   164,   -55,  -170,   180,  -170,  -170,     5,  -170,
      24,   312,  -170,   176,   -34,  -170,  -170,  -170,  -170,    31,
    -170,    31,  -170,     3,  -170,   189,  -170,   240,  -170,   240,
    -170,   240,  -170,   240,  -170,   240,  -170,   240,  -170,   240,
    -170,   -26,  -170,   -26,  -170,   243,  -170,   243,  -170,   243,
      96,   251,   196,    -8,    28,  -170,  -170,   -51,   105,    27,
      27,  -170,  -170,   113,  1667,  -170,  -170,  -170,  -170,  -170,
      50,    57,    61,    63,    67,    70,    71,    73,    77,    93,
      95,   106,    54,   108,   110,  -170,   240,  -170,  -170,  1012,
    1789,  -170,  -170,  -170,  -170,  -170,  -170,  1538,  -170,  -170,
    -170,   240,  1538,  -170,   204,   128,  -170,   218,  1850,   376,
     501,  1877,  -170,  -170,   248,  -170,  -170,   253,  -170,   257,
     259,  1938,  -170,   148,  -170,  -170,  -170,   260,   245,  2026,
    -170,   264,  -170,  -170,  1999,   265,  -170
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -170,  -170,  -170,  -110,   239,  -170,  -170,   241,  -170,  -170,
    -170,  -170,  -170,  -169,   258,    29,  -170,  -170,  -170,    59,
      14,   246,  -114,   -74,    -2,   -42,   -40,    80,   390,  -170,
    -170,     0,  -170,  -170,  -170,  -170
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -79
static const yytype_int16 yytable[] =
{
      43,    62,   162,   108,   238,   240,   140,   128,   216,   158,
     129,   130,   131,   175,   166,   132,   133,   128,   117,    71,
     129,   130,   131,   135,   136,   132,   133,   217,   128,    38,
      76,   129,   130,   131,    43,   153,   132,   133,    81,    74,
      75,   108,   140,    73,   135,   136,   213,   163,    77,   235,
     135,   136,   242,   -58,   137,   138,   139,   -70,   116,   119,
     -59,   160,   161,    38,   -60,   109,   -61,   237,   117,   164,
     -62,   146,   207,   -63,   -64,   149,   -65,   258,   144,   145,
     -66,   103,   157,   173,   261,   206,   177,   179,   181,   183,
     185,   187,   189,   150,   271,   104,   -67,   163,   -68,   244,
     245,   147,   134,   163,   108,   148,   279,   152,   239,   -69,
      46,   -71,   134,   -57,   284,   145,   167,    82,   169,   171,
     159,   236,   174,   134,   125,    47,    48,    49,    50,    51,
      52,    53,   105,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    54,    30,    31,   -58,   209,
      55,    56,   -70,   -58,   109,   -59,   210,   -70,   211,   -60,
     -59,   -61,    57,    58,   -60,   -62,   -61,   212,   -63,   -64,
     -62,   -65,    59,   -63,   -64,   -66,   -65,   219,   120,   121,
     -66,   215,   -78,   145,   120,   121,    60,   -78,    61,   120,
     121,   -67,   241,   -68,    84,    85,   -67,   251,   -68,   252,
     263,   264,    46,   243,   -69,   259,   -71,   262,   -57,   -69,
     140,   -71,   247,   -57,    43,   191,   193,    47,    48,    49,
      50,    51,    52,    53,    86,   220,   221,   222,   223,   224,
     225,   226,   227,   228,   229,   230,   231,   232,   233,   234,
      43,   266,    55,    56,   128,   115,   278,   129,   130,   131,
     260,   272,   132,   133,    57,    58,   274,   140,    43,   154,
     275,    43,   276,   280,    59,   140,   125,   282,   286,   281,
      46,    43,   125,    78,   269,    79,   165,   125,    60,    43,
      61,   143,   144,   145,    43,    47,    48,    49,    50,    51,
      52,    53,    80,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    54,    30,    31,   127,   118,
      55,    56,     0,     0,   265,   218,   128,     0,     0,   129,
     130,   131,    57,    58,   132,   133,   141,   142,   143,   144,
     145,     0,    59,     0,    46,   142,   143,   144,   145,   134,
       0,     0,     0,     0,     0,     0,    60,     0,    61,    47,
      48,    49,    50,    51,    52,    53,     0,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    54,
      30,    31,     0,   168,    55,    56,     0,     0,     0,   268,
     128,     0,     0,   129,   130,   131,    57,    58,   132,   133,
       0,     0,     0,     0,     0,     0,    59,     0,    46,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      60,   134,    61,    47,    48,    49,    50,    51,    52,    53,
       0,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    54,    30,    31,     0,   170,    55,    56,
       0,     0,     0,     0,     0,     0,     0,   111,   113,   114,
      57,    58,     0,     0,     0,     0,     0,     0,     0,     0,
      59,     0,    46,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    60,   134,    61,    47,    48,    49,
      50,    51,    52,    53,     0,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    54,    30,    31,
       0,   172,    55,    56,     0,     0,   120,   121,     0,     0,
       0,     0,     0,     0,    57,    58,     0,     0,     0,     0,
       0,     0,     0,     0,    59,     0,    46,   195,   197,   199,
     200,   201,   202,   203,   204,   205,     0,     0,    60,     0,
      61,    47,    48,    49,    50,    51,    52,    53,     0,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    54,    30,    31,     0,   176,    55,    56,     0,   122,
     123,   124,     0,     0,     0,     0,     0,     0,    57,    58,
       0,     0,     0,     0,     0,     0,     0,     0,    59,     0,
      46,     0,     0,     0,   125,     0,     0,     0,     0,     0,
       0,     0,    60,     0,    61,    47,    48,    49,    50,    51,
      52,    53,     0,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    54,    30,    31,     0,   178,
      55,    56,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    57,    58,     0,     0,     0,     0,     0,     0,
       0,     0,    59,     0,    46,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    60,     0,    61,    47,
      48,    49,    50,    51,    52,    53,     0,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    54,
      30,    31,     0,   180,    55,    56,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    57,    58,     0,     0,
       0,     0,     0,     0,     0,     0,    59,     0,    46,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      60,     0,    61,    47,    48,    49,    50,    51,    52,    53,
       0,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    54,    30,    31,     0,   182,    55,    56,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      57,    58,     0,     0,     0,     0,     0,     0,     0,     0,
      59,     0,    46,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    60,     0,    61,    47,    48,    49,
      50,    51,    52,    53,     0,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    54,    30,    31,
       0,   184,    55,    56,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    57,    58,     0,     0,     0,     0,
       0,     0,     0,     0,    59,     0,    46,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    60,     0,
      61,    47,    48,    49,    50,    51,    52,    53,     0,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    54,    30,    31,     0,   186,    55,    56,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    57,    58,
       0,     0,     0,     0,     0,     0,     0,     0,    59,     0,
      46,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    60,     0,    61,    47,    48,    49,    50,    51,
      52,    53,     0,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    54,    30,    31,     0,   188,
      55,    56,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    57,    58,     0,     0,     0,     0,     0,     0,
       0,     0,    59,     0,    46,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    60,     0,    61,    47,
      48,    49,    50,    51,    52,    53,     0,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    54,
      30,    31,     0,   250,    55,    56,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    57,    58,     0,     0,
       0,     0,     0,     0,     0,     0,    59,     0,    46,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      60,     0,    61,    47,    48,    49,    50,    51,    52,    53,
       0,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    54,    30,    31,     0,   112,    55,    56,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      57,    58,     0,     0,     0,     0,     0,     0,     0,     0,
      59,     0,    46,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    60,     0,    61,    47,    48,    49,
      50,    51,    52,    53,     0,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    54,    30,    31,
     190,     0,    55,    56,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    57,    58,     0,     0,     0,     0,
       0,     0,     0,     0,    59,    46,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   110,     0,
      47,    48,    49,    50,    51,    52,    53,     0,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      54,    30,    31,   192,     0,    55,    56,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    57,    58,     0,
       0,     0,     0,     0,     0,     0,     0,    59,    46,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   110,     0,    47,    48,    49,    50,    51,    52,    53,
       0,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    54,    30,    31,   194,     0,    55,    56,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      57,    58,     0,     0,     0,     0,     0,     0,     0,     0,
      59,    46,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   110,     0,    47,    48,    49,    50,
      51,    52,    53,     0,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    54,    30,    31,   196,
       0,    55,    56,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    57,    58,     0,     0,     0,     0,     0,
       0,     0,     0,    59,    46,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   110,     0,    47,
      48,    49,    50,    51,    52,    53,     0,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    54,
      30,    31,   198,     0,    55,    56,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    57,    58,     0,     0,
       0,     0,     0,     0,     0,     0,    59,    46,     0,     0,
       0,     0,     0,     0,     0,     0,   120,   121,     0,     0,
     110,     0,    47,    48,    49,    50,    51,    52,    53,     0,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    54,    30,    31,     0,     0,    55,    56,     7,
       8,     9,     0,     0,     0,     0,     0,     0,     0,    57,
      58,     0,     0,     0,     0,     0,     0,     0,     0,    59,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   122,
     123,   124,     0,   110,     0,     0,     0,     0,     0,     0,
      46,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   125,    47,    48,    49,    50,    51,
      52,    53,   105,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    54,    30,    31,     0,     0,
      55,    56,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    57,    58,     0,     0,     0,     0,     0,     0,
       0,     0,    59,     0,    46,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    60,     0,    61,    47,
      48,    49,    50,    51,    52,    53,     0,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    54,
      30,    31,     0,     0,    55,    56,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    57,    58,     0,     0,
       0,     0,     0,     0,     0,     0,    59,     0,    46,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      60,     0,    61,    47,    48,    49,    50,    51,    52,    53,
       0,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    54,    30,    31,     0,     0,    55,    56,
       1,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      57,    58,     0,     2,     3,     4,     0,     0,     0,     0,
      59,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   110,     7,     8,     9,     0,     0,
       0,     0,     0,     0,     0,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,     1,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    32,     0,   248,     2,     3,     4,     0,     0,     5,
       0,     0,     0,     0,     0,     6,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     7,     8,     9,    10,
      11,    12,    13,    14,    15,     0,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,     1,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    32,     0,     0,     2,     3,     4,   155,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,   156,    30,    31,     0,     0,     0,     7,     8,     9,
       0,     0,     0,     0,     0,     0,     0,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,     1,     0,     0,     0,     0,     0,     0,
     252,   253,   254,    32,     0,     0,     2,     3,     4,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   267,     0,
       1,     0,     0,     0,     0,     0,     0,     0,     7,     8,
       9,     0,     0,     2,     3,     4,     0,     0,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,     0,     7,     8,     9,     0,     0,
       0,     0,     0,     0,    32,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,     1,     0,     0,     0,     0,     0,     0,     0,     0,
     270,    32,     0,     0,     2,     3,     4,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     7,     8,     9,     0,
       0,     0,     0,     0,     0,     0,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,     1,     0,     0,     0,     0,     0,     0,     0,
       0,   277,    32,     0,     0,     2,     3,     4,     0,     0,
       0,   285,     0,     0,     0,     0,     0,     0,     0,     1,
       0,     0,     0,     0,     0,     0,     0,     7,     8,     9,
       0,     0,     2,     3,     4,     0,     0,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,     0,     7,     8,     9,     0,     0,     0,
       0,    84,    85,    32,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      32,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101
};

static const yytype_int16 yycheck[] =
{
       0,     3,     3,    45,     1,   174,    14,     4,     3,    83,
       7,     8,     9,   127,     1,    12,    13,     4,    60,     3,
       7,     8,     9,    78,    79,    12,    13,     3,     4,     0,
      32,     7,     8,     9,    34,    75,    12,    13,    19,    99,
     100,    83,    14,     1,    78,    79,   101,    98,     0,   163,
      78,    79,   103,     3,    80,    81,    82,     3,    60,    61,
       3,   103,   104,    34,     3,   100,     3,   101,   110,   109,
       3,   102,   146,     3,     3,    48,     3,   246,    86,    87,
       3,    99,    82,   125,   253,     1,   128,   129,   130,   131,
     132,   133,   134,    66,   263,    99,     3,    98,     3,   209,
     210,    48,    99,    98,   146,     1,   275,    61,   105,     3,
      26,     3,    99,     3,   283,    87,   103,    98,   120,   121,
       3,   163,     3,    99,    93,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    98,    98,
      66,    67,    98,   103,   100,    98,    98,   103,     3,    98,
     103,    98,    78,    79,   103,    98,   103,     3,    98,    98,
     103,    98,    88,   103,   103,    98,   103,     1,     5,     6,
     103,     1,    98,    87,     5,     6,   102,   103,   104,     5,
       6,    98,     3,    98,    18,    19,   103,   239,   103,    71,
      72,    73,    26,    98,    98,   247,    98,     3,    98,   103,
      14,   103,    99,   103,   214,   135,   136,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
     240,    23,    66,    67,     4,     1,    98,     7,     8,     9,
     252,     3,    12,    13,    78,    79,     3,    14,   258,    75,
       3,   261,     3,     3,    88,    14,    93,     3,     3,    24,
      26,   271,    93,    34,   260,    34,   103,    93,   102,   279,
     104,    85,    86,    87,   284,    41,    42,    43,    44,    45,
      46,    47,    34,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    62,     1,
      66,    67,    -1,    -1,   255,     3,     4,    -1,    -1,     7,
       8,     9,    78,    79,    12,    13,    83,    84,    85,    86,
      87,    -1,    88,    -1,    26,    84,    85,    86,    87,    99,
      -1,    -1,    -1,    -1,    -1,    -1,   102,    -1,   104,    41,
      42,    43,    44,    45,    46,    47,    -1,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    -1,     1,    66,    67,    -1,    -1,    -1,     3,
       4,    -1,    -1,     7,     8,     9,    78,    79,    12,    13,
      -1,    -1,    -1,    -1,    -1,    -1,    88,    -1,    26,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     102,    99,   104,    41,    42,    43,    44,    45,    46,    47,
      -1,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    -1,     1,    66,    67,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    57,    58,    59,
      78,    79,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      88,    -1,    26,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   102,    99,   104,    41,    42,    43,
      44,    45,    46,    47,    -1,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      -1,     1,    66,    67,    -1,    -1,     5,     6,    -1,    -1,
      -1,    -1,    -1,    -1,    78,    79,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    88,    -1,    26,   137,   138,   139,
     140,   141,   142,   143,   144,   145,    -1,    -1,   102,    -1,
     104,    41,    42,    43,    44,    45,    46,    47,    -1,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    -1,     1,    66,    67,    -1,    68,
      69,    70,    -1,    -1,    -1,    -1,    -1,    -1,    78,    79,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    88,    -1,
      26,    -1,    -1,    -1,    93,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   102,    -1,   104,    41,    42,    43,    44,    45,
      46,    47,    -1,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    -1,     1,
      66,    67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    78,    79,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    88,    -1,    26,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   102,    -1,   104,    41,
      42,    43,    44,    45,    46,    47,    -1,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    -1,     1,    66,    67,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    78,    79,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    88,    -1,    26,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     102,    -1,   104,    41,    42,    43,    44,    45,    46,    47,
      -1,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    -1,     1,    66,    67,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      78,    79,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      88,    -1,    26,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   102,    -1,   104,    41,    42,    43,
      44,    45,    46,    47,    -1,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      -1,     1,    66,    67,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    78,    79,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    88,    -1,    26,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   102,    -1,
     104,    41,    42,    43,    44,    45,    46,    47,    -1,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    -1,     1,    66,    67,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    78,    79,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    88,    -1,
      26,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   102,    -1,   104,    41,    42,    43,    44,    45,
      46,    47,    -1,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    -1,     1,
      66,    67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    78,    79,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    88,    -1,    26,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   102,    -1,   104,    41,
      42,    43,    44,    45,    46,    47,    -1,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    -1,     1,    66,    67,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    78,    79,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    88,    -1,    26,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     102,    -1,   104,    41,    42,    43,    44,    45,    46,    47,
      -1,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    -1,     1,    66,    67,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      78,    79,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      88,    -1,    26,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   102,    -1,   104,    41,    42,    43,
      44,    45,    46,    47,    -1,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
       1,    -1,    66,    67,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    78,    79,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    88,    26,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   102,    -1,
      41,    42,    43,    44,    45,    46,    47,    -1,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,     1,    -1,    66,    67,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    78,    79,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    88,    26,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   102,    -1,    41,    42,    43,    44,    45,    46,    47,
      -1,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,     1,    -1,    66,    67,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      78,    79,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      88,    26,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   102,    -1,    41,    42,    43,    44,
      45,    46,    47,    -1,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,     1,
      -1,    66,    67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    78,    79,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    88,    26,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   102,    -1,    41,
      42,    43,    44,    45,    46,    47,    -1,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,     1,    -1,    66,    67,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    78,    79,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    88,    26,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     5,     6,    -1,    -1,
     102,    -1,    41,    42,    43,    44,    45,    46,    47,    -1,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    -1,    -1,    66,    67,    38,
      39,    40,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    78,
      79,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    88,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,
      69,    70,    -1,   102,    -1,    -1,    -1,    -1,    -1,    -1,
      26,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    93,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    -1,    -1,
      66,    67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    78,    79,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    88,    -1,    26,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   102,    -1,   104,    41,
      42,    43,    44,    45,    46,    47,    -1,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    -1,    -1,    66,    67,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    78,    79,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    88,    -1,    26,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     102,    -1,   104,    41,    42,    43,    44,    45,    46,    47,
      -1,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    -1,    -1,    66,    67,
       3,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      78,    79,    -1,    16,    17,    18,    -1,    -1,    -1,    -1,
      88,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   102,    38,    39,    40,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,     3,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    74,    -1,    76,    16,    17,    18,    -1,    -1,    21,
      -1,    -1,    -1,    -1,    -1,    27,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    -1,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,     3,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    74,    -1,    -1,    16,    17,    18,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    -1,    -1,    -1,    38,    39,    40,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,     3,    -1,    -1,    -1,    -1,    -1,    -1,
      71,    72,    73,    74,    -1,    -1,    16,    17,    18,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    28,    -1,
       3,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    38,    39,
      40,    -1,    -1,    16,    17,    18,    -1,    -1,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    -1,    38,    39,    40,    -1,    -1,
      -1,    -1,    -1,    -1,    74,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,     3,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      73,    74,    -1,    -1,    16,    17,    18,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    38,    39,    40,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,     3,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    73,    74,    -1,    -1,    16,    17,    18,    -1,    -1,
      -1,    22,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    38,    39,    40,
      -1,    -1,    16,    17,    18,    -1,    -1,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    -1,    38,    39,    40,    -1,    -1,    -1,
      -1,    18,    19,    74,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      74,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    16,    17,    18,    21,    27,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    74,   107,   108,   110,   113,   120,   121,   122,
     123,   127,   136,   137,   138,   140,    26,    41,    42,    43,
      44,    45,    46,    47,    61,    66,    67,    78,    79,    88,
     102,   104,   130,   131,   132,   133,   134,   135,   137,   139,
     114,     3,   111,     1,    99,   100,   130,     0,   110,   113,
     120,    19,    98,   141,    18,    19,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,   128,    99,    99,    48,   129,   130,   131,   100,
     102,   134,     1,   134,   134,     1,   130,   131,     1,   130,
       5,     6,    68,    69,    70,    93,   126,   127,     4,     7,
       8,     9,    12,    13,    99,    78,    79,    80,    81,    82,
      14,    83,    84,    85,    86,    87,   102,    48,     1,    48,
      66,   109,    61,   132,    75,    48,    61,   137,   129,     3,
     131,   131,     3,    98,   132,   103,     1,   103,     1,   130,
       1,   130,     1,   131,     3,   128,     1,   131,     1,   131,
       1,   131,     1,   131,     1,   131,     1,   131,     1,   131,
       1,   133,     1,   133,     1,   134,     1,   134,     1,   134,
     134,   134,   134,   134,   134,   134,     1,   129,   115,    98,
      98,     3,     3,   101,   119,     1,     3,     3,     3,     1,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,   128,   131,   101,     1,   105,
     119,     3,   103,    98,   109,   109,   112,    99,    76,   121,
       1,   131,    71,    72,    73,   124,   125,   116,   119,   131,
     130,   119,     3,    72,    73,   125,    23,    28,     3,   126,
      73,   119,     3,   117,     3,     3,     3,    73,    98,   119,
       3,    24,     3,   118,   119,    22,     3
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (parm, scanner, csound, astTree, YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (&yylval, YYLEX_PARAM)
#else
# define YYLEX yylex (&yylval, csound, scanner)
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value, parm, scanner, csound, astTree); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, PARSE_PARM *parm, void *scanner, CSOUND * csound, TREE * astTree)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, parm, scanner, csound, astTree)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    PARSE_PARM *parm;
    void *scanner;
    CSOUND * csound;
    TREE * astTree;
#endif
{
  if (!yyvaluep)
    return;
  YYUSE (parm);
  YYUSE (scanner);
  YYUSE (csound);
  YYUSE (astTree);
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, PARSE_PARM *parm, void *scanner, CSOUND * csound, TREE * astTree)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, parm, scanner, csound, astTree)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    PARSE_PARM *parm;
    void *scanner;
    CSOUND * csound;
    TREE * astTree;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep, parm, scanner, csound, astTree);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule, PARSE_PARM *parm, void *scanner, CSOUND * csound, TREE * astTree)
#else
static void
yy_reduce_print (yyvsp, yyrule, parm, scanner, csound, astTree)
    YYSTYPE *yyvsp;
    int yyrule;
    PARSE_PARM *parm;
    void *scanner;
    CSOUND * csound;
    TREE * astTree;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       , parm, scanner, csound, astTree);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule, parm, scanner, csound, astTree); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, PARSE_PARM *parm, void *scanner, CSOUND * csound, TREE * astTree)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, parm, scanner, csound, astTree)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    PARSE_PARM *parm;
    void *scanner;
    CSOUND * csound;
    TREE * astTree;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (parm);
  YYUSE (scanner);
  YYUSE (csound);
  YYUSE (astTree);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (PARSE_PARM *parm, void *scanner, CSOUND * csound, TREE * astTree);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */





/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (PARSE_PARM *parm, void *scanner, CSOUND * csound, TREE * astTree)
#else
int
yyparse (parm, scanner, csound, astTree)
    PARSE_PARM *parm;
    void *scanner;
    CSOUND * csound;
    TREE * astTree;
#endif
#endif
{
/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

    /* Number of syntax errors so far.  */
    int yynerrs;

    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1464 of yacc.c  */
#line 179 "csound_orc.y"
    {
                            *astTree = *((TREE *)(yyvsp[(1) - (1)]));
                            csound->synterrcnt = csound_orcnerrs;
                            //print_tree(csound, "ALL", $1);
                        ;}
    break;

  case 3:

/* Line 1464 of yacc.c  */
#line 187 "csound_orc.y"
    {
                        (yyval) = appendToTree(csound, (yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]));
                        ;}
    break;

  case 4:

/* Line 1464 of yacc.c  */
#line 191 "csound_orc.y"
    {
                        (yyval) = appendToTree(csound, (yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]));
                        ;}
    break;

  case 5:

/* Line 1464 of yacc.c  */
#line 195 "csound_orc.y"
    {
                        (yyval) = appendToTree(csound, (yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]));
                        ;}
    break;

  case 9:

/* Line 1464 of yacc.c  */
#line 204 "csound_orc.y"
    { (yyval) = make_node(csound,LINE, T_INSTLIST,
                               make_leaf(csound, LINE,
                                         INTEGER_TOKEN, (ORCTOKEN *)(yyvsp[(1) - (3)])), (yyvsp[(3) - (3)])); ;}
    break;

  case 10:

/* Line 1464 of yacc.c  */
#line 208 "csound_orc.y"
    {
#ifdef PARCS
                  csp_orc_sa_instr_add(csound, ((ORCTOKEN *)(yyvsp[(1) - (3)]))->lexeme);
#endif
                  (yyval) = make_node(csound,LINE, T_INSTLIST,
                               make_leaf(csound, LINE,
                                         T_IDENT, (ORCTOKEN *)(yyvsp[(1) - (3)])), (yyvsp[(3) - (3)])); ;}
    break;

  case 11:

/* Line 1464 of yacc.c  */
#line 215 "csound_orc.y"
    { (yyval) = make_leaf(csound, LINE,
                                           INTEGER_TOKEN, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 12:

/* Line 1464 of yacc.c  */
#line 217 "csound_orc.y"
    { (yyval) = make_leaf(csound, LINE, T_IDENT, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 13:

/* Line 1464 of yacc.c  */
#line 221 "csound_orc.y"
    { namedInstrFlag = 1; ;}
    break;

  case 14:

/* Line 1464 of yacc.c  */
#line 223 "csound_orc.y"
    { namedInstrFlag = 0;
#ifdef PARCS
                  csp_orc_sa_instr_add_tree(csound, (yyvsp[(3) - (4)]));
#endif
                ;}
    break;

  case 15:

/* Line 1464 of yacc.c  */
#line 229 "csound_orc.y"
    {
                    (yyval) = make_node(csound, LINE, INSTR_TOKEN, (yyvsp[(3) - (8)]), (yyvsp[(6) - (8)]));
#ifdef PARCS
                    csp_orc_sa_instr_finalize(csound);
#endif
                ;}
    break;

  case 16:

/* Line 1464 of yacc.c  */
#line 236 "csound_orc.y"
    {
                    namedInstrFlag = 0;
                    csound->Message(csound, Str("No number following instr\n"));
#ifdef PARCS
                    csp_orc_sa_instr_finalize(csound);
#endif
                ;}
    break;

  case 17:

/* Line 1464 of yacc.c  */
#line 246 "csound_orc.y"
    { udoflag = -2; ;}
    break;

  case 18:

/* Line 1464 of yacc.c  */
#line 248 "csound_orc.y"
    { udoflag = -1; ;}
    break;

  case 19:

/* Line 1464 of yacc.c  */
#line 250 "csound_orc.y"
    { udoflag = 0;;}
    break;

  case 20:

/* Line 1464 of yacc.c  */
#line 252 "csound_orc.y"
    { udoflag = 1; ;}
    break;

  case 21:

/* Line 1464 of yacc.c  */
#line 254 "csound_orc.y"
    {
                udoflag = 2;
                add_udo_definition(csound,
                        ((ORCTOKEN *)(yyvsp[(3) - (11)]))->lexeme,
                        ((ORCTOKEN *)(yyvsp[(7) - (11)]))->lexeme,
                        ((ORCTOKEN *)(yyvsp[(10) - (11)]))->lexeme);
              ;}
    break;

  case 22:

/* Line 1464 of yacc.c  */
#line 262 "csound_orc.y"
    {
                TREE *udoTop = make_leaf(csound, LINE, UDO_TOKEN,
                                         (ORCTOKEN *)NULL);
                TREE *ident = make_leaf(csound, LINE, T_IDENT,
                                        (ORCTOKEN *)(yyvsp[(3) - (15)]));
                TREE *udoAns = make_leaf(csound, LINE, UDO_ANS_TOKEN,
                                         (ORCTOKEN *)(yyvsp[(7) - (15)]));
                TREE *udoArgs = make_leaf(csound, LINE, UDO_ARGS_TOKEN,
                                          (ORCTOKEN *)(yyvsp[(10) - (15)]));
                udoflag = -1;
                if (UNLIKELY(PARSER_DEBUG))
                  csound->Message(csound, "UDO COMPLETE\n");

                udoTop->left = ident;
                ident->left = udoAns;
                ident->right = udoArgs;

                udoTop->right = (TREE *)(yyvsp[(13) - (15)]);

                (yyval) = udoTop;

                if (UNLIKELY(PARSER_DEBUG))
                  print_tree(csound, "UDO\n", (TREE *)(yyval));

              ;}
    break;

  case 23:

/* Line 1464 of yacc.c  */
#line 291 "csound_orc.y"
    {
                    (yyval) = appendToTree(csound, (TREE *)(yyvsp[(1) - (2)]), (TREE *)(yyvsp[(2) - (2)]));
                ;}
    break;

  case 24:

/* Line 1464 of yacc.c  */
#line 294 "csound_orc.y"
    { (yyval) = NULL; ;}
    break;

  case 25:

/* Line 1464 of yacc.c  */
#line 298 "csound_orc.y"
    {

                  TREE *ans = make_leaf(csound,LINE, '=', (ORCTOKEN *)(yyvsp[(2) - (4)]));
                  ans->left = (TREE *)(yyvsp[(1) - (4)]);
                  ans->right = (TREE *)(yyvsp[(3) - (4)]);
                  /* ans->value->lexeme = get_assignment_type(csound,
                      ans->left->value->lexeme, ans->right->value->lexeme); */

                  (yyval) = ans;
                ;}
    break;

  case 26:

/* Line 1464 of yacc.c  */
#line 308 "csound_orc.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 27:

/* Line 1464 of yacc.c  */
#line 313 "csound_orc.y"
    {
                  TREE *ans = make_leaf(csound,LINE, '=', (ORCTOKEN *)(yyvsp[(2) - (4)]));
                  ans->left = (TREE *)(yyvsp[(1) - (4)]);
                  ans->right = (TREE *)(yyvsp[(3) - (4)]);
                  /* ans->value->lexeme = get_assignment_type(csound,
                     ans->left->value->lexeme, ans->right->value->lexeme); */

                  (yyval) = ans;
#ifdef PARCS
                  csp_orc_sa_global_read_write_add_list(csound,
                                    csp_orc_sa_globals_find(csound, ans->left),
                                    csp_orc_sa_globals_find(csound, ans->right));
#endif
                ;}
    break;

  case 28:

/* Line 1464 of yacc.c  */
#line 328 "csound_orc.y"
    {
              ORCTOKEN *op = lookup_token(csound, "#copytab", NULL);
              TREE *ans = make_leaf(csound,LINE, T_OPCODE, op);
              ans->left = make_leaf(csound,LINE, T_IDENT_T, (ORCTOKEN *)(yyvsp[(1) - (4)]));
              ans->right = make_leaf(csound,LINE, T_IDENT_T, (ORCTOKEN *)(yyvsp[(3) - (4)]));
              (yyval) = ans;
          ;}
    break;

  case 29:

/* Line 1464 of yacc.c  */
#line 336 "csound_orc.y"
    {
              TREE *ans = make_leaf(csound,LINE, '=', (ORCTOKEN *)(yyvsp[(5) - (7)]));
              ans->left = make_leaf(csound,LINE, T_IDENT_T, (ORCTOKEN *)(yyvsp[(1) - (7)]));
              ans->right = appendToTree(csound, (yyvsp[(3) - (7)]), (yyvsp[(6) - (7)]));
                  /* ans->value->lexeme = get_assignment_type(csound,
                     ans->left->value->lexeme, ans->right->value->lexeme); */
              //print_tree(csound, "TABLE ASSIGN", ans);
              (yyval) = ans;
  /* #ifdef PARCS */
  /*                   csp_orc_sa_global_read_write_add_list(csound, */
  /*                      csp_orc_sa_globals_find(csound, ans->left) */
  /*                   csp_orc_sa_globals_find(csound, ans->right)); */
  /* #endif */
          ;}
    break;

  case 30:

/* Line 1464 of yacc.c  */
#line 351 "csound_orc.y"
    {

                  (yyvsp[(2) - (4)])->left = (yyvsp[(1) - (4)]);
                  (yyvsp[(2) - (4)])->right = (yyvsp[(3) - (4)]);

                  (yyval) = (yyvsp[(2) - (4)]);
#ifdef PARCS
                  csp_orc_sa_global_read_write_add_list(csound,
                                    csp_orc_sa_globals_find(csound, (yyvsp[(2) - (4)])->left),
                                    csp_orc_sa_globals_find(csound, (yyvsp[(2) - (4)])->right));
                  csp_orc_sa_interlocks(csound, (yyvsp[(2) - (4)])->value);
#endif
                ;}
    break;

  case 31:

/* Line 1464 of yacc.c  */
#line 365 "csound_orc.y"
    {
                  ((TREE *)(yyvsp[(1) - (3)]))->left = NULL;
                  ((TREE *)(yyvsp[(1) - (3)]))->right = (TREE *)(yyvsp[(2) - (3)]);

                  (yyval) = (yyvsp[(1) - (3)]);
#ifdef PARCS
                  csp_orc_sa_global_read_add_list(csound,
                                  csp_orc_sa_globals_find(csound,
                                                          (yyvsp[(1) - (3)])->right));
                  csp_orc_sa_interlocks(csound, (yyvsp[(1) - (3)])->value);
#endif
                ;}
    break;

  case 32:

/* Line 1464 of yacc.c  */
#line 378 "csound_orc.y"
    {
                    (yyval) = make_leaf(csound,LINE, LABEL_TOKEN, (ORCTOKEN *)(yyvsp[(1) - (1)]));
                ;}
    break;

  case 33:

/* Line 1464 of yacc.c  */
#line 382 "csound_orc.y"
    {
                    (yyvsp[(1) - (3)])->left = NULL;
                    (yyvsp[(1) - (3)])->right = make_leaf(csound, LINE,
                                          LABEL_TOKEN, (ORCTOKEN *)(yyvsp[(2) - (3)]));
                    (yyval) = (yyvsp[(1) - (3)]);
                ;}
    break;

  case 34:

/* Line 1464 of yacc.c  */
#line 389 "csound_orc.y"
    {
                    (yyvsp[(3) - (5)])->left = NULL;
                    (yyvsp[(3) - (5)])->right = make_leaf(csound, LINE,
                                          LABEL_TOKEN, (ORCTOKEN *)(yyvsp[(4) - (5)]));
                    (yyval) = make_node(csound,LINE, IF_TOKEN, (yyvsp[(2) - (5)]), (yyvsp[(3) - (5)]));
                ;}
    break;

  case 36:

/* Line 1464 of yacc.c  */
#line 397 "csound_orc.y"
    {
                  (yyval) = make_leaf(csound,LINE, UNTIL_TOKEN, (ORCTOKEN *)(yyvsp[(1) - (5)]));
                  (yyval)->left = (yyvsp[(2) - (5)]);
                  (yyval)->right = (yyvsp[(4) - (5)]);
              ;}
    break;

  case 37:

/* Line 1464 of yacc.c  */
#line 402 "csound_orc.y"
    { (yyval) = NULL; ;}
    break;

  case 38:

/* Line 1464 of yacc.c  */
#line 404 "csound_orc.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 39:

/* Line 1464 of yacc.c  */
#line 406 "csound_orc.y"
    { csound->Message(csound,
                      "Unexpected untyped word %s when expecting a variable\n", 
                      ((ORCTOKEN*)(yyvsp[(1) - (2)]))->lexeme);
                (yyval) = NULL;
              ;}
    break;

  case 40:

/* Line 1464 of yacc.c  */
#line 411 "csound_orc.y"
    { (yyval) = appendToTree(csound, (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 41:

/* Line 1464 of yacc.c  */
#line 413 "csound_orc.y"
    { csound->Message(csound,
                      "Unexpected untyped word %s when expecting a variable\n", 
                               ((ORCTOKEN*)(yyvsp[(3) - (4)]))->lexeme);
                (yyval) = appendToTree(csound, (yyvsp[(1) - (4)]), NULL);
              ;}
    break;

  case 42:

/* Line 1464 of yacc.c  */
#line 421 "csound_orc.y"
    {
            (yyvsp[(3) - (7)])->right = (yyvsp[(5) - (7)]);
            (yyval) = make_node(csound,LINE, IF_TOKEN, (yyvsp[(2) - (7)]), (yyvsp[(3) - (7)]));
            //print_tree(csound, "if-endif", $$);
          ;}
    break;

  case 43:

/* Line 1464 of yacc.c  */
#line 428 "csound_orc.y"
    {
            (yyvsp[(3) - (9)])->right = (yyvsp[(5) - (9)]);
            (yyvsp[(3) - (9)])->next = make_node(csound,LINE, ELSE_TOKEN, NULL, (yyvsp[(7) - (9)]));
            (yyval) = make_node(csound,LINE, IF_TOKEN, (yyvsp[(2) - (9)]), (yyvsp[(3) - (9)]));
            //print_tree(csound, "if-else", $$);

          ;}
    break;

  case 44:

/* Line 1464 of yacc.c  */
#line 436 "csound_orc.y"
    {
            if (UNLIKELY(PARSER_DEBUG))
                csound->Message(csound, "IF-ELSEIF FOUND!\n");
            (yyvsp[(3) - (8)])->right = (yyvsp[(5) - (8)]);
            (yyvsp[(3) - (8)])->next = (yyvsp[(6) - (8)]);
            (yyval) = make_node(csound, LINE, IF_TOKEN, (yyvsp[(2) - (8)]), (yyvsp[(3) - (8)]));
            //print_tree(csound, "if-elseif\n", $$);
          ;}
    break;

  case 45:

/* Line 1464 of yacc.c  */
#line 446 "csound_orc.y"
    {
            TREE * tempLastNode;

            (yyvsp[(3) - (10)])->right = (yyvsp[(5) - (10)]);
            (yyvsp[(3) - (10)])->next = (yyvsp[(6) - (10)]);

            (yyval) = make_node(csound, LINE, IF_TOKEN, (yyvsp[(2) - (10)]), (yyvsp[(3) - (10)]));

            tempLastNode = (yyval);

            while (tempLastNode->right!=NULL && tempLastNode->right->next!=NULL) {
                tempLastNode = tempLastNode->right->next;
            }

            tempLastNode->right->next = make_node(csound, LINE,
                                                  ELSE_TOKEN, NULL, (yyvsp[(8) - (10)]));
            //print_tree(csound, "IF TREE", $$);
          ;}
    break;

  case 46:

/* Line 1464 of yacc.c  */
#line 467 "csound_orc.y"
    {
                TREE * tempLastNode = (yyvsp[(1) - (2)]);

                while (tempLastNode->right!=NULL &&
                       tempLastNode->right->next!=NULL) {
                    tempLastNode = tempLastNode->right->next;
                }

                tempLastNode->right->next = (yyvsp[(2) - (2)]);
                (yyval) = (yyvsp[(1) - (2)]);
            ;}
    break;

  case 47:

/* Line 1464 of yacc.c  */
#line 478 "csound_orc.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 48:

/* Line 1464 of yacc.c  */
#line 482 "csound_orc.y"
    {
                if (UNLIKELY(PARSER_DEBUG))
                  csound->Message(csound, "ELSEIF FOUND!\n");
                (yyvsp[(3) - (5)])->right = (yyvsp[(5) - (5)]);
                (yyval) = make_node(csound,LINE, ELSEIF_TOKEN, (yyvsp[(2) - (5)]), (yyvsp[(3) - (5)]));
                //print_tree(csound, "ELSEIF", $$);
            ;}
    break;

  case 49:

/* Line 1464 of yacc.c  */
#line 492 "csound_orc.y"
    { (yyval) = make_leaf(csound,LINE, THEN_TOKEN, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 50:

/* Line 1464 of yacc.c  */
#line 494 "csound_orc.y"
    { (yyval) = make_leaf(csound,LINE, KTHEN_TOKEN, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 51:

/* Line 1464 of yacc.c  */
#line 496 "csound_orc.y"
    { (yyval) = make_leaf(csound,LINE, ITHEN_TOKEN, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 52:

/* Line 1464 of yacc.c  */
#line 500 "csound_orc.y"
    { (yyval) = make_leaf(csound,LINE, GOTO_TOKEN, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 53:

/* Line 1464 of yacc.c  */
#line 502 "csound_orc.y"
    { (yyval) = make_leaf(csound,LINE, KGOTO_TOKEN, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 54:

/* Line 1464 of yacc.c  */
#line 504 "csound_orc.y"
    { (yyval) = make_leaf(csound,LINE, IGOTO_TOKEN, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 55:

/* Line 1464 of yacc.c  */
#line 508 "csound_orc.y"
    { (yyval) = (TREE *)(yyvsp[(1) - (1)]); ;}
    break;

  case 56:

/* Line 1464 of yacc.c  */
#line 509 "csound_orc.y"
    { (yyval) = (TREE *)(yyvsp[(1) - (1)]); ;}
    break;

  case 57:

/* Line 1464 of yacc.c  */
#line 510 "csound_orc.y"
    { (yyval) = (TREE *)(yyvsp[(1) - (1)]); ;}
    break;

  case 58:

/* Line 1464 of yacc.c  */
#line 511 "csound_orc.y"
    { (yyval) = (TREE *)(yyvsp[(1) - (1)]); ;}
    break;

  case 59:

/* Line 1464 of yacc.c  */
#line 512 "csound_orc.y"
    { (yyval) = (TREE *)(yyvsp[(1) - (1)]); ;}
    break;

  case 60:

/* Line 1464 of yacc.c  */
#line 513 "csound_orc.y"
    { (yyval) = (TREE *)(yyvsp[(1) - (1)]); ;}
    break;

  case 61:

/* Line 1464 of yacc.c  */
#line 514 "csound_orc.y"
    { (yyval) = (TREE *)(yyvsp[(1) - (1)]); ;}
    break;

  case 62:

/* Line 1464 of yacc.c  */
#line 515 "csound_orc.y"
    { (yyval) = (TREE *)(yyvsp[(1) - (1)]); ;}
    break;

  case 63:

/* Line 1464 of yacc.c  */
#line 516 "csound_orc.y"
    { (yyval) = (TREE *)(yyvsp[(1) - (1)]); ;}
    break;

  case 64:

/* Line 1464 of yacc.c  */
#line 517 "csound_orc.y"
    { (yyval) = (TREE *)(yyvsp[(1) - (1)]); ;}
    break;

  case 65:

/* Line 1464 of yacc.c  */
#line 518 "csound_orc.y"
    { (yyval) = (TREE *)(yyvsp[(1) - (1)]); ;}
    break;

  case 66:

/* Line 1464 of yacc.c  */
#line 519 "csound_orc.y"
    { (yyval) = (TREE *)(yyvsp[(1) - (1)]); ;}
    break;

  case 67:

/* Line 1464 of yacc.c  */
#line 520 "csound_orc.y"
    { (yyval) = (TREE *)(yyvsp[(1) - (1)]); ;}
    break;

  case 68:

/* Line 1464 of yacc.c  */
#line 521 "csound_orc.y"
    { (yyval) = (TREE *)(yyvsp[(1) - (1)]); ;}
    break;

  case 69:

/* Line 1464 of yacc.c  */
#line 522 "csound_orc.y"
    { (yyval) = (TREE *)(yyvsp[(1) - (1)]); ;}
    break;

  case 70:

/* Line 1464 of yacc.c  */
#line 523 "csound_orc.y"
    { (yyval) = (TREE *)(yyvsp[(1) - (1)]); ;}
    break;

  case 71:

/* Line 1464 of yacc.c  */
#line 524 "csound_orc.y"
    { (yyval) = (TREE *)(yyvsp[(1) - (1)]); ;}
    break;

  case 72:

/* Line 1464 of yacc.c  */
#line 525 "csound_orc.y"
    { (yyval) = (TREE *)(yyvsp[(1) - (1)]); ;}
    break;

  case 73:

/* Line 1464 of yacc.c  */
#line 530 "csound_orc.y"
    {
                    /* $$ = make_node(',', $1, $3); */
                    (yyval) = appendToTree(csound, (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
                ;}
    break;

  case 74:

/* Line 1464 of yacc.c  */
#line 535 "csound_orc.y"
    {
                    /* $$ = make_node(',', $1, $3); */
                    (yyval) = appendToTree(csound, (yyvsp[(1) - (3)]),
                                      make_leaf(csound, LINE,
                                                LABEL_TOKEN, (ORCTOKEN *)(yyvsp[(3) - (3)])));
                ;}
    break;

  case 76:

/* Line 1464 of yacc.c  */
#line 542 "csound_orc.y"
    { (yyval) = (yyvsp[(1) - (1)]);     ;}
    break;

  case 77:

/* Line 1464 of yacc.c  */
#line 543 "csound_orc.y"
    { (yyval) = make_leaf(csound, LINE, LABEL_TOKEN, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 78:

/* Line 1464 of yacc.c  */
#line 544 "csound_orc.y"
    { (yyval) = NULL; ;}
    break;

  case 79:

/* Line 1464 of yacc.c  */
#line 547 "csound_orc.y"
    { (yyval) = (yyvsp[(2) - (3)]); ;}
    break;

  case 80:

/* Line 1464 of yacc.c  */
#line 548 "csound_orc.y"
    { (yyval) = make_node(csound, LINE, S_LE, (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 82:

/* Line 1464 of yacc.c  */
#line 550 "csound_orc.y"
    { (yyval) = make_node(csound, LINE, S_GE, (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 84:

/* Line 1464 of yacc.c  */
#line 552 "csound_orc.y"
    { (yyval) = make_node(csound, LINE, S_NEQ, (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 86:

/* Line 1464 of yacc.c  */
#line 554 "csound_orc.y"
    { (yyval) = make_node(csound, LINE, S_EQ, (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 88:

/* Line 1464 of yacc.c  */
#line 556 "csound_orc.y"
    { (yyval) = make_node(csound, LINE, S_EQ, (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 90:

/* Line 1464 of yacc.c  */
#line 558 "csound_orc.y"
    { (yyval) = make_node(csound, LINE, S_GT, (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 92:

/* Line 1464 of yacc.c  */
#line 560 "csound_orc.y"
    { (yyval) = make_node(csound, LINE, S_LT, (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 94:

/* Line 1464 of yacc.c  */
#line 562 "csound_orc.y"
    { (yyval) = make_node(csound, LINE, S_AND, (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 96:

/* Line 1464 of yacc.c  */
#line 564 "csound_orc.y"
    { (yyval) = make_node(csound, LINE, S_OR, (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 98:

/* Line 1464 of yacc.c  */
#line 566 "csound_orc.y"
    { (yyval) = make_node(csound, LINE,
                                                    S_UNOT, (yyvsp[(2) - (2)]), NULL); ;}
    break;

  case 100:

/* Line 1464 of yacc.c  */
#line 572 "csound_orc.y"
    { (yyval) = make_node(csound,LINE, '?', (yyvsp[(1) - (5)]),
                             make_node(csound, LINE, ':', (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)]))); ;}
    break;

  case 104:

/* Line 1464 of yacc.c  */
#line 577 "csound_orc.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 105:

/* Line 1464 of yacc.c  */
#line 580 "csound_orc.y"
    { (yyval) = make_node(csound, LINE, '+', (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 107:

/* Line 1464 of yacc.c  */
#line 582 "csound_orc.y"
    { (yyval) = make_node(csound ,LINE, '-', (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 109:

/* Line 1464 of yacc.c  */
#line 584 "csound_orc.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 110:

/* Line 1464 of yacc.c  */
#line 587 "csound_orc.y"
    { (yyval) = make_node(csound, LINE, '*', (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 112:

/* Line 1464 of yacc.c  */
#line 589 "csound_orc.y"
    { (yyval) = make_node(csound, LINE, '/', (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 114:

/* Line 1464 of yacc.c  */
#line 591 "csound_orc.y"
    { (yyval) = make_node(csound, LINE, '%', (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 116:

/* Line 1464 of yacc.c  */
#line 593 "csound_orc.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 117:

/* Line 1464 of yacc.c  */
#line 596 "csound_orc.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 118:

/* Line 1464 of yacc.c  */
#line 597 "csound_orc.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 119:

/* Line 1464 of yacc.c  */
#line 599 "csound_orc.y"
    {
              (yyval) = make_node(csound,LINE, S_TABREF,
                             make_leaf(csound, LINE,
                                       T_IDENT_T, (ORCTOKEN*)(yyvsp[(1) - (4)])), (yyvsp[(3) - (4)]));
          ;}
    break;

  case 120:

/* Line 1464 of yacc.c  */
#line 605 "csound_orc.y"
    {
                (yyval) = make_node(csound,LINE, S_UMINUS, NULL, (yyvsp[(2) - (2)]));
            ;}
    break;

  case 121:

/* Line 1464 of yacc.c  */
#line 609 "csound_orc.y"
    {
                (yyval) = (yyvsp[(2) - (2)]);
            ;}
    break;

  case 122:

/* Line 1464 of yacc.c  */
#line 612 "csound_orc.y"
    { (yyval) = make_node(csound, LINE, '^', (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 123:

/* Line 1464 of yacc.c  */
#line 613 "csound_orc.y"
    { (yyval) = make_node(csound, LINE, '|', (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 124:

/* Line 1464 of yacc.c  */
#line 614 "csound_orc.y"
    { (yyval) = make_node(csound, LINE, '&', (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 125:

/* Line 1464 of yacc.c  */
#line 615 "csound_orc.y"
    { (yyval) = make_node(csound, LINE, '#', (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 126:

/* Line 1464 of yacc.c  */
#line 617 "csound_orc.y"
    { (yyval) = make_node(csound, LINE, S_BITSHIFT_LEFT, (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 127:

/* Line 1464 of yacc.c  */
#line 619 "csound_orc.y"
    { (yyval) = make_node(csound, LINE, S_BITSHIFT_RIGHT, (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 128:

/* Line 1464 of yacc.c  */
#line 621 "csound_orc.y"
    { (yyval) = make_node(csound, LINE, '~', NULL, (yyvsp[(2) - (2)]));;}
    break;

  case 130:

/* Line 1464 of yacc.c  */
#line 623 "csound_orc.y"
    { (yyval) = (yyvsp[(2) - (3)]); ;}
    break;

  case 133:

/* Line 1464 of yacc.c  */
#line 627 "csound_orc.y"
    {
                (yyvsp[(1) - (4)])->left = NULL;
                (yyvsp[(1) - (4)])->right = (yyvsp[(3) - (4)]);

                (yyval) = (yyvsp[(1) - (4)]);
            ;}
    break;

  case 135:

/* Line 1464 of yacc.c  */
#line 636 "csound_orc.y"
    { 
             printf("FUNCTION ans=%p, token=%p %p\n",
                    (yyvsp[(1) - (1)]), ((ORCTOKEN *)(yyvsp[(1) - (1)]))->value);
#ifdef PARCS
    //                if ((ORCTOKEN *)$1->value != 0)
             csp_orc_sa_interlocksf(csound, ((ORCTOKEN *)(yyvsp[(1) - (1)]))->value);
#endif
             (yyval) = make_leaf(csound, LINE, T_FUNCTION, (ORCTOKEN *)(yyvsp[(1) - (1)])); 
                ;}
    break;

  case 136:

/* Line 1464 of yacc.c  */
#line 646 "csound_orc.y"
    { (yyval) = make_leaf(csound, LINE,
                                             SRATE_TOKEN, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 137:

/* Line 1464 of yacc.c  */
#line 648 "csound_orc.y"
    { (yyval) = make_leaf(csound, LINE,
                                             KRATE_TOKEN, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 138:

/* Line 1464 of yacc.c  */
#line 650 "csound_orc.y"
    { (yyval) = make_leaf(csound, LINE,
                                             KSMPS_TOKEN, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 139:

/* Line 1464 of yacc.c  */
#line 652 "csound_orc.y"
    { (yyval) = make_leaf(csound, LINE,
                                             NCHNLS_TOKEN, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 140:

/* Line 1464 of yacc.c  */
#line 654 "csound_orc.y"
    { (yyval) = make_leaf(csound, LINE,
                                             NCHNLSI_TOKEN, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 141:

/* Line 1464 of yacc.c  */
#line 656 "csound_orc.y"
    { (yyval) = make_leaf(csound, LINE,
                                             ZERODBFS_TOKEN, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 142:

/* Line 1464 of yacc.c  */
#line 660 "csound_orc.y"
    { (yyval) = make_leaf(csound, LINE, T_IDENT_I, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 143:

/* Line 1464 of yacc.c  */
#line 661 "csound_orc.y"
    { (yyval) = make_leaf(csound, LINE, T_IDENT_K, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 144:

/* Line 1464 of yacc.c  */
#line 662 "csound_orc.y"
    { (yyval) = make_leaf(csound, LINE, T_IDENT_F, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 145:

/* Line 1464 of yacc.c  */
#line 663 "csound_orc.y"
    { (yyval) = make_leaf(csound, LINE, T_IDENT_W, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 146:

/* Line 1464 of yacc.c  */
#line 664 "csound_orc.y"
    { (yyval) = make_leaf(csound, LINE, T_IDENT_S, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 147:

/* Line 1464 of yacc.c  */
#line 665 "csound_orc.y"
    { (yyval) = make_leaf(csound, LINE, T_IDENT_T, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 148:

/* Line 1464 of yacc.c  */
#line 666 "csound_orc.y"
    { (yyval) = make_leaf(csound, LINE, T_IDENT_A, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 149:

/* Line 1464 of yacc.c  */
#line 667 "csound_orc.y"
    { (yyval) = make_leaf(csound, LINE, T_IDENT_P, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 150:

/* Line 1464 of yacc.c  */
#line 668 "csound_orc.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 151:

/* Line 1464 of yacc.c  */
#line 671 "csound_orc.y"
    { (yyval) = make_leaf(csound, LINE, T_IDENT_GI, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 152:

/* Line 1464 of yacc.c  */
#line 672 "csound_orc.y"
    { (yyval) = make_leaf(csound, LINE, T_IDENT_GK, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 153:

/* Line 1464 of yacc.c  */
#line 673 "csound_orc.y"
    { (yyval) = make_leaf(csound, LINE, T_IDENT_GF, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 154:

/* Line 1464 of yacc.c  */
#line 674 "csound_orc.y"
    { (yyval) = make_leaf(csound, LINE, T_IDENT_GW, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 155:

/* Line 1464 of yacc.c  */
#line 675 "csound_orc.y"
    { (yyval) = make_leaf(csound, LINE, T_IDENT_GS, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 156:

/* Line 1464 of yacc.c  */
#line 676 "csound_orc.y"
    { (yyval) = make_leaf(csound, LINE, T_IDENT_GS, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 157:

/* Line 1464 of yacc.c  */
#line 677 "csound_orc.y"
    { (yyval) = make_leaf(csound, LINE, T_IDENT_GA, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 158:

/* Line 1464 of yacc.c  */
#line 680 "csound_orc.y"
    { (yyval) = make_leaf(csound, LINE,
                                           INTEGER_TOKEN, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 159:

/* Line 1464 of yacc.c  */
#line 682 "csound_orc.y"
    { (yyval) = make_leaf(csound, LINE,
                                           NUMBER_TOKEN, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 160:

/* Line 1464 of yacc.c  */
#line 684 "csound_orc.y"
    { (yyval) = make_leaf(csound, LINE,
                                           STRING_TOKEN, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 161:

/* Line 1464 of yacc.c  */
#line 686 "csound_orc.y"
    { (yyval) = make_leaf(csound, LINE,
                                           NUMBER_TOKEN, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 162:

/* Line 1464 of yacc.c  */
#line 688 "csound_orc.y"
    { (yyval) = make_leaf(csound, LINE,
                                           NUMBER_TOKEN, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 163:

/* Line 1464 of yacc.c  */
#line 690 "csound_orc.y"
    { (yyval) = make_leaf(csound, LINE,
                                           NUMBER_TOKEN, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 164:

/* Line 1464 of yacc.c  */
#line 692 "csound_orc.y"
    { (yyval) = make_leaf(csound, LINE,
                                           NUMBER_TOKEN, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 165:

/* Line 1464 of yacc.c  */
#line 694 "csound_orc.y"
    { (yyval) = make_leaf(csound, LINE,
                                           NUMBER_TOKEN, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 166:

/* Line 1464 of yacc.c  */
#line 696 "csound_orc.y"
    { (yyval) = make_leaf(csound, LINE,
                                            NUMBER_TOKEN, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 167:

/* Line 1464 of yacc.c  */
#line 701 "csound_orc.y"
    {
                if (UNLIKELY(PARSER_DEBUG))
                  csound->Message(csound, "opcode0 $1=%p (%s)\n",
                                  (yyvsp[(1) - (1)]),((ORCTOKEN *)(yyvsp[(1) - (1)]))->lexeme );
                (yyval) = make_leaf(csound,LINE, T_OPCODE0, (ORCTOKEN *)(yyvsp[(1) - (1)]));
            ;}
    break;

  case 168:

/* Line 1464 of yacc.c  */
#line 709 "csound_orc.y"
    { (yyval) = make_leaf(csound,LINE, T_OPCODE, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;



/* Line 1464 of yacc.c  */
#line 3362 "csound_orc.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (parm, scanner, csound, astTree, YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (parm, scanner, csound, astTree, yymsg);
	  }
	else
	  {
	    yyerror (parm, scanner, csound, astTree, YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval, parm, scanner, csound, astTree);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp, parm, scanner, csound, astTree);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (parm, scanner, csound, astTree, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval, parm, scanner, csound, astTree);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, parm, scanner, csound, astTree);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1684 of yacc.c  */
#line 712 "csound_orc.y"


#ifdef SOME_FINE_DAY
void
yyerror(char *s, ...)
{
  va_list ap;
  va_start(ap, s);

  if(yylloc.first_line)
    fprintf(stderr, "%d.%d-%d.%d: error: ",
            yylloc.first_line, yylloc.first_column,
	    yylloc.last_line, yylloc.last_column);
  vfprintf(stderr, s, ap);
  fprintf(stderr, "\n");

}

void
lyyerror(YYLTYPE t, char *s, ...)
{
  va_list ap;
  va_start(ap, s);

  if(t.first_line)
    fprintf(stderr, "%d.%d-%d.%d: error: ", t.first_line, t.first_column,
	    t.last_line, t.last_column);
  vfprintf(stderr, s, ap);
  fprintf(stderr, "\n");
}

#endif


