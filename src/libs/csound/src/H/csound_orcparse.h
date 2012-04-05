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




