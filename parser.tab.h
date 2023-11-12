
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
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
     AFF = 258,
     PVG = 259,
     INT = 260,
     FLOAT = 261,
     BOOL = 262,
     BEG = 263,
     END = 264,
     CONST = 265,
     Idf = 266,
     const_int = 267,
     const_float = 268,
     const_bool = 269,
     VIRGULE = 270,
     PLUS = 271,
     SUB = 272,
     MUL = 273,
     DIV = 274,
     INCREM = 275,
     DECREM = 276,
     SUP = 277,
     SUPEGAL = 278,
     INF = 279,
     INFEGAL = 280,
     DIFF = 281,
     EGAL = 282,
     DPAFF = 283,
     IF = 284,
     ELSE = 285,
     FOR = 286,
     PARG = 287,
     PARD = 288,
     CrochetG = 289,
     CrochetD = 290,
     Commentaire = 291
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1676 of yacc.c  */
#line 10 "parser.y"

    int entier;
    char* string;
    float reel;



/* Line 1676 of yacc.c  */
#line 96 "parser.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


