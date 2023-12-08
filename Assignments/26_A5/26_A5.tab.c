/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     CHAR = 258,
     ELSE = 259,
     FOR = 260,
     IF = 261,
     INT = 262,
     RETURN = 263,
     VOID = 264,
     ARROW = 265,
     LESSTHANEQ = 266,
     GREATERTHANEQ = 267,
     EQ = 268,
     NEQ = 269,
     LOGICALAND = 270,
     LOGICALOR = 271,
     IDENTIFIER = 272,
     STRING_LITERAL = 273,
     CHARACTER_CONSTANT = 274,
     INTEGER_CONSTANT = 275
   };
#endif
/* Tokens.  */
#define CHAR 258
#define ELSE 259
#define FOR 260
#define IF 261
#define INT 262
#define RETURN 263
#define VOID 264
#define ARROW 265
#define LESSTHANEQ 266
#define GREATERTHANEQ 267
#define EQ 268
#define NEQ 269
#define LOGICALAND 270
#define LOGICALOR 271
#define IDENTIFIER 272
#define STRING_LITERAL 273
#define CHARACTER_CONSTANT 274
#define INTEGER_CONSTANT 275




/* Copy the first part of user declarations.  */
#line 1 "26_A5.y"

    #include <stdio.h>
    #include <stdlib.h>
    #include "26_A5_translator.h"

    extern int yylex();

    void yyerror(char *s);
    extern char *yytext;
    


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

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 13 "26_A5.y"
{
    int intval;
    char *charval;
    symbol *symp;
    data_type *dtype;

    Expression *expr;
    Statement *stm;
    char unary_op;

    int num;
}
/* Line 193 of yacc.c.  */
#line 161 "26_A5.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 174 "26_A5.tab.c"

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
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
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
  yytype_int16 yyss;
  YYSTYPE yyvs;
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
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  15
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   182

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  41
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  43
/* YYNRULES -- Number of rules.  */
#define YYNRULES  96
/* YYNRULES -- Number of states.  */
#define YYNSTATES  163

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   275

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    30,     2,     2,     2,    32,    26,     2,
      21,    22,    27,    28,    25,    29,     2,    31,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    36,    38,
      33,    37,    34,    35,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    23,     2,    24,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    39,     2,    40,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19,    20
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     4,     5,     6,     7,     9,    11,    13,
      15,    19,    21,    26,    31,    35,    37,    38,    40,    44,
      46,    49,    51,    53,    55,    57,    59,    61,    65,    69,
      73,    75,    79,    83,    85,    89,    93,    97,   101,   103,
     107,   111,   113,   118,   120,   125,   127,   137,   139,   143,
     145,   149,   151,   155,   157,   159,   161,   164,   166,   168,
     173,   179,   181,   182,   184,   186,   190,   194,   197,   200,
     202,   204,   206,   208,   210,   212,   214,   218,   220,   221,
     223,   227,   229,   231,   234,   236,   238,   239,   248,   260,
     274,   278,   281,   283,   286,   288,   290
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      81,     0,    -1,    -1,    -1,    -1,    -1,    17,    -1,    20,
      -1,    19,    -1,    18,    -1,    21,    60,    22,    -1,    46,
      -1,    47,    23,    60,    24,    -1,    47,    21,    48,    22,
      -1,    47,    10,    17,    -1,    49,    -1,    -1,    59,    -1,
      49,    25,    59,    -1,    47,    -1,    51,    50,    -1,    26,
      -1,    27,    -1,    28,    -1,    29,    -1,    30,    -1,    50,
      -1,    52,    27,    50,    -1,    52,    31,    50,    -1,    52,
      32,    50,    -1,    52,    -1,    53,    28,    52,    -1,    53,
      29,    52,    -1,    53,    -1,    54,    33,    53,    -1,    54,
      34,    53,    -1,    54,    11,    53,    -1,    54,    12,    53,
      -1,    54,    -1,    55,    13,    54,    -1,    55,    14,    54,
      -1,    55,    -1,    56,    15,    45,    55,    -1,    56,    -1,
      57,    16,    45,    56,    -1,    57,    -1,    57,    44,    35,
      45,    60,    44,    36,    45,    58,    -1,    58,    -1,    50,
      37,    59,    -1,    59,    -1,    63,    62,    38,    -1,    64,
      -1,    64,    37,    70,    -1,     9,    -1,     3,    -1,     7,
      -1,    67,    65,    -1,    65,    -1,    17,    -1,    17,    23,
      20,    24,    -1,    17,    21,    42,    66,    22,    -1,    68,
      -1,    -1,    27,    -1,    69,    -1,    68,    25,    69,    -1,
      63,    67,    17,    -1,    63,    17,    -1,    63,    67,    -1,
      63,    -1,    59,    -1,    72,    -1,    76,    -1,    78,    -1,
      79,    -1,    80,    -1,    39,    73,    40,    -1,    74,    -1,
      -1,    75,    -1,    74,    45,    75,    -1,    61,    -1,    71,
      -1,    60,    38,    -1,    38,    -1,    60,    -1,    -1,     6,
      21,    60,    44,    22,    45,    71,    44,    -1,     6,    21,
      60,    44,    22,    45,    71,    44,     4,    45,    71,    -1,
       5,    21,    77,    38,    45,    77,    38,    45,    77,    44,
      22,    45,    71,    -1,     8,    60,    38,    -1,     8,    38,
      -1,    82,    -1,    81,    82,    -1,    61,    -1,    83,    -1,
      63,    64,    43,    72,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    96,    96,   101,   107,   116,   125,   130,   139,   148,
     157,   164,   168,   174,   195,   199,   202,   208,   212,   219,
     222,   267,   270,   273,   276,   279,   285,   301,   310,   319,
     331,   334,   343,   355,   358,   375,   392,   406,   426,   429,
     445,   466,   469,   483,   486,   499,   502,   522,   525,   540,
     548,   554,   569,   586,   589,   592,   598,   618,   624,   635,
     647,   663,   664,   668,   672,   674,   679,   684,   688,   691,
     697,   705,   708,   712,   715,   718,   724,   730,   733,   739,
     742,   749,   752,   758,   761,   767,   770,   777,   785,   797,
     822,   833,   847,   848,   852,   853,   857
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "CHAR", "ELSE", "FOR", "IF", "INT",
  "RETURN", "VOID", "ARROW", "LESSTHANEQ", "GREATERTHANEQ", "EQ", "NEQ",
  "LOGICALAND", "LOGICALOR", "IDENTIFIER", "STRING_LITERAL",
  "CHARACTER_CONSTANT", "INTEGER_CONSTANT", "'('", "')'", "'['", "']'",
  "','", "'&'", "'*'", "'+'", "'-'", "'!'", "'/'", "'%'", "'<'", "'>'",
  "'?'", "':'", "'='", "';'", "'{'", "'}'", "$accept", "create_table",
  "change_table", "M", "N", "primary_expression", "postfix_expression",
  "argument_expression_list_opt", "argument_expression_list",
  "unary_expression", "unary_operator", "multiplicative_expression",
  "additive_expression", "relational_expression", "equality_expression",
  "logical_and_expression", "logical_or_expression",
  "conditional_expression", "assignment_expression", "expression",
  "declaration", "init_declarator", "type_specifier", "declarator",
  "direct_declarator", "parameter_list_opt", "pointer", "parameter_list",
  "parameter_declaration", "initializer", "statement",
  "compound_statement", "block_item_list_opt", "block_item_list",
  "block_item", "expression_statement", "expression_opt",
  "selection_statement", "iteration_statement", "jump_statement",
  "translation_unit", "external_declaration", "function_definition", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,    40,    41,    91,    93,    44,    38,    42,    43,    45,
      33,    47,    37,    60,    62,    63,    58,    61,    59,   123,
     125
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    41,    42,    43,    44,    45,    46,    46,    46,    46,
      46,    47,    47,    47,    47,    48,    48,    49,    49,    50,
      50,    51,    51,    51,    51,    51,    52,    52,    52,    52,
      53,    53,    53,    54,    54,    54,    54,    54,    55,    55,
      55,    56,    56,    57,    57,    58,    58,    59,    59,    60,
      61,    62,    62,    63,    63,    63,    64,    64,    65,    65,
      65,    66,    66,    67,    68,    68,    69,    69,    69,    69,
      70,    71,    71,    71,    71,    71,    72,    73,    73,    74,
      74,    75,    75,    76,    76,    77,    77,    78,    78,    79,
      80,    80,    81,    81,    82,    82,    83
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     0,     0,     0,     1,     1,     1,     1,
       3,     1,     4,     4,     3,     1,     0,     1,     3,     1,
       2,     1,     1,     1,     1,     1,     1,     3,     3,     3,
       1,     3,     3,     1,     3,     3,     3,     3,     1,     3,
       3,     1,     4,     1,     4,     1,     9,     1,     3,     1,
       3,     1,     3,     1,     1,     1,     2,     1,     1,     4,
       5,     1,     0,     1,     1,     3,     3,     2,     2,     1,
       1,     1,     1,     1,     1,     1,     3,     1,     0,     1,
       3,     1,     1,     2,     1,     1,     0,     8,    11,    13,
       3,     2,     1,     2,     1,     1,     4
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    54,    55,    53,    94,     0,     0,    92,    95,    58,
      63,     0,     3,    57,     0,     1,    93,     2,     0,    50,
       0,     0,    56,    62,     0,     6,     9,     8,     7,     0,
      21,    22,    23,    24,    25,    11,    19,    26,     0,    30,
      33,    38,    41,    43,    45,    47,    70,    52,    78,    96,
      69,     0,    61,    64,    59,    49,     0,     0,    16,     0,
       0,    20,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     5,     5,     0,     0,     0,     0,    84,
       0,    81,     0,    82,    71,     0,     5,    79,    72,    73,
      74,    75,    67,    68,    60,     0,    10,    14,     0,    15,
      17,     0,    48,    27,    28,    29,    26,    31,    32,    36,
      37,    34,    35,    39,    40,     0,     0,     5,    86,     0,
      91,     0,    83,    51,    76,     0,    66,    65,    13,     0,
      12,    42,    44,     0,    85,     0,     4,    90,    80,    18,
       4,     5,     0,     0,    86,     5,     5,     0,     0,     0,
       5,     4,    46,    86,    87,     4,     5,     0,     0,     5,
      88,     0,    89
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    23,    21,    75,   115,    35,    36,    98,    99,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    55,    80,
       4,    11,     5,    12,    13,    51,    14,    52,    53,    47,
      83,    84,    85,    86,    87,    88,   135,    89,    90,    91,
       6,     7,     8
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -141
static const yytype_int16 yypact[] =
{
      43,  -141,  -141,  -141,  -141,    -8,    71,  -141,  -141,    24,
    -141,   -26,    22,  -141,    -2,  -141,  -141,  -141,    -3,  -141,
     142,   -14,  -141,    43,     5,  -141,  -141,  -141,  -141,   142,
    -141,  -141,  -141,  -141,  -141,  -141,    -7,    11,   142,    66,
      33,    -6,    56,    36,     8,  -141,  -141,  -141,   102,  -141,
      -4,    69,    63,  -141,  -141,  -141,    72,    59,   142,   142,
     142,  -141,   142,   142,   142,   142,   142,   142,   142,   142,
     142,   142,   142,  -141,  -141,    61,    85,    91,    37,  -141,
      76,  -141,    -8,  -141,  -141,    87,    95,  -141,  -141,  -141,
    -141,  -141,  -141,   120,  -141,    43,  -141,  -141,   116,   114,
    -141,   118,  -141,  -141,  -141,  -141,  -141,    66,    66,    33,
      33,    33,    33,    -6,    -6,   142,   142,  -141,   142,   142,
    -141,   105,  -141,   107,  -141,   102,  -141,  -141,  -141,   142,
    -141,    56,    36,   142,  -141,   112,  -141,  -141,  -141,  -141,
    -141,  -141,   129,   117,   142,  -141,  -141,   126,   128,   142,
    -141,  -141,  -141,   142,   148,  -141,  -141,   143,   128,  -141,
    -141,   128,  -141
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -141,  -141,  -141,   -68,   -64,  -141,  -141,  -141,  -141,   -31,
    -141,    51,    32,    54,    58,    60,  -141,    25,   -16,   -29,
     -46,  -141,   -22,    93,   163,  -141,   130,  -141,    83,  -141,
    -140,   158,  -141,  -141,    57,  -141,  -133,  -141,  -141,  -141,
    -141,   175,  -141
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -78
static const yytype_int16 yytable[] =
{
      56,    50,    81,    57,    46,    67,    68,    61,   151,     9,
     116,   147,    19,    92,    58,     9,    59,    24,   160,    10,
     155,   162,   125,    10,    74,    48,    82,    69,    70,    54,
     101,   103,   104,   105,   106,   106,   106,   106,   106,   106,
     106,   106,   100,    -4,   102,    17,     1,    18,    60,   121,
       2,    73,     3,   133,    25,    26,    27,    28,    29,    20,
     -51,    65,    66,    30,    31,    32,    33,    34,   142,    71,
      72,    15,   143,    50,     1,   120,    97,   144,     2,    81,
       3,   148,   149,   154,   106,   106,   153,   157,    95,   134,
     136,    94,   158,    62,    96,   161,   117,    63,    64,   109,
     110,   111,   112,    82,   140,     1,   118,    76,    77,     2,
      78,     3,   119,   139,   122,   134,   107,   108,   106,    25,
      26,    27,    28,    29,   134,   113,   114,   124,    30,    31,
      32,    33,    34,    76,    77,   -77,    78,   126,   128,   129,
      79,    48,   130,   137,    20,    25,    26,    27,    28,    29,
     141,   145,   156,   146,    30,    31,    32,    33,    34,    25,
      26,    27,    28,    29,   150,   159,    79,    48,    30,    31,
      32,    33,    34,   131,   152,   123,   132,    22,   127,    49,
      93,    16,   138
};

static const yytype_uint8 yycheck[] =
{
      29,    23,    48,    10,    20,    11,    12,    38,   148,    17,
      74,   144,    38,    17,    21,    17,    23,    20,   158,    27,
     153,   161,    86,    27,    16,    39,    48,    33,    34,    24,
      59,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    58,    35,    60,    21,     3,    23,    37,    78,
       7,    15,     9,   117,    17,    18,    19,    20,    21,    37,
      38,    28,    29,    26,    27,    28,    29,    30,   136,    13,
      14,     0,   140,    95,     3,    38,    17,   141,     7,   125,
       9,   145,   146,   151,   115,   116,   150,   155,    25,   118,
     119,    22,   156,    27,    22,   159,    35,    31,    32,    67,
      68,    69,    70,   125,   133,     3,    21,     5,     6,     7,
       8,     9,    21,   129,    38,   144,    65,    66,   149,    17,
      18,    19,    20,    21,   153,    71,    72,    40,    26,    27,
      28,    29,    30,     5,     6,    40,     8,    17,    22,    25,
      38,    39,    24,    38,    37,    17,    18,    19,    20,    21,
      38,    22,     4,    36,    26,    27,    28,    29,    30,    17,
      18,    19,    20,    21,    38,    22,    38,    39,    26,    27,
      28,    29,    30,   115,   149,    82,   116,    14,    95,    21,
      50,     6,   125
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     7,     9,    61,    63,    81,    82,    83,    17,
      27,    62,    64,    65,    67,     0,    82,    21,    23,    38,
      37,    43,    65,    42,    20,    17,    18,    19,    20,    21,
      26,    27,    28,    29,    30,    46,    47,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    70,    39,    72,
      63,    66,    68,    69,    24,    59,    60,    10,    21,    23,
      37,    50,    27,    31,    32,    28,    29,    11,    12,    33,
      34,    13,    14,    15,    16,    44,     5,     6,     8,    38,
      60,    61,    63,    71,    72,    73,    74,    75,    76,    78,
      79,    80,    17,    67,    22,    25,    22,    17,    48,    49,
      59,    60,    59,    50,    50,    50,    50,    52,    52,    53,
      53,    53,    53,    54,    54,    45,    45,    35,    21,    21,
      38,    60,    38,    64,    40,    45,    17,    69,    22,    25,
      24,    55,    56,    45,    60,    77,    60,    38,    75,    59,
      60,    38,    44,    44,    45,    22,    36,    77,    45,    45,
      38,    71,    58,    45,    44,    77,     4,    44,    45,    22,
      71,    45,    71
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
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
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
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
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



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

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
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

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
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

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

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
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

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
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
#line 96 "26_A5.y"
    {
                    current_table = create_symboltable();
                ;}
    break;

  case 3:
#line 101 "26_A5.y"
    {
                    current_table = table_pointer;
                    emit(FUNC, table_name, NULL, NULL);
                ;}
    break;

  case 4:
#line 107 "26_A5.y"
    {   
        (yyval.stm) = statCreate();
        (yyval.stm)->nextlist = newList(giveNextInstr());
        char *value = (char*)malloc(sizeof(char)*100);
        sprintf(value, "%d", giveNextInstr());
        emit(GOTO, "M", NULL, NULL);
    ;}
    break;

  case 5:
#line 116 "26_A5.y"
    {    
        (yyval.num) = giveNextInstr();
    ;}
    break;

  case 6:
#line 125 "26_A5.y"
    {   
                                (yyval.expr) = exprCreate();
                                (yyval.expr)->loc = (yyvsp[(1) - (1)].symp);
                                (yyval.expr)->isBoolean = false;
                            ;}
    break;

  case 7:
#line 130 "26_A5.y"
    {
                                (yyval.expr) = exprCreate();
                                (yyval.expr)->loc = gentemp();
                                char * value = (char*)malloc(sizeof(char)*100);
                                sprintf(value, "%d", (yyvsp[(1) - (1)].intval));
                                (yyval.expr)->loc = update_symboltable(current_table, (yyval.expr)->loc->name, TYPE_INT, value, size_of_int, TEMP, 0, NULL);
                                (yyval.expr)->isBoolean = false;
                                emit(ASSIGN, (yyval.expr)->loc->name, value, NULL);
                            ;}
    break;

  case 8:
#line 139 "26_A5.y"
    {
                                (yyval.expr) = exprCreate();
                                (yyval.expr)->loc = gentemp();
                                char *value = (char *)malloc(sizeof(char) * 10);
                                value = strdup((yyvsp[(1) - (1)].charval));
                                (yyval.expr)->loc = update_symboltable(current_table, (yyval.expr)->loc->name, TYPE_CHAR, value, size_of_char, TEMP, 0, NULL);
                                (yyval.expr)->isBoolean = false;
                                emit(ASSIGN, (yyval.expr)->loc->name, value, NULL);
                            ;}
    break;

  case 9:
#line 148 "26_A5.y"
    {
                                (yyval.expr) = exprCreate();
                                (yyval.expr)->loc = gentemp();
                                char *value = (char *)malloc(sizeof(char) * 10);
                                value = strdup((yyvsp[(1) - (1)].charval));
                                (yyval.expr)->loc = update_symboltable(current_table, (yyval.expr)->loc->name, TYPE_CHAR, value, size_of_char, TEMP, 0, NULL);
                                (yyval.expr)->isBoolean = false;
                                emit(ASSIGN, (yyval.expr)->loc->name, value, NULL);
                            ;}
    break;

  case 10:
#line 157 "26_A5.y"
    {
        
                                (yyval.expr) = (yyvsp[(2) - (3)].expr);
                            ;}
    break;

  case 11:
#line 164 "26_A5.y"
    {
                                                                    (yyval.expr) = (yyvsp[(1) - (1)].expr);
                                                                    (yyval.expr)->loc->arrayName = (yyvsp[(1) - (1)].expr)->loc->name;
                                                                ;}
    break;

  case 12:
#line 168 "26_A5.y"
    {
                                                                    (yyval.expr) = exprCreate();
                                                                    (yyval.expr)->loc = (yyvsp[(3) - (4)].expr)->loc;
                                                                    (yyval.expr)->loc->arrayName = (yyvsp[(1) - (4)].expr)->loc->name; 
                                                                    (yyval.expr)->isArray = true;
                                                                ;}
    break;

  case 13:
#line 174 "26_A5.y"
    {
                                                                    (yyval.expr) = exprCreate();
                                                                    
                                                                    if ((yyvsp[(1) - (4)].expr)->loc->nested_table == NULL){
                                                                        yyerror("Function not defined");
                                                                    }

                                                                    char* value = (char*)malloc(sizeof(char)*100);
                                                                    if ((yyvsp[(1) - (4)].expr)->loc->type == TYPE_VOID){
                                                                        sprintf(value, "%d", (yyvsp[(3) - (4)].num));
                                                                        emit(CALL, NULL, (yyvsp[(1) - (4)].expr)->loc->name, value);
                                                                        (yyval.expr)->loc = (yyvsp[(1) - (4)].expr)->loc;
                                                                    }
                                                                    else{
                                                                        (yyval.expr)->loc = gentemp();
                                                                        (yyval.expr)->loc = update_symboltable(current_table, (yyval.expr)->loc->name, (yyvsp[(1) - (4)].expr)->loc->type, NULL, (yyvsp[(1) - (4)].expr)->loc->size, TEMP, 0, NULL);
                                                                        (yyval.expr)->loc->arrayName = (yyvsp[(1) - (4)].expr)->loc->name;
                                                                        sprintf(value, "%d", (yyvsp[(3) - (4)].num));
                                                                        emit(CALL, (yyval.expr)->loc->name, (yyvsp[(1) - (4)].expr)->loc->name, value);
                                                                    }
                                                                ;}
    break;

  case 15:
#line 199 "26_A5.y"
    {
                                    (yyval.num) = (yyvsp[(1) - (1)].num);
                                ;}
    break;

  case 16:
#line 202 "26_A5.y"
    {
                                    (yyval.num) = 0;
                                ;}
    break;

  case 17:
#line 208 "26_A5.y"
    {
                                                                (yyval.num) = 1;
                                                                emit(PARAM, (yyvsp[(1) - (1)].expr)->loc->name, NULL, NULL);
                                                            ;}
    break;

  case 18:
#line 212 "26_A5.y"
    {   
                                                                (yyval.num) = (yyvsp[(1) - (3)].num) + 1;
                                                                emit(PARAM, (yyvsp[(3) - (3)].expr)->loc->name, NULL, NULL);
                                                            ;}
    break;

  case 19:
#line 219 "26_A5.y"
    {
                                            (yyval.expr) = (yyvsp[(1) - (1)].expr);    
                                        ;}
    break;

  case 20:
#line 222 "26_A5.y"
    {
                                            (yyval.expr) = exprCreate();
                                            
                                            switch((yyvsp[(1) - (2)].unary_op)){
                                                case '&':
                                                    (yyval.expr)->loc = gentemp();
                                                    (yyval.expr)->loc = update_symboltable(current_table, (yyval.expr)->loc->name, TYPE_PTR, NULL, size_of_pointer, TEMP, 0, (yyval.expr)->loc->name);
                                                    emit(ADDR, (yyval.expr)->loc->arrayName, (yyvsp[(2) - (2)].expr)->loc->arrayName, NULL);
                                                    break;
                                                
                                                case '*':
                                                    (yyval.expr)->isPointer = true;
                                                    (yyval.expr)->loc = gentemp();
                                                    (yyval.expr)->loc = update_symboltable(current_table, (yyval.expr)->loc->name, (yyvsp[(2) - (2)].expr)->loc->type + TYPE_PTR, NULL, size_of_pointer, TEMP, 0, (yyval.expr)->loc->name);
                                                    (yyval.expr)->loc->arrayName = (yyvsp[(2) - (2)].expr)->loc->arrayName;
                                                    emit(PTR_ASSIGN, (yyval.expr)->loc->name, (yyvsp[(2) - (2)].expr)->loc->arrayName, NULL);
                                                    break;

                                                case '+':
                                                    (yyval.expr) = (yyvsp[(2) - (2)].expr);
                                                    break;

                                                case '-':
                                                    (yyval.expr)->loc = gentemp();
                                                    (yyval.expr)->loc = update_symboltable(current_table, (yyval.expr)->loc->name, (yyvsp[(2) - (2)].expr)->loc->type, NULL, (yyvsp[(2) - (2)].expr)->loc->size, TEMP, 0, (yyval.expr)->loc->name);
                                                    emit(UMINUS, (yyval.expr)->loc->arrayName, (yyvsp[(2) - (2)].expr)->loc->arrayName, NULL);
                                                    break;

                                                case '!':
                                                    if ((yyvsp[(2) - (2)].expr)->isBoolean){
                                                        (yyval.expr)->isBoolean = true;
                                                        (yyval.expr)->truelist = (yyvsp[(2) - (2)].expr)->falselist;
                                                        (yyval.expr)->falselist = (yyvsp[(2) - (2)].expr)->truelist;
                                                        (yyval.expr)->loc = (yyvsp[(2) - (2)].expr)->loc;
                                                        (yyval.expr)->loc->arrayName = (yyvsp[(2) - (2)].expr)->loc->arrayName;
                                                    }    
                                                    else{
                                                        yyerror("Value not Boolean");
                                                    }
                                                    break;
                                            }
                                        ;}
    break;

  case 21:
#line 267 "26_A5.y"
    {
                (yyval.unary_op) = '&'; 
            ;}
    break;

  case 22:
#line 270 "26_A5.y"
    {
                (yyval.unary_op) = '*'; 
            ;}
    break;

  case 23:
#line 273 "26_A5.y"
    {
                (yyval.unary_op) = '+'; 
            ;}
    break;

  case 24:
#line 276 "26_A5.y"
    {
                (yyval.unary_op) = '-'; 
            ;}
    break;

  case 25:
#line 279 "26_A5.y"
    {
                (yyval.unary_op) = '!'; 
            ;}
    break;

  case 26:
#line 285 "26_A5.y"
    {
                                                            (yyval.expr) = exprCreate();
                                                            
                                                            if ((yyvsp[(1) - (1)].expr)->isArray){
                                                                (yyval.expr)->loc = gentemp();
                                                                (yyval.expr)->loc = update_symboltable(current_table, (yyval.expr)->loc->name, (yyvsp[(1) - (1)].expr)->loc->type, NULL, (yyvsp[(1) - (1)].expr)->loc->size, TEMP, 0, NULL);
                                                                emit(READIDX, (yyval.expr)->loc->name, (yyvsp[(1) - (1)].expr)->loc->arrayName, (yyvsp[(1) - (1)].expr)->loc->name);
                                                                (yyvsp[(1) - (1)].expr)->isArray = false;
                                                            }
                                                            else if ((yyvsp[(1) - (1)].expr)->isPointer){
                                                                (yyval.expr)->loc = (yyvsp[(1) - (1)].expr)->loc;
                                                            }
                                                            else{
                                                                (yyval.expr) = (yyvsp[(1) - (1)].expr);
                                                            }
                                                        ;}
    break;

  case 27:
#line 301 "26_A5.y"
    {
                                                            if ((yyvsp[(1) - (3)].expr)->loc->type != TYPE_INT || (yyvsp[(3) - (3)].expr)->loc->type != TYPE_INT){
                                                                yyerror("Type mismatch");
                                                            }
                                                            (yyval.expr) = exprCreate();
                                                            (yyval.expr)->loc = gentemp();
                                                            (yyval.expr)->loc = update_symboltable(current_table, (yyval.expr)->loc->name, TYPE_INT, NULL, size_of_int, TEMP, 0, NULL);                                                            
                                                            emit(MULT, (yyval.expr)->loc->name, (yyvsp[(1) - (3)].expr)->loc->name, (yyvsp[(3) - (3)].expr)->loc->name);
                                                        ;}
    break;

  case 28:
#line 310 "26_A5.y"
    {
                                                            if ((yyvsp[(1) - (3)].expr)->loc->type != TYPE_INT || (yyvsp[(3) - (3)].expr)->loc->type != TYPE_INT){
                                                                yyerror("Type mismatch");
                                                            }
                                                            (yyval.expr) = exprCreate();
                                                            (yyval.expr)->loc = gentemp();
                                                            (yyval.expr)->loc = update_symboltable(current_table, (yyval.expr)->loc->name, TYPE_INT, NULL, size_of_int, TEMP, 0, NULL);                                                            
                                                            emit(DIV, (yyval.expr)->loc->name, (yyvsp[(1) - (3)].expr)->loc->name, (yyvsp[(3) - (3)].expr)->loc->name);
                                                        ;}
    break;

  case 29:
#line 319 "26_A5.y"
    {
                                                            if ((yyvsp[(1) - (3)].expr)->loc->type != TYPE_INT || (yyvsp[(3) - (3)].expr)->loc->type != TYPE_INT){
                                                                yyerror("Type mismatch");
                                                            }
                                                            (yyval.expr) = exprCreate();
                                                            (yyval.expr)->loc = gentemp();
                                                            (yyval.expr)->loc = update_symboltable(current_table, (yyval.expr)->loc->name, TYPE_INT, NULL, size_of_int, TEMP, 0, NULL);                                                            
                                                            emit(MOD, (yyval.expr)->loc->name, (yyvsp[(1) - (3)].expr)->loc->name, (yyvsp[(3) - (3)].expr)->loc->name);
                                                        ;}
    break;

  case 30:
#line 331 "26_A5.y"
    {
                                                            (yyval.expr) = (yyvsp[(1) - (1)].expr);
                                                        ;}
    break;

  case 31:
#line 334 "26_A5.y"
    {
                                                            if ((yyvsp[(1) - (3)].expr)->loc->type != TYPE_INT || (yyvsp[(3) - (3)].expr)->loc->type != TYPE_INT){
                                                               yyerror("Type mismatch");
                                                            }
                                                            (yyval.expr) = exprCreate();
                                                            (yyval.expr)->loc = gentemp();
                                                            (yyval.expr)->loc = update_symboltable(current_table, (yyval.expr)->loc->name, TYPE_INT, NULL, size_of_int, TEMP, 0, NULL);
                                                            emit(PLUS, (yyval.expr)->loc->name, (yyvsp[(1) - (3)].expr)->loc->name, (yyvsp[(3) - (3)].expr)->loc->name);
                                                        ;}
    break;

  case 32:
#line 343 "26_A5.y"
    {
                                                            if ((yyvsp[(1) - (3)].expr)->loc->type != TYPE_INT || (yyvsp[(3) - (3)].expr)->loc->type != TYPE_INT){
                                                               yyerror("Type mismatch");
                                                            }
                                                            (yyval.expr) = exprCreate();
                                                            (yyval.expr)->loc = gentemp();
                                                            (yyval.expr)->loc = update_symboltable(current_table, (yyval.expr)->loc->name, TYPE_INT, NULL, size_of_int, TEMP, 0, NULL);
                                                            emit(MINUS, (yyval.expr)->loc->name, (yyvsp[(1) - (3)].expr)->loc->name, (yyvsp[(3) - (3)].expr)->loc->name);
                                                        ;}
    break;

  case 33:
#line 355 "26_A5.y"
    {
                                                                    (yyval.expr) = (yyvsp[(1) - (1)].expr);
                                                                ;}
    break;

  case 34:
#line 358 "26_A5.y"
    {
                                                                    if ((yyvsp[(1) - (3)].expr)->loc->type != (yyvsp[(3) - (3)].expr)->loc->type){
                                                                        yyerror("Type mismatch");
                                                                    }
                                                                    else{
                                                                        (yyval.expr) = exprCreate();
                                                                        (yyval.expr)->loc = (yyvsp[(1) - (3)].expr)->loc;
                                                                        (yyval.expr)->isBoolean = true;

                                                                        (yyval.expr)->truelist = newList(giveNextInstr());

                                                                        (yyval.expr)->falselist = newList(giveNextInstr()+1);

                                                                        emit(LT, NULL, (yyvsp[(1) - (3)].expr)->loc->name, (yyvsp[(3) - (3)].expr)->loc->name);
                                                                        emit(GOTO, "RE", NULL, NULL);
                                                                    }
                                                                ;}
    break;

  case 35:
#line 375 "26_A5.y"
    {
                                                                    if ((yyvsp[(1) - (3)].expr)->loc->type != (yyvsp[(3) - (3)].expr)->loc->type){
                                                                        yyerror("Type mismatch");
                                                                    }
                                                                    else{
                                                                        (yyval.expr) = exprCreate();
                                                                        (yyval.expr)->loc = (yyvsp[(1) - (3)].expr)->loc;
                                                                        (yyval.expr)->isBoolean = true;

                                                                        (yyval.expr)->truelist = newList(giveNextInstr());

                                                                        (yyval.expr)->falselist = newList(giveNextInstr()+1);

                                                                        emit(GT, "GT", (yyvsp[(1) - (3)].expr)->loc->name, (yyvsp[(3) - (3)].expr)->loc->name);
                                                                        emit(GOTO, "RE", NULL, NULL);
                                                                    }
                                                                ;}
    break;

  case 36:
#line 392 "26_A5.y"
    {
                                                                    if ((yyvsp[(1) - (3)].expr)->loc->type != (yyvsp[(3) - (3)].expr)->loc->type){
                                                                        yyerror("Type mismatch");
                                                                    }
                                                                    else{
                                                                        (yyval.expr) = exprCreate();
                                                                        (yyval.expr)->loc = (yyvsp[(1) - (3)].expr)->loc;
                                                                        (yyval.expr)->isBoolean = true;
                                                                        (yyval.expr)->truelist = newList(giveNextInstr());
                                                                        (yyval.expr)->falselist = newList(giveNextInstr()+1);
                                                                        emit(LTE, "", (yyvsp[(1) - (3)].expr)->loc->name, (yyvsp[(3) - (3)].expr)->loc->name);
                                                                        emit(GOTO, "RE", NULL, NULL);
                                                                    }
                                                                ;}
    break;

  case 37:
#line 406 "26_A5.y"
    {
                                                                    if ((yyvsp[(1) - (3)].expr)->loc->type != (yyvsp[(3) - (3)].expr)->loc->type){
                                                                        yyerror("Type mismatch");
                                                                    }
                                                                    else{
                                                                        (yyval.expr) = exprCreate();
                                                                        (yyval.expr)->loc = (yyvsp[(1) - (3)].expr)->loc;
                                                                        (yyval.expr)->isBoolean = true;

                                                                        (yyval.expr)->truelist = newList(giveNextInstr());

                                                                        (yyval.expr)->falselist = newList(giveNextInstr()+1);

                                                                        emit(GTE, "", (yyvsp[(1) - (3)].expr)->loc->name, (yyvsp[(3) - (3)].expr)->loc->name);
                                                                        emit(GOTO, "RE", NULL, NULL);
                                                                    }
                                                                ;}
    break;

  case 38:
#line 426 "26_A5.y"
    {
                                                        (yyval.expr) = (yyvsp[(1) - (1)].expr);
                                                    ;}
    break;

  case 39:
#line 429 "26_A5.y"
    {
                                                        if ((yyvsp[(1) - (3)].expr)->loc->type != (yyvsp[(3) - (3)].expr)->loc->type){
                                                            yyerror("Type mismatch");
                                                        }
                                                        else{
                                                            boolToInt((yyvsp[(1) - (3)].expr));
                                                            boolToInt((yyvsp[(3) - (3)].expr));
                                                            (yyval.expr) = exprCreate();
                                                            (yyval.expr)->loc = (yyvsp[(1) - (3)].expr)->loc;
                                                            (yyval.expr)->isBoolean = true;
                                                            (yyval.expr)->truelist = newList(giveNextInstr());
                                                            (yyval.expr)->falselist = newList(giveNextInstr()+1);
                                                            emit(EQUAL, "", (yyvsp[(1) - (3)].expr)->loc->name, (yyvsp[(3) - (3)].expr)->loc->name);
                                                            emit(GOTO, "EQEXP", NULL, NULL);
                                                        }
                                                    ;}
    break;

  case 40:
#line 445 "26_A5.y"
    {
                                                        if ((yyvsp[(1) - (3)].expr)->loc->type != (yyvsp[(3) - (3)].expr)->loc->type)
                                                        {
                                                            yyerror("Type mismatch");
                                                        }
                                                        else{
                                                            boolToInt((yyvsp[(1) - (3)].expr));
                                                            boolToInt((yyvsp[(3) - (3)].expr));
                                                            (yyval.expr) = exprCreate();
                                                            (yyval.expr)->loc = (yyvsp[(1) - (3)].expr)->loc;
                                                            (yyval.expr)->isBoolean = true;
                                                            (yyval.expr)->truelist = newList(giveNextInstr());
                                                            (yyval.expr)->falselist = newList(giveNextInstr()+1);

                                                            emit(NE, "", (yyvsp[(1) - (3)].expr)->loc->name, (yyvsp[(3) - (3)].expr)->loc->name);
                                                            emit(GOTO, "EQEXP", NULL, NULL);
                                                        }
                                                    ;}
    break;

  case 41:
#line 466 "26_A5.y"
    {
                                                                (yyval.expr) = (yyvsp[(1) - (1)].expr);
                                                            ;}
    break;

  case 42:
#line 469 "26_A5.y"
    {
                                                                
                                                                intToBool((yyvsp[(4) - (4)].expr));
                                                                intToBool((yyvsp[(1) - (4)].expr));
                                                                (yyval.expr) = exprCreate();
                                                                (yyval.expr)->loc = (yyvsp[(1) - (4)].expr)->loc;
                                                                (yyval.expr)->isBoolean = true;
                                                                backpatch((yyvsp[(1) - (4)].expr)->truelist, (yyvsp[(3) - (4)].num));
                                                                (yyval.expr)->truelist = (yyvsp[(4) - (4)].expr)->truelist;
                                                                (yyval.expr)->falselist = merge((yyvsp[(1) - (4)].expr)->falselist, (yyvsp[(4) - (4)].expr)->falselist);
                                                            ;}
    break;

  case 43:
#line 483 "26_A5.y"
    {
                                                                    (yyval.expr) = (yyvsp[(1) - (1)].expr);
                                                                ;}
    break;

  case 44:
#line 486 "26_A5.y"
    {
                                                                    intToBool((yyvsp[(4) - (4)].expr));
                                                                    intToBool((yyvsp[(1) - (4)].expr));
                                                                    (yyval.expr) = exprCreate();
                                                                    (yyval.expr)->loc = (yyvsp[(1) - (4)].expr)->loc;
                                                                    (yyval.expr)->isBoolean = true;
                                                                    backpatch((yyvsp[(1) - (4)].expr)->falselist, (yyvsp[(3) - (4)].num));
                                                                    (yyval.expr)->truelist = merge((yyvsp[(1) - (4)].expr)->truelist, (yyvsp[(4) - (4)].expr)->truelist);
                                                                    (yyval.expr)->falselist = (yyvsp[(4) - (4)].expr)->falselist;
                                                                ;}
    break;

  case 45:
#line 499 "26_A5.y"
    {
                                                                            (yyval.expr) = (yyvsp[(1) - (1)].expr);
                                                                        ;}
    break;

  case 46:
#line 502 "26_A5.y"
    {
                                                                                    (yyval.expr)->loc = gentemp();
                                                                                    (yyval.expr)->loc = update_symboltable(current_table, (yyval.expr)->loc->name, (yyvsp[(5) - (9)].expr)->loc->type, NULL, (yyvsp[(1) - (9)].expr)->loc->size, TEMP, 0, NULL);
                                                                                    emit(ASSIGN, (yyval.expr)->loc->name, (yyvsp[(9) - (9)].expr)->loc->name, NULL);
                                                                                    List *t = newList(giveNextInstr());
                                                                                    emit(GOTO, "ConExp", NULL, NULL);
                                                                                    backpatch((yyvsp[(6) - (9)].stm)->nextlist, giveNextInstr());
                                                                                    emit(ASSIGN, (yyval.expr)->loc->name, (yyvsp[(5) - (9)].expr)->loc->name, NULL);
                                                                                    List *l = newList(giveNextInstr());
                                                                                    l = merge(l, t);
                                                                                    emit(GOTO, "ConExp", NULL, NULL);
                                                                                    backpatch((yyvsp[(2) - (9)].stm)->nextlist, giveNextInstr());
                                                                                    intToBool((yyvsp[(1) - (9)].expr));
                                                                                    backpatch((yyvsp[(1) - (9)].expr)->truelist, (yyvsp[(4) - (9)].num));
                                                                                    backpatch((yyvsp[(1) - (9)].expr)->falselist, (yyvsp[(8) - (9)].num));
                                                                                    backpatch(l, giveNextInstr());
                                                                                ;}
    break;

  case 47:
#line 522 "26_A5.y"
    {
                                                        (yyval.expr) = (yyvsp[(1) - (1)].expr);
                                                    ;}
    break;

  case 48:
#line 525 "26_A5.y"
    {
                                                        if((yyvsp[(1) - (3)].expr)->isArray){
                                                            emit(WRITEIDX, (yyvsp[(1) - (3)].expr)->loc->arrayName, (yyvsp[(1) - (3)].expr)->loc->name, (yyvsp[(3) - (3)].expr)->loc->name);
                                                        }
                                                        else if((yyvsp[(1) - (3)].expr)->isPointer){
                                                            emit(PTR_ASSIGN, (yyvsp[(1) - (3)].expr)->loc->name, (yyvsp[(3) - (3)].expr)->loc->name, NULL);
                                                        }
                                                        else{
                                                            emit(ASSIGN, (yyvsp[(1) - (3)].expr)->loc->name, (yyvsp[(3) - (3)].expr)->loc->name, NULL);
                                                        }
                                                        (yyval.expr) = (yyvsp[(3) - (3)].expr);
                                                    ;}
    break;

  case 49:
#line 540 "26_A5.y"
    {
                                (yyval.expr) = (yyvsp[(1) - (1)].expr);
                            ;}
    break;

  case 50:
#line 548 "26_A5.y"
    {   
                                            table_pointer = NULL;
                                        ;}
    break;

  case 51:
#line 554 "26_A5.y"
    {
                                        if (current_table == global_table){
                                            if((yyvsp[(1) - (1)].symp)->type == TYPE_INT || (yyvsp[(1) - (1)].symp)->type == TYPE_CHAR || (yyvsp[(1) - (1)].symp)->type == TYPE_PTR || (yyvsp[(1) - (1)].symp)->type == TYPE_INT_PTR || (yyvsp[(1) - (1)].symp)->type == TYPE_CHAR_PTR || (yyvsp[(1) - (1)].symp)->type == TYPE_VOID_PTR){
                                                if ((yyvsp[(1) - (1)].symp)->type == TYPE_PTR || (yyvsp[(1) - (1)].symp)->type == TYPE_INT_PTR || (yyvsp[(1) - (1)].symp)->type == TYPE_CHAR_PTR || (yyvsp[(1) - (1)].symp)->type == TYPE_VOID_PTR){
                                                    (yyvsp[(1) - (1)].symp)->size = size_of_pointer;
                                                }
                                                update_symboltable(current_table, (yyvsp[(1) - (1)].symp)->name, (yyvsp[(1) - (1)].symp)->type, 0, (yyvsp[(1) - (1)].symp)->size, GLOBAL, (yyvsp[(1) - (1)].symp)->arraySize, NULL);
                                            }
                                            else{
                                                yyerror("Invalid type");
                                            }
                                        }
                                        else{
                                        }
                                    ;}
    break;

  case 52:
#line 569 "26_A5.y"
    {
                                        if ((yyvsp[(3) - (3)].symp)->value != NULL){
                                            (yyvsp[(1) - (3)].symp)->value = (yyvsp[(3) - (3)].symp)->value;
                                        }
                                        if ((yyvsp[(1) - (3)].symp)->type == TYPE_INT_PTR || (yyvsp[(1) - (3)].symp)->type == TYPE_CHAR_PTR || (yyvsp[(1) - (3)].symp)->type == TYPE_VOID_PTR){
                                            emit(PTR_ASSIGN, (yyvsp[(1) - (3)].symp)->name, (yyvsp[(3) - (3)].symp)->name, NULL);
                                        }
                                        else if ((yyvsp[(1) - (3)].symp)->arraySize != 0){
                                            emit(WRITEIDX, (yyvsp[(1) - (3)].symp)->name, (yyvsp[(1) - (3)].symp)->arrayName, (yyvsp[(3) - (3)].symp)->name);
                                        }
                                        else{
                                            emit(ASSIGN, (yyvsp[(1) - (3)].symp)->name, (yyvsp[(3) - (3)].symp)->name, NULL);
                                        }
                                    ;}
    break;

  case 53:
#line 586 "26_A5.y"
    {
                push(&dTypeStack, voidType);
            ;}
    break;

  case 54:
#line 589 "26_A5.y"
    {
                push(&dTypeStack, charType);
            ;}
    break;

  case 55:
#line 592 "26_A5.y"
    {
                push(&dTypeStack, intType);
            ;}
    break;

  case 56:
#line 598 "26_A5.y"
    {
                                        if ((yyvsp[(2) - (2)].symp)->nested_table != NULL){
                                            
                                            (yyval.symp) = (yyvsp[(2) - (2)].symp);
                                            int type = (yyval.symp)->type;
                                            (yyval.symp)->type = type - TYPE_PTR;
                                            (yyval.symp)->size = size_of_pointer;
                                            if ((yyval.symp)->type != TYPE_VOID){
                                                symbol *RV = symlook((yyval.symp)->nested_table, "retVal");
                                                RV = update_symboltable((yyval.symp)->nested_table, RV->name, (yyval.symp)->type, 0, (yyval.symp)->size, LOCAL, 0, NULL);
                                            }
                                        }
                                        else{
                                            (yyval.symp) = (yyvsp[(2) - (2)].symp);
                                            //$$->arraySize = 1;
                                            //$$->arrayName = $2->arrayName; // not sure if that would be array or not
                                            (yyval.symp)->type = (yyval.symp)->type - TYPE_PTR;
                                            (yyval.symp)->size = size_of_pointer;
                                        }
                                    ;}
    break;

  case 57:
#line 618 "26_A5.y"
    {
                                        (yyval.symp) = (yyvsp[(1) - (1)].symp);
                                    ;}
    break;

  case 58:
#line 624 "26_A5.y"
    {   
                                                            (yyval.symp) = create_symbol();
                                                            data_type dType = pop(&dTypeStack);
                                                            if (current_table != global_table){
                                                                (yyvsp[(1) - (1)].symp) = update_symboltable(current_table, (yyvsp[(1) - (1)].symp)->name, dType.type, 0, dType.size, LOCAL, 0, NULL);
                                                            }
                                                            else{
                                                                (yyvsp[(1) - (1)].symp) = update_symboltable(current_table, (yyvsp[(1) - (1)].symp)->name, dType.type, 0, dType.size, NONE, 0, NULL);
                                                            }
                                                            (yyval.symp) = (yyvsp[(1) - (1)].symp);
                                                        ;}
    break;

  case 59:
#line 635 "26_A5.y"
    {   
                                                            (yyval.symp) = create_symbol();
                                                            data_type dType = pop(&dTypeStack);
                                                            if (current_table != global_table){
                                                                (yyvsp[(1) - (4)].symp) = update_symboltable(current_table, (yyvsp[(1) - (4)].symp)->name, dType.type, 0, dType.size, LOCAL, (yyvsp[(3) - (4)].intval), (yyvsp[(1) - (4)].symp)->name);
                                                            }
                                                            else{
                                                                (yyvsp[(1) - (4)].symp) = update_symboltable(current_table, (yyvsp[(1) - (4)].symp)->name, dType.type, 0, dType.size, NONE, (yyvsp[(3) - (4)].intval), (yyvsp[(1) - (4)].symp)->name);
                                                            }
                                                            (yyval.symp)->arrayName = (yyvsp[(1) - (4)].symp)->name;
                                                            (yyval.symp) = (yyvsp[(1) - (4)].symp);
                                                        ;}
    break;

  case 60:
#line 647 "26_A5.y"
    {   
                                                            table_name = strdup((yyvsp[(1) - (5)].symp)->name);
                                                            data_type dType = pop(&dTypeStack);
                                                            (yyvsp[(1) - (5)].symp) = update_symboltable(global_table, (yyvsp[(1) - (5)].symp)->name, dType.type, 0, 0, FUNCTION, 0, NULL);
                                                            if (dType.type != TYPE_VOID){
                                                                symbol *RV = symlook(current_table, "retVal");
                                                                RV = update_symboltable(current_table, RV->name, (yyvsp[(1) - (5)].symp)->type, 0, dType.size, LOCAL, 0, NULL);
                                                            }
                                                            (yyvsp[(1) - (5)].symp)->nested_table = current_table;
                                                            table_pointer = current_table;
                                                            current_table = global_table;
                                                            (yyval.symp) = (yyvsp[(1) - (5)].symp);
                                                        ;}
    break;

  case 63:
#line 668 "26_A5.y"
    {;}
    break;

  case 64:
#line 672 "26_A5.y"
    {
                                                ;}
    break;

  case 65:
#line 674 "26_A5.y"
    {
                                                ;}
    break;

  case 66:
#line 679 "26_A5.y"
    {   

                                                data_type dType = pop(&dTypeStack);
                                                (yyvsp[(3) - (3)].symp) = update_symboltable(current_table, (yyvsp[(3) - (3)].symp)->name, dType.type - TYPE_PTR, 0, size_of_pointer, PARAMETER, 0, NULL);
                                            ;}
    break;

  case 67:
#line 684 "26_A5.y"
    {   
                                                data_type dType = pop(&dTypeStack);
                                                (yyvsp[(2) - (2)].symp) = update_symboltable(current_table, (yyvsp[(2) - (2)].symp)->name, dType.type, 0, dType.size, PARAMETER, 0, NULL);
                                            ;}
    break;

  case 68:
#line 688 "26_A5.y"
    {
                                                data_type dType = pop(&dTypeStack);
                                            ;}
    break;

  case 69:
#line 691 "26_A5.y"
    {   
                                                data_type dType = pop(&dTypeStack);
                                            ;}
    break;

  case 70:
#line 697 "26_A5.y"
    {   
                                (yyval.symp) = (yyvsp[(1) - (1)].expr)->loc;
                            ;}
    break;

  case 71:
#line 705 "26_A5.y"
    {   
                                (yyval.stm) = (yyvsp[(1) - (1)].stm);
                            ;}
    break;

  case 72:
#line 708 "26_A5.y"
    {
                                (yyval.stm) = statCreate();
                                (yyval.stm)->nextlist = (yyvsp[(1) - (1)].expr)->nextlist;
                            ;}
    break;

  case 73:
#line 712 "26_A5.y"
    {
                                (yyval.stm) = (yyvsp[(1) - (1)].stm);
                            ;}
    break;

  case 74:
#line 715 "26_A5.y"
    {
                                (yyval.stm) = (yyvsp[(1) - (1)].stm);
                            ;}
    break;

  case 75:
#line 718 "26_A5.y"
    {
                                (yyval.stm) = (yyvsp[(1) - (1)].stm);
                            ;}
    break;

  case 76:
#line 724 "26_A5.y"
    {
                                    (yyval.stm) = (yyvsp[(2) - (3)].stm);
                                ;}
    break;

  case 77:
#line 730 "26_A5.y"
    {
                        (yyval.stm) = (yyvsp[(1) - (1)].stm);
                    ;}
    break;

  case 78:
#line 733 "26_A5.y"
    {
                        (yyval.stm) = statCreate();
                    ;}
    break;

  case 79:
#line 739 "26_A5.y"
    {
                                        (yyval.stm) = (yyvsp[(1) - (1)].stm);
                                    ;}
    break;

  case 80:
#line 742 "26_A5.y"
    {
                                        (yyval.stm) = (yyvsp[(3) - (3)].stm);
                                        backpatch((yyvsp[(1) - (3)].stm)->nextlist, (yyvsp[(2) - (3)].num));
                                    ;}
    break;

  case 81:
#line 749 "26_A5.y"
    {
                    (yyval.stm) = statCreate();
                ;}
    break;

  case 82:
#line 752 "26_A5.y"
    {
                    (yyval.stm) = (yyvsp[(1) - (1)].stm);
                ;}
    break;

  case 83:
#line 758 "26_A5.y"
    {   
                        (yyval.expr) = (yyvsp[(1) - (2)].expr);
                    ;}
    break;

  case 84:
#line 761 "26_A5.y"
    {
                        (yyval.expr) = exprCreate();
                    ;}
    break;

  case 85:
#line 767 "26_A5.y"
    {
                    (yyval.expr) = (yyvsp[(1) - (1)].expr);
                ;}
    break;

  case 86:
#line 770 "26_A5.y"
    {
                    (yyval.expr) = exprCreate();
                    (yyval.expr)->nextlist = newList(-1); // a checker if expression is null
                ;}
    break;

  case 87:
#line 777 "26_A5.y"
    {  
                                                                backpatch((yyvsp[(4) - (8)].stm)->nextlist, giveNextInstr());
                                                                (yyvsp[(3) - (8)].expr) = intToBool((yyvsp[(3) - (8)].expr));
                                                                (yyval.stm) = statCreate();
                                                                backpatch((yyvsp[(3) - (8)].expr)->truelist, (yyvsp[(6) - (8)].num));
                                                                List *t = merge((yyvsp[(3) - (8)].expr)->falselist, (yyvsp[(7) - (8)].stm)->nextlist);
                                                                (yyval.stm)->nextlist = merge((yyvsp[(8) - (8)].stm)->nextlist, t);
                                                            ;}
    break;

  case 88:
#line 785 "26_A5.y"
    {
                                                                backpatch((yyvsp[(4) - (11)].stm)->nextlist, giveNextInstr());
                                                                intToBool((yyvsp[(3) - (11)].expr));
                                                                (yyval.stm) = statCreate();
                                                                backpatch((yyvsp[(3) - (11)].expr)->truelist, (yyvsp[(6) - (11)].num));
                                                                backpatch((yyvsp[(3) - (11)].expr)->falselist, (yyvsp[(10) - (11)].num));
                                                                List *t = merge((yyvsp[(7) - (11)].stm)->nextlist, (yyvsp[(8) - (11)].stm)->nextlist);
                                                                (yyval.stm)->nextlist = merge((yyvsp[(11) - (11)].stm)->nextlist, t);
                                                            ;}
    break;

  case 89:
#line 798 "26_A5.y"
    {   
                                                                                            (yyval.stm) = statCreate();
                                                                                            if ((yyvsp[(6) - (13)].expr)->nextlist != NULL){ 
                                                                                                // missing the middle expression, making it while loop
                                                                                                backpatch((yyvsp[(10) - (13)].stm)->nextlist, (yyvsp[(12) - (13)].num));
                                                                                                backpatch((yyvsp[(13) - (13)].stm)->nextlist, (yyvsp[(8) - (13)].num));
                                                                                                char *value = (char*)malloc(sizeof(char)*100);
                                                                                                sprintf(value, "%d", (yyvsp[(5) - (13)].num));
                                                                                                emit(GOTO, value, NULL, NULL);
                                                                                            }
                                                                                            else{
                                                                                                intToBool((yyvsp[(6) - (13)].expr));
                                                                                                backpatch((yyvsp[(6) - (13)].expr)->truelist, (yyvsp[(12) - (13)].num));
                                                                                                backpatch((yyvsp[(10) - (13)].stm)->nextlist, (yyvsp[(5) - (13)].num));
                                                                                                backpatch((yyvsp[(13) - (13)].stm)->nextlist, (yyvsp[(8) - (13)].num));
                                                                                                char *value = (char*)malloc(sizeof(char)*100);
                                                                                                sprintf(value, "%d", (yyvsp[(8) - (13)].num));
                                                                                                emit(GOTO, value, NULL, NULL);
                                                                                                (yyval.stm)->nextlist = (yyvsp[(6) - (13)].expr)->falselist;
                                                                                            }
                                                                                        ;}
    break;

  case 90:
#line 822 "26_A5.y"
    {
                                    symbol *RV = searchTable(current_table, "retVal");

                                    if ((yyvsp[(2) - (3)].expr)->loc->type != RV->type){
                                        yyerror("Return value mismatch.");
                                    }
                                    else{
                                        (yyval.stm) = statCreate();
                                        emit(RET, (yyvsp[(2) - (3)].expr)->loc->name, NULL, NULL);
                                    }
                                ;}
    break;

  case 91:
#line 833 "26_A5.y"
    {   
                                    symbol *RV = searchTable(current_table, "retVal");
                                    if (RV != NULL){
                                        yyerror("Return value mismatch. Type not VOID");
                                    }
                                    else{
                                        (yyval.stm) = statCreate();
                                        
                                        emit(RET, "", NULL, NULL);
                                    }
                                ;}
    break;

  case 92:
#line 847 "26_A5.y"
    {;}
    break;

  case 93:
#line 848 "26_A5.y"
    {;}
    break;

  case 94:
#line 852 "26_A5.y"
    {;}
    break;

  case 95:
#line 853 "26_A5.y"
    {;}
    break;

  case 96:
#line 857 "26_A5.y"
    {
                                                                    table_pointer = NULL;
                                                                    
                                                                    backpatch((yyvsp[(4) - (4)].stm)->nextlist, giveNextInstr());
                                                                    emit(FUNC_END, table_name, NULL, NULL);
                                                                    current_table = global_table;
                                                                ;}
    break;


/* Line 1267 of yacc.c.  */
#line 2538 "26_A5.tab.c"
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
      /* If just tried and failed to reuse look-ahead token after an
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

  /* Else will try to reuse look-ahead token after shifting the error
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

  if (yyn == YYFINAL)
    YYACCEPT;

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

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
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


#line 865 "26_A5.y"



void yyerror(char *s) {
    printf("Error: %s on '%s'", s, yytext);
}
