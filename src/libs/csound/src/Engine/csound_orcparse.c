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
#line 141 "csound_orc.y"

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
#define LOCN csound_orcget_locn(scanner)
extern int csound_orcget_locn(void *);
extern int csound_orcget_lineno(void *);


/* Line 189 of yacc.c  */
#line 118 "csound_orc.tab.c"

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
     S_GEQ = 333,
     S_LEQ = 334,
     S_BITSHIFT_RIGHT = 335,
     S_UNOT = 336,
     S_UMINUS = 337,
     S_ATAT = 338,
     S_AT = 339,
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
#line 246 "csound_orc.tab.c"

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
#define YYLAST   2784

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  106
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  37
/* YYNRULES -- Number of rules.  */
#define YYNRULES  196
/* YYNRULES -- Number of states.  */
#define YYNSTATES  319

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
       2,     2,     2,   104,     2,    90,     2,    88,    80,     2,
     102,   103,    86,    84,    98,    85,     2,    87,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   105,     2,
       2,    99,     2,    78,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   100,     2,   101,    89,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    79,     2,    91,     2,     2,     2,
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
      75,    76,    77,    81,    82,    83,    92,    93,    94,    95,
      96,    97
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     8,    11,    14,    16,    18,    20,
      24,    28,    33,    36,    38,    40,    41,    42,    51,    55,
      57,    59,    61,    62,    63,    64,    65,    66,    82,    85,
      86,    91,    93,    98,   103,   111,   116,   120,   122,   126,
     132,   134,   140,   142,   144,   147,   151,   156,   164,   174,
     183,   194,   197,   199,   205,   207,   209,   211,   213,   215,
     217,   219,   221,   223,   225,   227,   229,   231,   233,   235,
     237,   239,   241,   243,   245,   247,   249,   251,   253,   255,
     257,   259,   261,   263,   265,   267,   269,   271,   273,   275,
     277,   281,   285,   289,   291,   293,   295,   297,   299,   300,
     304,   308,   312,   316,   320,   324,   328,   332,   336,   340,
     344,   348,   352,   356,   360,   364,   368,   372,   376,   379,
     382,   388,   394,   399,   403,   405,   409,   413,   417,   421,
     424,   427,   430,   433,   435,   439,   443,   447,   451,   455,
     459,   463,   467,   469,   471,   473,   478,   482,   486,   490,
     494,   498,   502,   506,   510,   514,   518,   521,   524,   528,
     532,   535,   540,   544,   546,   548,   550,   552,   554,   556,
     558,   560,   562,   564,   566,   568,   570,   572,   574,   576,
     578,   580,   582,   584,   586,   588,   590,   592,   594,   596,
     598,   600,   602,   604,   606,   608,   610
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     107,     0,    -1,   108,    -1,   108,   121,    -1,   108,   110,
      -1,   108,   114,    -1,   121,    -1,   110,    -1,   114,    -1,
      66,    98,   109,    -1,   129,    98,   109,    -1,    84,   129,
      98,   109,    -1,    84,   129,    -1,    66,    -1,   129,    -1,
      -1,    -1,    27,   111,   109,     3,   112,   120,    28,     3,
      -1,    27,     3,     1,    -1,    48,    -1,    19,    -1,    18,
      -1,    -1,    -1,    -1,    -1,    -1,    21,   115,   113,   116,
      98,   117,    23,   118,    98,    24,     3,   119,   120,    22,
       3,    -1,   120,   122,    -1,    -1,   137,    99,   132,     3,
      -1,   122,    -1,   138,    99,   132,     3,    -1,    61,    99,
      61,     3,    -1,    61,   100,   133,   101,    99,   132,     3,
      -1,   123,   142,   130,     3,    -1,   141,   130,     3,    -1,
      16,    -1,   128,   129,     3,    -1,    17,   131,   128,   129,
       3,    -1,   124,    -1,    74,   131,    75,   120,    76,    -1,
       3,    -1,   138,    -1,    48,     1,    -1,   123,    98,   138,
      -1,   123,    98,    48,     1,    -1,    17,   131,   127,     3,
     120,    73,     3,    -1,    17,   131,   127,     3,   120,    72,
     120,    73,     3,    -1,    17,   131,   127,     3,   120,   125,
      73,     3,    -1,    17,   131,   127,     3,   120,   125,    72,
     120,    73,     3,    -1,   125,   126,    -1,   126,    -1,    71,
     131,   127,     3,   120,    -1,    68,    -1,    70,    -1,    69,
      -1,    38,    -1,    39,    -1,    40,    -1,    19,    -1,    18,
      -1,    26,    -1,    63,    -1,    49,    -1,    50,    -1,    51,
      -1,    52,    -1,    53,    -1,    54,    -1,    55,    -1,    56,
      -1,    57,    -1,    58,    -1,    59,    -1,    60,    -1,    61,
      -1,    62,    -1,    48,    -1,    17,    -1,    68,    -1,    69,
      -1,    70,    -1,    71,    -1,    73,    -1,    74,    -1,    75,
      -1,    76,    -1,    66,    -1,    28,    -1,   130,    98,   132,
      -1,   130,    98,   129,    -1,   130,    98,     1,    -1,   132,
      -1,   131,    -1,    48,    -1,    19,    -1,    26,    -1,    -1,
     102,   131,   103,    -1,   132,     8,   132,    -1,   132,     8,
       1,    -1,   132,    13,   132,    -1,   132,    13,     1,    -1,
     132,     4,   132,    -1,   132,     4,     1,    -1,   132,     9,
     132,    -1,   132,     9,     1,    -1,   132,    99,   132,    -1,
     132,    99,     1,    -1,   132,    12,   132,    -1,   132,    12,
       1,    -1,   132,     7,   132,    -1,   132,     7,     1,    -1,
     131,     5,   131,    -1,   131,     5,     1,    -1,   131,     6,
     131,    -1,   131,     6,     1,    -1,   104,   131,    -1,   104,
       1,    -1,   131,    78,   132,   105,   132,    -1,   131,    78,
     132,   105,     1,    -1,   131,    78,   132,     1,    -1,   131,
      78,     1,    -1,   133,    -1,   133,    84,   133,    -1,   133,
      84,     1,    -1,   133,    85,   133,    -1,   133,    85,     1,
      -1,    85,   133,    -1,    85,     1,    -1,    84,   133,    -1,
      84,     1,    -1,   134,    -1,   133,    86,   133,    -1,   133,
      86,     1,    -1,   133,    87,   133,    -1,   133,    87,     1,
      -1,   133,    89,   133,    -1,   133,    89,     1,    -1,   133,
      88,   133,    -1,   133,    88,     1,    -1,   135,    -1,   138,
      -1,   140,    -1,    61,   100,   133,   101,    -1,   133,    79,
     133,    -1,   133,    79,     1,    -1,   133,    80,   133,    -1,
     133,    80,     1,    -1,   133,    90,   133,    -1,   133,    90,
       1,    -1,   133,    14,   133,    -1,   133,    14,     1,    -1,
     133,    83,   133,    -1,   133,    83,     1,    -1,    91,   133,
      -1,    91,     1,    -1,   102,   132,   103,    -1,   102,   132,
       1,    -1,   102,     1,    -1,   136,   102,   130,   103,    -1,
     136,   102,     1,    -1,    26,    -1,    41,    -1,    42,    -1,
      43,    -1,    44,    -1,    45,    -1,    46,    -1,    49,    -1,
      51,    -1,    57,    -1,    55,    -1,    59,    -1,    61,    -1,
      53,    -1,    63,    -1,   139,    -1,    50,    -1,    52,    -1,
      58,    -1,    56,    -1,    60,    -1,    62,    -1,    54,    -1,
      66,    -1,    67,    -1,    47,    -1,    41,    -1,    42,    -1,
      43,    -1,    44,    -1,    45,    -1,    46,    -1,    18,    -1,
      19,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   179,   179,   188,   192,   196,   200,   201,   202,   205,
     209,   217,   226,   232,   234,   238,   240,   237,   252,   262,
     263,   264,   267,   269,   271,   273,   275,   266,   311,   315,
     318,   329,   333,   348,   356,   371,   385,   398,   402,   409,
     416,   417,   423,   425,   426,   432,   433,   441,   447,   456,
     465,   487,   499,   502,   512,   514,   516,   520,   522,   524,
     529,   530,   531,   532,   533,   534,   535,   536,   537,   538,
     539,   540,   541,   542,   543,   544,   545,   546,   547,   548,
     549,   550,   551,   552,   553,   554,   555,   556,   557,   558,
     562,   567,   574,   575,   576,   577,   578,   579,   580,   583,
     584,   585,   586,   587,   588,   589,   590,   591,   592,   593,
     594,   595,   596,   597,   598,   599,   600,   601,   602,   604,
     607,   610,   611,   612,   613,   616,   617,   618,   619,   620,
     624,   625,   629,   630,   633,   634,   635,   636,   637,   638,
     639,   640,   641,   644,   645,   646,   652,   653,   654,   655,
     656,   657,   658,   660,   661,   663,   664,   666,   667,   668,
     669,   670,   677,   680,   690,   692,   694,   696,   698,   700,
     704,   705,   706,   707,   708,   709,   710,   711,   712,   715,
     716,   717,   718,   719,   720,   721,   724,   726,   728,   730,
     732,   734,   736,   738,   740,   744,   753
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
  "'?'", "'|'", "'&'", "S_GEQ", "S_LEQ", "S_BITSHIFT_RIGHT", "'+'", "'-'",
  "'*'", "'/'", "'%'", "'^'", "'#'", "'~'", "S_UNOT", "S_UMINUS", "S_ATAT",
  "S_AT", "S_GOTO", "T_HIGHEST", "','", "'='", "'['", "']'", "'('", "')'",
  "'!'", "':'", "$accept", "orcfile", "rootstatement", "instlist",
  "instrdecl", "$@1", "$@2", "udoname", "udodecl", "$@3", "$@4", "$@5",
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
     325,   326,   327,   328,   329,   330,   331,   332,    63,   124,
      38,   333,   334,   335,    43,    45,    42,    47,    37,    94,
      35,   126,   336,   337,   338,   339,   340,   341,    44,    61,
      91,    93,    40,    41,    33,    58
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   106,   107,   108,   108,   108,   108,   108,   108,   109,
     109,   109,   109,   109,   109,   111,   112,   110,   110,   113,
     113,   113,   115,   116,   117,   118,   119,   114,   120,   120,
     121,   121,   122,   122,   122,   122,   122,   122,   122,   122,
     122,   122,   122,   123,   123,   123,   123,   124,   124,   124,
     124,   125,   125,   126,   127,   127,   127,   128,   128,   128,
     129,   129,   129,   129,   129,   129,   129,   129,   129,   129,
     129,   129,   129,   129,   129,   129,   129,   129,   129,   129,
     129,   129,   129,   129,   129,   129,   129,   129,   129,   129,
     130,   130,   130,   130,   130,   130,   130,   130,   130,   131,
     131,   131,   131,   131,   131,   131,   131,   131,   131,   131,
     131,   131,   131,   131,   131,   131,   131,   131,   131,   131,
     132,   132,   132,   132,   132,   133,   133,   133,   133,   133,
     133,   133,   133,   133,   134,   134,   134,   134,   134,   134,
     134,   134,   134,   135,   135,   135,   135,   135,   135,   135,
     135,   135,   135,   135,   135,   135,   135,   135,   135,   135,
     135,   135,   135,   136,   137,   137,   137,   137,   137,   137,
     138,   138,   138,   138,   138,   138,   138,   138,   138,   139,
     139,   139,   139,   139,   139,   139,   140,   140,   140,   140,
     140,   140,   140,   140,   140,   141,   142
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     2,     2,     1,     1,     1,     3,
       3,     4,     2,     1,     1,     0,     0,     8,     3,     1,
       1,     1,     0,     0,     0,     0,     0,    15,     2,     0,
       4,     1,     4,     4,     7,     4,     3,     1,     3,     5,
       1,     5,     1,     1,     2,     3,     4,     7,     9,     8,
      10,     2,     1,     5,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     3,     3,     1,     1,     1,     1,     1,     0,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     2,     2,
       5,     5,     4,     3,     1,     3,     3,     3,     3,     2,
       2,     2,     2,     1,     3,     3,     3,     3,     3,     3,
       3,     3,     1,     1,     1,     4,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     2,     2,     3,     3,
       2,     4,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    42,    37,     0,   195,    22,    15,    57,    58,    59,
     164,   165,   166,   167,   168,   169,     0,   170,   179,   171,
     180,   176,   185,   173,   182,   172,   181,   174,   183,   175,
     184,   177,     0,     0,     2,     7,     8,     6,    31,     0,
      40,     0,     0,    43,   178,    98,   163,   189,   190,   191,
     192,   193,   194,   188,   175,   186,   187,     0,     0,     0,
       0,     0,     0,     0,   124,   133,   142,     0,   143,   144,
       0,     0,     0,    44,     0,     0,     0,     1,     4,     5,
       3,   196,     0,    98,    79,    61,    60,    62,    89,    78,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    63,    88,    80,    81,    82,    83,
      84,    85,    86,    87,     0,     0,     0,    96,    97,    95,
       0,    94,    93,     0,   132,     0,   131,   130,   129,   157,
     156,   160,     0,     0,   119,   118,     0,     0,    54,    56,
      55,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    21,    20,    19,    23,    18,    13,     0,
       0,    14,     0,     0,    29,     0,   175,    45,     0,    38,
       0,     0,     0,    36,     0,     0,    99,   159,   158,   115,
     114,   117,   116,   123,     0,    29,     0,   105,   104,   113,
     112,   101,   100,   107,   106,   111,   110,   103,   102,   109,
     108,   153,   152,   147,   146,   149,   148,   155,   154,   126,
     125,   128,   127,   135,   134,   137,   136,   141,   140,   139,
     138,   151,   150,   162,     0,     0,     0,    12,    16,     0,
      33,     0,     0,    46,    35,    30,    32,    92,    62,   170,
     179,   171,   180,   176,   185,   173,   182,   172,   181,   174,
     183,   175,   184,   177,   186,    91,    90,   145,   122,     0,
       0,    39,   161,    24,     9,     0,    29,    10,     0,    41,
      28,   121,   120,     0,    29,     0,     0,    52,     0,    11,
       0,     0,     0,     0,    47,    29,     0,    51,    25,     0,
      34,     0,     0,     0,    49,     0,    17,    29,    48,     0,
       0,    53,    50,     0,    26,    29,     0,     0,    27
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    33,    34,   170,    35,    72,   276,   166,    36,    70,
     235,   288,   305,   315,   242,    37,   280,    39,    40,   286,
     287,   142,    41,   171,   120,   180,    63,    64,    65,    66,
      67,    42,    68,    44,    69,    45,    83
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -205
static const yytype_int16 yypact[] =
{
    2303,  -205,  -205,  2117,  -205,  -205,     3,  -205,  -205,  -205,
    -205,  -205,  -205,  -205,  -205,  -205,    25,  -205,  -205,  -205,
    -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,   -51,
    -205,  -205,  2117,    33,  2303,  -205,  -205,  -205,  -205,   -12,
    -205,  2708,   -59,   -43,  -205,  2053,  -205,  -205,  -205,  -205,
    -205,  -205,  -205,  -205,   -40,  -205,  -205,  1172,  1235,  1298,
     340,   404,    23,   405,   349,  -205,  -205,   -45,  -205,  -205,
      18,    69,  2648,  -205,    11,  2181,   190,  -205,  -205,  -205,
    -205,  -205,   616,  2053,  -205,  -205,  -205,  -205,  -205,  -205,
    -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,
    -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,
    -205,  -205,  -205,  -205,    77,  2117,  2117,  -205,   -14,  -205,
      -1,     6,   405,  2181,  -205,   340,  -205,  -205,  -205,  -205,
    -205,  -205,     9,    38,  -205,  -205,   468,   532,  -205,  -205,
    -205,   596,    91,  2708,   660,   724,   788,   852,   916,   980,
    1044,  1361,  1424,  1487,  1550,  1613,  1676,  1739,  1802,  1865,
    1928,  1991,   276,  -205,  -205,  -205,  -205,  -205,    -3,  2708,
      93,    17,   113,   396,  -205,   118,  -205,  -205,     2,  -205,
       6,   254,   271,  -205,   131,   459,  -205,  -205,  -205,  -205,
    -205,  -205,  -205,  -205,    12,  -205,   127,  -205,   405,  -205,
     405,  -205,   405,  -205,   405,  -205,   405,  -205,   405,  -205,
     405,  -205,   220,  -205,   522,  -205,   478,  -205,   220,  -205,
     -11,  -205,   -11,  -205,   -25,  -205,   -25,  -205,   -25,  -205,
      48,  -205,  -205,  -205,   -81,    42,  2648,    60,  -205,  2648,
    -205,   104,  2242,  -205,  -205,  -205,  -205,  -205,   -14,    20,
      28,    41,    49,   110,   111,   122,   125,   140,   142,   143,
     150,    24,   151,   152,   153,  -205,   405,  -205,  -205,  1108,
    2364,  -205,  -205,  -205,  -205,  2648,  -205,  -205,  2117,  -205,
    -205,  -205,   405,  2117,  -205,   207,   -18,  -205,   188,  -205,
    2425,   342,   550,  2452,  -205,  -205,   209,  -205,  -205,   214,
    -205,   215,   216,  2513,  -205,   123,  -205,  -205,  -205,   221,
     202,  2601,  -205,   226,  -205,  -205,  2574,   227,  -205
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -205,  -205,  -205,  -204,   197,  -205,  -205,  -205,   198,  -205,
    -205,  -205,  -205,  -205,  -186,   200,     4,  -205,  -205,  -205,
     -49,   -53,   182,   -33,   -73,    -2,   -42,    10,  -205,  -205,
    -205,  -205,     0,  -205,  -205,  -205,  -205
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -164
static const yytype_int16 yytable[] =
{
      43,    62,   183,   122,    38,   244,    71,    81,   114,   270,
     178,   136,   137,   268,   136,   137,   144,   184,   133,   145,
     146,   147,   272,   -64,   148,   149,    73,   -76,   136,   137,
      76,   -65,   274,    77,    43,   277,   163,   164,    38,   187,
     115,   122,   144,   121,   -66,   145,   146,   147,    74,    75,
     148,   149,   -67,   283,   295,   296,   116,   162,   132,   135,
     123,     7,     8,     9,   160,   161,   165,   126,   128,   130,
     167,   289,   172,   181,   182,   157,   158,   159,   160,   161,
     179,   121,   177,   133,   141,   173,    82,   141,  -163,   234,
     290,   138,   139,   140,   195,   236,   238,   184,   293,   194,
     184,   141,   198,   200,   202,   204,   206,   208,   210,   303,
     196,   150,   186,   -68,   -69,   239,   240,   269,   -64,   243,
     122,   311,   -76,   -64,   123,   -70,   -65,   -76,   -71,   316,
     271,   -65,   247,   185,   190,   192,   237,   150,   161,   -66,
     273,   188,   266,   -72,   -66,   -73,   -74,   -67,    84,    85,
      86,   265,   -67,   -75,   -77,   -63,   -88,   248,   275,    88,
     121,   212,   214,   216,   218,   220,   222,   224,   226,   228,
     230,   232,    47,    48,    49,    50,    51,    52,    53,    89,
     249,   250,   251,   252,   253,   254,   255,   256,   257,   258,
     259,   260,   261,   262,   263,   136,   137,   264,    56,   106,
     107,   108,   109,   278,   110,   111,   112,   113,   -68,   -69,
     294,   298,   304,   -68,   -69,    57,    58,   306,   307,   308,
     -70,   310,    59,   -71,   312,   -70,   313,   282,   -71,   314,
     318,    78,    79,    60,    80,    61,   291,   297,   -72,   301,
     -73,   -74,    43,   -72,   143,   -73,   -74,     0,   -75,   -77,
     -63,   -88,     0,   -75,   -77,   -63,   -88,   245,   144,     0,
       0,   145,   146,   147,     0,   174,   148,   149,   141,     0,
      43,     0,     0,     0,   246,   144,     0,   233,   145,   146,
     147,   292,     0,   148,   149,     0,     0,     0,     0,     0,
      43,     0,     0,    43,     0,   117,     0,     0,     0,     0,
       0,     0,   118,    43,   155,   156,   157,   158,   159,   160,
     161,    43,     0,     0,     0,     0,    43,    47,    48,    49,
      50,    51,    52,    53,   119,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    54,    30,    31,
       0,   131,    55,    56,     0,   300,   144,     0,     0,   145,
     146,   147,     0,   150,   148,   149,     0,     0,     0,     0,
      57,    58,     0,   151,     0,     0,    46,    59,     0,     0,
     150,     0,     0,     0,   -98,     0,     0,     0,    60,   -98,
      61,    47,    48,    49,    50,    51,    52,    53,     0,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    54,    30,    31,     0,   134,    55,    56,     0,   144,
     151,     0,   145,   146,   147,     0,     0,   148,   149,     0,
       0,     0,     0,     0,    57,    58,     0,     0,   152,   153,
      46,    59,   154,   155,   156,   157,   158,   159,   160,   161,
       0,   150,    60,     0,    61,    47,    48,    49,    50,    51,
      52,    53,     0,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    54,    30,    31,     0,   189,
      55,    56,     0,   151,     0,   152,   153,     0,     0,   154,
     155,   156,   157,   158,   159,   160,   161,     0,    57,    58,
       0,     0,   151,     0,    46,    59,     0,   241,     0,     0,
       0,     0,     0,     0,   150,     0,    60,     0,    61,    47,
      48,    49,    50,    51,    52,    53,     0,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    54,
      30,    31,     0,   191,    55,    56,   151,     0,   152,   153,
       0,     0,   154,   155,   156,   157,   158,   159,   160,   161,
       0,     0,    57,    58,     0,   136,   137,     0,    46,    59,
     267,   154,   155,   156,   157,   158,   159,   160,   161,     0,
      60,     0,    61,    47,    48,    49,    50,    51,    52,    53,
       0,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    54,    30,    31,     0,   193,    55,    56,
       0,     0,   153,     0,     0,   154,   155,   156,   157,   158,
     159,   160,   161,     0,     0,     0,    57,    58,   138,   139,
     140,     0,    46,    59,     0,     0,     0,     0,   141,     0,
       0,     0,     0,     0,    60,     0,    61,    47,    48,    49,
      50,    51,    52,    53,     0,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    54,    30,    31,
       0,   197,    55,    56,   175,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,   176,    30,    31,
      57,    58,     0,     0,     0,     0,    46,    59,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    60,     0,
      61,    47,    48,    49,    50,    51,    52,    53,     0,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    54,    30,    31,     0,   199,    55,    56,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    57,    58,     0,     0,     0,     0,
      46,    59,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    60,     0,    61,    47,    48,    49,    50,    51,
      52,    53,     0,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    54,    30,    31,     0,   201,
      55,    56,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    57,    58,
       0,     0,     0,     0,    46,    59,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    60,     0,    61,    47,
      48,    49,    50,    51,    52,    53,     0,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    54,
      30,    31,     0,   203,    55,    56,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    57,    58,     0,     0,     0,     0,    46,    59,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      60,     0,    61,    47,    48,    49,    50,    51,    52,    53,
       0,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    54,    30,    31,     0,   205,    55,    56,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    57,    58,     0,     0,
       0,     0,    46,    59,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    60,     0,    61,    47,    48,    49,
      50,    51,    52,    53,     0,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    54,    30,    31,
       0,   207,    55,    56,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      57,    58,     0,     0,     0,     0,    46,    59,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    60,     0,
      61,    47,    48,    49,    50,    51,    52,    53,     0,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    54,    30,    31,     0,   209,    55,    56,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    57,    58,     0,     0,     0,     0,
      46,    59,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    60,     0,    61,    47,    48,    49,    50,    51,
      52,    53,     0,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    54,    30,    31,     0,   281,
      55,    56,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    57,    58,
       0,     0,     0,     0,    46,    59,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    60,     0,    61,    47,
      48,    49,    50,    51,    52,    53,     0,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    54,
      30,    31,     0,   124,    55,    56,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    57,    58,     0,     0,     0,     0,    46,    59,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      60,     0,    61,    47,    48,    49,    50,    51,    52,    53,
       0,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    54,    30,    31,   127,     0,    55,    56,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    57,    58,     0,     0,
       0,    46,     0,    59,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   125,     0,    47,    48,    49,    50,
      51,    52,    53,     0,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    54,    30,    31,   129,
       0,    55,    56,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    57,
      58,     0,     0,     0,    46,     0,    59,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   125,     0,    47,
      48,    49,    50,    51,    52,    53,     0,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    54,
      30,    31,   211,     0,    55,    56,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    57,    58,     0,     0,     0,    46,     0,    59,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     125,     0,    47,    48,    49,    50,    51,    52,    53,     0,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    54,    30,    31,   213,     0,    55,    56,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    57,    58,     0,     0,     0,
      46,     0,    59,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   125,     0,    47,    48,    49,    50,    51,
      52,    53,     0,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    54,    30,    31,   215,     0,
      55,    56,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    57,    58,
       0,     0,     0,    46,     0,    59,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   125,     0,    47,    48,
      49,    50,    51,    52,    53,     0,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    54,    30,
      31,   217,     0,    55,    56,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    57,    58,     0,     0,     0,    46,     0,    59,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   125,
       0,    47,    48,    49,    50,    51,    52,    53,     0,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    54,    30,    31,   219,     0,    55,    56,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    57,    58,     0,     0,     0,    46,
       0,    59,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   125,     0,    47,    48,    49,    50,    51,    52,
      53,     0,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    54,    30,    31,   221,     0,    55,
      56,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    57,    58,     0,
       0,     0,    46,     0,    59,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   125,     0,    47,    48,    49,
      50,    51,    52,    53,     0,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    54,    30,    31,
     223,     0,    55,    56,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      57,    58,     0,     0,     0,    46,     0,    59,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   125,     0,
      47,    48,    49,    50,    51,    52,    53,     0,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      54,    30,    31,   225,     0,    55,    56,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    57,    58,     0,     0,     0,    46,     0,
      59,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   125,     0,    47,    48,    49,    50,    51,    52,    53,
       0,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    54,    30,    31,   227,     0,    55,    56,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    57,    58,     0,     0,
       0,    46,     0,    59,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   125,     0,    47,    48,    49,    50,
      51,    52,    53,     0,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    54,    30,    31,   229,
       0,    55,    56,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    57,
      58,     0,     0,     0,    46,     0,    59,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   125,     0,    47,
      48,    49,    50,    51,    52,    53,     0,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    54,
      30,    31,   231,     0,    55,    56,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    57,    58,     0,     0,     0,    46,     0,    59,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     125,     0,    47,    48,    49,    50,    51,    52,    53,     0,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    54,    30,    31,     0,     0,    55,    56,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   117,     0,     0,    57,    58,     0,     0,   118,
       0,     0,    59,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   125,    47,    48,    49,    50,    51,    52,
      53,   119,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    54,    30,    31,     0,     0,    55,
      56,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    57,    58,     0,
       0,     0,     0,    46,    59,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    60,     0,    61,    47,    48,
      49,    50,    51,    52,    53,     0,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    54,    30,
      31,     0,     0,    55,    56,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    57,    58,     0,     0,     0,     0,    46,    59,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    60,
       0,    61,    47,    48,    49,    50,    51,    52,    53,     0,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    54,    30,    31,     1,     0,    55,    56,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     2,     3,
       4,     0,     0,     0,     0,    57,    58,     0,     0,     0,
       0,     0,    59,     0,     0,     0,     0,     0,     0,     0,
       7,     8,     9,   125,     0,     0,     0,     0,     0,     0,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,     1,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    32,     0,   279,     2,
       3,     4,     0,     0,     5,     0,     0,     0,     0,     0,
       6,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     7,     8,     9,    10,    11,    12,    13,    14,    15,
       0,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,     1,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    32,     0,     0,
       2,     3,     4,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     7,     8,     9,     0,     0,     0,     0,     0,
       0,     0,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,     1,     0,
       0,     0,     0,     0,     0,   283,   284,   285,    32,     0,
       0,     2,     3,     4,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   299,     0,     1,     0,     0,     0,     0,
       0,     0,     0,     7,     8,     9,     0,     0,     2,     3,
       4,     0,     0,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,     0,
       7,     8,     9,     0,     0,     0,     0,     0,     0,    32,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,     1,     0,     0,     0,
       0,     0,     0,     0,     0,   302,    32,     0,     0,     2,
       3,     4,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     7,     8,     9,     0,     0,     0,     0,     0,     0,
       0,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,     1,     0,     0,
       0,     0,     0,     0,     0,     0,   309,    32,     0,     0,
       2,     3,     4,     0,     0,     0,   317,     0,     0,     0,
       0,     0,     0,     0,     1,     0,     0,     0,     0,     0,
       0,     0,     7,     8,     9,     0,     0,     2,     3,     4,
       0,     0,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,     0,     7,
       8,     9,     0,     0,     0,     0,     0,     0,    32,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    84,    85,    86,     0,     0,
       0,     0,     0,     0,    87,    32,    88,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,     0,     0,   168,     0,   106,   107,   108,   109,
       0,   110,   111,   112,   113,    84,    85,    86,     0,     0,
       0,     0,   169,     0,    87,     0,    88,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,     0,     0,   105,     0,   106,   107,   108,   109,
       0,   110,   111,   112,   113
};

static const yytype_int16 yycheck[] =
{
       0,     3,     3,    45,     0,     3,     3,    19,    41,   195,
      83,     5,     6,     1,     5,     6,     4,    98,    60,     7,
       8,     9,   103,     3,    12,    13,     1,     3,     5,     6,
      32,     3,   236,     0,    34,   239,    18,    19,    34,     1,
      99,    83,     4,    45,     3,     7,     8,     9,    99,   100,
      12,    13,     3,    71,    72,    73,    99,   102,    60,    61,
     100,    38,    39,    40,    89,    90,    48,    57,    58,    59,
       1,   275,    61,   115,   116,    86,    87,    88,    89,    90,
       3,    83,    82,   125,    78,    75,    98,    78,   102,   162,
     276,    68,    69,    70,     3,    98,     3,    98,   284,   141,
      98,    78,   144,   145,   146,   147,   148,   149,   150,   295,
     143,    99,   103,     3,     3,    98,     3,   105,    98,     1,
     162,   307,    98,   103,   100,     3,    98,   103,     3,   315,
       3,   103,     1,   123,   136,   137,   169,    99,    90,    98,
      98,   103,   184,     3,   103,     3,     3,    98,    17,    18,
      19,   184,   103,     3,     3,     3,     3,    26,    98,    28,
     162,   151,   152,   153,   154,   155,   156,   157,   158,   159,
     160,   161,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,     5,     6,    66,    67,    68,
      69,    70,    71,    99,    73,    74,    75,    76,    98,    98,
       3,    23,     3,   103,   103,    84,    85,     3,     3,     3,
      98,    98,    91,    98,     3,   103,    24,   269,   103,     3,
       3,    34,    34,   102,    34,   104,   278,   286,    98,   292,
      98,    98,   242,   103,    62,   103,   103,    -1,    98,    98,
      98,    98,    -1,   103,   103,   103,   103,     3,     4,    -1,
      -1,     7,     8,     9,    -1,    75,    12,    13,    78,    -1,
     270,    -1,    -1,    -1,     3,     4,    -1,     1,     7,     8,
       9,   283,    -1,    12,    13,    -1,    -1,    -1,    -1,    -1,
     290,    -1,    -1,   293,    -1,    19,    -1,    -1,    -1,    -1,
      -1,    -1,    26,   303,    84,    85,    86,    87,    88,    89,
      90,   311,    -1,    -1,    -1,    -1,   316,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      -1,     1,    66,    67,    -1,     3,     4,    -1,    -1,     7,
       8,     9,    -1,    99,    12,    13,    -1,    -1,    -1,    -1,
      84,    85,    -1,    14,    -1,    -1,    26,    91,    -1,    -1,
      99,    -1,    -1,    -1,    98,    -1,    -1,    -1,   102,   103,
     104,    41,    42,    43,    44,    45,    46,    47,    -1,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    -1,     1,    66,    67,    -1,     4,
      14,    -1,     7,     8,     9,    -1,    -1,    12,    13,    -1,
      -1,    -1,    -1,    -1,    84,    85,    -1,    -1,    79,    80,
      26,    91,    83,    84,    85,    86,    87,    88,    89,    90,
      -1,    99,   102,    -1,   104,    41,    42,    43,    44,    45,
      46,    47,    -1,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    -1,     1,
      66,    67,    -1,    14,    -1,    79,    80,    -1,    -1,    83,
      84,    85,    86,    87,    88,    89,    90,    -1,    84,    85,
      -1,    -1,    14,    -1,    26,    91,    -1,   101,    -1,    -1,
      -1,    -1,    -1,    -1,    99,    -1,   102,    -1,   104,    41,
      42,    43,    44,    45,    46,    47,    -1,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    -1,     1,    66,    67,    14,    -1,    79,    80,
      -1,    -1,    83,    84,    85,    86,    87,    88,    89,    90,
      -1,    -1,    84,    85,    -1,     5,     6,    -1,    26,    91,
     101,    83,    84,    85,    86,    87,    88,    89,    90,    -1,
     102,    -1,   104,    41,    42,    43,    44,    45,    46,    47,
      -1,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    -1,     1,    66,    67,
      -1,    -1,    80,    -1,    -1,    83,    84,    85,    86,    87,
      88,    89,    90,    -1,    -1,    -1,    84,    85,    68,    69,
      70,    -1,    26,    91,    -1,    -1,    -1,    -1,    78,    -1,
      -1,    -1,    -1,    -1,   102,    -1,   104,    41,    42,    43,
      44,    45,    46,    47,    -1,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      -1,     1,    66,    67,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      84,    85,    -1,    -1,    -1,    -1,    26,    91,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   102,    -1,
     104,    41,    42,    43,    44,    45,    46,    47,    -1,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    -1,     1,    66,    67,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    84,    85,    -1,    -1,    -1,    -1,
      26,    91,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   102,    -1,   104,    41,    42,    43,    44,    45,
      46,    47,    -1,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    -1,     1,
      66,    67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    84,    85,
      -1,    -1,    -1,    -1,    26,    91,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   102,    -1,   104,    41,
      42,    43,    44,    45,    46,    47,    -1,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    -1,     1,    66,    67,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    84,    85,    -1,    -1,    -1,    -1,    26,    91,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     102,    -1,   104,    41,    42,    43,    44,    45,    46,    47,
      -1,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    -1,     1,    66,    67,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    84,    85,    -1,    -1,
      -1,    -1,    26,    91,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   102,    -1,   104,    41,    42,    43,
      44,    45,    46,    47,    -1,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      -1,     1,    66,    67,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      84,    85,    -1,    -1,    -1,    -1,    26,    91,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   102,    -1,
     104,    41,    42,    43,    44,    45,    46,    47,    -1,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    -1,     1,    66,    67,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    84,    85,    -1,    -1,    -1,    -1,
      26,    91,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   102,    -1,   104,    41,    42,    43,    44,    45,
      46,    47,    -1,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    -1,     1,
      66,    67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    84,    85,
      -1,    -1,    -1,    -1,    26,    91,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   102,    -1,   104,    41,
      42,    43,    44,    45,    46,    47,    -1,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    -1,     1,    66,    67,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    84,    85,    -1,    -1,    -1,    -1,    26,    91,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     102,    -1,   104,    41,    42,    43,    44,    45,    46,    47,
      -1,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,     1,    -1,    66,    67,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    84,    85,    -1,    -1,
      -1,    26,    -1,    91,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   102,    -1,    41,    42,    43,    44,
      45,    46,    47,    -1,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,     1,
      -1,    66,    67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    84,
      85,    -1,    -1,    -1,    26,    -1,    91,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   102,    -1,    41,
      42,    43,    44,    45,    46,    47,    -1,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,     1,    -1,    66,    67,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    84,    85,    -1,    -1,    -1,    26,    -1,    91,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     102,    -1,    41,    42,    43,    44,    45,    46,    47,    -1,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,     1,    -1,    66,    67,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    84,    85,    -1,    -1,    -1,
      26,    -1,    91,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   102,    -1,    41,    42,    43,    44,    45,
      46,    47,    -1,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,     1,    -1,
      66,    67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    84,    85,
      -1,    -1,    -1,    26,    -1,    91,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   102,    -1,    41,    42,
      43,    44,    45,    46,    47,    -1,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,     1,    -1,    66,    67,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    84,    85,    -1,    -1,    -1,    26,    -1,    91,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   102,
      -1,    41,    42,    43,    44,    45,    46,    47,    -1,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,     1,    -1,    66,    67,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    84,    85,    -1,    -1,    -1,    26,
      -1,    91,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   102,    -1,    41,    42,    43,    44,    45,    46,
      47,    -1,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,     1,    -1,    66,
      67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    84,    85,    -1,
      -1,    -1,    26,    -1,    91,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   102,    -1,    41,    42,    43,
      44,    45,    46,    47,    -1,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
       1,    -1,    66,    67,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      84,    85,    -1,    -1,    -1,    26,    -1,    91,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   102,    -1,
      41,    42,    43,    44,    45,    46,    47,    -1,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,     1,    -1,    66,    67,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    84,    85,    -1,    -1,    -1,    26,    -1,
      91,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   102,    -1,    41,    42,    43,    44,    45,    46,    47,
      -1,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,     1,    -1,    66,    67,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    84,    85,    -1,    -1,
      -1,    26,    -1,    91,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   102,    -1,    41,    42,    43,    44,
      45,    46,    47,    -1,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,     1,
      -1,    66,    67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    84,
      85,    -1,    -1,    -1,    26,    -1,    91,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   102,    -1,    41,
      42,    43,    44,    45,    46,    47,    -1,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,     1,    -1,    66,    67,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    84,    85,    -1,    -1,    -1,    26,    -1,    91,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     102,    -1,    41,    42,    43,    44,    45,    46,    47,    -1,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    -1,    -1,    66,    67,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    19,    -1,    -1,    84,    85,    -1,    -1,    26,
      -1,    -1,    91,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   102,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    -1,    -1,    66,
      67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    84,    85,    -1,
      -1,    -1,    -1,    26,    91,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   102,    -1,   104,    41,    42,
      43,    44,    45,    46,    47,    -1,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    -1,    -1,    66,    67,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    84,    85,    -1,    -1,    -1,    -1,    26,    91,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   102,
      -1,   104,    41,    42,    43,    44,    45,    46,    47,    -1,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,     3,    -1,    66,    67,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    16,    17,
      18,    -1,    -1,    -1,    -1,    84,    85,    -1,    -1,    -1,
      -1,    -1,    91,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      38,    39,    40,   102,    -1,    -1,    -1,    -1,    -1,    -1,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,     3,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    74,    -1,    76,    16,
      17,    18,    -1,    -1,    21,    -1,    -1,    -1,    -1,    -1,
      27,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      -1,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,     3,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    74,    -1,    -1,
      16,    17,    18,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    38,    39,    40,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,     3,    -1,
      -1,    -1,    -1,    -1,    -1,    71,    72,    73,    74,    -1,
      -1,    16,    17,    18,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    28,    -1,     3,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    38,    39,    40,    -1,    -1,    16,    17,
      18,    -1,    -1,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    -1,
      38,    39,    40,    -1,    -1,    -1,    -1,    -1,    -1,    74,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,     3,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    73,    74,    -1,    -1,    16,
      17,    18,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    38,    39,    40,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,     3,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    73,    74,    -1,    -1,
      16,    17,    18,    -1,    -1,    -1,    22,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     3,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    38,    39,    40,    -1,    -1,    16,    17,    18,
      -1,    -1,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    -1,    38,
      39,    40,    -1,    -1,    -1,    -1,    -1,    -1,    74,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    17,    18,    19,    -1,    -1,
      -1,    -1,    -1,    -1,    26,    74,    28,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    -1,    -1,    66,    -1,    68,    69,    70,    71,
      -1,    73,    74,    75,    76,    17,    18,    19,    -1,    -1,
      -1,    -1,    84,    -1,    26,    -1,    28,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    -1,    -1,    66,    -1,    68,    69,    70,    71,
      -1,    73,    74,    75,    76
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    16,    17,    18,    21,    27,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    74,   107,   108,   110,   114,   121,   122,   123,
     124,   128,   137,   138,   139,   141,    26,    41,    42,    43,
      44,    45,    46,    47,    61,    66,    67,    84,    85,    91,
     102,   104,   131,   132,   133,   134,   135,   136,   138,   140,
     115,     3,   111,     1,    99,   100,   131,     0,   110,   114,
     121,    19,    98,   142,    17,    18,    19,    26,    28,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    66,    68,    69,    70,    71,
      73,    74,    75,    76,   129,    99,    99,    19,    26,    48,
     130,   131,   132,   100,     1,   102,   133,     1,   133,     1,
     133,     1,   131,   132,     1,   131,     5,     6,    68,    69,
      70,    78,   127,   128,     4,     7,     8,     9,    12,    13,
      99,    14,    79,    80,    83,    84,    85,    86,    87,    88,
      89,    90,   102,    18,    19,    48,   113,     1,    66,    84,
     109,   129,    61,   133,    75,    48,    61,   138,   130,     3,
     131,   132,   132,     3,    98,   133,   103,     1,   103,     1,
     131,     1,   131,     1,   132,     3,   129,     1,   132,     1,
     132,     1,   132,     1,   132,     1,   132,     1,   132,     1,
     132,     1,   133,     1,   133,     1,   133,     1,   133,     1,
     133,     1,   133,     1,   133,     1,   133,     1,   133,     1,
     133,     1,   133,     1,   130,   116,    98,   129,     3,    98,
       3,   101,   120,     1,     3,     3,     3,     1,    26,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    66,   129,   132,   101,     1,   105,
     120,     3,   103,    98,   109,    98,   112,   109,    99,    76,
     122,     1,   132,    71,    72,    73,   125,   126,   117,   109,
     120,   132,   131,   120,     3,    72,    73,   126,    23,    28,
       3,   127,    73,   120,     3,   118,     3,     3,     3,    73,
      98,   120,     3,    24,     3,   119,   120,    22,     3
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
#line 180 "csound_orc.y"
    {
                            if ((yyvsp[(1) - (1)]) != NULL)
                              *astTree = *((TREE *)(yyvsp[(1) - (1)]));
                            csound->synterrcnt = csound_orcnerrs;
                            //print_tree(csound, "ALL", $1);
                        ;}
    break;

  case 3:

/* Line 1464 of yacc.c  */
#line 189 "csound_orc.y"
    {
                        (yyval) = appendToTree(csound, (yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]));
                        ;}
    break;

  case 4:

/* Line 1464 of yacc.c  */
#line 193 "csound_orc.y"
    {
                        (yyval) = appendToTree(csound, (yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]));
                        ;}
    break;

  case 5:

