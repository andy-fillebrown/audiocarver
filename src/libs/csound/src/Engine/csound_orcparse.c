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
#line 161 "csound_orc.y"

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
extern void csound_orcerror(PARSE_PARM *, void *, CSOUND *, TREE*, char*);
extern void add_udo_definition(CSOUND*, char *, char *, char *);
extern ORCTOKEN *lookup_token(CSOUND*,char*,void*);


/* Line 189 of yacc.c  */
#line 114 "csound_orc.tab.c"

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
     S_COM = 258,
     S_Q = 259,
     S_COL = 260,
     S_NOT = 261,
     S_PLUS = 262,
     S_MINUS = 263,
     S_TIMES = 264,
     S_DIV = 265,
     S_MOD = 266,
     S_POW = 267,
     S_NL = 268,
     S_LB = 269,
     S_RB = 270,
     S_SLB = 271,
     S_SRB = 272,
     S_NEQ = 273,
     S_AND = 274,
     S_OR = 275,
     S_LT = 276,
     S_LE = 277,
     S_EQ = 278,
     S_ASSIGN = 279,
     S_TASSIGN = 280,
     S_TABREF = 281,
     S_GT = 282,
     S_GE = 283,
     S_BITAND = 284,
     S_BITOR = 285,
     S_NEQV = 286,
     S_BITSHL = 287,
     S_BITSHR = 288,
     S_BITNOT = 289,
     T_LABEL = 290,
     T_IF = 291,
     T_OPCODE0 = 292,
     T_OPCODE = 293,
     T_UDO = 294,
     T_UDOSTART = 295,
     T_UDOEND = 296,
     T_UDO_ANS = 297,
     T_UDO_ARGS = 298,
     T_ERROR = 299,
     T_FUNCTION = 300,
     T_INSTR = 301,
     T_ENDIN = 302,
     T_STRSET = 303,
     T_PSET = 304,
     T_CTRLINIT = 305,
     T_MASSIGN = 306,
     T_TURNON = 307,
     T_PREALLOC = 308,
     T_ZAKINIT = 309,
     T_FTGEN = 310,
     T_INIT = 311,
     T_GOTO = 312,
     T_KGOTO = 313,
     T_IGOTO = 314,
     T_SRATE = 315,
     T_KRATE = 316,
     T_KSMPS = 317,
     T_NCHNLS = 318,
     T_NCHNLSI = 319,
     T_0DBFS = 320,
     T_STRCONST = 321,
     T_IDENT = 322,
     T_IDENT_I = 323,
     T_IDENT_GI = 324,
     T_IDENT_K = 325,
     T_IDENT_GK = 326,
     T_IDENT_A = 327,
     T_IDENT_GA = 328,
     T_IDENT_W = 329,
     T_IDENT_GW = 330,
     T_IDENT_F = 331,
     T_IDENT_GF = 332,
     T_IDENT_S = 333,
     T_IDENT_GS = 334,
     T_IDENT_T = 335,
     T_IDENT_GT = 336,
     T_IDENT_P = 337,
     T_IDENT_B = 338,
     T_IDENT_b = 339,
     T_INTGR = 340,
     T_NUMBER = 341,
     T_THEN = 342,
     T_ITHEN = 343,
     T_KTHEN = 344,
     T_ELSEIF = 345,
     T_ELSE = 346,
     T_ENDIF = 347,
     T_UNTIL = 348,
     T_DO = 349,
     T_OD = 350,
     T_INSTLIST = 351,
     S_SLASH = 352,
     S_STAR = 353,
     S_UNOT = 354,
     S_UMINUS = 355,
     S_ATAT = 356,
     S_AT = 357,
     S_GEQ = 358,
     S_LEQ = 359,
     S_GOTO = 360,
     T_HIGHEST = 361
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
#line 262 "csound_orc.tab.c"

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
#define YYFINAL  76
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   2468

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  107
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  35
/* YYNRULES -- Number of rules.  */
#define YYNRULES  167
/* YYNRULES -- Number of states.  */
#define YYNSTATES  282

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   361

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106
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
     262,   268,   273,   277,   281,   285,   289,   293,   297,   301,
     305,   309,   313,   317,   321,   325,   329,   333,   337,   341,
     345,   349,   352,   355,   357,   361,   365,   369,   373,   375,
     379,   383,   387,   391,   395,   399,   401,   403,   405,   410,
     413,   416,   420,   424,   428,   432,   436,   440,   443,   446,
     450,   454,   457,   462,   466,   468,   470,   472,   474,   476,
     478,   480,   482,   484,   486,   488,   490,   492,   494,   496,
     498,   500,   502,   504,   506,   508,   510,   512,   514,   516,
     518,   520,   522,   524,   526,   528,   530,   532
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     108,     0,    -1,   109,    -1,   109,   121,    -1,   109,   111,
      -1,   109,   114,    -1,   121,    -1,   111,    -1,   114,    -1,
      85,     3,   110,    -1,    67,     3,   110,    -1,    85,    -1,
      67,    -1,    -1,    -1,    46,   112,   110,    13,   113,   120,
      47,    13,    -1,    46,    13,     1,    -1,    -1,    -1,    -1,
      -1,    -1,    40,   115,    67,   116,     3,   117,    42,   118,
       3,    43,    13,   119,   120,    41,    13,    -1,   120,   122,
      -1,    -1,   136,    24,   131,    13,    -1,   122,    -1,   137,
      24,   131,    13,    -1,    80,    24,    80,    13,    -1,    80,
      16,   132,    17,    24,   131,    13,    -1,   123,   141,   130,
      13,    -1,   140,   130,    13,    -1,    35,    -1,   128,   129,
      13,    -1,    36,   131,   128,   129,    13,    -1,   124,    -1,
      93,   131,    94,   120,    95,    -1,    13,    -1,   137,    -1,
      67,     1,    -1,   123,     3,   137,    -1,   123,     3,    67,
       1,    -1,    36,   131,   127,    13,   120,    92,    13,    -1,
      36,   131,   127,    13,   120,    91,   120,    92,    13,    -1,
      36,   131,   127,    13,   120,   125,    92,    13,    -1,    36,
     131,   127,    13,   120,   125,    91,   120,    92,    13,    -1,
     125,   126,    -1,   126,    -1,    90,   131,   127,    13,   120,
      -1,    87,    -1,    89,    -1,    88,    -1,    57,    -1,    58,
      -1,    59,    -1,    38,    -1,    37,    -1,    82,    -1,    68,
      -1,    69,    -1,    70,    -1,    71,    -1,    72,    -1,    73,
      -1,    74,    -1,    75,    -1,    76,    -1,    77,    -1,    78,
      -1,    79,    -1,    80,    -1,    81,    -1,    67,    -1,   130,
       3,   131,    -1,   130,     3,   129,    -1,   130,     3,     1,
      -1,   131,    -1,    67,    -1,    -1,   131,     4,   131,     5,
     131,    -1,   131,     4,   131,     5,     1,    -1,   131,     4,
     131,     1,    -1,   131,     4,     1,    -1,   131,    22,   131,
      -1,   131,    22,     1,    -1,   131,    28,   131,    -1,   131,
      28,     1,    -1,   131,    18,   131,    -1,   131,    18,     1,
      -1,   131,    23,   131,    -1,   131,    23,     1,    -1,   131,
      24,   131,    -1,   131,    24,     1,    -1,   131,    27,   131,
      -1,   131,    27,     1,    -1,   131,    21,   131,    -1,   131,
      21,     1,    -1,   131,    19,   131,    -1,   131,    19,     1,
      -1,   131,    20,   131,    -1,   131,    20,     1,    -1,     6,
     131,    -1,     6,     1,    -1,   132,    -1,   132,     7,   133,
      -1,   132,     7,     1,    -1,   132,     8,   133,    -1,   132,
       8,     1,    -1,   133,    -1,   133,     9,   134,    -1,   133,
       9,     1,    -1,   133,    10,   134,    -1,   133,    10,     1,
      -1,   133,    11,   134,    -1,   133,    11,     1,    -1,   134,
      -1,   137,    -1,   139,    -1,    80,    16,   132,    17,    -1,
       8,   134,    -1,     7,   134,    -1,   134,    12,   134,    -1,
     134,    30,   134,    -1,   134,    29,   134,    -1,   134,    31,
     134,    -1,   134,    32,   134,    -1,   134,    33,   134,    -1,
      34,   134,    -1,     8,     1,    -1,    14,   131,    15,    -1,
      14,   131,     1,    -1,    14,     1,    -1,   135,    14,   130,
      15,    -1,   135,    14,     1,    -1,    45,    -1,    60,    -1,
      61,    -1,    62,    -1,    63,    -1,    64,    -1,    65,    -1,
      68,    -1,    70,    -1,    76,    -1,    74,    -1,    78,    -1,
      80,    -1,    72,    -1,    82,    -1,   138,    -1,    69,    -1,
      71,    -1,    77,    -1,    75,    -1,    79,    -1,    81,    -1,
      73,    -1,    85,    -1,    86,    -1,    66,    -1,    60,    -1,
      61,    -1,    62,    -1,    63,    -1,    64,    -1,    65,    -1,
      37,    -1,    38,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   195,   195,   202,   206,   210,   214,   215,   216,   219,
     222,   229,   230,   234,   236,   233,   266,   277,   279,   281,
     283,   285,   276,   317,   321,   324,   335,   339,   354,   362,
     377,   391,   404,   408,   414,   420,   421,   427,   429,   430,
     436,   437,   447,   453,   461,   470,   491,   502,   505,   515,
     517,   519,   523,   525,   527,   532,   533,   534,   535,   536,
     537,   538,   539,   540,   541,   542,   543,   544,   545,   546,
     547,   548,   549,   553,   558,   564,   565,   566,   567,   570,
     573,   574,   575,   576,   577,   578,   579,   580,   581,   582,
     583,   584,   585,   586,   587,   588,   589,   590,   591,   592,
     593,   594,   595,   596,   599,   600,   601,   602,   603,   606,
     607,   608,   609,   610,   611,   612,   615,   616,   617,   622,
     626,   630,   631,   632,   633,   634,   635,   636,   638,   639,
     640,   641,   642,   649,   652,   661,   662,   663,   664,   665,
     666,   669,   670,   671,   672,   673,   674,   675,   676,   677,
     680,   681,   682,   683,   684,   685,   686,   689,   690,   691,
     692,   693,   694,   695,   696,   697,   700,   709
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "S_COM", "S_Q", "S_COL", "S_NOT",
  "S_PLUS", "S_MINUS", "S_TIMES", "S_DIV", "S_MOD", "S_POW", "S_NL",
  "S_LB", "S_RB", "S_SLB", "S_SRB", "S_NEQ", "S_AND", "S_OR", "S_LT",
  "S_LE", "S_EQ", "S_ASSIGN", "S_TASSIGN", "S_TABREF", "S_GT", "S_GE",
  "S_BITAND", "S_BITOR", "S_NEQV", "S_BITSHL", "S_BITSHR", "S_BITNOT",
  "T_LABEL", "T_IF", "T_OPCODE0", "T_OPCODE", "T_UDO", "T_UDOSTART",
  "T_UDOEND", "T_UDO_ANS", "T_UDO_ARGS", "T_ERROR", "T_FUNCTION",
  "T_INSTR", "T_ENDIN", "T_STRSET", "T_PSET", "T_CTRLINIT", "T_MASSIGN",
  "T_TURNON", "T_PREALLOC", "T_ZAKINIT", "T_FTGEN", "T_INIT", "T_GOTO",
  "T_KGOTO", "T_IGOTO", "T_SRATE", "T_KRATE", "T_KSMPS", "T_NCHNLS",
  "T_NCHNLSI", "T_0DBFS", "T_STRCONST", "T_IDENT", "T_IDENT_I",
  "T_IDENT_GI", "T_IDENT_K", "T_IDENT_GK", "T_IDENT_A", "T_IDENT_GA",
  "T_IDENT_W", "T_IDENT_GW", "T_IDENT_F", "T_IDENT_GF", "T_IDENT_S",
  "T_IDENT_GS", "T_IDENT_T", "T_IDENT_GT", "T_IDENT_P", "T_IDENT_B",
  "T_IDENT_b", "T_INTGR", "T_NUMBER", "T_THEN", "T_ITHEN", "T_KTHEN",
  "T_ELSEIF", "T_ELSE", "T_ENDIF", "T_UNTIL", "T_DO", "T_OD", "T_INSTLIST",
  "S_SLASH", "S_STAR", "S_UNOT", "S_UMINUS", "S_ATAT", "S_AT", "S_GEQ",
  "S_LEQ", "S_GOTO", "T_HIGHEST", "$accept", "orcfile", "rootstatement",
  "instlist", "instrdecl", "$@1", "$@2", "udodecl", "$@3", "$@4", "$@5",
  "$@6", "$@7", "statementlist", "topstatement", "statement", "ans",
  "ifthen", "elseiflist", "elseif", "then", "goto", "label", "exprlist",
  "expr", "iexp", "iterm", "ifac", "function", "rident", "ident", "gident",
  "constant", "opcode0", "opcode", 0
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
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   107,   108,   109,   109,   109,   109,   109,   109,   110,
     110,   110,   110,   112,   113,   111,   111,   115,   116,   117,
     118,   119,   114,   120,   120,   121,   121,   122,   122,   122,
     122,   122,   122,   122,   122,   122,   122,   122,   123,   123,
     123,   123,   124,   124,   124,   124,   125,   125,   126,   127,
     127,   127,   128,   128,   128,   129,   129,   129,   129,   129,
     129,   129,   129,   129,   129,   129,   129,   129,   129,   129,
     129,   129,   129,   130,   130,   130,   130,   130,   130,   131,
     131,   131,   131,   131,   131,   131,   131,   131,   131,   131,
     131,   131,   131,   131,   131,   131,   131,   131,   131,   131,
     131,   131,   131,   131,   132,   132,   132,   132,   132,   133,
     133,   133,   133,   133,   133,   133,   134,   134,   134,   134,
     134,   134,   134,   134,   134,   134,   134,   134,   134,   134,
     134,   134,   134,   134,   135,   136,   136,   136,   136,   136,
     136,   137,   137,   137,   137,   137,   137,   137,   137,   137,
     138,   138,   138,   138,   138,   138,   138,   139,   139,   139,
     139,   139,   139,   139,   139,   139,   140,   141
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
       1,     1,     1,     3,     3,     3,     1,     1,     0,     5,
       5,     4,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     2,     2,     1,     3,     3,     3,     3,     1,     3,
       3,     3,     3,     3,     3,     1,     1,     1,     4,     2,
       2,     3,     3,     3,     3,     3,     3,     2,     2,     3,
       3,     2,     4,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    37,    32,     0,   166,    17,    13,    52,    53,    54,
     135,   136,   137,   138,   139,   140,     0,   141,   150,   142,
     151,   147,   156,   144,   153,   143,   152,   145,   154,   146,
     155,   148,     0,     0,     2,     7,     8,     6,    26,     0,
      35,     0,     0,    38,   149,    78,     0,     0,     0,     0,
       0,   134,   160,   161,   162,   163,   164,   165,   159,   146,
     157,   158,     0,   103,   108,   115,     0,   116,   117,     0,
       0,     0,    39,     0,     0,     0,     1,     4,     5,     3,
       0,   167,    78,    56,    55,    72,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      57,     0,     0,     0,    77,     0,    76,   102,   101,   120,
     128,   119,   131,     0,   127,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    49,    51,    50,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    18,    16,    12,    11,     0,     0,     0,
      24,     0,   146,    40,     0,    33,     0,     0,     0,    31,
     130,   129,     0,    82,     0,    88,    87,    98,    97,   100,
      99,    96,    95,    84,    83,    90,    89,    92,    91,    94,
      93,    86,    85,    24,     0,   105,   104,   107,   106,   110,
     109,   112,   111,   114,   113,   121,   123,   122,   124,   125,
     126,   133,     0,     0,     0,     0,    14,     0,    28,     0,
      41,    30,    25,    27,    75,   141,   150,   142,   151,   147,
     156,   144,   153,   143,   152,   145,   154,   146,   155,   148,
      74,    73,   118,    81,     0,     0,    34,   132,    19,    10,
       9,    24,     0,    36,    23,    80,    79,     0,    24,     0,
       0,    47,     0,     0,     0,     0,     0,    42,    24,     0,
      46,    20,     0,    29,     0,     0,     0,    44,     0,    15,
      24,    43,     0,     0,    48,    45,     0,    21,    24,     0,
       0,    22
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    33,    34,   147,    35,    71,   241,    36,    69,   203,
     252,   268,   278,   209,    37,   244,    39,    40,   250,   251,
     129,    41,   101,   105,   106,    63,    64,    65,    66,    42,
      67,    44,    68,    45,    82
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -182
static const yytype_int16 yypact[] =
{
    1896,  -182,  -182,  2054,  -182,  -182,    -3,  -182,  -182,  -182,
    -182,  -182,  -182,  -182,  -182,  -182,    20,  -182,  -182,  -182,
    -182,  -182,  -182,  -182,  -182,  -182,  -182,  -182,  -182,    -4,
    -182,  -182,  2054,    36,  1896,  -182,  -182,  -182,  -182,     2,
    -182,  2333,    15,    18,  -182,  1973,   302,  2382,  1368,   384,
    2382,  -182,  -182,  -182,  -182,  -182,  -182,  -182,  -182,    32,
    -182,  -182,  1809,    43,    84,   217,    59,  -182,  -182,    14,
      69,   -56,  -182,  2382,    16,     4,  -182,  -182,  -182,  -182,
     332,  -182,  1973,  -182,  -182,  -182,  -182,  -182,  -182,  -182,
    -182,  -182,  -182,  -182,  -182,  -182,  -182,  -182,  -182,  -182,
    -182,    77,  2054,  2054,  -182,   141,   333,  -182,   215,  -182,
    -182,  -182,  -182,    34,  -182,  2382,   466,   548,   630,   712,
     794,   876,   958,  1040,  1122,  1204,  -182,  -182,  -182,    86,
    2333,  1450,  1532,  1614,  1696,  1778,  2382,  2382,  2382,  2382,
    2382,  2382,   125,  -182,  -182,   124,   135,   130,    58,   133,
    -182,   146,  -182,  -182,   228,  -182,   156,   300,   220,  -182,
    -182,  -182,   260,  -182,   144,  -182,   415,  -182,   215,  -182,
     215,  -182,   415,  -182,   333,  -182,   415,  -182,   333,  -182,
     415,  -182,   333,  -182,   137,  -182,    84,  -182,    84,  -182,
     217,  -182,   217,  -182,   217,   364,   -18,   390,    46,   128,
    -182,  -182,     3,   152,   -56,   -56,  -182,   134,  -182,  1848,
    -182,  -182,  -182,  -182,  -182,    30,    61,   121,   122,   205,
     209,   210,   248,   249,   256,   257,   412,    56,   413,   417,
    -182,   333,  -182,  -182,  1286,  2108,  -182,  -182,  -182,  -182,
    -182,  -182,  2054,  -182,  -182,  -182,   460,  2054,  -182,   160,
      21,  -182,   115,  2156,   321,    64,  2183,  -182,  -182,   168,
    -182,  -182,   169,  -182,   201,   202,  2231,  -182,   213,  -182,
    -182,  -182,   204,   187,  2306,  -182,   231,  -182,  -182,  2279,
     242,  -182
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -182,  -182,  -182,   -75,   239,  -182,  -182,   241,  -182,  -182,
    -182,  -182,  -182,  -181,   244,     7,  -182,  -182,  -182,    26,
      52,   250,  -121,   -79,    -2,   -69,    10,   -31,  -182,  -182,
       0,  -182,  -182,  -182,  -182
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -79
static const yytype_int16 yytable[] =
{
      43,    62,   235,   154,   148,    80,   158,    38,   116,   184,
      70,   145,    73,   139,   140,   141,   109,   111,   237,   114,
      74,    72,   117,   118,   119,   120,   121,   122,   123,   146,
      75,   124,   125,   -58,    43,   160,    76,   230,   116,   102,
      81,    38,   103,   -58,   108,   -58,   162,   113,   115,   161,
     131,   132,   117,   118,   119,   120,   121,   122,   123,   -70,
     253,   124,   125,   202,   -59,   131,   132,   256,   116,   -70,
     144,   -70,   115,   142,   -59,   207,   -59,   266,   140,   141,
     153,   143,   117,   118,   119,   120,   121,   122,   123,   274,
     155,   124,   125,   133,   134,   135,   149,   279,   150,   183,
     156,   157,   190,   192,   194,   195,   196,   197,   198,   199,
     200,   247,   258,   259,   164,   166,   168,   170,   172,   174,
     176,   178,   180,   182,   -60,   -61,   201,   204,   -78,   239,
     240,    46,    47,    48,   -60,   -61,   -60,   -61,   205,    49,
     -78,   186,   188,   206,   158,   233,   208,   210,   116,   234,
     236,   126,   127,   128,   159,   238,   231,   261,   242,    50,
     116,   141,   117,   118,   119,   120,   121,   122,   123,   212,
      51,   124,   125,   257,   117,   118,   119,   120,   121,   122,
     123,   267,   269,   124,   125,    52,    53,    54,    55,    56,
      57,    58,   104,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    59,    30,    31,   -62,    43,
      60,    61,   -63,   -64,   270,   271,   273,   275,   -62,   116,
     -62,   214,   -63,   -64,   -63,   -64,    46,    47,    48,   136,
     276,   158,   246,   117,    49,    43,   120,   121,   122,   123,
     254,   211,   124,   125,   277,   255,   137,   138,   139,   140,
     141,   -65,   -66,    43,    50,   281,    43,    83,    84,   -67,
     -68,   -65,   -66,   -65,   -66,    51,    43,   131,   132,   -67,
     -68,   -67,   -68,    77,    43,    78,   260,   232,    79,    43,
      52,    53,    54,    55,    56,    57,    58,    85,   215,   216,
     217,   218,   219,   220,   221,   222,   223,   224,   225,   226,
     227,   228,   229,   107,   116,    60,    61,   264,    46,    47,
      48,     0,   130,   213,     0,     0,    49,     0,   117,   118,
     119,   120,   121,   122,   123,   116,     0,   124,   125,     0,
       0,     0,     0,     0,   263,     0,    50,   116,     0,   117,
     118,   119,   120,   121,   122,   123,     0,    51,   124,   125,
       0,   117,   118,   119,   120,   121,   122,   123,     0,     0,
     124,   125,    52,    53,    54,    55,    56,    57,    58,     0,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    59,    30,    31,   112,     0,    60,    61,     0,
      46,    47,    48,   137,   138,   139,   140,   141,    49,   151,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,   152,    30,    31,   -69,   -71,     0,    50,   137,
     -57,   139,   140,   141,     0,   -69,   -71,   -69,   -71,    51,
     -57,     0,   -57,   -79,     0,     0,   -79,   121,   -79,   123,
       0,     0,   -79,   125,    52,    53,    54,    55,    56,    57,
      58,     0,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    59,    30,    31,   163,     0,    60,
      61,     0,    46,    47,    48,     0,     0,     0,   117,     0,
      49,   120,   121,   122,   123,     0,     0,   124,   125,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      50,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    51,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    52,    53,    54,    55,
      56,    57,    58,     0,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    59,    30,    31,   165,
       0,    60,    61,     0,    46,    47,    48,     0,     0,     0,
       0,     0,    49,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    50,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    51,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    52,    53,
      54,    55,    56,    57,    58,     0,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    59,    30,
      31,   167,     0,    60,    61,     0,    46,    47,    48,     0,
       0,     0,     0,     0,    49,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    50,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    51,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      52,    53,    54,    55,    56,    57,    58,     0,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      59,    30,    31,   169,     0,    60,    61,     0,    46,    47,
      48,     0,     0,     0,     0,     0,    49,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    50,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    51,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    52,    53,    54,    55,    56,    57,    58,     0,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    59,    30,    31,   171,     0,    60,    61,     0,
      46,    47,    48,     0,     0,     0,     0,     0,    49,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    50,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    51,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    52,    53,    54,    55,    56,    57,
      58,     0,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    59,    30,    31,   173,     0,    60,
      61,     0,    46,    47,    48,     0,     0,     0,     0,     0,
      49,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      50,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    51,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    52,    53,    54,    55,
      56,    57,    58,     0,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    59,    30,    31,   175,
       0,    60,    61,     0,    46,    47,    48,     0,     0,     0,
       0,     0,    49,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    50,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    51,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    52,    53,
      54,    55,    56,    57,    58,     0,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    59,    30,
      31,   177,     0,    60,    61,     0,    46,    47,    48,     0,
       0,     0,     0,     0,    49,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    50,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    51,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      52,    53,    54,    55,    56,    57,    58,     0,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      59,    30,    31,   179,     0,    60,    61,     0,    46,    47,
      48,     0,     0,     0,     0,     0,    49,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    50,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    51,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    52,    53,    54,    55,    56,    57,    58,     0,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    59,    30,    31,   181,     0,    60,    61,     0,
      46,    47,    48,     0,     0,     0,     0,     0,    49,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    50,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    51,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    52,    53,    54,    55,    56,    57,
      58,     0,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    59,    30,    31,   245,     0,    60,
      61,     0,    46,    47,    48,     0,     0,     0,     0,     0,
      49,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      50,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    51,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    52,    53,    54,    55,
      56,    57,    58,     0,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    59,    30,    31,   110,
       0,    60,    61,     0,     0,    47,    48,     0,     0,     0,
       0,     0,    49,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    50,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    51,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    52,    53,
      54,    55,    56,    57,    58,     0,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    59,    30,
      31,   185,     0,    60,    61,     0,     0,    47,    48,     0,
       0,     0,     0,     0,    49,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    50,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    51,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      52,    53,    54,    55,    56,    57,    58,     0,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      59,    30,    31,   187,     0,    60,    61,     0,     0,    47,
      48,     0,     0,     0,     0,     0,    49,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    50,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    51,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    52,    53,    54,    55,    56,    57,    58,     0,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    59,    30,    31,   189,     0,    60,    61,     0,
       0,    47,    48,     0,     0,     0,     0,     0,    49,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    50,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    51,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    52,    53,    54,    55,    56,    57,
      58,     0,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    59,    30,    31,   191,     0,    60,
      61,     0,     0,    47,    48,     0,     0,     0,     0,     0,
      49,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      50,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    51,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    52,    53,    54,    55,
      56,    57,    58,     0,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    59,    30,    31,   193,
       0,    60,    61,     0,     0,    47,    48,     0,     0,     0,
       0,     0,    49,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    50,   116,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    51,     0,     0,     0,   117,   118,   119,
     120,   121,   122,   123,     0,     0,   124,   125,    52,    53,
      54,    55,    56,    57,    58,     0,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    59,    30,
      31,     1,     0,    60,    61,     0,     7,     8,     9,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     2,     3,     4,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   126,   127,   128,     0,
       0,     0,     0,     0,     0,     7,     8,     9,     0,     1,
       0,     0,     0,     0,     0,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,     2,     3,     4,     0,     0,     5,     0,     0,     0,
       0,    32,     6,   243,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     7,     8,     9,    10,    11,    12,    13,
      14,    15,     0,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    46,
      47,    48,     0,     0,     0,     0,     0,    49,     0,    32,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    50,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    51,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    52,    53,    54,    55,    56,    57,    58,
     104,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    59,    30,    31,     0,     0,    60,    61,
      46,    47,    48,     0,     0,     0,     0,     0,    49,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    50,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    51,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    52,    53,    54,    55,    56,    57,
      58,     1,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    59,    30,    31,     0,     0,    60,
      61,     0,     0,     2,     3,     4,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     7,     8,     9,     0,     1,
       0,     0,     0,     0,     0,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,     2,     3,     4,     0,     0,     1,     0,   247,   248,
     249,    32,     0,   262,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     7,     8,     9,     0,     0,     2,     3,
       4,     0,     0,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,     0,
       7,     8,     9,     0,     1,     0,     0,     0,     0,    32,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,     2,     3,     4,     0,
       0,     0,     0,     0,     0,   265,    32,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     7,     8,
       9,     0,     1,     0,     0,     0,     0,     0,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,     2,     3,     4,     0,     0,     1,
     280,     0,     0,   272,    32,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     7,     8,     9,     0,
       0,     2,     3,     4,     0,     0,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,     0,     7,     8,     9,     0,     0,     0,     0,
      83,    84,    32,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    47,
      48,     0,     0,     0,     0,     0,    49,     0,     0,    32,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,    50,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    51,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    52,    53,    54,    55,    56,    57,    58,     0,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    59,    30,    31,     0,     0,    60,    61
};

static const yytype_int16 yycheck[] =
{
       0,     3,   183,    82,    73,     3,     3,     0,     4,   130,
      13,    67,    16,    31,    32,    33,    47,    48,    15,    50,
      24,     1,    18,    19,    20,    21,    22,    23,    24,    85,
      32,    27,    28,     3,    34,     1,     0,   158,     4,    24,
      38,    34,    24,    13,    46,    15,   115,    49,    16,    15,
       7,     8,    18,    19,    20,    21,    22,    23,    24,     3,
     241,    27,    28,   142,     3,     7,     8,   248,     4,    13,
       1,    15,    16,    14,    13,    17,    15,   258,    32,    33,
      80,    67,    18,    19,    20,    21,    22,    23,    24,   270,
      13,    27,    28,     9,    10,    11,    80,   278,    94,    13,
     102,   103,   133,   134,   135,   136,   137,   138,   139,   140,
     141,    90,    91,    92,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,     3,     3,     1,     3,     3,   204,
     205,     6,     7,     8,    13,    13,    15,    15,     3,    14,
      15,   131,   132,    13,     3,     1,    13,     1,     4,     5,
      13,    87,    88,    89,    13,     3,   158,    42,    24,    34,
       4,    33,    18,    19,    20,    21,    22,    23,    24,    13,
      45,    27,    28,    13,    18,    19,    20,    21,    22,    23,
      24,    13,    13,    27,    28,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,     3,   209,
      85,    86,     3,     3,    13,    13,     3,    13,    13,     4,
      15,     1,    13,    13,    15,    15,     6,     7,     8,    12,
      43,     3,   234,    18,    14,   235,    21,    22,    23,    24,
     242,    13,    27,    28,    13,   247,    29,    30,    31,    32,
      33,     3,     3,   253,    34,    13,   256,    37,    38,     3,
       3,    13,    13,    15,    15,    45,   266,     7,     8,    13,
      13,    15,    15,    34,   274,    34,   250,    17,    34,   279,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,     1,     4,    85,    86,   255,     6,     7,
       8,    -1,    62,    13,    -1,    -1,    14,    -1,    18,    19,
      20,    21,    22,    23,    24,     4,    -1,    27,    28,    -1,
      -1,    -1,    -1,    -1,    13,    -1,    34,     4,    -1,    18,
      19,    20,    21,    22,    23,    24,    -1,    45,    27,    28,
      -1,    18,    19,    20,    21,    22,    23,    24,    -1,    -1,
      27,    28,    60,    61,    62,    63,    64,    65,    66,    -1,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,     1,    -1,    85,    86,    -1,
       6,     7,     8,    29,    30,    31,    32,    33,    14,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,     3,     3,    -1,    34,    29,
       3,    31,    32,    33,    -1,    13,    13,    15,    15,    45,
      13,    -1,    15,    18,    -1,    -1,    21,    22,    23,    24,
      -1,    -1,    27,    28,    60,    61,    62,    63,    64,    65,
      66,    -1,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,     1,    -1,    85,
      86,    -1,     6,     7,     8,    -1,    -1,    -1,    18,    -1,
      14,    21,    22,    23,    24,    -1,    -1,    27,    28,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      34,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    45,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    60,    61,    62,    63,
      64,    65,    66,    -1,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,     1,
      -1,    85,    86,    -1,     6,     7,     8,    -1,    -1,    -1,
      -1,    -1,    14,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    34,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    45,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    60,    61,
      62,    63,    64,    65,    66,    -1,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,     1,    -1,    85,    86,    -1,     6,     7,     8,    -1,
      -1,    -1,    -1,    -1,    14,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    34,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    45,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      60,    61,    62,    63,    64,    65,    66,    -1,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,     1,    -1,    85,    86,    -1,     6,     7,
       8,    -1,    -1,    -1,    -1,    -1,    14,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    34,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    45,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    60,    61,    62,    63,    64,    65,    66,    -1,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,     1,    -1,    85,    86,    -1,
       6,     7,     8,    -1,    -1,    -1,    -1,    -1,    14,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    34,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    45,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    60,    61,    62,    63,    64,    65,
      66,    -1,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,     1,    -1,    85,
      86,    -1,     6,     7,     8,    -1,    -1,    -1,    -1,    -1,
      14,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      34,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    45,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    60,    61,    62,    63,
      64,    65,    66,    -1,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,     1,
      -1,    85,    86,    -1,     6,     7,     8,    -1,    -1,    -1,
      -1,    -1,    14,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    34,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    45,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    60,    61,
      62,    63,    64,    65,    66,    -1,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,     1,    -1,    85,    86,    -1,     6,     7,     8,    -1,
      -1,    -1,    -1,    -1,    14,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    34,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    45,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      60,    61,    62,    63,    64,    65,    66,    -1,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,     1,    -1,    85,    86,    -1,     6,     7,
       8,    -1,    -1,    -1,    -1,    -1,    14,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    34,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    45,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    60,    61,    62,    63,    64,    65,    66,    -1,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,     1,    -1,    85,    86,    -1,
       6,     7,     8,    -1,    -1,    -1,    -1,    -1,    14,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    34,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    45,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    60,    61,    62,    63,    64,    65,
      66,    -1,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,     1,    -1,    85,
      86,    -1,     6,     7,     8,    -1,    -1,    -1,    -1,    -1,
      14,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      34,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    45,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    60,    61,    62,    63,
      64,    65,    66,    -1,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,     1,
      -1,    85,    86,    -1,    -1,     7,     8,    -1,    -1,    -1,
      -1,    -1,    14,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    34,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    45,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    60,    61,
      62,    63,    64,    65,    66,    -1,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,     1,    -1,    85,    86,    -1,    -1,     7,     8,    -1,
      -1,    -1,    -1,    -1,    14,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    34,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    45,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      60,    61,    62,    63,    64,    65,    66,    -1,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,     1,    -1,    85,    86,    -1,    -1,     7,
       8,    -1,    -1,    -1,    -1,    -1,    14,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    34,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    45,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    60,    61,    62,    63,    64,    65,    66,    -1,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,     1,    -1,    85,    86,    -1,
      -1,     7,     8,    -1,    -1,    -1,    -1,    -1,    14,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    34,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    45,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    60,    61,    62,    63,    64,    65,
      66,    -1,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,     1,    -1,    85,
      86,    -1,    -1,     7,     8,    -1,    -1,    -1,    -1,    -1,
      14,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      34,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    45,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    60,    61,    62,    63,
      64,    65,    66,    -1,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,     1,
      -1,    85,    86,    -1,    -1,     7,     8,    -1,    -1,    -1,
      -1,    -1,    14,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    34,     4,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    45,    -1,    -1,    -1,    18,    19,    20,
      21,    22,    23,    24,    -1,    -1,    27,    28,    60,    61,
      62,    63,    64,    65,    66,    -1,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    13,    -1,    85,    86,    -1,    57,    58,    59,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    35,    36,    37,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    87,    88,    89,    -1,
      -1,    -1,    -1,    -1,    -1,    57,    58,    59,    -1,    13,
      -1,    -1,    -1,    -1,    -1,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    35,    36,    37,    -1,    -1,    40,    -1,    -1,    -1,
      -1,    93,    46,    95,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    -1,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,     6,
       7,     8,    -1,    -1,    -1,    -1,    -1,    14,    -1,    93,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    34,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    45,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    -1,    -1,    85,    86,
       6,     7,     8,    -1,    -1,    -1,    -1,    -1,    14,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    34,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    45,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    60,    61,    62,    63,    64,    65,
      66,    13,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    -1,    -1,    85,
      86,    -1,    -1,    35,    36,    37,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    57,    58,    59,    -1,    13,
      -1,    -1,    -1,    -1,    -1,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    35,    36,    37,    -1,    -1,    13,    -1,    90,    91,
      92,    93,    -1,    47,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    57,    58,    59,    -1,    -1,    35,    36,
      37,    -1,    -1,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    -1,
      57,    58,    59,    -1,    13,    -1,    -1,    -1,    -1,    93,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    35,    36,    37,    -1,
      -1,    -1,    -1,    -1,    -1,    92,    93,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    57,    58,
      59,    -1,    13,    -1,    -1,    -1,    -1,    -1,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    35,    36,    37,    -1,    -1,    13,
      41,    -1,    -1,    92,    93,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    57,    58,    59,    -1,
      -1,    35,    36,    37,    -1,    -1,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    -1,    57,    58,    59,    -1,    -1,    -1,    -1,
      37,    38,    93,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,     7,
       8,    -1,    -1,    -1,    -1,    -1,    14,    -1,    -1,    93,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    34,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    45,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    60,    61,    62,    63,    64,    65,    66,    -1,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    -1,    -1,    85,    86
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    13,    35,    36,    37,    40,    46,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    93,   108,   109,   111,   114,   121,   122,   123,
     124,   128,   136,   137,   138,   140,     6,     7,     8,    14,
      34,    45,    60,    61,    62,    63,    64,    65,    66,    80,
      85,    86,   131,   132,   133,   134,   135,   137,   139,   115,
      13,   112,     1,    16,    24,   131,     0,   111,   114,   121,
       3,    38,   141,    37,    38,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,   129,    24,    24,    67,   130,   131,     1,   131,   134,
       1,   134,     1,   131,   134,    16,     4,    18,    19,    20,
      21,    22,    23,    24,    27,    28,    87,    88,    89,   127,
     128,     7,     8,     9,    10,    11,    12,    29,    30,    31,
      32,    33,    14,    67,     1,    67,    85,   110,   132,    80,
      94,    67,    80,   137,   130,    13,   131,   131,     3,    13,
       1,    15,   132,     1,   131,     1,   131,     1,   131,     1,
     131,     1,   131,     1,   131,     1,   131,     1,   131,     1,
     131,     1,   131,    13,   129,     1,   133,     1,   133,     1,
     134,     1,   134,     1,   134,   134,   134,   134,   134,   134,
     134,     1,   130,   116,     3,     3,    13,    17,    13,   120,
       1,    13,    13,    13,     1,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
     129,   131,    17,     1,     5,   120,    13,    15,     3,   110,
     110,   113,    24,    95,   122,     1,   131,    90,    91,    92,
     125,   126,   117,   120,   131,   131,   120,    13,    91,    92,
     126,    42,    47,    13,   127,    92,   120,    13,   118,    13,
      13,    13,    92,     3,   120,    13,    43,    13,   119,   120,
      41,    13
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
#line 196 "csound_orc.y"
    {
                            *astTree = *((TREE *)(yyvsp[(1) - (1)]));
                            //print_tree(csound, "ALL", $1);
                        ;}
    break;

  case 3:

/* Line 1464 of yacc.c  */
#line 203 "csound_orc.y"
    {
                        (yyval) = appendToTree(csound, (yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]));
                        ;}
    break;

  case 4:

/* Line 1464 of yacc.c  */
#line 207 "csound_orc.y"
    {
                        (yyval) = appendToTree(csound, (yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]));
                        ;}
    break;

  case 5:

