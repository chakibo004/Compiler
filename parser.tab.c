
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
    char type_Calcul[200];
    char valeur[200];
    char result[1000];
    
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

    float evaluate(char *expression){
        int len = strlen(expression);

        float operandStack[len];
        char operatorStack[len];
        int operandTop = -1;
        int operatorTop = -1;

        for (int i = 0; i < len; i++) {
            if (expression[i] == '-' && (i == 0 || !isNumeric(expression[i - 1]))) {
                float operand = -atof(&expression[++i]); 
                operandStack[++operandTop] = operand;
            } else if (isNumeric(expression[i])) {
                float operand = atof(&expression[i]);
                while (i < len && (isNumeric(expression[i]) || expression[i] == '.')) {
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
                    operandStack[++operandTop] = performOperation(operand1, operand2, currentOperator);
                }

                operatorStack[++operatorTop] = expression[i];
            } else if (expression[i] == '(') {
                operatorStack[++operatorTop] = expression[i];
            } else if (expression[i] == ')') {
                while (operatorTop >= 0 && operatorStack[operatorTop] != '(') {
                    float operand2 = operandStack[operandTop--];
                    float operand1 = operandStack[operandTop--];
                    char currentOperator = operatorStack[operatorTop--];
                    operandStack[++operandTop] = performOperation(operand1, operand2, currentOperator);
                }
                
                operatorTop--;
            }
        }

        while (operatorTop >= 0) {
            float operand2 = operandStack[operandTop--];
            float operand1 = operandStack[operandTop--];
            char currentOperator = operatorStack[operatorTop--];
            operandStack[++operandTop] = performOperation(operand1, operand2, currentOperator);
        }
        return operandStack[operandTop];
    }


    int evaluateCondition(float operand1, char* condition, float operand2 ){
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

    char* getCalculType(float nombre) {
        if (nombre == (int)nombre) {
            return "int";
        } else {
            return "float";
        }
    }
    


/* Line 189 of yacc.c  */
#line 226 "parser.tab.c"

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

/* Line 214 of yacc.c  */
#line 153 "parser.y"

    int entier;
    char* string;
    float reel;



/* Line 214 of yacc.c  */
#line 308 "parser.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 320 "parser.tab.c"

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
#define YYFINAL  12
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   135

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  39
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  25
/* YYNRULES -- Number of rules.  */
#define YYNRULES  65
/* YYNRULES -- Number of states.  */
#define YYNSTATES  117

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   293

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
      35,    36,    37,    38
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     8,    10,    12,    14,    16,    18,    20,
      22,    24,    26,    28,    30,    32,    34,    36,    38,    40,
      42,    44,    46,    48,    50,    52,    54,    56,    58,    60,
      64,    68,    72,    75,    78,    82,    86,    88,    92,    94,
      97,    99,   102,   104,   106,   108,   111,   115,   119,   123,
     127,   129,   133,   135,   139,   141,   143,   145,   149,   153,
     157,   169,   181,   189,   193,   195
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      40,     0,    -1,    48,    10,    52,    11,    -1,    20,    -1,
      21,    -1,    22,    -1,    23,    -1,    24,    -1,    25,    -1,
      26,    -1,    27,    -1,    28,    -1,    29,    -1,     6,    -1,
       7,    -1,     5,    -1,     8,    -1,     9,    -1,    14,    -1,
      15,    -1,    16,    -1,    17,    -1,    18,    -1,    14,    -1,
      15,    -1,    16,    -1,    17,    -1,    18,    -1,    13,    -1,
      13,     3,    44,    -1,    13,     3,    44,    -1,    49,     4,
      48,    -1,    49,     4,    -1,    43,    50,    -1,    12,    43,
      51,    -1,    46,    19,    50,    -1,    46,    -1,    47,    19,
      51,    -1,    47,    -1,    53,    52,    -1,    53,    -1,    54,
       4,    -1,    60,    -1,    61,    -1,    38,    -1,    59,     4,
      -1,    13,    30,    56,    -1,    34,    56,    35,    -1,    56,
      41,    56,    -1,    13,    41,    56,    -1,    13,    -1,    45,
      41,    56,    -1,    45,    -1,    34,    58,    35,    -1,    55,
      -1,    13,    -1,    45,    -1,    57,    42,    57,    -1,    13,
      20,    20,    -1,    13,    21,    21,    -1,    33,    34,    54,
       4,    62,     4,    63,    35,    36,    52,    37,    -1,    31,
      34,    62,    35,    36,    52,    37,    32,    36,    52,    37,
      -1,    31,    34,    62,    35,    36,    52,    37,    -1,    56,
      42,    56,    -1,    54,    -1,    59,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   178,   178,   183,   184,   185,   186,   188,   189,   190,
     191,   192,   193,   195,   195,   195,   195,   195,   196,   196,
     196,   196,   196,   197,   197,   197,   197,   197,   199,   207,
     222,   237,   238,   240,   241,   243,   244,   246,   247,   249,
     250,   252,   253,   254,   255,   256,   258,   298,   307,   317,
     379,   395,   454,   464,   465,   467,   492,   508,   516,   535,
     554,   556,   557,   560,   578,   579
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "AFF", "PVG", "INT", "FLOAT", "BOOL",
  "CHAR", "STRING", "BEG", "END", "CONST", "Idf", "const_int",
  "const_float", "const_bool", "const_char", "const_string", "VIRGULE",
  "PLUS", "SUB", "MUL", "DIV", "SUP", "SUPEGAL", "INF", "INFEGAL", "DIFF",
  "EGAL", "DPAFF", "IF", "ELSE", "FOR", "PARG", "PARD", "CrochetG",
  "CrochetD", "Commentaire", "$accept", "program", "OPP", "OppCond",
  "type", "DEC_VALUES", "INSTR_VALUES", "DEC_IDF", "CONST_IDF",
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
     285,   286,   287,   288,   289,   290,   291,   292,   293
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    39,    40,    41,    41,    41,    41,    42,    42,    42,
      42,    42,    42,    43,    43,    43,    43,    43,    44,    44,
      44,    44,    44,    45,    45,    45,    45,    45,    46,    46,
      47,    48,    48,    49,    49,    50,    50,    51,    51,    52,
      52,    53,    53,    53,    53,    53,    54,    55,    56,    56,
      56,    56,    56,    56,    56,    57,    57,    58,    59,    59,
      60,    61,    61,    62,    63,    63
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     4,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       3,     3,     2,     2,     3,     3,     1,     3,     1,     2,
       1,     2,     1,     1,     1,     2,     3,     3,     3,     3,
       1,     3,     1,     3,     1,     1,     1,     3,     3,     3,
      11,    11,     7,     3,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    15,    13,    14,    16,    17,     0,     0,     0,     0,
       0,     0,     1,    28,    36,    33,     0,    32,     0,    38,
      34,     0,     0,     0,     0,     0,    44,     0,    40,     0,
       0,    42,    43,    31,     0,     0,    18,    19,    20,    21,
      22,    29,    35,     0,     0,     0,     0,     0,     2,    39,
      41,    45,    30,    37,    58,    59,    50,    23,    24,    25,
      26,    27,     0,    52,    54,    46,     0,     0,     0,     0,
       3,     4,     5,     6,     0,    55,    56,     0,     0,     0,
       0,     0,     7,     8,     9,    10,    11,    12,     0,     0,
       0,    49,    47,     0,    53,    51,    48,    63,     0,     0,
      55,    56,    57,     0,     0,    62,    64,    65,     0,     0,
       0,     0,     0,     0,     0,    61,    60
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     7,    81,    88,     8,    41,    63,    14,    19,     9,
      10,    15,    20,    27,    28,    29,    64,    66,    78,    79,
      30,    31,    32,    67,   108
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -60
static const yytype_int8 yypact[] =
{
      80,   -60,   -60,   -60,   -60,   -60,   100,    17,     5,    11,
      19,    12,   -60,    25,    14,   -60,    -9,    80,    27,    16,
     -60,    96,     5,    34,     2,    23,   -60,    48,    -9,    56,
      58,   -60,   -60,   -60,    96,    12,   -60,   -60,   -60,   -60,
     -60,   -60,   -60,    43,    60,    -8,    -8,    77,   -60,   -60,
     -60,   -60,   -60,   -60,   -60,   -60,    46,   -60,   -60,   -60,
     -60,   -60,    -2,    46,   -60,    46,    51,    47,    61,   111,
     -60,   -60,   -60,   -60,    -8,    21,    26,    30,    69,    81,
      -8,    -8,   -60,   -60,   -60,   -60,   -60,   -60,    -8,    82,
      -8,    46,   -60,    86,   -60,    46,    46,    46,    -9,   113,
     -60,   -60,   -60,    83,   106,    89,   -60,   -60,    87,    88,
      90,    -9,    -9,    91,    92,   -60,   -60
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -60,   -60,   -36,    45,   119,    93,   -59,   -60,   -60,   114,
     -60,   108,    97,   -28,   -60,   -46,   -60,   -43,    40,   -60,
      31,   -60,   -60,    44,   -60
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -53
static const yytype_int8 yytable[] =
{
      49,    69,    65,    76,    23,    56,    57,    58,    59,    60,
      61,    75,    57,    58,    59,    60,    61,    12,    13,    77,
      74,    16,    24,    17,    25,    18,    62,    80,    21,    26,
      34,    91,    62,    22,   101,    35,    46,    95,    96,    74,
      80,    70,    71,    72,    73,    97,    70,    71,    72,    73,
      70,    71,    72,    73,    43,    44,   -50,    47,   106,    48,
      50,   -52,    51,    54,    45,    92,    70,    71,    72,    73,
     103,    70,    71,    72,    73,    82,    83,    84,    85,    86,
      87,    55,    89,   113,   114,     1,     2,     3,     4,     5,
      68,    45,     6,    82,    83,    84,    85,    86,    87,   100,
      57,    58,    59,    60,    61,     1,     2,     3,     4,     5,
      36,    37,    38,    39,    40,    90,    94,   104,    98,    23,
     105,   109,   110,    93,   111,    11,   112,    52,   115,   116,
      42,    33,    53,   102,    99,   107
};

static const yytype_uint8 yycheck[] =
{
      28,    47,    45,    62,    13,    13,    14,    15,    16,    17,
      18,    13,    14,    15,    16,    17,    18,     0,    13,    62,
      56,    10,    31,     4,    33,    13,    34,    63,     3,    38,
       3,    74,    34,    19,    93,    19,    34,    80,    81,    75,
      76,    20,    21,    22,    23,    88,    20,    21,    22,    23,
      20,    21,    22,    23,    20,    21,    35,    34,   104,    11,
       4,    35,     4,    20,    30,    35,    20,    21,    22,    23,
      98,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    21,    35,   111,   112,     5,     6,     7,     8,     9,
      13,    30,    12,    24,    25,    26,    27,    28,    29,    13,
      14,    15,    16,    17,    18,     5,     6,     7,     8,     9,
      14,    15,    16,    17,    18,     4,    35,     4,    36,    13,
      37,    32,    35,    78,    36,     6,    36,    34,    37,    37,
      22,    17,    35,    93,    90,   104
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     5,     6,     7,     8,     9,    12,    40,    43,    48,
      49,    43,     0,    13,    46,    50,    10,     4,    13,    47,
      51,     3,    19,    13,    31,    33,    38,    52,    53,    54,
      59,    60,    61,    48,     3,    19,    14,    15,    16,    17,
      18,    44,    50,    20,    21,    30,    34,    34,    11,    52,
       4,     4,    44,    51,    20,    21,    13,    14,    15,    16,
      17,    18,    34,    45,    55,    56,    56,    62,    13,    54,
      20,    21,    22,    23,    41,    13,    45,    56,    57,    58,
      41,    41,    24,    25,    26,    27,    28,    29,    42,    35,
       4,    56,    35,    42,    35,    56,    56,    56,    36,    62,
      13,    45,    57,    52,     4,    37,    54,    59,    63,    32,
      35,    36,    36,    52,    52,    37,    37
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
#line 195 "parser.y"
    {strcpy(Var_type,(yyvsp[(1) - (1)].string));;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 195 "parser.y"
    {strcpy(Var_type,(yyvsp[(1) - (1)].string));;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 196 "parser.y"
    {strcpy(type_VALUE,"int");strcpy(num_VALUE,(yyvsp[(1) - (1)].string));;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 196 "parser.y"
    {strcpy(type_VALUE,"float");strcpy(num_VALUE,(yyvsp[(1) - (1)].string));;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 196 "parser.y"
    {strcpy(type_VALUE,"bool");strcpy(num_VALUE,(yyvsp[(1) - (1)].string));;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 196 "parser.y"
    {strcpy(type_VALUE,"char");strcpy(num_VALUE,(yyvsp[(1) - (1)].string));;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 196 "parser.y"
    {strcpy(type_VALUE,"string"); strcpy(num_VALUE,(yyvsp[(1) - (1)].string));;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 197 "parser.y"
    {push("int");push((yyvsp[(1) - (1)].string));;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 197 "parser.y"
    {push("float");push((yyvsp[(1) - (1)].string));;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 197 "parser.y"
    {push("bool");push((yyvsp[(1) - (1)].string));;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 197 "parser.y"
    {push("char");push((yyvsp[(1) - (1)].string));;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 197 "parser.y"
    {push("string"); push((yyvsp[(1) - (1)].string));;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 199 "parser.y"
    {
    if (rechercher((yyvsp[(1) - (1)].string))!=-1 && strcmp(typeIDF((yyvsp[(1) - (1)].string)),"/")!=0){
        printf("\nERREUR SEMANTIQUE ::: LA VARIABLE %s EST DEJA DECLAREE ligne ::: %d, col ::: %d\n",(yyvsp[(1) - (1)].string),nblignes,col);
        exit(EXIT_FAILURE);
    }else{
        UpdateTypeConst((yyvsp[(1) - (1)].string),Var_type,"non");
    }
;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 207 "parser.y"
    {
    if (rechercher((yyvsp[(1) - (3)].string))!=-1 && strcmp(typeIDF((yyvsp[(1) - (3)].string)),"/")!=0){
        printf("\nERREUR SEMANTIQUE ::: LA VARIABLE %s EST DEJA DECLAREE ::: ligne ::: %d, col ::: %d\n",(yyvsp[(1) - (3)].string),nblignes,col);
        exit(EXIT_FAILURE);
    }else{
        UpdateTypeConst((yyvsp[(1) - (3)].string),Var_type,"non");        
        if ((strcmp(Var_type, type_VALUE) == 0) || ((strcmp(Var_type, "float") == 0) && (strcmp(type_VALUE, "int") == 0))){
            insertVALUE(num_VALUE);
        }else{
            printf("\nERREUR SEMANTIQUE ::: Type incompatible pour la variable: %s, TYPE affectee : %s, TYPE attendue : %s, ::: ligne %d, col ::: %d\n",(yyvsp[(1) - (3)].string),type_VALUE,Var_type,nblignes,col);
            exit(EXIT_FAILURE);
        }
    }
;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 222 "parser.y"
    {
        if (rechercher((yyvsp[(1) - (3)].string))!=-1 && strcmp(typeIDF((yyvsp[(1) - (3)].string)),"/")!=0){
        printf("\nERREUR SEMANTIQUE LA VARIABLE %s EST DEJA DECLAREE ::: ligne %d, col ::: %d\n",(yyvsp[(1) - (3)].string),nblignes,col);
        exit(EXIT_FAILURE);
    } else{
        UpdateTypeConst((yyvsp[(1) - (3)].string),Var_type,"oui");
        if ((strcmp(Var_type, type_VALUE) == 0) || ((strcmp(Var_type, "float") == 0) && (strcmp(type_VALUE, "int") == 0))){
            insertVALUE(num_VALUE);
        }else{
            printf("\nERREUR SEMANTIQUE ::: Type incompatible pour la variable: %s, TYPE affectee : %s, TYPE attendue : %s, ::: ligne %d, col ::: %d\n",(yyvsp[(1) - (3)].string),type_VALUE,Var_type,nblignes,col);
            exit(EXIT_FAILURE);
        }
    }
;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 258 "parser.y"
    {
    if (rechercher((yyvsp[(1) - (3)].string))!=-1 && strcmp(typeIDF((yyvsp[(1) - (3)].string)),"/")==0){
        printf("\nERREUR SEMANTIQUE LA VARIABLE %s N'EST PAS DECLAREE ::: ligne %d, col ::: %d",(yyvsp[(1) - (3)].string),nblignes,col);
        exit(EXIT_FAILURE);
    }else if(isconst((yyvsp[(1) - (3)].string))){
        printf("\nERREUR SEMANTIQUE ::: MODIFICATION DE CONSTANTE %s INTERDITE ::: ligne %d, col ::: %d",(yyvsp[(1) - (3)].string),nblignes,col);
        exit(EXIT_FAILURE);
    }else{
        if(strcmp(type_Calcul,"bool")==0 || strcmp(type_Calcul,"char")==0 || strcmp(type_Calcul,"string")==0){
            if(strcmp(typeIDF((yyvsp[(1) - (3)].string)),type_Calcul)!=0){
                printf("\nERREUR SEMANTIQUE ::: INCOMPATIBILTE DE TYPE -> VARIABLE: %s, TYPE affectee : %s, TYPE attendue : %s, ::: ligne %d, col ::: %d\n",(yyvsp[(1) - (3)].string),type_Calcul,typeIDF((yyvsp[(1) - (3)].string)),nblignes,col);
                pop(); // Libérer la pile
                exit(EXIT_FAILURE);
            }else{
                char* AFF = mirrorString(pop());
                printf("\n Expression : %s := %s\n",(yyvsp[(1) - (3)].string),AFF);

                updateIDFValue((yyvsp[(1) - (3)].string),AFF);
            }
        }else{
            strcpy(result,pop());
            char* ret = mirrorString(result);
            float value = evaluate(ret);
            char* type_value = getCalculType(value);

            printf("\n Expression : %s := %s => %s = %g\n",(yyvsp[(1) - (3)].string),ret,(yyvsp[(1) - (3)].string),value);

            if(strcmp(typeIDF((yyvsp[(1) - (3)].string)),type_value)==0){
                sprintf(ret,"%g",value);
                updateIDFValue((yyvsp[(1) - (3)].string),ret);
            }else{
                printf("\nERREUR SEMANTIQUE ::: INCOMPATIBILTE DE TYPE -> VARIABLE: %s, TYPE affectee : %s, TYPE attendue : %s, ::: ligne %d, col ::: %d\n",(yyvsp[(1) - (3)].string),type_value,typeIDF((yyvsp[(1) - (3)].string)),nblignes,col);
                exit(EXIT_FAILURE);
            }


        }
    }
;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 298 "parser.y"
    {
    char* value = pop();
    char* result = (char*)malloc((strlen("(") + strlen(value) + strlen(")") + 1) * sizeof(char));
    strcpy(result, ")");
    strcat(result, value);
    strcat(result, "(");
    push(result);
;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 307 "parser.y"
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

  case 49:

/* Line 1455 of yacc.c  */
#line 317 "parser.y"
    {
    char* right = pop();
    char* OPR = pop();
    strcpy(valeur,getValue((yyvsp[(1) - (3)].string)));

        if (rechercher((yyvsp[(1) - (3)].string)) != -1 && strcmp(typeIDF((yyvsp[(1) - (3)].string)), "/") == 0) {
            printf("\nERREUR SEMANTIQUE LA VARIABLE %s N'EST PAS DECLAREE ::: ligne %d, col ::: %d", (yyvsp[(1) - (3)].string), nblignes,col);
            exit(EXIT_FAILURE);
        }else if (strcmp(getValue((yyvsp[(1) - (3)].string)), "/") == 0) {
            printf("\nERREUR SEMANTIQUE LA VARIABLE %s N'A PAS DE VALEUR ASSIGNEE ::: ligne %d, col ::: %d", (yyvsp[(1) - (3)].string), nblignes,col);
            exit(EXIT_FAILURE);
        }else if (strcmp(typeIDF((yyvsp[(1) - (3)].string)),"bool") == 0 || strcmp(type_Calcul,"bool") == 0){
            printf("\nERREUR SEMANTIQUE ::: OPERATION IMPOSSIBLE SUR DES OPERANDES BOOLEEN ::: ligne %d, col ::: %d\n", nblignes,col);
            exit(EXIT_FAILURE);
        }else if(strcmp(typeIDF((yyvsp[(1) - (3)].string)),"char") == 0 || strcmp(type_Calcul,"char") == 0){
            printf("\nERREUR SEMANTIQUE ::: OPERATION IMPOSSIBLE SUR DES CARACTERES ::: ligne %d, col ::: %d\n", nblignes,col);
            exit(EXIT_FAILURE);
        }else if (strcmp(type_Calcul, "string") == 0 && strcmp(typeIDF((yyvsp[(1) - (3)].string)), "string") == 0){

            if(strcmp(OPR,"+")!=0){
                printf("\nERREUR SEMANTIQUE ::: OPERATION IMPOSSIBLE SUR DES CHAINES DE CARACTERES ::: ligne %d, col ::: %d\n", nblignes,col);
                exit(EXIT_FAILURE);
            }else{
                //Faire La concaténation

                if (right[0] == '\"' && right[strlen(right) - 1] == '\"' && valeur[0] == '\"' && valeur[strlen(valeur) - 1] == '\"') {
                        
                    char NewStr1[100],NewStr2[100];
                    strncpy(NewStr1, right + 1, strlen(right) - 2);
                    strncpy(NewStr2, valeur + 1, strlen(valeur) - 2);

                    NewStr1[strlen(right) - 2] = '\0';
                    NewStr2[strlen(valeur) - 2] = '\0';

                    char* result = (char*)malloc(( strlen(NewStr1) + strlen(NewStr2) + 1) * sizeof(char));
                    char* ret = mirrorString(NewStr2);
                    
                    strcpy(result,"\"");
                    strcat(result,NewStr1);
                    strcat(result,ret);
                    strcat(result,"\"");

                    push(result);
                }
            }
        }else if((strcmp(typeIDF((yyvsp[(1) - (3)].string)),"string") != 0 && strcmp(type_Calcul,"string")== 0) || (strcmp(typeIDF((yyvsp[(1) - (3)].string)),"string") == 0 && strcmp(type_Calcul,"string")!= 0)){
                printf("\nERREUR SEMANTIQUE ::: OPERATION IMPOSSIBLE SUR DES CHAINES DE CARACTERES ::: ligne %d, col ::: %d\n", nblignes,col);
                exit(EXIT_FAILURE);
        }else{


            char* ret = mirrorString(valeur);
            char* result = (char*)malloc((strlen(right) + strlen(valeur) + strlen(OPR) + 1) * sizeof(char));

            strcpy(result,right);
            strcat(result,OPR);

            strcat(result,ret);

            push(result);
        }
;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 379 "parser.y"
    {
    if (rechercher((yyvsp[(1) - (1)].string)) != -1 && strcmp(typeIDF((yyvsp[(1) - (1)].string)), "/") == 0) {
        printf("\nERREUR SEMANTIQUE LA VARIABLE %s N'EST PAS DECLAREE ::: ligne %d, col ::: %d", (yyvsp[(1) - (1)].string), nblignes,col);
        exit(EXIT_FAILURE);
    }else if (strcmp(getValue((yyvsp[(1) - (1)].string)), "/") == 0) {
        printf("\nERREUR SEMANTIQUE LA VARIABLE %s N'A PAS DE VALEUR ASSIGNEE ::: ligne %d, col ::: %d", (yyvsp[(1) - (1)].string), nblignes,col);
        exit(EXIT_FAILURE);
    }else{

        strcpy(type_Calcul,typeIDF((yyvsp[(1) - (1)].string)));

        strcpy(result,getValue((yyvsp[(1) - (1)].string)));
        char* ret = mirrorString(result);
        push(ret);
    }
;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 395 "parser.y"
    {

    char* right = pop();
    char* OPR = pop();
    char* valeur = pop();
    char* type = pop();


    if (strcmp(type,"bool") == 0 || strcmp(type_Calcul,"bool") == 0){
        printf("\nERREUR SEMANTIQUE ::: OPERATION IMPOSSIBLE SUR DES OPERANDES BOOLEEN ::: ligne %d, col ::: %d\n", nblignes,col);
        exit(EXIT_FAILURE);
    }else if(strcmp(type,"char") == 0 || strcmp(type_Calcul,"char") == 0){
        printf("\nERREUR SEMANTIQUE ::: OPERATION IMPOSSIBLE SUR DES CARACTERES ::: ligne %d, col ::: %d\n", nblignes,col);
        exit(EXIT_FAILURE);
    }else if (strcmp(type_Calcul, "string") == 0 && strcmp(type, "string") == 0){

        if(strcmp(OPR,"+")!=0){
            printf("\nERREUR SEMANTIQUE ::: OPERATION IMPOSSIBLE SUR DES CHAINES DE CARACTERES ::: ligne %d, col ::: %d\n", nblignes,col);
            exit(EXIT_FAILURE);
        }else{
        //Faire La concaténation

            if (right[0] == '\"' && right[strlen(right) - 1] == '\"' && valeur[0] == '\"' && valeur[strlen(valeur) - 1] == '\"') {
                    
                char NewStr1[100],NewStr2[100];
                strncpy(NewStr1, right + 1, strlen(right) - 2);
                strncpy(NewStr2, valeur + 1, strlen(valeur) - 2);

                NewStr1[strlen(right) - 2] = '\0';
                NewStr2[strlen(valeur) - 2] = '\0';

                char* result = (char*)malloc(( strlen(NewStr1) + strlen(NewStr2) + 1) * sizeof(char));
                char* ret = mirrorString(NewStr2);
                
                strcpy(result,"\"");
                strcat(result,NewStr1);
                strcat(result,ret);
                strcat(result,"\"");

                push(result);
            }
        }
    }else if((strcmp(type,"string") != 0 && strcmp(type_Calcul,"string")== 0) || (strcmp(type,"string") == 0 && strcmp(type_Calcul,"string")!= 0)){
            printf("\nERREUR SEMANTIQUE ::: OPERATION IMPOSSIBLE SUR DES CHAINES DE CARACTERES ::: ligne %d, col ::: %d\n", nblignes,col);
            exit(EXIT_FAILURE);
    }else{
        char* result = (char*)malloc((strlen(right) + strlen(valeur) + strlen(OPR) + 1) * sizeof(char));

        char* ret = mirrorString(valeur);

        strcpy(result,right);
        strcat(result,OPR);
        strcat(result,ret);


        push(result);

    }
;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 454 "parser.y"
    {
    strcpy(result,pop());

    char* type = pop();
    strcpy(type_Calcul,type);

    char* ret = mirrorString(result);

    push(ret);
;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 467 "parser.y"
    {
    if (rechercher((yyvsp[(1) - (1)].string)) != -1 && strcmp(typeIDF((yyvsp[(1) - (1)].string)), "/") == 0) {
        printf("\nERREUR SEMANTIQUE LA VARIABLE %s N'EST PAS DECLAREE ::: ligne %d, col ::: %d", (yyvsp[(1) - (1)].string), nblignes,col);
        exit(EXIT_FAILURE);
    }else if (strcmp(getValue((yyvsp[(1) - (1)].string)), "/") == 0) {
        printf("\nERREUR SEMANTIQUE LA VARIABLE %s N'A PAS DE VALEUR ASSIGNEE ::: ligne %d, col ::: %d", (yyvsp[(1) - (1)].string), nblignes,col);
        exit(EXIT_FAILURE);
    }else{
        if (strcmp(typeIDF((yyvsp[(1) - (1)].string)),"bool") == 0){
            printf("\nERREUR SEMANTIQUE ::: OPERATION IMPOSSIBLE SUR DES OPERANDES BOOLEEN ::: ligne %d, col ::: %d\n", nblignes,col);
            exit(EXIT_FAILURE);
        }else if(strcmp(typeIDF((yyvsp[(1) - (1)].string)),"char") == 0){
            printf("\nERREUR SEMANTIQUE ::: OPERATION IMPOSSIBLE SUR DES CARACTERES ::: ligne %d, col ::: %d\n", nblignes,col);
            exit(EXIT_FAILURE);
        }else if(strcmp(typeIDF((yyvsp[(1) - (1)].string)),"string") == 0){
            printf("\nERREUR SEMANTIQUE ::: OPERATION IMPOSSIBLE SUR DES CHAINES DE CARACTERES ::: ligne %d, col ::: %d\n", nblignes,col);
            exit(EXIT_FAILURE);
        }


        strcpy(result,getValue((yyvsp[(1) - (1)].string)));
        char* ret = mirrorString(result);
        push(ret);
    }
;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 492 "parser.y"
    {
    strcpy(result,pop());
    char* type = pop();
    if (strcmp(type, "bool") == 0) {
        printf("\nERREUR SEMANTIQUE ::: OPERATION IMPOSSIBLE SUR DES OPERANDES BOOLEEN ::: ligne %d, col ::: %d\n", nblignes,col);
        exit(EXIT_FAILURE);
    }
    else{
        strcpy(type_Calcul,type);

        char* ret = mirrorString(result);

        push(ret);
    }
;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 508 "parser.y"
    {
    int valeur = evaluateCondition(atof(pop()),pop(),atof(pop()));
    char* result = (char*)malloc(sizeof(char));

    sprintf(result,"%d",valeur);
    push(result);
;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 516 "parser.y"
    {
    if (rechercher((yyvsp[(1) - (3)].string)) != -1 && strcmp(typeIDF((yyvsp[(1) - (3)].string)), "/") == 0) {
        printf("\nERREUR SEMANTIQUE LA VARIABLE %s N'EST PAS DECLAREE ::: ligne %d, col ::: %d", (yyvsp[(1) - (3)].string), nblignes,col);
        exit(EXIT_FAILURE);
    }else if (strcmp(getValue((yyvsp[(1) - (3)].string)), "/") == 0) {
        printf("\nERREUR SEMANTIQUE LA VARIABLE %s N'A PAS DE VALEUR ASSIGNEE ::: ligne %d, col ::: %d", (yyvsp[(1) - (3)].string), nblignes,col);
        exit(EXIT_FAILURE);
    }else{
        char* valeur = getValue((yyvsp[(1) - (3)].string));

        strcpy(result,valeur);
        strcat(result,"+");
        strcat(result,"1");
        printf("\n Expression : %s := %s\n",(yyvsp[(1) - (3)].string),result);

        sprintf(result,"%g",evaluate(result));
        updateIDFValue((yyvsp[(1) - (3)].string),result);
    }
;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 535 "parser.y"
    {
    if (rechercher((yyvsp[(1) - (3)].string)) != -1 && strcmp(typeIDF((yyvsp[(1) - (3)].string)), "/") == 0) {
        printf("\nERREUR SEMANTIQUE LA VARIABLE %s N'EST PAS DECLAREE ::: ligne %d, col ::: %d", (yyvsp[(1) - (3)].string), nblignes,col);
        exit(EXIT_FAILURE);
    }else if (strcmp(getValue((yyvsp[(1) - (3)].string)), "/") == 0) {
        printf("\nERREUR SEMANTIQUE LA VARIABLE %s N'A PAS DE VALEUR ASSIGNEE ::: ligne %d, col ::: %d", (yyvsp[(1) - (3)].string), nblignes,col);
        exit(EXIT_FAILURE);
    }else{
        char* valeur = getValue((yyvsp[(1) - (3)].string));

        strcpy(result,valeur);
        strcat(result,"-");
        strcat(result,"1");
        printf("\n Expression : %s := %s\n",(yyvsp[(1) - (3)].string),result);
        sprintf(result,"%.2f",evaluate(result));
        updateIDFValue((yyvsp[(1) - (3)].string),result);
    }
;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 560 "parser.y"
    {

    char* OPR1 = pop();
    OPR1 = mirrorString(OPR1);
    float value1 = evaluate(OPR1);

    char* OPR = pop();

    char* OPR2 = pop();
    OPR2 = mirrorString(OPR2);
    float value2 = evaluate(OPR2);

    char* result = (char*)malloc(sizeof(char));

    sprintf(result,"%d",evaluateCondition(value1,OPR,value2));
    
;}
    break;



/* Line 1455 of yacc.c  */
#line 2241 "parser.tab.c"
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
#line 580 "parser.y"
  

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
    printf("\n\nSYNTAX ERROR at line ::: %d, col ::: %d",nblignes,col);
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