/* Line 1464 of yacc.c  */
#line 197 "csound_orc.y"
    {
                        (yyval) = appendToTree(csound, (yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]));
                        ;}
    break;

  case 9:

/* Line 1464 of yacc.c  */
#line 206 "csound_orc.y"
    { (yyval) = make_node(csound, LINE, LOCN, T_INSTLIST,
                               make_leaf(csound, LINE,LOCN,
                                         INTEGER_TOKEN, (ORCTOKEN *)(yyvsp[(1) - (3)])), (yyvsp[(3) - (3)])); ;}
    break;

  case 10:

/* Line 1464 of yacc.c  */
#line 210 "csound_orc.y"
    {
#ifdef PARCS
                  csp_orc_sa_instr_add(csound, ((ORCTOKEN *)(yyvsp[(1) - (3)]))->lexeme);
#endif
                  (yyval) = make_node(csound,LINE,LOCN, T_INSTLIST,
                               make_leaf(csound, LINE,LOCN,
                                         T_IDENT, (ORCTOKEN *)(yyvsp[(1) - (3)])), (yyvsp[(3) - (3)])); ;}
    break;

  case 11:

/* Line 1464 of yacc.c  */
#line 218 "csound_orc.y"
    {
                  TREE *ans;
                  ans = make_leaf(csound, LINE,LOCN, T_IDENT, (ORCTOKEN *)(yyvsp[(2) - (4)]));
                  ans->rate = (int) '+';
#ifdef PARCS
                  csp_orc_sa_instr_add(csound, ((ORCTOKEN *)(yyvsp[(2) - (4)]))->lexeme);
#endif
                  (yyval) = make_node(csound,LINE,LOCN, T_INSTLIST, ans, (yyvsp[(4) - (4)])); ;}
    break;

  case 12:

/* Line 1464 of yacc.c  */
#line 227 "csound_orc.y"
    {
                  TREE *ans;
                  ans = make_leaf(csound, LINE,LOCN, T_IDENT, (ORCTOKEN *)(yyvsp[(2) - (2)]));
                  ans->rate = (int) '+';
                  (yyval) = ans; ;}
    break;

  case 13:

/* Line 1464 of yacc.c  */
#line 232 "csound_orc.y"
    { (yyval) = make_leaf(csound, LINE,LOCN,
                                           INTEGER_TOKEN, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 14:

/* Line 1464 of yacc.c  */
#line 234 "csound_orc.y"
    { (yyval) = make_leaf(csound, LINE,LOCN, T_IDENT, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 15:

/* Line 1464 of yacc.c  */
#line 238 "csound_orc.y"
    { namedInstrFlag = 1; ;}
    break;

  case 16:

/* Line 1464 of yacc.c  */
#line 240 "csound_orc.y"
    { namedInstrFlag = 0;
#ifdef PARCS
                  csp_orc_sa_instr_add_tree(csound, (yyvsp[(3) - (4)]));
#endif
                ;}
    break;

  case 17:

/* Line 1464 of yacc.c  */
#line 246 "csound_orc.y"
    {
                    (yyval) = make_node(csound, LINE,LOCN, INSTR_TOKEN, (yyvsp[(3) - (8)]), (yyvsp[(6) - (8)]));
#ifdef PARCS
                    csp_orc_sa_instr_finalize(csound);
#endif
                ;}
    break;

  case 18:

/* Line 1464 of yacc.c  */
#line 253 "csound_orc.y"
    {
                    namedInstrFlag = 0;
                    csound->Message(csound, Str("No number following instr\n"));
#ifdef PARCS
                    csp_orc_sa_instr_finalize(csound);
#endif
                ;}
    break;

  case 19:

/* Line 1464 of yacc.c  */
#line 262 "csound_orc.y"
    { (yyval) = (TREE *)(yyvsp[(1) - (1)]); ;}
    break;

  case 20:

/* Line 1464 of yacc.c  */
#line 263 "csound_orc.y"
    { (yyval) = (TREE *)(yyvsp[(1) - (1)]); ;}
    break;

  case 21:

/* Line 1464 of yacc.c  */
#line 264 "csound_orc.y"
    { (yyval) = (TREE *)(yyvsp[(1) - (1)]); ;}
    break;

  case 22:

/* Line 1464 of yacc.c  */
#line 267 "csound_orc.y"
    { udoflag = -2; ;}
    break;

  case 23:

/* Line 1464 of yacc.c  */
#line 269 "csound_orc.y"
    { udoflag = -1; ;}
    break;

  case 24:

/* Line 1464 of yacc.c  */
#line 271 "csound_orc.y"
    { udoflag = 0;;}
    break;

  case 25:

/* Line 1464 of yacc.c  */
#line 273 "csound_orc.y"
    { udoflag = 1; ;}
    break;

  case 26:

/* Line 1464 of yacc.c  */
#line 275 "csound_orc.y"
    {
                udoflag = 2;
                add_udo_definition(csound,
                        ((ORCTOKEN *)(yyvsp[(3) - (11)]))->lexeme,
                        ((ORCTOKEN *)(yyvsp[(7) - (11)]))->lexeme,
                        ((ORCTOKEN *)(yyvsp[(10) - (11)]))->lexeme);
              ;}
    break;

  case 27:

/* Line 1464 of yacc.c  */
#line 283 "csound_orc.y"
    {
                TREE *udoTop = make_leaf(csound, LINE,LOCN, UDO_TOKEN,
                                         (ORCTOKEN *)NULL);
                TREE *ident = make_leaf(csound, LINE,LOCN, T_IDENT,
                                        (ORCTOKEN *)(yyvsp[(3) - (15)]));
                TREE *udoAns = make_leaf(csound, LINE,LOCN, UDO_ANS_TOKEN,
                                         (ORCTOKEN *)(yyvsp[(7) - (15)]));
                TREE *udoArgs = make_leaf(csound, LINE,LOCN, UDO_ARGS_TOKEN,
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

  case 28:

/* Line 1464 of yacc.c  */
#line 312 "csound_orc.y"
    {
                    (yyval) = appendToTree(csound, (TREE *)(yyvsp[(1) - (2)]), (TREE *)(yyvsp[(2) - (2)]));
                ;}
    break;

  case 29:

/* Line 1464 of yacc.c  */
#line 315 "csound_orc.y"
    { (yyval) = NULL; ;}
    break;

  case 30:

/* Line 1464 of yacc.c  */
#line 319 "csound_orc.y"
    {

                  TREE *ans = make_leaf(csound,LINE,LOCN, '=', (ORCTOKEN *)(yyvsp[(2) - (4)]));
                  ans->left = (TREE *)(yyvsp[(1) - (4)]);
                  ans->right = (TREE *)(yyvsp[(3) - (4)]);
                  /* ans->value->lexeme = get_assignment_type(csound,
                      ans->left->value->lexeme, ans->right->value->lexeme); */

                  (yyval) = ans;
                ;}
    break;

  case 31:

/* Line 1464 of yacc.c  */
#line 329 "csound_orc.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 32:

/* Line 1464 of yacc.c  */
#line 334 "csound_orc.y"
    {
                  TREE *ans = make_leaf(csound,LINE,LOCN, '=', (ORCTOKEN *)(yyvsp[(2) - (4)]));
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

  case 33:

/* Line 1464 of yacc.c  */
#line 349 "csound_orc.y"
    {
              ORCTOKEN *op = lookup_token(csound, "#copytab", NULL);
              TREE *ans = make_leaf(csound,LINE,LOCN, T_OPCODE, op);
              ans->left = make_leaf(csound,LINE,LOCN, T_IDENT_T, (ORCTOKEN *)(yyvsp[(1) - (4)]));
              ans->right = make_leaf(csound,LINE,LOCN, T_IDENT_T, (ORCTOKEN *)(yyvsp[(3) - (4)]));
              (yyval) = ans;
          ;}
    break;

  case 34:

/* Line 1464 of yacc.c  */
#line 357 "csound_orc.y"
    {
              TREE *ans = make_leaf(csound,LINE,LOCN, '=', (ORCTOKEN *)(yyvsp[(5) - (7)]));
              ans->left = make_leaf(csound,LINE,LOCN, T_IDENT_T, (ORCTOKEN *)(yyvsp[(1) - (7)]));
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

  case 35:

/* Line 1464 of yacc.c  */
#line 372 "csound_orc.y"
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

  case 36:

/* Line 1464 of yacc.c  */
#line 386 "csound_orc.y"
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

  case 37:

/* Line 1464 of yacc.c  */
#line 399 "csound_orc.y"
    {
                    (yyval) = make_leaf(csound,LINE,LOCN, LABEL_TOKEN, (ORCTOKEN *)(yyvsp[(1) - (1)]));
                ;}
    break;

  case 38:

/* Line 1464 of yacc.c  */
#line 403 "csound_orc.y"
    {
                    (yyvsp[(1) - (3)])->left = NULL;
                    (yyvsp[(1) - (3)])->right = make_leaf(csound, LINE,LOCN,
                                          LABEL_TOKEN, (ORCTOKEN *)(yyvsp[(2) - (3)]));
                    (yyval) = (yyvsp[(1) - (3)]);
                ;}
    break;

  case 39:

/* Line 1464 of yacc.c  */
#line 410 "csound_orc.y"
    {
                    (yyvsp[(3) - (5)])->left = NULL;
                    (yyvsp[(3) - (5)])->right = make_leaf(csound, LINE,LOCN,
                                          LABEL_TOKEN, (ORCTOKEN *)(yyvsp[(4) - (5)]));
                    (yyval) = make_node(csound,LINE,LOCN, IF_TOKEN, (yyvsp[(2) - (5)]), (yyvsp[(3) - (5)]));
                ;}
    break;

  case 41:

/* Line 1464 of yacc.c  */
#line 418 "csound_orc.y"
    {
                  (yyval) = make_leaf(csound,LINE,LOCN, UNTIL_TOKEN, (ORCTOKEN *)(yyvsp[(1) - (5)]));
                  (yyval)->left = (yyvsp[(2) - (5)]);
                  (yyval)->right = (yyvsp[(4) - (5)]);
              ;}
    break;

  case 42:

/* Line 1464 of yacc.c  */
#line 423 "csound_orc.y"
    { (yyval) = NULL; ;}
    break;

  case 43:

/* Line 1464 of yacc.c  */
#line 425 "csound_orc.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 44:

/* Line 1464 of yacc.c  */
#line 427 "csound_orc.y"
    { csound->Message(csound,
                      "Unexpected untyped word %s when expecting a variable\n", 
                      ((ORCTOKEN*)(yyvsp[(1) - (2)]))->lexeme);
                (yyval) = NULL;
              ;}
    break;

  case 45:

/* Line 1464 of yacc.c  */
#line 432 "csound_orc.y"
    { (yyval) = appendToTree(csound, (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 46:

/* Line 1464 of yacc.c  */
#line 434 "csound_orc.y"
    { csound->Message(csound,
                      "Unexpected untyped word %s when expecting a variable\n", 
                               ((ORCTOKEN*)(yyvsp[(3) - (4)]))->lexeme);
                (yyval) = appendToTree(csound, (yyvsp[(1) - (4)]), NULL);
              ;}
    break;

  case 47:

/* Line 1464 of yacc.c  */
#line 442 "csound_orc.y"
    {
            (yyvsp[(3) - (7)])->right = (yyvsp[(5) - (7)]);
            (yyval) = make_node(csound,LINE,LOCN, IF_TOKEN, (yyvsp[(2) - (7)]), (yyvsp[(3) - (7)]));
            //print_tree(csound, "if-endif", $$);
          ;}
    break;

  case 48:

/* Line 1464 of yacc.c  */
#line 449 "csound_orc.y"
    {
            (yyvsp[(3) - (9)])->right = (yyvsp[(5) - (9)]);
            (yyvsp[(3) - (9)])->next = make_node(csound,LINE,LOCN, ELSE_TOKEN, NULL, (yyvsp[(7) - (9)]));
            (yyval) = make_node(csound,LINE,LOCN, IF_TOKEN, (yyvsp[(2) - (9)]), (yyvsp[(3) - (9)]));
            //print_tree(csound, "if-else", $$);

          ;}
    break;

  case 49:

/* Line 1464 of yacc.c  */
#line 457 "csound_orc.y"
    {
            if (UNLIKELY(PARSER_DEBUG))
                csound->Message(csound, "IF-ELSEIF FOUND!\n");
            (yyvsp[(3) - (8)])->right = (yyvsp[(5) - (8)]);
            (yyvsp[(3) - (8)])->next = (yyvsp[(6) - (8)]);
            (yyval) = make_node(csound, LINE,LOCN, IF_TOKEN, (yyvsp[(2) - (8)]), (yyvsp[(3) - (8)]));
            //print_tree(csound, "if-elseif\n", $$);
          ;}
    break;

  case 50:

/* Line 1464 of yacc.c  */
#line 467 "csound_orc.y"
    {
            TREE * tempLastNode;

            (yyvsp[(3) - (10)])->right = (yyvsp[(5) - (10)]);
            (yyvsp[(3) - (10)])->next = (yyvsp[(6) - (10)]);

            (yyval) = make_node(csound, LINE,LOCN, IF_TOKEN, (yyvsp[(2) - (10)]), (yyvsp[(3) - (10)]));

            tempLastNode = (yyval);

            while (tempLastNode->right!=NULL && tempLastNode->right->next!=NULL) {
                tempLastNode = tempLastNode->right->next;
            }

            tempLastNode->right->next = make_node(csound, LINE,LOCN,
                                                  ELSE_TOKEN, NULL, (yyvsp[(8) - (10)]));
            //print_tree(csound, "IF TREE", $$);
          ;}
    break;

  case 51:

/* Line 1464 of yacc.c  */
#line 488 "csound_orc.y"
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

  case 52:

/* Line 1464 of yacc.c  */
#line 499 "csound_orc.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 53:

/* Line 1464 of yacc.c  */
#line 503 "csound_orc.y"
    {
                if (UNLIKELY(PARSER_DEBUG))
                  csound->Message(csound, "ELSEIF FOUND!\n");
                (yyvsp[(3) - (5)])->right = (yyvsp[(5) - (5)]);
                (yyval) = make_node(csound,LINE,LOCN, ELSEIF_TOKEN, (yyvsp[(2) - (5)]), (yyvsp[(3) - (5)]));
                //print_tree(csound, "ELSEIF", $$);
            ;}
    break;

  case 54:

/* Line 1464 of yacc.c  */
#line 513 "csound_orc.y"
    { (yyval) = make_leaf(csound,LINE,LOCN, THEN_TOKEN, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 55:

/* Line 1464 of yacc.c  */
#line 515 "csound_orc.y"
    { (yyval) = make_leaf(csound,LINE,LOCN, KTHEN_TOKEN, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 56:

/* Line 1464 of yacc.c  */
#line 517 "csound_orc.y"
    { (yyval) = make_leaf(csound,LINE,LOCN, ITHEN_TOKEN, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 57:

/* Line 1464 of yacc.c  */
#line 521 "csound_orc.y"
    { (yyval) = make_leaf(csound,LINE,LOCN, GOTO_TOKEN, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 58:

/* Line 1464 of yacc.c  */
#line 523 "csound_orc.y"
    { (yyval) = make_leaf(csound,LINE,LOCN, KGOTO_TOKEN, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 59:

/* Line 1464 of yacc.c  */
#line 525 "csound_orc.y"
    { (yyval) = make_leaf(csound,LINE,LOCN, IGOTO_TOKEN, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 60:

/* Line 1464 of yacc.c  */
#line 529 "csound_orc.y"
    { (yyval) = (TREE *)(yyvsp[(1) - (1)]); ;}
    break;

  case 61:

/* Line 1464 of yacc.c  */
#line 530 "csound_orc.y"
    { (yyval) = (TREE *)(yyvsp[(1) - (1)]); ;}
    break;

  case 62:

/* Line 1464 of yacc.c  */
#line 531 "csound_orc.y"
    { (yyval) = (TREE *)(yyvsp[(1) - (1)]); ;}
    break;

  case 63:

/* Line 1464 of yacc.c  */
#line 532 "csound_orc.y"
    { (yyval) = (TREE *)(yyvsp[(1) - (1)]); ;}
    break;

  case 64:

/* Line 1464 of yacc.c  */
#line 533 "csound_orc.y"
    { (yyval) = (TREE *)(yyvsp[(1) - (1)]); ;}
    break;

  case 65:

/* Line 1464 of yacc.c  */
#line 534 "csound_orc.y"
    { (yyval) = (TREE *)(yyvsp[(1) - (1)]); ;}
    break;

  case 66:

/* Line 1464 of yacc.c  */
#line 535 "csound_orc.y"
    { (yyval) = (TREE *)(yyvsp[(1) - (1)]); ;}
    break;

  case 67:

/* Line 1464 of yacc.c  */
#line 536 "csound_orc.y"
    { (yyval) = (TREE *)(yyvsp[(1) - (1)]); ;}
    break;

  case 68:

/* Line 1464 of yacc.c  */
#line 537 "csound_orc.y"
    { (yyval) = (TREE *)(yyvsp[(1) - (1)]); ;}
    break;

  case 69:

/* Line 1464 of yacc.c  */
#line 538 "csound_orc.y"
    { (yyval) = (TREE *)(yyvsp[(1) - (1)]); ;}
    break;

  case 70:

/* Line 1464 of yacc.c  */
#line 539 "csound_orc.y"
    { (yyval) = (TREE *)(yyvsp[(1) - (1)]); ;}
    break;

  case 71:

/* Line 1464 of yacc.c  */
#line 540 "csound_orc.y"
    { (yyval) = (TREE *)(yyvsp[(1) - (1)]); ;}
    break;

  case 72:

/* Line 1464 of yacc.c  */
#line 541 "csound_orc.y"
    { (yyval) = (TREE *)(yyvsp[(1) - (1)]); ;}
    break;

  case 73:

/* Line 1464 of yacc.c  */
#line 542 "csound_orc.y"
    { (yyval) = (TREE *)(yyvsp[(1) - (1)]); ;}
    break;

  case 74:

/* Line 1464 of yacc.c  */
#line 543 "csound_orc.y"
    { (yyval) = (TREE *)(yyvsp[(1) - (1)]); ;}
    break;

  case 75:

/* Line 1464 of yacc.c  */
#line 544 "csound_orc.y"
    { (yyval) = (TREE *)(yyvsp[(1) - (1)]); ;}
    break;

  case 76:

/* Line 1464 of yacc.c  */
#line 545 "csound_orc.y"
    { (yyval) = (TREE *)(yyvsp[(1) - (1)]); ;}
    break;

  case 77:

/* Line 1464 of yacc.c  */
#line 546 "csound_orc.y"
    { (yyval) = (TREE *)(yyvsp[(1) - (1)]); ;}
    break;

  case 78:

/* Line 1464 of yacc.c  */
#line 547 "csound_orc.y"
    { (yyval) = (TREE *)(yyvsp[(1) - (1)]); ;}
    break;

  case 79:

/* Line 1464 of yacc.c  */
#line 548 "csound_orc.y"
    { (yyval) = (TREE *)(yyvsp[(1) - (1)]); ;}
    break;

  case 80:

/* Line 1464 of yacc.c  */
#line 549 "csound_orc.y"
    { (yyval) = (TREE *)(yyvsp[(1) - (1)]); ;}
    break;

  case 81:

/* Line 1464 of yacc.c  */
#line 550 "csound_orc.y"
    { (yyval) = (TREE *)(yyvsp[(1) - (1)]); ;}
    break;

  case 82:

/* Line 1464 of yacc.c  */
#line 551 "csound_orc.y"
    { (yyval) = (TREE *)(yyvsp[(1) - (1)]); ;}
    break;

  case 83:

/* Line 1464 of yacc.c  */
#line 552 "csound_orc.y"
    { (yyval) = (TREE *)(yyvsp[(1) - (1)]); ;}
    break;

  case 84:

/* Line 1464 of yacc.c  */
#line 553 "csound_orc.y"
    { (yyval) = (TREE *)(yyvsp[(1) - (1)]); ;}
    break;

  case 85:

/* Line 1464 of yacc.c  */
#line 554 "csound_orc.y"
    { (yyval) = (TREE *)(yyvsp[(1) - (1)]); ;}
    break;

  case 86:

/* Line 1464 of yacc.c  */
#line 555 "csound_orc.y"
    { (yyval) = (TREE *)(yyvsp[(1) - (1)]); ;}
    break;

  case 87:

/* Line 1464 of yacc.c  */
#line 556 "csound_orc.y"
    { (yyval) = (TREE *)(yyvsp[(1) - (1)]); ;}
    break;

  case 88:

/* Line 1464 of yacc.c  */
#line 557 "csound_orc.y"
    { (yyval) = (TREE *)(yyvsp[(1) - (1)]); ;}
    break;

  case 89:

/* Line 1464 of yacc.c  */
#line 558 "csound_orc.y"
    { (yyval) = (TREE *)(yyvsp[(1) - (1)]); ;}
    break;

  case 90:

/* Line 1464 of yacc.c  */
#line 563 "csound_orc.y"
    {
                    /* $$ = make_node(',', $1, $3); */
                    (yyval) = appendToTree(csound, (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
                ;}
    break;

  case 91:

/* Line 1464 of yacc.c  */
#line 568 "csound_orc.y"
    {
                    /* $$ = make_node(',', $1, $3); */
                    (yyval) = appendToTree(csound, (yyvsp[(1) - (3)]),
                                      make_leaf(csound, LINE,LOCN,
                                                LABEL_TOKEN, (ORCTOKEN *)(yyvsp[(3) - (3)])));
                ;}
    break;

  case 93:

/* Line 1464 of yacc.c  */
#line 575 "csound_orc.y"
    { (yyval) = (yyvsp[(1) - (1)]);     ;}
    break;

  case 94:

/* Line 1464 of yacc.c  */
#line 576 "csound_orc.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 95:

/* Line 1464 of yacc.c  */
#line 577 "csound_orc.y"
    { (yyval) = make_leaf(csound, LINE,LOCN, LABEL_TOKEN, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 96:

/* Line 1464 of yacc.c  */
#line 578 "csound_orc.y"
    { (yyval) = make_leaf(csound, LINE,LOCN, LABEL_TOKEN, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 97:

/* Line 1464 of yacc.c  */
#line 579 "csound_orc.y"
    { (yyval) = make_leaf(csound, LINE,LOCN, LABEL_TOKEN, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 98:

/* Line 1464 of yacc.c  */
#line 580 "csound_orc.y"
    { (yyval) = NULL; ;}
    break;

  case 99:

/* Line 1464 of yacc.c  */
#line 583 "csound_orc.y"
    { (yyval) = (yyvsp[(2) - (3)]); ;}
    break;

  case 100:

/* Line 1464 of yacc.c  */
#line 584 "csound_orc.y"
    { (yyval) = make_node(csound, LINE,LOCN, S_LE, (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 102:

/* Line 1464 of yacc.c  */
#line 586 "csound_orc.y"
    { (yyval) = make_node(csound, LINE,LOCN, S_GE, (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 104:

/* Line 1464 of yacc.c  */
#line 588 "csound_orc.y"
    { (yyval) = make_node(csound, LINE,LOCN, S_NEQ, (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 106:

/* Line 1464 of yacc.c  */
#line 590 "csound_orc.y"
    { (yyval) = make_node(csound, LINE,LOCN, S_EQ, (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 108:

/* Line 1464 of yacc.c  */
#line 592 "csound_orc.y"
    { (yyval) = make_node(csound, LINE,LOCN, S_EQ, (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 110:

/* Line 1464 of yacc.c  */
#line 594 "csound_orc.y"
    { (yyval) = make_node(csound, LINE,LOCN, S_GT, (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 112:

/* Line 1464 of yacc.c  */
#line 596 "csound_orc.y"
    { (yyval) = make_node(csound, LINE,LOCN, S_LT, (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 114:

/* Line 1464 of yacc.c  */
#line 598 "csound_orc.y"
    { (yyval) = make_node(csound, LINE,LOCN, S_AND, (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 116:

/* Line 1464 of yacc.c  */
#line 600 "csound_orc.y"
    { (yyval) = make_node(csound, LINE,LOCN, S_OR, (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 118:

/* Line 1464 of yacc.c  */
#line 602 "csound_orc.y"
    { (yyval) = make_node(csound, LINE,LOCN,
                                                    S_UNOT, (yyvsp[(2) - (2)]), NULL); ;}
    break;

  case 119:

/* Line 1464 of yacc.c  */
#line 604 "csound_orc.y"
    { (yyval) = NULL; ;}
    break;

  case 120:

/* Line 1464 of yacc.c  */
#line 608 "csound_orc.y"
    { (yyval) = make_node(csound,LINE,LOCN, '?', (yyvsp[(1) - (5)]),
                             make_node(csound, LINE,LOCN, ':', (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)]))); ;}
    break;

  case 124:

/* Line 1464 of yacc.c  */
#line 613 "csound_orc.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 125:

/* Line 1464 of yacc.c  */
#line 616 "csound_orc.y"
    { (yyval) = make_node(csound, LINE,LOCN, '+', (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 127:

/* Line 1464 of yacc.c  */
#line 618 "csound_orc.y"
    { (yyval) = make_node(csound ,LINE,LOCN, '-', (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 129:

/* Line 1464 of yacc.c  */
#line 621 "csound_orc.y"
    {
                (yyval) = make_node(csound,LINE,LOCN, S_UMINUS, NULL, (yyvsp[(2) - (2)]));
            ;}
    break;

  case 130:

/* Line 1464 of yacc.c  */
#line 624 "csound_orc.y"
    { (yyval) = NULL; ;}
    break;

  case 131:

/* Line 1464 of yacc.c  */
#line 626 "csound_orc.y"
    {
                (yyval) = (yyvsp[(2) - (2)]);
            ;}
    break;

  case 132:

/* Line 1464 of yacc.c  */
#line 629 "csound_orc.y"
    { (yyval) = NULL; ;}
    break;

  case 133:

/* Line 1464 of yacc.c  */
#line 630 "csound_orc.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 134:

/* Line 1464 of yacc.c  */
#line 633 "csound_orc.y"
    { (yyval) = make_node(csound, LINE,LOCN, '*', (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 136:

/* Line 1464 of yacc.c  */
#line 635 "csound_orc.y"
    { (yyval) = make_node(csound, LINE,LOCN, '/', (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 138:

/* Line 1464 of yacc.c  */
#line 637 "csound_orc.y"
    { (yyval) = make_node(csound, LINE,LOCN, '^', (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 140:

/* Line 1464 of yacc.c  */
#line 639 "csound_orc.y"
    { (yyval) = make_node(csound, LINE,LOCN, '%', (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 142:

/* Line 1464 of yacc.c  */
#line 641 "csound_orc.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 143:

/* Line 1464 of yacc.c  */
#line 644 "csound_orc.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 144:

/* Line 1464 of yacc.c  */
#line 645 "csound_orc.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 145:

/* Line 1464 of yacc.c  */
#line 647 "csound_orc.y"
    {
              (yyval) = make_node(csound,LINE,LOCN, S_TABREF,
                             make_leaf(csound, LINE,LOCN,
                                       T_IDENT_T, (ORCTOKEN*)(yyvsp[(1) - (4)])), (yyvsp[(3) - (4)]));
          ;}
    break;

  case 146:

/* Line 1464 of yacc.c  */
#line 652 "csound_orc.y"
    { (yyval) = make_node(csound, LINE,LOCN, '|', (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 148:

/* Line 1464 of yacc.c  */
#line 654 "csound_orc.y"
    { (yyval) = make_node(csound, LINE,LOCN, '&', (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 150:

/* Line 1464 of yacc.c  */
#line 656 "csound_orc.y"
    { (yyval) = make_node(csound, LINE,LOCN, '#', (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 152:

/* Line 1464 of yacc.c  */
#line 659 "csound_orc.y"
    { (yyval) = make_node(csound, LINE,LOCN, S_BITSHIFT_LEFT, (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 154:

/* Line 1464 of yacc.c  */
#line 662 "csound_orc.y"
    { (yyval) = make_node(csound, LINE,LOCN, S_BITSHIFT_RIGHT, (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 156:

/* Line 1464 of yacc.c  */
#line 665 "csound_orc.y"
    { (yyval) = make_node(csound, LINE,LOCN, '~', NULL, (yyvsp[(2) - (2)]));;}
    break;

  case 157:

/* Line 1464 of yacc.c  */
#line 666 "csound_orc.y"
    { (yyval) = NULL; ;}
    break;

  case 158:

/* Line 1464 of yacc.c  */
#line 667 "csound_orc.y"
    { (yyval) = (yyvsp[(2) - (3)]); ;}
    break;

  case 159:

/* Line 1464 of yacc.c  */
#line 668 "csound_orc.y"
    { (yyval) = NULL; ;}
    break;

  case 160:

/* Line 1464 of yacc.c  */
#line 669 "csound_orc.y"
    { (yyval) = NULL; ;}
    break;

  case 161:

/* Line 1464 of yacc.c  */
#line 671 "csound_orc.y"
    {
                (yyvsp[(1) - (4)])->left = NULL;
                (yyvsp[(1) - (4)])->right = (yyvsp[(3) - (4)]);

                (yyval) = (yyvsp[(1) - (4)]);
            ;}
    break;

  case 163:

/* Line 1464 of yacc.c  */
#line 680 "csound_orc.y"
    { 
             csound->DebugMsg(csound,"FUNCTION ans=%p, token=%p %p\n",
                    (yyvsp[(1) - (1)]), ((ORCTOKEN *)(yyvsp[(1) - (1)]))->value);
#ifdef PARCS
    //                if ((ORCTOKEN *)$1->value != 0)
             csp_orc_sa_interlocksf(csound, ((ORCTOKEN *)(yyvsp[(1) - (1)]))->value);
#endif
             (yyval) = make_leaf(csound, LINE,LOCN, T_FUNCTION, (ORCTOKEN *)(yyvsp[(1) - (1)])); 
                ;}
    break;

  case 164:

/* Line 1464 of yacc.c  */
#line 690 "csound_orc.y"
    { (yyval) = make_leaf(csound, LINE,LOCN,
                                             SRATE_TOKEN, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 165:

/* Line 1464 of yacc.c  */
#line 692 "csound_orc.y"
    { (yyval) = make_leaf(csound, LINE,LOCN,
                                             KRATE_TOKEN, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 166:

/* Line 1464 of yacc.c  */
#line 694 "csound_orc.y"
    { (yyval) = make_leaf(csound, LINE,LOCN,
                                             KSMPS_TOKEN, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 167:

/* Line 1464 of yacc.c  */
#line 696 "csound_orc.y"
    { (yyval) = make_leaf(csound, LINE,LOCN,
                                             NCHNLS_TOKEN, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 168:

/* Line 1464 of yacc.c  */
#line 698 "csound_orc.y"
    { (yyval) = make_leaf(csound, LINE,LOCN,
                                             NCHNLSI_TOKEN, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 169:

/* Line 1464 of yacc.c  */
#line 700 "csound_orc.y"
    { (yyval) = make_leaf(csound, LINE,LOCN,
                                             ZERODBFS_TOKEN, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 170:

/* Line 1464 of yacc.c  */
#line 704 "csound_orc.y"
    { (yyval) = make_leaf(csound, LINE,LOCN, T_IDENT_I, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 171:

/* Line 1464 of yacc.c  */
#line 705 "csound_orc.y"
    { (yyval) = make_leaf(csound, LINE,LOCN, T_IDENT_K, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 172:

/* Line 1464 of yacc.c  */
#line 706 "csound_orc.y"
    { (yyval) = make_leaf(csound, LINE,LOCN, T_IDENT_F, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 173:

/* Line 1464 of yacc.c  */
#line 707 "csound_orc.y"
    { (yyval) = make_leaf(csound, LINE,LOCN, T_IDENT_W, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 174:

/* Line 1464 of yacc.c  */
#line 708 "csound_orc.y"
    { (yyval) = make_leaf(csound, LINE,LOCN, T_IDENT_S, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 175:

/* Line 1464 of yacc.c  */
#line 709 "csound_orc.y"
    { (yyval) = make_leaf(csound, LINE,LOCN, T_IDENT_T, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 176:

/* Line 1464 of yacc.c  */
#line 710 "csound_orc.y"
    { (yyval) = make_leaf(csound, LINE,LOCN, T_IDENT_A, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 177:

/* Line 1464 of yacc.c  */
#line 711 "csound_orc.y"
    { (yyval) = make_leaf(csound, LINE,LOCN, T_IDENT_P, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 178:

/* Line 1464 of yacc.c  */
#line 712 "csound_orc.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 179:

/* Line 1464 of yacc.c  */
#line 715 "csound_orc.y"
    { (yyval) = make_leaf(csound, LINE,LOCN, T_IDENT_GI, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 180:

/* Line 1464 of yacc.c  */
#line 716 "csound_orc.y"
    { (yyval) = make_leaf(csound, LINE,LOCN, T_IDENT_GK, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 181:

/* Line 1464 of yacc.c  */
#line 717 "csound_orc.y"
    { (yyval) = make_leaf(csound, LINE,LOCN, T_IDENT_GF, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 182:

/* Line 1464 of yacc.c  */
#line 718 "csound_orc.y"
    { (yyval) = make_leaf(csound, LINE,LOCN, T_IDENT_GW, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 183:

/* Line 1464 of yacc.c  */
#line 719 "csound_orc.y"
    { (yyval) = make_leaf(csound, LINE,LOCN, T_IDENT_GS, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 184:

/* Line 1464 of yacc.c  */
#line 720 "csound_orc.y"
    { (yyval) = make_leaf(csound, LINE,LOCN, T_IDENT_GS, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 185:

/* Line 1464 of yacc.c  */
#line 721 "csound_orc.y"
    { (yyval) = make_leaf(csound, LINE,LOCN, T_IDENT_GA, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 186:

/* Line 1464 of yacc.c  */
#line 724 "csound_orc.y"
    { (yyval) = make_leaf(csound, LINE,LOCN,
                                           INTEGER_TOKEN, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 187:

/* Line 1464 of yacc.c  */
#line 726 "csound_orc.y"
    { (yyval) = make_leaf(csound, LINE,LOCN,
                                           NUMBER_TOKEN, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 188:

/* Line 1464 of yacc.c  */
#line 728 "csound_orc.y"
    { (yyval) = make_leaf(csound, LINE,LOCN,
                                           STRING_TOKEN, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 189:

/* Line 1464 of yacc.c  */
#line 730 "csound_orc.y"
    { (yyval) = make_leaf(csound, LINE,LOCN,
                                           SRATE_TOKEN, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 190:

/* Line 1464 of yacc.c  */
#line 732 "csound_orc.y"
    { (yyval) = make_leaf(csound, LINE,LOCN,
                                           KRATE_TOKEN, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 191:

/* Line 1464 of yacc.c  */
#line 734 "csound_orc.y"
    { (yyval) = make_leaf(csound, LINE,LOCN,
                                           KSMPS_TOKEN, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 192:

/* Line 1464 of yacc.c  */
#line 736 "csound_orc.y"
    { (yyval) = make_leaf(csound, LINE,LOCN,
                                           NCHNLS_TOKEN, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 193:

/* Line 1464 of yacc.c  */
#line 738 "csound_orc.y"
    { (yyval) = make_leaf(csound, LINE,LOCN,
                                           NCHNLSI_TOKEN, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 194:

/* Line 1464 of yacc.c  */
#line 740 "csound_orc.y"
    { (yyval) = make_leaf(csound, LINE,LOCN,
                                            ZERODBFS_TOKEN, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;

  case 195:

/* Line 1464 of yacc.c  */
#line 745 "csound_orc.y"
    {
                if (UNLIKELY(PARSER_DEBUG))
                  csound->Message(csound, "opcode0 $1=%p (%s)\n",
                                  (yyvsp[(1) - (1)]),((ORCTOKEN *)(yyvsp[(1) - (1)]))->lexeme );
                (yyval) = make_leaf(csound,LINE,LOCN, T_OPCODE0, (ORCTOKEN *)(yyvsp[(1) - (1)]));
            ;}
    break;

  case 196:

/* Line 1464 of yacc.c  */
#line 753 "csound_orc.y"
    { (yyval) = make_leaf(csound,LINE,LOCN, T_OPCODE, (ORCTOKEN *)(yyvsp[(1) - (1)])); ;}
    break;



/* Line 1464 of yacc.c  */
#line 3721 "csound_orc.tab.c"
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
#line 756 "csound_orc.y"


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