/* Line 1464 of yacc.c  */
#line 211 "csound_orc.y"
    {
                        (yyval) = appendToTree(csound, (yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]));
                        ;}
    break;

  case 9:

/* Line 1464 of yacc.c  */
#line 220 "csound_orc.y"
    { (yyval) = make_node(csound, T_INSTLIST,
                               make_leaf(csound, T_INTGR, (ORCTOKEN *)(yyvsp[(1) - (3)])), (yyvsp[(3) - (3)])); ;}
    break;

  case 10:

/* Line 1464 of yacc.c  */
#line 223 "csound_orc.y"
    {
#ifdef PARCS
                  csp_orc_sa_instr_add(csound, ((ORCTOKEN *)(yyvsp[(1) - (3)]))->lexeme);
#endif
                  (yyval) = make_node(csound, T_INSTLIST,
                               make_leaf(csound, T_IDENT, (ORCTOKEN *)(yyvsp[(1) - (3)])), (yyvsp[(3) - (3)])); ;}
    break;

  case 11:

/* Line 1464 of yacc.c  */
#line 229 "csound_orc.y"
    { (yyval) = make_leaf(csound, T_INTGR, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 12:

/* Line 1464 of yacc.c  */
#line 230 "csound_orc.y"
    { (yyval) = make_leaf(csound, T_IDENT, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 13:

/* Line 1464 of yacc.c  */
#line 234 "csound_orc.y"
    { namedInstrFlag = 1; ;}
    break;

  case 14:

/* Line 1464 of yacc.c  */
#line 236 "csound_orc.y"
    { namedInstrFlag = 0;
#ifdef PARCS
                  csp_orc_sa_instr_add_tree(csound, (yyvsp[(3) - (4)]));
#endif
                ;}
    break;

  case 15:

/* Line 1464 of yacc.c  */
#line 242 "csound_orc.y"
    {
                    (yyval) = make_node(csound, T_INSTR, (yyvsp[(3) - (8)]), (yyvsp[(6) - (8)]));
#ifdef PARCS
                    csp_orc_sa_instr_finalize(csound);
#endif
                ;}
    break;

  case 16:

/* Line 1464 of yacc.c  */
#line 267 "csound_orc.y"
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
#line 277 "csound_orc.y"
    { udoflag = -2; ;}
    break;

  case 18:

/* Line 1464 of yacc.c  */
#line 279 "csound_orc.y"
    { udoflag = -1; ;}
    break;

  case 19:

/* Line 1464 of yacc.c  */
#line 281 "csound_orc.y"
    { udoflag = 0;;}
    break;

  case 20:

/* Line 1464 of yacc.c  */
#line 283 "csound_orc.y"
    { udoflag = 1; ;}
    break;

  case 21:

/* Line 1464 of yacc.c  */
#line 285 "csound_orc.y"
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
#line 293 "csound_orc.y"
    {
                TREE *udoTop = make_leaf(csound, T_UDO, (ORCTOKEN *)NULL);
                TREE *ident = make_leaf(csound, T_IDENT, (ORCTOKEN *)(yyvsp[(3) - (15)]));
                TREE *udoAns = make_leaf(csound, T_UDO_ANS, (ORCTOKEN *)(yyvsp[(7) - (15)]));
                TREE *udoArgs = make_leaf(csound, T_UDO_ARGS, (ORCTOKEN *)(yyvsp[(10) - (15)]));
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
#line 318 "csound_orc.y"
    {
                    (yyval) = appendToTree(csound, (TREE *)(yyvsp[(1) - (2)]), (TREE *)(yyvsp[(2) - (2)]));
                ;}
    break;

  case 24:

/* Line 1464 of yacc.c  */
#line 321 "csound_orc.y"
    { (yyval) = NULL; ;}
    break;

  case 25:

/* Line 1464 of yacc.c  */
#line 325 "csound_orc.y"
    {

                  TREE *ans = make_leaf(csound, S_ASSIGN, (ORCTOKEN *)(yyvsp[(2) - (4)]));
                  ans->left = (TREE *)(yyvsp[(1) - (4)]);
                  ans->right = (TREE *)(yyvsp[(3) - (4)]);
                  /* ans->value->lexeme = get_assignment_type(csound,
                      ans->left->value->lexeme, ans->right->value->lexeme); */

                  (yyval) = ans;
                ;}
    break;

  case 26:

/* Line 1464 of yacc.c  */
#line 335 "csound_orc.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 27:

/* Line 1464 of yacc.c  */
#line 340 "csound_orc.y"
    {
                  TREE *ans = make_leaf(csound, S_ASSIGN, (ORCTOKEN *)(yyvsp[(2) - (4)]));
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
#line 355 "csound_orc.y"
    {
              ORCTOKEN *op = lookup_token(csound, "#copytab", NULL);
              TREE *ans = make_leaf(csound, T_OPCODE, op);
              ans->left = make_leaf(csound, T_IDENT_T, (ORCTOKEN *)(yyvsp[(1) - (4)]));
              ans->right = make_leaf(csound, T_IDENT_T, (ORCTOKEN *)(yyvsp[(3) - (4)]));
              (yyval) = ans;
          ;}
    break;

  case 29:

/* Line 1464 of yacc.c  */
#line 363 "csound_orc.y"
    {
              TREE *ans = make_leaf(csound, S_ASSIGN, (ORCTOKEN *)(yyvsp[(5) - (7)]));
              ans->left = make_leaf(csound, T_IDENT_T, (ORCTOKEN *)(yyvsp[(1) - (7)]));
              ans->right = appendToTree(csound, (yyvsp[(3) - (7)]), (yyvsp[(6) - (7)]));
                  /* ans->value->lexeme = get_assignment_type(csound,
                     ans->left->value->lexeme, ans->right->value->lexeme); */
              //print_tree(csound, "TABLE ASSIGN", ans);
              (yyval) = ans;
  /* #ifdef PARCS */
  /*                   csp_orc_sa_global_read_write_add_list(csound, */
  /*                                     csp_orc_sa_globals_find(csound, ans->left) */
  /*                                     csp_orc_sa_globals_find(csound, ans->right)); */
  /* #endif */
          ;}
    break;

  case 30:

/* Line 1464 of yacc.c  */
#line 378 "csound_orc.y"
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
#line 392 "csound_orc.y"
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
#line 405 "csound_orc.y"
    {
                    (yyval) = make_leaf(csound, T_LABEL, (ORCTOKEN *)(yyvsp[(1) - (1)]));
                ;}
    break;

  case 33:

/* Line 1464 of yacc.c  */
#line 409 "csound_orc.y"
    {
                    (yyvsp[(1) - (3)])->left = NULL;
                    (yyvsp[(1) - (3)])->right = make_leaf(csound, T_LABEL, (ORCTOKEN *)(yyvsp[(2) - (3)]));
                    (yyval) = (yyvsp[(1) - (3)]);
                ;}
    break;

  case 34:

/* Line 1464 of yacc.c  */
#line 415 "csound_orc.y"
    {
                    (yyvsp[(3) - (5)])->left = NULL;
                    (yyvsp[(3) - (5)])->right = make_leaf(csound, T_LABEL, (ORCTOKEN *)(yyvsp[(4) - (5)]));
                    (yyval) = make_node(csound, T_IF, (yyvsp[(2) - (5)]), (yyvsp[(3) - (5)]));
                ;}
    break;

  case 36:

/* Line 1464 of yacc.c  */
#line 422 "csound_orc.y"
    {
                  (yyval) = make_leaf(csound, T_UNTIL, (ORCTOKEN *)(yyvsp[(1) - (5)]));
                  (yyval)->left = (yyvsp[(2) - (5)]);
                  (yyval)->right = (yyvsp[(4) - (5)]);
              ;}
    break;

  case 37:

/* Line 1464 of yacc.c  */
#line 427 "csound_orc.y"
    { (yyval) = NULL; ;}
    break;

  case 38:

/* Line 1464 of yacc.c  */
#line 429 "csound_orc.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 39:

/* Line 1464 of yacc.c  */
#line 431 "csound_orc.y"
    { csound->Message(csound,
                      "Unexpected untyped word %s when expecting a variable\n", 
                      ((ORCTOKEN*)(yyvsp[(1) - (2)]))->lexeme);
                (yyval) = make_leaf(csound, T_SRATE, (ORCTOKEN *)(yyvsp[(1) - (2)]));
              ;}
    break;

  case 40:

/* Line 1464 of yacc.c  */
#line 436 "csound_orc.y"
    { (yyval) = appendToTree(csound, (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 41:

/* Line 1464 of yacc.c  */
#line 438 "csound_orc.y"
    { csound->Message(csound,
                      "Unexpected untyped word %s when expecting a variable\n", 
                               ((ORCTOKEN*)(yyvsp[(3) - (4)]))->lexeme);
                (yyval) = appendToTree(csound, (yyvsp[(1) - (4)]), 
                               make_leaf(csound, T_SRATE,
                               (ORCTOKEN *)(yyvsp[(3) - (4)])));
              ;}
    break;

  case 42:

/* Line 1464 of yacc.c  */
#line 448 "csound_orc.y"
    {
            (yyvsp[(3) - (7)])->right = (yyvsp[(5) - (7)]);
            (yyval) = make_node(csound, T_IF, (yyvsp[(2) - (7)]), (yyvsp[(3) - (7)]));
            //print_tree(csound, "if-endif", $$);
          ;}
    break;

  case 43:

/* Line 1464 of yacc.c  */
#line 454 "csound_orc.y"
    {
            (yyvsp[(3) - (9)])->right = (yyvsp[(5) - (9)]);
            (yyvsp[(3) - (9)])->next = make_node(csound, T_ELSE, NULL, (yyvsp[(7) - (9)]));
            (yyval) = make_node(csound, T_IF, (yyvsp[(2) - (9)]), (yyvsp[(3) - (9)]));
            //print_tree(csound, "if-else", $$);

          ;}
    break;

  case 44:

/* Line 1464 of yacc.c  */
#line 462 "csound_orc.y"
    {
            if (UNLIKELY(PARSER_DEBUG))
                csound->Message(csound, "IF-ELSEIF FOUND!\n");
            (yyvsp[(3) - (8)])->right = (yyvsp[(5) - (8)]);
            (yyvsp[(3) - (8)])->next = (yyvsp[(6) - (8)]);
            (yyval) = make_node(csound, T_IF, (yyvsp[(2) - (8)]), (yyvsp[(3) - (8)]));
            //print_tree(csound, "if-elseif\n", $$);
          ;}
    break;

  case 45:

/* Line 1464 of yacc.c  */
#line 472 "csound_orc.y"
    {
            TREE * tempLastNode;

            (yyvsp[(3) - (10)])->right = (yyvsp[(5) - (10)]);
            (yyvsp[(3) - (10)])->next = (yyvsp[(6) - (10)]);

            (yyval) = make_node(csound, T_IF, (yyvsp[(2) - (10)]), (yyvsp[(3) - (10)]));

            tempLastNode = (yyval);

            while (tempLastNode->right!=NULL && tempLastNode->right->next!=NULL) {
                tempLastNode = tempLastNode->right->next;
            }

            tempLastNode->right->next = make_node(csound, T_ELSE, NULL, (yyvsp[(8) - (10)]));
            //print_tree(csound, "IF TREE", $$);
          ;}
    break;

  case 46:

/* Line 1464 of yacc.c  */
#line 492 "csound_orc.y"
    {
                TREE * tempLastNode = (yyvsp[(1) - (2)]);

                while (tempLastNode->right!=NULL && tempLastNode->right->next!=NULL) {
                    tempLastNode = tempLastNode->right->next;
                }

                tempLastNode->right->next = (yyvsp[(2) - (2)]);
                (yyval) = (yyvsp[(1) - (2)]);
            ;}
    break;

  case 47:

/* Line 1464 of yacc.c  */
#line 502 "csound_orc.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 48:

/* Line 1464 of yacc.c  */
#line 506 "csound_orc.y"
    {
                if (UNLIKELY(PARSER_DEBUG))
                  csound->Message(csound, "ELSEIF FOUND!\n");
                (yyvsp[(3) - (5)])->right = (yyvsp[(5) - (5)]);
                (yyval) = make_node(csound, T_ELSEIF, (yyvsp[(2) - (5)]), (yyvsp[(3) - (5)]));
                //print_tree(csound, "ELSEIF", $$);
            ;}
    break;

  case 49:

/* Line 1464 of yacc.c  */
#line 516 "csound_orc.y"
    { (yyval) = make_leaf(csound, T_THEN, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 50:

/* Line 1464 of yacc.c  */
#line 518 "csound_orc.y"
    { (yyval) = make_leaf(csound, T_KTHEN, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 51:

/* Line 1464 of yacc.c  */
#line 520 "csound_orc.y"
    { (yyval) = make_leaf(csound, T_ITHEN, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 52:

/* Line 1464 of yacc.c  */
#line 524 "csound_orc.y"
    { (yyval) = make_leaf(csound, T_GOTO, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 53:

/* Line 1464 of yacc.c  */
#line 526 "csound_orc.y"
    { (yyval) = make_leaf(csound, T_KGOTO, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 54:

/* Line 1464 of yacc.c  */
#line 528 "csound_orc.y"
    { (yyval) = make_leaf(csound, T_IGOTO, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 55:

/* Line 1464 of yacc.c  */
#line 532 "csound_orc.y"
    { (yyval) = (TREE *)(yyvsp[(1) - (1)]); ;}
    break;

  case 56:

/* Line 1464 of yacc.c  */
#line 533 "csound_orc.y"
    { (yyval) = (TREE *)(yyvsp[(1) - (1)]); ;}
    break;

  case 57:

/* Line 1464 of yacc.c  */
#line 534 "csound_orc.y"
    { (yyval) = (TREE *)(yyvsp[(1) - (1)]); ;}
    break;

  case 58:

/* Line 1464 of yacc.c  */
#line 535 "csound_orc.y"
    { (yyval) = (TREE *)(yyvsp[(1) - (1)]); ;}
    break;

  case 59:

/* Line 1464 of yacc.c  */
#line 536 "csound_orc.y"
    { (yyval) = (TREE *)(yyvsp[(1) - (1)]); ;}
    break;

  case 60:

/* Line 1464 of yacc.c  */
#line 537 "csound_orc.y"
    { (yyval) = (TREE *)(yyvsp[(1) - (1)]); ;}
    break;

  case 61:

/* Line 1464 of yacc.c  */
#line 538 "csound_orc.y"
    { (yyval) = (TREE *)(yyvsp[(1) - (1)]); ;}
    break;

  case 62:

/* Line 1464 of yacc.c  */
#line 539 "csound_orc.y"
    { (yyval) = (TREE *)(yyvsp[(1) - (1)]); ;}
    break;

  case 63:

/* Line 1464 of yacc.c  */
#line 540 "csound_orc.y"
    { (yyval) = (TREE *)(yyvsp[(1) - (1)]); ;}
    break;

  case 64:

/* Line 1464 of yacc.c  */
#line 541 "csound_orc.y"
    { (yyval) = (TREE *)(yyvsp[(1) - (1)]); ;}
    break;

  case 65:

/* Line 1464 of yacc.c  */
#line 542 "csound_orc.y"
    { (yyval) = (TREE *)(yyvsp[(1) - (1)]); ;}
    break;

  case 66:

/* Line 1464 of yacc.c  */
#line 543 "csound_orc.y"
    { (yyval) = (TREE *)(yyvsp[(1) - (1)]); ;}
    break;

  case 67:

/* Line 1464 of yacc.c  */
#line 544 "csound_orc.y"
    { (yyval) = (TREE *)(yyvsp[(1) - (1)]); ;}
    break;

  case 68:

/* Line 1464 of yacc.c  */
#line 545 "csound_orc.y"
    { (yyval) = (TREE *)(yyvsp[(1) - (1)]); ;}
    break;

  case 69:

/* Line 1464 of yacc.c  */
#line 546 "csound_orc.y"
    { (yyval) = (TREE *)(yyvsp[(1) - (1)]); ;}
    break;

  case 70:

/* Line 1464 of yacc.c  */
#line 547 "csound_orc.y"
    { (yyval) = (TREE *)(yyvsp[(1) - (1)]); ;}
    break;

  case 71:

/* Line 1464 of yacc.c  */
#line 548 "csound_orc.y"
    { (yyval) = (TREE *)(yyvsp[(1) - (1)]); ;}
    break;

  case 72:

/* Line 1464 of yacc.c  */
#line 549 "csound_orc.y"
    { (yyval) = (TREE *)(yyvsp[(1) - (1)]); ;}
    break;

  case 73:

/* Line 1464 of yacc.c  */
#line 554 "csound_orc.y"
    {
                    /* $$ = make_node(S_COM, $1, $3); */
                    (yyval) = appendToTree(csound, (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
                ;}
    break;

  case 74:

/* Line 1464 of yacc.c  */
#line 559 "csound_orc.y"
    {
                    /* $$ = make_node(S_COM, $1, $3); */
                    (yyval) = appendToTree(csound, (yyvsp[(1) - (3)]),
                                      make_leaf(csound, T_LABEL, (ORCTOKEN *)(yyvsp[(3) - (3)])));
                ;}
    break;

  case 76:

/* Line 1464 of yacc.c  */
#line 565 "csound_orc.y"
    { (yyval) = (yyvsp[(1) - (1)]);     ;}
    break;

  case 77:

/* Line 1464 of yacc.c  */
#line 566 "csound_orc.y"
    { (yyval) = make_leaf(csound, T_LABEL, (ORCTOKEN *)(yyvsp[(1) - (1)]));     ;}
    break;

  case 78:

/* Line 1464 of yacc.c  */
#line 567 "csound_orc.y"
    { (yyval) = NULL; ;}
    break;

  case 79:

/* Line 1464 of yacc.c  */
#line 571 "csound_orc.y"
    { (yyval) = make_node(csound, S_Q, (yyvsp[(1) - (5)]),
                             make_node(csound, S_COL, (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)]))); ;}
    break;

  case 83:

/* Line 1464 of yacc.c  */
#line 576 "csound_orc.y"
    { (yyval) = make_node(csound, S_LE, (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 85:

/* Line 1464 of yacc.c  */
#line 578 "csound_orc.y"
    { (yyval) = make_node(csound, S_GE, (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 87:

/* Line 1464 of yacc.c  */
#line 580 "csound_orc.y"
    { (yyval) = make_node(csound, S_NEQ, (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 89:

/* Line 1464 of yacc.c  */
#line 582 "csound_orc.y"
    { (yyval) = make_node(csound, S_EQ, (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 91:

/* Line 1464 of yacc.c  */
#line 584 "csound_orc.y"
    { (yyval) = make_node(csound, S_EQ, (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 93:

/* Line 1464 of yacc.c  */
#line 586 "csound_orc.y"
    { (yyval) = make_node(csound, S_GT, (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 95:

/* Line 1464 of yacc.c  */
#line 588 "csound_orc.y"
    { (yyval) = make_node(csound, S_LT, (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 97:

/* Line 1464 of yacc.c  */
#line 590 "csound_orc.y"
    { (yyval) = make_node(csound, S_AND, (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 99:

/* Line 1464 of yacc.c  */
#line 592 "csound_orc.y"
    { (yyval) = make_node(csound, S_OR, (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 101:

/* Line 1464 of yacc.c  */
#line 594 "csound_orc.y"
    { (yyval) = make_node(csound, S_UNOT, (yyvsp[(2) - (2)]), NULL); ;}
    break;

  case 103:

/* Line 1464 of yacc.c  */
#line 596 "csound_orc.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 104:

/* Line 1464 of yacc.c  */
#line 599 "csound_orc.y"
    { (yyval) = make_node(csound, S_PLUS, (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 106:

/* Line 1464 of yacc.c  */
#line 601 "csound_orc.y"
    { (yyval) = make_node(csound, S_MINUS, (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 108:

/* Line 1464 of yacc.c  */
#line 603 "csound_orc.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 109:

/* Line 1464 of yacc.c  */
#line 606 "csound_orc.y"
    { (yyval) = make_node(csound, S_TIMES, (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 111:

/* Line 1464 of yacc.c  */
#line 608 "csound_orc.y"
    { (yyval) = make_node(csound, S_DIV, (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 113:

/* Line 1464 of yacc.c  */
#line 610 "csound_orc.y"
    { (yyval) = make_node(csound, S_MOD, (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 115:

/* Line 1464 of yacc.c  */
#line 612 "csound_orc.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 116:

/* Line 1464 of yacc.c  */
#line 615 "csound_orc.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 117:

/* Line 1464 of yacc.c  */
#line 616 "csound_orc.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 118:

/* Line 1464 of yacc.c  */
#line 618 "csound_orc.y"
    {
              (yyval) = make_node(csound, S_TABREF,
                             make_leaf(csound, T_IDENT_T, (ORCTOKEN*)(yyvsp[(1) - (4)])), (yyvsp[(3) - (4)]));
          ;}
    break;

  case 119:

/* Line 1464 of yacc.c  */
#line 623 "csound_orc.y"
    {
                (yyval) = make_node(csound, S_UMINUS, NULL, (yyvsp[(2) - (2)]));
            ;}
    break;

  case 120:

/* Line 1464 of yacc.c  */
#line 627 "csound_orc.y"
    {
                (yyval) = (yyvsp[(2) - (2)]);
            ;}
    break;

  case 121:

/* Line 1464 of yacc.c  */
#line 630 "csound_orc.y"
    { (yyval) = make_node(csound, S_POW, (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 122:

/* Line 1464 of yacc.c  */
#line 631 "csound_orc.y"
    { (yyval) = make_node(csound, S_BITOR, (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 123:

/* Line 1464 of yacc.c  */
#line 632 "csound_orc.y"
    { (yyval) = make_node(csound, S_BITAND, (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 124:

/* Line 1464 of yacc.c  */
#line 633 "csound_orc.y"
    { (yyval) = make_node(csound, S_NEQV, (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 125:

/* Line 1464 of yacc.c  */
#line 634 "csound_orc.y"
    { (yyval) = make_node(csound, S_BITSHL, (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 126:

/* Line 1464 of yacc.c  */
#line 635 "csound_orc.y"
    { (yyval) = make_node(csound, S_BITSHR, (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 127:

/* Line 1464 of yacc.c  */
#line 637 "csound_orc.y"
    { (yyval) = make_node(csound, S_BITNOT, NULL, (yyvsp[(2) - (2)]));;}
    break;

  case 129:

/* Line 1464 of yacc.c  */
#line 639 "csound_orc.y"
    { (yyval) = (yyvsp[(2) - (3)]); ;}
    break;

  case 132:

/* Line 1464 of yacc.c  */
#line 643 "csound_orc.y"
    {
                (yyvsp[(1) - (4)])->left = NULL;
                (yyvsp[(1) - (4)])->right = (yyvsp[(3) - (4)]);

                (yyval) = (yyvsp[(1) - (4)]);
            ;}
    break;

  case 134:

/* Line 1464 of yacc.c  */
#line 652 "csound_orc.y"
    { 
    printf("FUNCTION ans=%p, token=%p %p\n", (yyvsp[(1) - (1)]), ((ORCTOKEN *)(yyvsp[(1) - (1)]))->value);
#ifdef PARCS
    //                if ((ORCTOKEN *)$1->value != 0)
    csp_orc_sa_interlocksf(csound, ((ORCTOKEN *)(yyvsp[(1) - (1)]))->value);
#endif
    (yyval) = make_leaf(csound, T_FUNCTION, (ORCTOKEN *)(yyvsp[(1) - (1)])); 
                ;}
    break;

  case 135:

/* Line 1464 of yacc.c  */
#line 661 "csound_orc.y"
    { (yyval) = make_leaf(csound, T_SRATE, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 136:

/* Line 1464 of yacc.c  */
#line 662 "csound_orc.y"
    { (yyval) = make_leaf(csound, T_KRATE, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 137:

/* Line 1464 of yacc.c  */
#line 663 "csound_orc.y"
    { (yyval) = make_leaf(csound, T_KSMPS, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 138:

/* Line 1464 of yacc.c  */
#line 664 "csound_orc.y"
    { (yyval) = make_leaf(csound, T_NCHNLS, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 139:

/* Line 1464 of yacc.c  */
#line 665 "csound_orc.y"
    { (yyval) = make_leaf(csound, T_NCHNLSI, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 140:

/* Line 1464 of yacc.c  */
#line 666 "csound_orc.y"
    { (yyval) = make_leaf(csound, T_0DBFS, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 141:

/* Line 1464 of yacc.c  */
#line 669 "csound_orc.y"
    { (yyval) = make_leaf(csound, T_IDENT_I, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 142:

/* Line 1464 of yacc.c  */
#line 670 "csound_orc.y"
    { (yyval) = make_leaf(csound, T_IDENT_K, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 143:

/* Line 1464 of yacc.c  */
#line 671 "csound_orc.y"
    { (yyval) = make_leaf(csound, T_IDENT_F, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 144:

/* Line 1464 of yacc.c  */
#line 672 "csound_orc.y"
    { (yyval) = make_leaf(csound, T_IDENT_W, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 145:

/* Line 1464 of yacc.c  */
#line 673 "csound_orc.y"
    { (yyval) = make_leaf(csound, T_IDENT_S, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 146:

/* Line 1464 of yacc.c  */
#line 674 "csound_orc.y"
    { (yyval) = make_leaf(csound, T_IDENT_T, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 147:

/* Line 1464 of yacc.c  */
#line 675 "csound_orc.y"
    { (yyval) = make_leaf(csound, T_IDENT_A, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 148:

/* Line 1464 of yacc.c  */
#line 676 "csound_orc.y"
    { (yyval) = make_leaf(csound, T_IDENT_P, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 149:

/* Line 1464 of yacc.c  */
#line 677 "csound_orc.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 150:

/* Line 1464 of yacc.c  */
#line 680 "csound_orc.y"
    { (yyval) = make_leaf(csound, T_IDENT_GI, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 151:

/* Line 1464 of yacc.c  */
#line 681 "csound_orc.y"
    { (yyval) = make_leaf(csound, T_IDENT_GK, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 152:

/* Line 1464 of yacc.c  */
#line 682 "csound_orc.y"
    { (yyval) = make_leaf(csound, T_IDENT_GF, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 153:

/* Line 1464 of yacc.c  */
#line 683 "csound_orc.y"
    { (yyval) = make_leaf(csound, T_IDENT_GW, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 154:

/* Line 1464 of yacc.c  */
#line 684 "csound_orc.y"
    { (yyval) = make_leaf(csound, T_IDENT_GS, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 155:

/* Line 1464 of yacc.c  */
#line 685 "csound_orc.y"
    { (yyval) = make_leaf(csound, T_IDENT_GS, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 156:

/* Line 1464 of yacc.c  */
#line 686 "csound_orc.y"
    { (yyval) = make_leaf(csound, T_IDENT_GA, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 157:

/* Line 1464 of yacc.c  */
#line 689 "csound_orc.y"
    { (yyval) = make_leaf(csound, T_INTGR, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 158:

/* Line 1464 of yacc.c  */
#line 690 "csound_orc.y"
    { (yyval) = make_leaf(csound, T_NUMBER, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 159:

/* Line 1464 of yacc.c  */
#line 691 "csound_orc.y"
    { (yyval) = make_leaf(csound, T_STRCONST, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 160:

/* Line 1464 of yacc.c  */
#line 692 "csound_orc.y"
    { (yyval) = make_leaf(csound, T_NUMBER, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 161:

/* Line 1464 of yacc.c  */
#line 693 "csound_orc.y"
    { (yyval) = make_leaf(csound, T_NUMBER, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 162:

/* Line 1464 of yacc.c  */
#line 694 "csound_orc.y"
    { (yyval) = make_leaf(csound, T_NUMBER, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 163:

/* Line 1464 of yacc.c  */
#line 695 "csound_orc.y"
    { (yyval) = make_leaf(csound, T_NUMBER, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 164:

/* Line 1464 of yacc.c  */
#line 696 "csound_orc.y"
    { (yyval) = make_leaf(csound, T_NUMBER, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 165:

/* Line 1464 of yacc.c  */
#line 697 "csound_orc.y"
    { (yyval) = make_leaf(csound, T_NUMBER, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 166:

/* Line 1464 of yacc.c  */
#line 701 "csound_orc.y"
    {
                if (UNLIKELY(PARSER_DEBUG))
                  csound->Message(csound, "opcode0 $1=%p (%s)\n",
                                  (yyvsp[(1) - (1)]),((ORCTOKEN *)(yyvsp[(1) - (1)]))->lexeme );
                (yyval) = make_leaf(csound, T_OPCODE0, (ORCTOKEN *)(yyvsp[(1) - (1)]));
            ;}
    break;

  case 167:

/* Line 1464 of yacc.c  */
#line 709 "csound_orc.y"
    { (yyval) = make_leaf(csound, T_OPCODE, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;



/* Line 1464 of yacc.c  */
#line 3414 "csound_orc.tab.c"
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
    fprintf(stderr, "%d.%d-%d.%d: error: ", yylloc.first_line, yylloc.first_column,
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


