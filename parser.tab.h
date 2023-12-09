
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
     CHAR = 263,
     STRING = 264,
     BEG = 265,
     END = 266,
     CONST = 267,
     Idf = 268,
     const_int = 269,
     const_float = 270,
     const_bool = 271,
     const_char = 272,
     const_string = 273,
     VIRGULE = 274,
     PLUS = 275,
     SUB = 276,
     MUL = 277,
     DIV = 278,
     SUP = 279,
     SUPEGAL = 280,
     INF = 281,
     INFEGAL = 282,
     DIFF = 283,
     EGAL = 284,
     DPAFF = 285,
     IF = 286,
     ELSE = 287,
     FOR = 288,
     PARG = 289,
     PARD = 290,
     CrochetG = 291,
     CrochetD = 292,
     Commentaire = 293
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1676 of yacc.c  */
#line 153 "parser.y"

    int entier;
    char* string;
    float reel;



/* Line 1676 of yacc.c  */
#line 98 "parser.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


