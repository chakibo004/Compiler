
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
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
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "parser.y"

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <ctype.h>

    #define MAX_NUM_LENGTH 50

    char Var_type[200];
    int nblignes=1;
    int col=1;
    char type_VALUE[200];
    char num_VALUE[200];
    char sauvOpr[200];
    char VARAFF[200];
    char type_Calcul[200];
    char type_Expression[200];
    char valeur[200];
    char result[1000];
    char cond[1];

    char* mirrorString(const char* str) {
        int length = strlen(str);
        char* mirroredStr = (char*)malloc((length + 1) * sizeof(char));
        
        if (mirroredStr == NULL) {
            fprintf(stderr, "Memory allocation error\n");
            exit(EXIT_FAILURE);
        }

        for (int i = 0; i < length; ++i) {
            mirroredStr[i] = str[length - 1 - i];
        }

        mirroredStr[length] = '\0'; 
        return mirroredStr;
    }

    int isNumeric(char ch) { return (isdigit(ch) || ch == '.'); }

    int isOperator(char ch) {
        return (ch == '+' || ch == '-' || ch == '*' || ch == '/');
    }

    float performOperation(float operand1, float operand2, char operator) {
        switch (operator) {
            case '+':
                return operand1 + operand2;
            case '-':
                return operand1 - operand2;
            case '*':
                return operand1 * operand2;
            case '/':
                if (operand2 != 0) {
                return operand1 / operand2;
                } else {
                printf("Error: Division by zero\n");
                exit(EXIT_FAILURE);
                }
            default:
                printf("Error: Invalid operator\n");
                exit(EXIT_FAILURE);
        }
    }

    float evaluate(char *expression) {
        int len = strlen(expression);

        float operandStack[len];
        char operatorStack[len];
        int operandTop = -1;
        int operatorTop = -1;

        for (int i = 0; i < len; i++) {
            if (isNumeric(expression[i])) {

            float operand = atof(&expression[i]);
            while (i < len && isNumeric(expression[i])) {
                i++;
            }
            i--; 
            operandStack[++operandTop] = operand;
            } else if (isOperator(expression[i])) {
            
            while (operatorTop >= 0 &&
                    (operatorStack[operatorTop] == '+' ||
                    operatorStack[operatorTop] == '-' ||
                    operatorStack[operatorTop] == '*' ||
                    operatorStack[operatorTop] == '/') &&
                    (expression[i] == '+' || expression[i] == '-')) {
                
                float operand2 = operandStack[operandTop--];
                float operand1 = operandStack[operandTop--];
                char currentOperator = operatorStack[operatorTop--];
                operandStack[++operandTop] =
                    performOperation(operand1, operand2, currentOperator);
            }

            operatorStack[++operatorTop] = expression[i];
            } else if (expression[i] == '(') {
            operatorStack[++operatorTop] = expression[i];
            } else if (expression[i] == ')') {
            while (operatorTop >= 0 && operatorStack[operatorTop] != '(') {
                float operand2 = operandStack[operandTop--];
                float operand1 = operandStack[operandTop--];
                char currentOperator = operatorStack[operatorTop--];
                operandStack[++operandTop] =
                    performOperation(operand1, operand2, currentOperator);
            }
            
            operatorTop--;
            }
        }

        while (operatorTop >= 0) {
            float operand2 = operandStack[operandTop--];
            float operand1 = operandStack[operandTop--];
            char currentOperator = operatorStack[operatorTop--];
            operandStack[++operandTop] =
                performOperation(operand1, operand2, currentOperator);
        }

        return operandStack[operandTop];
    }


    int evaluateCondition(float operand1, char* condition, float operand2 ) {
        int result;
        if (strcmp(condition,"==")==0) {
            result = operand1 == operand2;
        } else if (strcmp(condition,">")==0) {
            result = operand1 > operand2;
        } else if (strcmp(condition,"<")==0) {
            result = operand1 < operand2;
        } else if (strcmp(condition,">=")==0) {
            result = operand1 >= operand2;
        } else if (strcmp(condition,"<=")==0) {
            result = operand1 <= operand2;
        } else if (strcmp(condition,"<>")==0) {
            result = operand1 != operand2;
        } else {
            // Condition non reconnue
            printf("Condition non prise en charge\n");
            result = -1; // Valeur d'erreur
        }
        return result;
    }
    


