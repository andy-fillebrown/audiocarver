/* A Bison parser, made by GNU Bison 2.4.2.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
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