/* Line 189 of yacc.c  */
#line 224 "parser.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
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
     SUP = 275,
     SUPEGAL = 276,
     INF = 277,
     INFEGAL = 278,
     DIFF = 279,
     EGAL = 280,
     DPAFF = 281,
     IF = 282,
     ELSE = 283,
     FOR = 284,
     PARG = 285,
     PARD = 286,
     CrochetG = 287,
     CrochetD = 288,
     Commentaire = 289
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 151 "parser.y"

    int entier;
    char* string;
    float reel;



/* Line 214 of yacc.c  */
#line 302 "parser.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 314 "parser.tab.c"

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
# if YYENABLE_NLS
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
#define YYFINAL  10
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   125

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  35
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  25
/* YYNRULES -- Number of rules.  */
#define YYNRULES  59
/* YYNRULES -- Number of states.  */
#define YYNSTATES  111

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   289

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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     8,    10,    12,    14,    16,    18,    20,
      22,    24,    26,    28,    30,    32,    34,    36,    38,    40,
      42,    44,    46,    48,    52,    56,    60,    63,    66,    70,
      74,    76,    80,    82,    85,    87,    90,    92,    94,    96,
      99,   103,   107,   111,   115,   117,   121,   123,   127,   129,
     131,   133,   137,   141,   145,   157,   169,   177,   181,   183
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      36,     0,    -1,    44,     8,    48,     9,    -1,    16,    -1,
      17,    -1,    18,    -1,    19,    -1,    20,    -1,    21,    -1,
      22,    -1,    23,    -1,    24,    -1,    25,    -1,     6,    -1,
       7,    -1,     5,    -1,    12,    -1,    13,    -1,    14,    -1,
      12,    -1,    13,    -1,    14,    -1,    11,    -1,    11,     3,
      40,    -1,    11,     3,    40,    -1,    45,     4,    44,    -1,
      45,     4,    -1,    39,    46,    -1,    10,    39,    47,    -1,
      42,    15,    46,    -1,    42,    -1,    43,    15,    47,    -1,
      43,    -1,    49,    48,    -1,    49,    -1,    50,     4,    -1,
      56,    -1,    57,    -1,    34,    -1,    55,     4,    -1,    11,
      26,    52,    -1,    30,    52,    31,    -1,    52,    37,    52,
      -1,    11,    37,    52,    -1,    11,    -1,    41,    37,    52,
      -1,    41,    -1,    30,    54,    31,    -1,    51,    -1,    11,
      -1,    41,    -1,    53,    38,    53,    -1,    11,    16,    16,
      -1,    11,    17,    17,    -1,    29,    30,    50,     4,    58,
       4,    59,    31,    32,    48,    33,    -1,    27,    30,    58,
      31,    32,    48,    33,    28,    32,    48,    33,    -1,    27,
      30,    58,    31,    32,    48,    33,    -1,    52,    38,    52,
      -1,    50,    -1,    55,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   178,   178,   183,   184,   185,   186,   188,   189,   190,
     191,   192,   193,   195,   195,   195,   196,   196,   196,   197,
     197,   197,   199,   207,   222,   237,   238,   240,   241,   243,
     244,   246,   247,   249,   250,   252,   253,   254,   255,   256,
     258,   282,   291,   301,   334,   351,   377,   386,   387,   389,
     406,   422,   430,   449,   468,   470,   471,   473,   478,   479
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "AFF", "PVG", "INT", "FLOAT", "BOOL",
  "BEG", "END", "CONST", "Idf", "const_int", "const_float", "const_bool",
  "VIRGULE", "PLUS", "SUB", "MUL", "DIV", "SUP", "SUPEGAL", "INF",
  "INFEGAL", "DIFF", "EGAL", "DPAFF", "IF", "ELSE", "FOR", "PARG", "PARD",
  "CrochetG", "CrochetD", "Commentaire", "$accept", "program", "OPP",
  "OppCond", "type", "DEC_VALUES", "INSTR_VALUES", "DEC_IDF", "CONST_IDF",
  "Liste_declarations", "Declaration", "DEC_VAR", "DEC_CONST",
  "Liste_instructions", "Instruction", "AFFECTATION",
  "ExpressionParenthese", "Expression", "COMPAREOPERANDS", "COMPARE_EXPR",
  "AUTOOPERATION", "BOUCLE", "CONDITION", "COMPARAISON", "Compteur", 0
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
     285,   286,   287,   288,   289
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    35,    36,    37,    37,    37,    37,    38,    38,    38,
      38,    38,    38,    39,    39,    39,    40,    40,    40,    41,
      41,    41,    42,    42,    43,    44,    44,    45,    45,    46,
      46,    47,    47,    48,    48,    49,    49,    49,    49,    49,
      50,    51,    52,    52,    52,    52,    52,    52,    52,    53,
      53,    54,    55,    55,    56,    57,    57,    58,    59,    59
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     4,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     3,     3,     2,     2,     3,     3,
       1,     3,     1,     2,     1,     2,     1,     1,     1,     2,
       3,     3,     3,     3,     1,     3,     1,     3,     1,     1,
       1,     3,     3,     3,    11,    11,     7,     3,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    15,    13,    14,     0,     0,     0,     0,     0,     0,
       1,    22,    30,    27,     0,    26,     0,    32,    28,     0,
       0,     0,     0,     0,    38,     0,    34,     0,     0,    36,
      37,    25,     0,     0,    16,    17,    18,    23,    29,     0,
       0,     0,     0,     0,     2,    33,    35,    39,    24,    31,
      52,    53,    44,    19,    20,    21,     0,    46,    48,    40,
       0,     0,     0,     0,     3,     4,     5,     6,     0,    49,
      50,     0,     0,     0,     0,     0,     7,     8,     9,    10,
      11,    12,     0,     0,     0,    43,    41,     0,    47,    45,
      42,    57,     0,     0,    49,    50,    51,     0,     0,    56,
      58,    59,     0,     0,     0,     0,     0,     0,     0,    55,
      54
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     5,    75,    82,     6,    37,    57,    12,    17,     7,
       8,    13,    18,    25,    26,    27,    58,    60,    72,    73,
      28,    29,    30,    61,   102
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -54
static const yytype_int8 yypact[] =
{
      48,   -54,   -54,   -54,    55,    13,     7,    15,    17,    19,
     -54,    23,    18,   -54,    -7,    48,    38,    27,   -54,    83,
       7,    -1,    34,    35,   -54,    68,    -7,    53,    74,   -54,
     -54,   -54,    83,    19,   -54,   -54,   -54,   -54,   -54,    82,
      84,    -6,    -6,    88,   -54,   -54,   -54,   -54,   -54,   -54,
     -54,   -54,    71,   -54,   -54,   -54,    -2,    71,   -54,    71,
      51,    69,    76,    99,   -54,   -54,   -54,   -54,    -6,    21,
      28,    32,    61,    73,    -6,    -6,   -54,   -54,   -54,   -54,
     -54,   -54,    -6,    75,    -6,    71,   -54,    80,   -54,    71,
      71,    71,    -7,   101,   -54,   -54,   -54,    77,    95,    81,
     -54,   -54,    85,    79,    86,    -7,    -7,    87,    89,   -54,
     -54
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -54,   -54,   -38,    36,   108,    91,   -53,   -54,   -54,    98,
     -54,    94,    92,   -26,   -54,   -42,   -54,   -39,    30,   -54,
      26,   -54,   -54,    31,   -54
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -47
static const yytype_int8 yytable[] =
{
      45,    63,    59,    70,    21,    52,    53,    54,    55,    69,
      53,    54,    55,    10,    68,    39,    40,    71,    11,    74,
      22,    15,    23,    14,    56,    41,    19,    24,    56,    85,
      16,    68,    74,    20,    95,    89,    90,    64,    65,    66,
      67,    32,    33,    91,    64,    65,    66,    67,    64,    65,
      66,    67,   -44,     1,     2,     3,   100,    46,     4,   -46,
       1,     2,     3,    86,    42,    43,    97,    64,    65,    66,
      67,    76,    77,    78,    79,    80,    81,    44,    47,   107,
     108,    76,    77,    78,    79,    80,    81,    64,    65,    66,
      67,    94,    53,    54,    55,    34,    35,    36,    50,    62,
      83,    51,    41,    84,    88,    98,    21,    92,    87,   103,
      99,   105,     9,    31,    38,    93,   104,    96,   106,     0,
     109,     0,   110,    48,   101,    49
};

static const yytype_int8 yycheck[] =
{
      26,    43,    41,    56,    11,    11,    12,    13,    14,    11,
      12,    13,    14,     0,    52,    16,    17,    56,    11,    57,
      27,     4,    29,     8,    30,    26,     3,    34,    30,    68,
      11,    69,    70,    15,    87,    74,    75,    16,    17,    18,
      19,     3,    15,    82,    16,    17,    18,    19,    16,    17,
      18,    19,    31,     5,     6,     7,    98,     4,    10,    31,
       5,     6,     7,    31,    30,    30,    92,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,     9,     4,   105,
     106,    20,    21,    22,    23,    24,    25,    16,    17,    18,
      19,    11,    12,    13,    14,    12,    13,    14,    16,    11,
      31,    17,    26,     4,    31,     4,    11,    32,    72,    28,
      33,    32,     4,    15,    20,    84,    31,    87,    32,    -1,
      33,    -1,    33,    32,    98,    33
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     5,     6,     7,    10,    36,    39,    44,    45,    39,
       0,    11,    42,    46,     8,     4,    11,    43,    47,     3,
      15,    11,    27,    29,    34,    48,    49,    50,    55,    56,
      57,    44,     3,    15,    12,    13,    14,    40,    46,    16,
      17,    26,    30,    30,     9,    48,     4,     4,    40,    47,
      16,    17,    11,    12,    13,    14,    30,    41,    51,    52,
      52,    58,    11,    50,    16,    17,    18,    19,    37,    11,
      41,    52,    53,    54,    37,    37,    20,    21,    22,    23,
      24,    25,    38,    31,     4,    52,    31,    38,    31,    52,
      52,    52,    32,    58,    11,    41,    53,    48,     4,    33,
      50,    55,    59,    28,    31,    32,    32,    48,    48,    33,
      33
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
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

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
      yyerror (YY_("syntax error: cannot back up")); \
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
# if YYLTYPE_IS_TRIVIAL
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
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
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
		  Type, Value); \
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
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
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
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
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
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

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
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



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
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


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

/* Line 1455 of yacc.c  */
#line 178 "parser.y"
    {
    printf("\nAnalyse syntaxique valide\n");
    YYACCEPT;
;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 183 "parser.y"
    {push("+");;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 184 "parser.y"
    {push("-");;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 185 "parser.y"
    {push("*");;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 186 "parser.y"
    {push("/");;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 188 "parser.y"
    {push(">");;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 189 "parser.y"
    {push(">=");;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 190 "parser.y"
    {push("<");;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 191 "parser.y"
    {push("<=");;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 192 "parser.y"
    {push("<>");;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 193 "parser.y"
    {push("==");;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 195 "parser.y"
    {strcpy(Var_type,(yyvsp[(1) - (1)].string));;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 195 "parser.y"
    {strcpy(Var_type,(yyvsp[(1) - (1)].string));;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 195 "parser.y"
    {strcpy(Var_type,(yyvsp[(1) - (1)].string));;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 196 "parser.y"
    {strcpy(type_VALUE,"int");strcpy(num_VALUE,(yyvsp[(1) - (1)].string));;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 196 "parser.y"
    {strcpy(type_VALUE,"float");strcpy(num_VALUE,(yyvsp[(1) - (1)].string));;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 196 "parser.y"
    {strcpy(type_VALUE,"bool");strcpy(num_VALUE,(yyvsp[(1) - (1)].string));;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 197 "parser.y"
    {strcpy(type_VALUE,"int");push((yyvsp[(1) - (1)].string));;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 197 "parser.y"
    {strcpy(type_VALUE,"float");push((yyvsp[(1) - (1)].string));;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 197 "parser.y"
    {strcpy(type_VALUE,"bool");push((yyvsp[(1) - (1)].string));;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 199 "parser.y"
    {
    if (rechercher((yyvsp[(1) - (1)].string))!=-1 && strcmp(typeIDF((yyvsp[(1) - (1)].string)),"/")!=0){
        printf("\nERREUR SEMANTIQUE ::: LA VARIABLE %s EST DEJA DECLAREE ligne ::: %d, col ::: %d",(yyvsp[(1) - (1)].string),nblignes,col);
        exit(EXIT_FAILURE);
    }else{
        UpdateTypeConst((yyvsp[(1) - (1)].string),Var_type,"non");
    }
;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 207 "parser.y"
    {
    if (rechercher((yyvsp[(1) - (3)].string))!=-1 && strcmp(typeIDF((yyvsp[(1) - (3)].string)),"/")!=0){
        printf("\nERREUR SEMANTIQUE ::: LA VARIABLE %s EST DEJA DECLAREE ::: ligne ::: %d, col ::: %d",(yyvsp[(1) - (3)].string),nblignes,col);
        exit(EXIT_FAILURE);
    }else{
        UpdateTypeConst((yyvsp[(1) - (3)].string),Var_type,"non");        
        if ((strcmp(Var_type, type_VALUE) == 0) || ((strcmp(Var_type, "float") == 0) && (strcmp(type_VALUE, "int") == 0))){
            insertVALUE(num_VALUE);
        }else{
            printf("\nERREUR SEMANTIQUE ::: Type incompatible pour la variable: %s, TYPE affectee : %s, TYPE attendue : %s, ::: ligne %d\n",(yyvsp[(1) - (3)].string),type_VALUE,Var_type,nblignes);
            exit(EXIT_FAILURE);
        }
    }
;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 222 "parser.y"
    {
        if (rechercher((yyvsp[(1) - (3)].string))!=-1 && strcmp(typeIDF((yyvsp[(1) - (3)].string)),"/")!=0){
        printf("\nERREUR SEMANTIQUE LA VARIABLE %s EST DEJA DECLAREE ::: ligne %d",(yyvsp[(1) - (3)].string),nblignes);
        exit(EXIT_FAILURE);
    } else{
        UpdateTypeConst((yyvsp[(1) - (3)].string),Var_type,"oui");
        if ((strcmp(Var_type, type_VALUE) == 0) || ((strcmp(Var_type, "float") == 0) && (strcmp(type_VALUE, "int") == 0))){
            insertVALUE(num_VALUE);
        }else{
            printf("\nERREUR SEMANTIQUE ::: Type incompatible pour la variable: %s, TYPE affectee : %s, TYPE attendue : %s, ::: ligne %d\n",(yyvsp[(1) - (3)].string),type_VALUE,Var_type,nblignes);
            exit(EXIT_FAILURE);
        }
    }
;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 258 "parser.y"
    {
    if (rechercher((yyvsp[(1) - (3)].string))!=-1 && strcmp(typeIDF((yyvsp[(1) - (3)].string)),"/")==0){
        printf("\nERREUR SEMANTIQUE LA VARIABLE %s N'EST PAS DECLAREE ::: ligne %d",(yyvsp[(1) - (3)].string),nblignes);
        exit(EXIT_FAILURE);
    }else if(isconst((yyvsp[(1) - (3)].string))){
        printf("\nERREUR SEMANTIQUE ::: MODIFICATION DE CONSTANTE %s INTERDITE ::: ligne %d",(yyvsp[(1) - (3)].string),nblignes);
        exit(EXIT_FAILURE);
    }else{
        if(strcmp(type_Calcul,"bool")==0){
            updateIDFValue((yyvsp[(1) - (3)].string),mirrorString(pop()));
        }
        else if(strcmp(type_Calcul,typeIDF((yyvsp[(1) - (3)].string)))==0 || strcmp(typeIDF((yyvsp[(1) - (3)].string)),"float")==0){
            strcpy(result,pop());
            char* ret = mirrorString(result);
            printf("\n Expression : %s",ret);
            sprintf(ret,"%g",evaluate(ret));
            updateIDFValue((yyvsp[(1) - (3)].string),ret);
        }else{
            printf("\nERREUR SEMANTIQUE ::: INCOMPATIBILTE DE TYPE -> VARIABLE: %s, TYPE affectee : %s, TYPE attendue : %s, ::: ligne %d\n",(yyvsp[(1) - (3)].string),type_Calcul,typeIDF((yyvsp[(1) - (3)].string)),nblignes);
            exit(EXIT_FAILURE);
        }
    }
;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 282 "parser.y"
    {
    char* value = pop();
    char* result = (char*)malloc((strlen("(") + strlen(value) + strlen(")") + 1) * sizeof(char));
    strcpy(result, ")");
    strcat(result, value);
    strcat(result, "(");
    push(result);
;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 291 "parser.y"
    {
    char *right = pop();
    char *OPR = pop();
    char *left = pop();

    char* expression = right; 
    strcat(expression, OPR);
    strcat(expression, left);
    push(expression);
;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 301 "parser.y"
    {

    if (rechercher((yyvsp[(1) - (3)].string)) != -1 && strcmp(typeIDF((yyvsp[(1) - (3)].string)), "/") == 0) {
        printf("\nERREUR SEMANTIQUE LA VARIABLE %s N'EST PAS DECLAREE ::: ligne %d", (yyvsp[(1) - (3)].string), nblignes);
        exit(EXIT_FAILURE);
    }else if (strcmp(getValue((yyvsp[(1) - (3)].string)), "/") == 0) {
        printf("\nERREUR SEMANTIQUE LA VARIABLE %s N'A PAS DE VALEUR ASSIGNEE ::: ligne %d", (yyvsp[(1) - (3)].string), nblignes);
        exit(EXIT_FAILURE);
    }else{

        if (strcmp(typeIDF((yyvsp[(1) - (3)].string)),"bool") == 0 || strcmp(type_Calcul,"bool") == 0) {
            printf("\nERREUR SEMANTIQUE ::: OPERATION IMPOSSIBLE SUR DES OPERANDES BOOLEEN ::: ligne %d\n", nblignes);
            exit(EXIT_FAILURE);
        }
        char* right = pop();
        strcpy(sauvOpr, pop());
        strcpy(valeur,getValue((yyvsp[(1) - (3)].string)));
        char* ret = mirrorString(valeur);

        strcpy(result,right);
        strcat(result,sauvOpr);

        strcat(result,ret);

        if(strcmp(typeIDF((yyvsp[(1) - (3)].string)),type_Expression)==0){
            strcpy(type_Calcul,type_Expression);
        }else{
            strcpy(type_Calcul,"float");
        }

        push(result);
    }
;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 334 "parser.y"
    {
    if (rechercher((yyvsp[(1) - (1)].string)) != -1 && strcmp(typeIDF((yyvsp[(1) - (1)].string)), "/") == 0) {
        printf("\nERREUR SEMANTIQUE LA VARIABLE %s N'EST PAS DECLAREE ::: ligne %d", (yyvsp[(1) - (1)].string), nblignes);
        exit(EXIT_FAILURE);
    }else if (strcmp(getValue((yyvsp[(1) - (1)].string)), "/") == 0) {
        printf("\nERREUR SEMANTIQUE LA VARIABLE %s N'A PAS DE VALEUR ASSIGNEE ::: ligne %d", (yyvsp[(1) - (1)].string), nblignes);
        exit(EXIT_FAILURE);
    }else{

        strcpy(type_Calcul,typeIDF((yyvsp[(1) - (1)].string)));
        strcpy(type_Expression,typeIDF((yyvsp[(1) - (1)].string)));

        strcpy(result,getValue((yyvsp[(1) - (1)].string)));
        char* ret = mirrorString(result);
        push(ret);
    }
;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 351 "parser.y"
    {

    char* right = pop();
    char* OPR = pop();

    if (strcmp(type_VALUE,"bool") == 0 || strcmp(type_Calcul,"bool") == 0) {
        printf("\nERREUR SEMANTIQUE ::: OPERATION IMPOSSIBLE SUR DES OPERANDES BOOLEEN ::: ligne %d\n", nblignes);
        exit(EXIT_FAILURE);
    }

    if(strcmp(type_VALUE,type_Expression)==0){
        strcpy(type_Calcul,type_Expression);
    }else{
        strcpy(type_Calcul,"float");
    }


    char* valeur = pop();
    char* ret = mirrorString(valeur);

    strcpy(result,right);
    strcat(result,OPR);
    strcat(result,ret);
    push(result);

;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 377 "parser.y"
    {
    strcpy(type_Calcul,type_VALUE);
    strcpy(type_Expression,type_VALUE);

    strcpy(result,pop());
    char* ret = mirrorString(result);

    push(ret);
;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 389 "parser.y"
    {
    if (rechercher((yyvsp[(1) - (1)].string)) != -1 && strcmp(typeIDF((yyvsp[(1) - (1)].string)), "/") == 0) {
        printf("\nERREUR SEMANTIQUE LA VARIABLE %s N'EST PAS DECLAREE ::: ligne %d", (yyvsp[(1) - (1)].string), nblignes);
        exit(EXIT_FAILURE);
    }else if (strcmp(getValue((yyvsp[(1) - (1)].string)), "/") == 0) {
        printf("\nERREUR SEMANTIQUE LA VARIABLE %s N'A PAS DE VALEUR ASSIGNEE ::: ligne %d", (yyvsp[(1) - (1)].string), nblignes);
        exit(EXIT_FAILURE);
    }else{
        if (strcmp(typeIDF((yyvsp[(1) - (1)].string)), "bool") == 0) {
            printf("\nERREUR SEMANTIQUE ::: OPERATION IMPOSSIBLE SUR DES OPERANDES BOOLEEN ::: ligne %d\n", nblignes);
            exit(EXIT_FAILURE);
        }
        strcpy(result,getValue((yyvsp[(1) - (1)].string)));
        char* ret = mirrorString(result);
        push(ret);
    }
;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 406 "parser.y"
    {
    if (strcmp(type_VALUE, "bool") == 0) {
        printf("\nERREUR SEMANTIQUE ::: OPERATION IMPOSSIBLE SUR DES OPERANDES BOOLEEN ::: ligne %d\n", nblignes);
        exit(EXIT_FAILURE);
    }
    else{
        strcpy(type_Calcul,type_VALUE);
        strcpy(type_Expression,type_VALUE);

        strcpy(result,pop());
        char* ret = mirrorString(result);

        push(ret);
    }
;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 422 "parser.y"
    {
    int valeur = evaluateCondition(atof(pop()),pop(),atof(pop()));
    char* result = (char*)malloc(sizeof(char));

    sprintf(result,"%d",valeur);
    push(result);
;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 430 "parser.y"
    {
    if (rechercher((yyvsp[(1) - (3)].string)) != -1 && strcmp(typeIDF((yyvsp[(1) - (3)].string)), "/") == 0) {
        printf("\nERREUR SEMANTIQUE LA VARIABLE %s N'EST PAS DECLAREE ::: ligne %d", (yyvsp[(1) - (3)].string), nblignes);
        exit(EXIT_FAILURE);
    }else if (strcmp(getValue((yyvsp[(1) - (3)].string)), "/") == 0) {
        printf("\nERREUR SEMANTIQUE LA VARIABLE %s N'A PAS DE VALEUR ASSIGNEE ::: ligne %d", (yyvsp[(1) - (3)].string), nblignes);
        exit(EXIT_FAILURE);
    }else{
        char* valeur = getValue((yyvsp[(1) - (3)].string));

        strcpy(result,valeur);
        strcat(result,"+");
        strcat(result,"1");
        printf("\n%s\n",result);

        sprintf(result,"%g",evaluate(result));
        updateIDFValue((yyvsp[(1) - (3)].string),result);
    }
;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 449 "parser.y"
    {
    if (rechercher((yyvsp[(1) - (3)].string)) != -1 && strcmp(typeIDF((yyvsp[(1) - (3)].string)), "/") == 0) {
        printf("\nERREUR SEMANTIQUE LA VARIABLE %s N'EST PAS DECLAREE ::: ligne %d", (yyvsp[(1) - (3)].string), nblignes);
        exit(EXIT_FAILURE);
    }else if (strcmp(getValue((yyvsp[(1) - (3)].string)), "/") == 0) {
        printf("\nERREUR SEMANTIQUE LA VARIABLE %s N'A PAS DE VALEUR ASSIGNEE ::: ligne %d", (yyvsp[(1) - (3)].string), nblignes);
        exit(EXIT_FAILURE);
    }else{
        char* valeur = getValue((yyvsp[(1) - (3)].string));

        strcpy(result,valeur);
        strcat(result,"-");
        strcat(result,"1");
        printf("\n%s\n",result);
        sprintf(result,"%.2f",evaluate(result));
        updateIDFValue((yyvsp[(1) - (3)].string),result);
    }
;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 473 "parser.y"
    {
    printf("\nligne ::: %d",nblignes);
    printStack();
;}
    break;



/* Line 1455 of yacc.c  */
#line 2085 "parser.tab.c"
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
      yyerror (YY_("syntax error"));
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
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
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
		      yytoken, &yylval);
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
		  yystos[yystate], yyvsp);
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
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
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



/* Line 1675 of yacc.c  */
#line 480 "parser.y"
  

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    FILE *file = freopen(argv[1], "r", stdin);
    if (file == NULL) {
        perror("Error");
        return 1;
    }

    yyparse();

    fclose(file);

    afficher();
    return 0;
}

void yyerror() {
    printf("\n\nSYNTAX ERROR at line ::: %d",nblignes);
    exit(EXIT_FAILURE);
}

void LXerror(char *error, char *msg,int line, int col){
    if (error != NULL && msg != NULL) {
        printf("\n\nLEXICAL ERROR: %s IN %s at line ::: %d col ::: %d\n", error, msg, line, col);
        exit(EXIT_FAILURE);
    }
}

void SNerror(char *error, char *msg,int line, int col) {
    if (error != NULL && msg != NULL) {
        printf("\n\nSYNTAX ERROR: %s IN %s at line ::: %d col ::: %d\n", error, msg, line, col);
    }
    exit(EXIT_FAILURE);
}


