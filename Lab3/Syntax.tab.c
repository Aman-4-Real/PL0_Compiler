/* A Bison parser, made by GNU Bison 2.7.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2012 Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.7"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
/* Line 371 of yacc.c  */
#line 1 "Syntax.y"

/*
Date: 2019.6.7
Author: Aman
ALL RIGHTS DESERVED
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


FILE *fi;  //指向输出文件的指针
FILE *fp;  //指向输出类pcode文件的指针
FILE *fh;  //指向输出层次结构的指针
extern int row_num, col_num;  //行数和列数
extern char key[14];
// extern char idname[20];

typedef struct node{
      char data[14];
      struct node* left;
      struct node* right;
}Node;

#define maxsize 50
typedef Node* elem;

typedef struct{
      Node* root;
}Tree;

typedef struct{
      int top;
      elem index[maxsize];
}Stack;

extern Stack stack;
extern Tree tree;


/**********Lab3 Part**********/
typedef struct{ 
      int kind;         //const = 1, var = 2, proc = 3
      char* name;
      int val;          //如果为-2则为过程名, -1为未赋值的变量
      int level;
      int addr;
      int size;         //只有过程名使用, 标记了过程中的变量数量
      int previous;
}symbol; 

#define MAX_SYMBOL_TABLE_SIZE 50
typedef symbol* sym;

typedef struct{
      int top;
      symbol index[MAX_SYMBOL_TABLE_SIZE];
}symbol_table;


symbol_table symtable;  //符号栈
int display_stack[20];  //display栈
int display_top = 0;   //display的栈顶
int now_Level = 0;    //当前的层数
int addr = 3;     //记录每个变量在运行栈中相对本过程基地址的偏移量

typedef struct{
    enum f{LIT, LOD, STO, CAL, INT, JMP, JPC, OPR} f;
    int l;
    int a;
}instruction; 

#define STACKSIZE 200
instruction code[STACKSIZE];
int code_line = 0;
char *fname[]={"LIT","LOD","STO","CAL","INT","JMP","JPC","OPR"};

int bkpchpos[50];  //记录回填的位置
int bkpchpos_top = -1;  //回填栈顶

#define MAXPRONUM 20
typedef struct{
    char *proname;
    int l;  //层差
    int pos;
}prostk; 
prostk prostack[MAXPRONUM];
int prostktop = -1;  //过程栈栈顶

int whilepos[10];  //记录循环的code_line
int whiletop = -1;

char *caseid;
/**********Lab3 Part**********/



//函数声明部分
int yylex();
int yyerror(char *s);
extern void Process(char* temp);
void left_insert(Node* parent, Node* son);
void right_insert(Node* node, Node* bro);
void init();
void stack_init();
elem stack_pop();
void stack_push(elem p);
void PreOrderTravel(Node* T, int k);
int stack_empty();
int stack_size();
elem stack_top();
void Reduce(char* name, int num);

void symtable_init();
void symtable_push();
void symtable_pop();
int if_declared();
int symtable_size();
symbol symtable_top();
int find_sign(char *sign_name);
int findpro(char *pname);
void Backpatch(int p, int l);
void gen(enum f f, int l, int a);
void OutputCode();

/* Line 371 of yacc.c  */
#line 195 "Syntax.tab.c"

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "Syntax.tab.h".  */
#ifndef YY_YY_SYNTAX_TAB_H_INCLUDED
# define YY_YY_SYNTAX_TAB_H_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     IDENTIFIER = 258,
     CONSTANT = 259,
     RELOP = 260,
     COMMA = 261,
     SEMI = 262,
     DOT = 263,
     LPAREN = 264,
     RPAREN = 265,
     ASSIGN = 266,
     MINUS = 267,
     COLON = 268,
     CONST = 269,
     VAR = 270,
     PROCEDURE = 271,
     _BEGIN_ = 272,
     END = 273,
     IF = 274,
     THEN = 275,
     ELSE = 276,
     ODD = 277,
     WHILE = 278,
     DO = 279,
     CALL = 280,
     READ = 281,
     WRITE = 282,
     CASE = 283,
     ENDCASE = 284,
     PLUS = 285,
     DIVIDE = 286,
     TIMES = 287,
     LOWER_THAN_ELSE = 288
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 387 of yacc.c  */
#line 129 "Syntax.y"

      struct{
            int val;
            char *str;
      }var;
      int val;


/* Line 387 of yacc.c  */
#line 280 "Syntax.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

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

#endif /* !YY_YY_SYNTAX_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

/* Line 390 of yacc.c  */
#line 308 "Syntax.tab.c"

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
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(N) (N)
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
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
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
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

# define YYCOPY_NEEDED 1

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

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   119

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  34
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  35
/* YYNRULES -- Number of rules.  */
#define YYNRULES  65
/* YYNRULES -- Number of states.  */
#define YYNSTATES  124

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   288

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
      25,    26,    27,    28,    29,    30,    31,    32,    33
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     6,    11,    15,    16,    17,    19,    22,
      25,    29,    32,    34,    36,    40,    44,    46,    50,    54,
      58,    60,    64,    69,    73,    75,    77,    79,    81,    83,
      85,    87,    89,    93,    97,   100,   104,   110,   119,   120,
     121,   125,   128,   132,   136,   139,   142,   144,   148,   152,
     154,   156,   158,   162,   169,   170,   171,   175,   179,   184,
     188,   190,   193,   198,   203,   207
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      35,     0,    -1,    36,     8,    -1,    37,    39,    38,    47,
      -1,    37,    38,    47,    -1,    -1,    -1,    40,    -1,    40,
      43,    -1,    40,    45,    -1,    40,    43,    45,    -1,    43,
      45,    -1,    43,    -1,    45,    -1,    14,    41,     7,    -1,
      41,     6,    42,    -1,    42,    -1,     3,     5,     4,    -1,
      15,    44,     7,    -1,    44,     6,     3,    -1,     3,    -1,
      46,    36,     7,    -1,    45,    46,    36,     7,    -1,    16,
       3,     7,    -1,    48,    -1,    49,    -1,    51,    -1,    58,
      -1,    61,    -1,    65,    -1,    66,    -1,    67,    -1,     3,
      11,    55,    -1,    17,    50,    18,    -1,    47,     7,    -1,
      50,    47,     7,    -1,    19,    54,    52,    20,    47,    -1,
      19,    54,    52,    20,    47,    21,    53,    47,    -1,    -1,
      -1,    55,     5,    55,    -1,    22,    55,    -1,    55,    30,
      56,    -1,    55,    12,    56,    -1,    30,    56,    -1,    12,
      56,    -1,    56,    -1,    56,    32,    57,    -1,    56,    31,
      57,    -1,    57,    -1,     3,    -1,     4,    -1,     9,    55,
      10,    -1,    23,    59,    54,    24,    60,    47,    -1,    -1,
      -1,    62,    63,    29,    -1,    28,     3,    13,    -1,    63,
      64,    13,    50,    -1,    64,    13,    50,    -1,     4,    -1,
      25,     3,    -1,    26,     9,     3,    10,    -1,    27,     9,
      68,    10,    -1,    68,     6,    55,    -1,    55,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   151,   151,   161,   165,   170,   177,   192,   196,   200,
     204,   208,   212,   216,   222,   227,   231,   236,   246,   251,
     259,   268,   276,   286,   306,   310,   314,   318,   322,   326,
     330,   334,   340,   357,   362,   366,   372,   377,   383,   388,
     394,   405,   411,   417,   423,   428,   434,   440,   446,   452,
     458,   474,   480,   485,   492,   496,   501,   508,   519,   525,
     532,   539,   551,   562,   569,   573
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IDENTIFIER", "CONSTANT", "RELOP",
  "COMMA", "SEMI", "DOT", "LPAREN", "RPAREN", "ASSIGN", "MINUS", "COLON",
  "CONST", "VAR", "PROCEDURE", "_BEGIN_", "END", "IF", "THEN", "ELSE",
  "ODD", "WHILE", "DO", "CALL", "READ", "WRITE", "CASE", "ENDCASE", "PLUS",
  "DIVIDE", "TIMES", "LOWER_THAN_ELSE", "$accept", "Program", "subProg",
  "BeforeDec", "BeforeSTM", "DeclarePart", "ConstDec", "ConstDef",
  "CDefine", "VarDec", "IdentiObj", "ProceDec", "ProceHead", "Statement",
  "AssignStm", "ComplexStm", "Statemt", "CondStm", "BeforeThen",
  "BeforeElseDo", "Condition", "Expr", "Term", "Factor", "WhilelpStm",
  "BeforeCond", "BeforeCondDo", "CaseStm", "CaseHead", "CaseBody",
  "AfterConst", "CallStm", "ReadStm", "WriteStm", "ExprObj", YY_NULL
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
     285,   286,   287,   288
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    34,    35,    36,    36,    37,    38,    39,    39,    39,
      39,    39,    39,    39,    40,    41,    41,    42,    43,    44,
      44,    45,    45,    46,    47,    47,    47,    47,    47,    47,
      47,    47,    48,    49,    50,    50,    51,    51,    52,    53,
      54,    54,    55,    55,    55,    55,    55,    56,    56,    56,
      57,    57,    57,    58,    59,    60,    61,    62,    63,    63,
      64,    65,    66,    67,    68,    68
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     4,     3,     0,     0,     1,     2,     2,
       3,     2,     1,     1,     3,     3,     1,     3,     3,     3,
       1,     3,     4,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     3,     2,     3,     5,     8,     0,     0,
       3,     2,     3,     3,     2,     2,     1,     3,     3,     1,
       1,     1,     3,     6,     0,     0,     3,     3,     4,     3,
       1,     2,     4,     4,     3,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       5,     0,     0,     6,     1,     2,     0,     0,     0,     0,
       6,     7,    12,    13,     5,     0,     0,    16,    20,     0,
       0,     0,     0,     0,    54,     0,     0,     0,     0,     4,
      24,    25,    26,    27,    28,     0,    29,    30,    31,     0,
       8,     9,    11,     5,     0,     0,     0,    14,     0,    18,
      23,     0,     0,     0,    50,    51,     0,     0,     0,     0,
      38,     0,    46,    49,     0,    61,     0,     0,     0,    60,
       0,     0,     3,    10,     0,    21,    17,    15,    19,    32,
      34,    33,     0,     0,    45,    41,    44,     0,     0,     0,
       0,     0,     0,     0,     0,    65,     0,    57,    56,     0,
       0,    22,    35,    52,     0,    40,    43,    42,    48,    47,
      55,    62,     0,    63,     0,    59,    36,     0,    64,    58,
      39,    53,     0,    37
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     1,     2,     3,     9,    10,    11,    16,    17,    12,
      19,    13,    14,    52,    30,    31,    53,    32,    87,   122,
      60,    61,    62,    63,    33,    64,   117,    34,    35,    70,
      71,    36,    37,    38,    96
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -56
static const yytype_int8 yypact[] =
{
     -56,     5,    14,    37,   -56,   -56,    23,    26,    56,    64,
     -56,    40,     0,     0,   -56,    66,    51,   -56,   -56,    62,
      69,    71,    64,    11,   -56,    81,    76,    77,    85,   -56,
     -56,   -56,   -56,   -56,   -56,    89,   -56,   -56,   -56,    64,
       0,     0,     0,   -56,    87,    92,    23,   -56,    94,   -56,
     -56,    15,    91,    47,   -56,   -56,    15,    45,    15,    45,
     -56,    16,    46,   -56,    11,   -56,    96,    15,    88,   -56,
       8,    90,   -56,     0,    93,   -56,   -56,   -56,   -56,    13,
     -56,   -56,    95,    30,    46,    13,    46,    84,    15,    45,
      45,    45,    45,    83,    99,    13,     3,   -56,   -56,    98,
      64,   -56,   -56,   -56,    64,    13,    46,    46,   -56,   -56,
     -56,   -56,    15,   -56,    64,    64,    97,    64,    13,    64,
     -56,   -56,    64,   -56
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -56,   -56,    -7,   -56,   102,   -56,   -56,   -56,    59,   103,
     -56,    -1,   -10,    -9,   -56,   -56,   -53,   -56,   -56,   -56,
      52,   -50,   -55,   -12,   -56,   -56,   -56,   -56,   -56,   -56,
      49,   -56,   -56,   -56,   -56
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      29,    79,    84,    43,    86,     4,    83,    44,    85,   112,
      41,    42,    69,   113,    54,    55,     8,    95,    54,    55,
      56,    88,     5,    57,    56,    89,    15,    57,    89,    18,
      72,    43,    43,    58,   106,   107,    74,    98,   105,    73,
     103,    59,    89,    90,    82,    59,    90,   115,    54,    55,
      21,     6,     7,     8,    56,     7,     8,    46,    47,    20,
      90,   119,   118,    43,    22,    81,    23,    21,    48,    49,
      24,    45,    25,    26,    27,    28,    50,    91,    92,   108,
     109,    22,    51,    23,    65,    66,    67,    24,    68,    25,
      26,    27,    28,    69,    75,   116,    76,    78,    80,    94,
     101,    97,   102,   100,   104,    77,    82,   110,   121,   111,
      82,   114,    39,   123,    40,     0,    93,     0,   120,    99
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-56)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int8 yycheck[] =
{
       9,    51,    57,    13,    59,     0,    56,    14,    58,     6,
      11,    12,     4,    10,     3,     4,    16,    67,     3,     4,
       9,     5,     8,    12,     9,    12,     3,    12,    12,     3,
      39,    41,    42,    22,    89,    90,    43,    29,    88,    40,
      10,    30,    12,    30,    53,    30,    30,   100,     3,     4,
       3,    14,    15,    16,     9,    15,    16,     6,     7,     3,
      30,   114,   112,    73,    17,    18,    19,     3,     6,     7,
      23,     5,    25,    26,    27,    28,     7,    31,    32,    91,
      92,    17,    11,    19,     3,     9,     9,    23,     3,    25,
      26,    27,    28,     4,     7,   104,     4,     3,     7,     3,
       7,    13,     7,    13,    20,    46,   115,    24,   117,    10,
     119,    13,    10,   122,    11,    -1,    64,    -1,    21,    70
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    35,    36,    37,     0,     8,    14,    15,    16,    38,
      39,    40,    43,    45,    46,     3,    41,    42,     3,    44,
       3,     3,    17,    19,    23,    25,    26,    27,    28,    47,
      48,    49,    51,    58,    61,    62,    65,    66,    67,    38,
      43,    45,    45,    46,    36,     5,     6,     7,     6,     7,
       7,    11,    47,    50,     3,     4,     9,    12,    22,    30,
      54,    55,    56,    57,    59,     3,     9,     9,     3,     4,
      63,    64,    47,    45,    36,     7,     4,    42,     3,    55,
       7,    18,    47,    55,    56,    55,    56,    52,     5,    12,
      30,    31,    32,    54,     3,    55,    68,    13,    29,    64,
      13,     7,     7,    10,    20,    55,    56,    56,    57,    57,
      24,    10,     6,    10,    13,    50,    47,    60,    55,    50,
      21,    47,    53,    47
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

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))

/* Error token number */
#define YYTERROR	1
#define YYERRCODE	256


/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
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
  FILE *yyo = yyoutput;
  YYUSE (yyo);
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

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
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




/* The lookahead symbol.  */
int yychar;


#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval YY_INITIAL_VALUE(yyval_default);

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
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
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
  int yytoken = 0;
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

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
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
  if (yypact_value_is_default (yyn))
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
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  Process(key);
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
/* Line 1792 of yacc.c  */
#line 151 "Syntax.y"
    {
                  fprintf(fi, "Program -> subProg.\n");
                  // symtable_pop();
                  gen(OPR, 0, 0);
                  Reduce("Program", 2);
                  tree.root = stack_pop();
                  // printf("---%s---\n", tree.root->left->data);
                  PreOrderTravel(tree.root, 0);
            }
    break;

  case 3:
/* Line 1792 of yacc.c  */
#line 161 "Syntax.y"
    {
                  fprintf(fi, "subProg -> DeclarePart Statement\n");
                  Reduce("subProg", 2);
            }
    break;

  case 4:
/* Line 1792 of yacc.c  */
#line 165 "Syntax.y"
    {
                  fprintf(fi, "subProg -> Statement\n");
                  Reduce("subProg", 1);
            }
    break;

  case 5:
/* Line 1792 of yacc.c  */
#line 170 "Syntax.y"
    {
                  if(symtable_size() == 0) display_stack[++display_top] = 1;
                  else display_stack[++display_top] = symtable_size();  //写display表
                  bkpchpos[++bkpchpos_top] = code_line;  //填入回填栈等待回填
                  gen(JMP, 0, 0);
            }
    break;

  case 6:
/* Line 1792 of yacc.c  */
#line 177 "Syntax.y"
    {
                  if(bkpchpos_top > -1){
                        Backpatch(bkpchpos[bkpchpos_top--], code_line);
                  }
                  if(display_stack[display_top] == 1){
                        gen(INT, 0, symtable.top + 3);
                  }
                  else{
                        gen(INT, 0, symtable.top - display_stack[display_top] + 3);
                  }
                  
                  // printf(">>>>>>>>>>> int 0 %d <<<<<<<<<<\n", symtable.top - display_stack[display_top] + 3);
            }
    break;

  case 7:
/* Line 1792 of yacc.c  */
#line 192 "Syntax.y"
    {
                  fprintf(fi, "DeclarePart -> ConstDec\n");
                  Reduce("DeclarePart", 1);
            }
    break;

  case 8:
/* Line 1792 of yacc.c  */
#line 196 "Syntax.y"
    {
                  fprintf(fi, "DeclarePart -> ConstDec VarDec\n");
                  Reduce("DeclarePart", 2);
            }
    break;

  case 9:
/* Line 1792 of yacc.c  */
#line 200 "Syntax.y"
    {
                  fprintf(fi, "DeclarePart -> ConstDec ProceDec\n");
                  Reduce("DeclarePart", 2);
            }
    break;

  case 10:
/* Line 1792 of yacc.c  */
#line 204 "Syntax.y"
    {
                  fprintf(fi, "DeclarePart -> ConstDec VarDec ProceDec\n");
                  Reduce("DeclarePart", 3);
            }
    break;

  case 11:
/* Line 1792 of yacc.c  */
#line 208 "Syntax.y"
    {
                  fprintf(fi, "DeclarePart -> VarDec ProceDec\n");
                  Reduce("DeclarePart", 2);
            }
    break;

  case 12:
/* Line 1792 of yacc.c  */
#line 212 "Syntax.y"
    {
                  fprintf(fi, "DeclarePart -> VarDec\n");
                  Reduce("DeclarePart", 1);
            }
    break;

  case 13:
/* Line 1792 of yacc.c  */
#line 216 "Syntax.y"
    {
                  fprintf(fi, "DeclarePart -> ProceDec\n");
                  Reduce("DeclarePart", 1);
            }
    break;

  case 14:
/* Line 1792 of yacc.c  */
#line 222 "Syntax.y"
    {
                  fprintf(fi, "ConstDec -> CONST ConstDef;\n");
                  Reduce("ConstDec", 3);
            }
    break;

  case 15:
/* Line 1792 of yacc.c  */
#line 227 "Syntax.y"
    {
                  fprintf(fi, "ConstDef -> ConstDef, CDefine\n");
                  Reduce("ConstDef", 3);
            }
    break;

  case 16:
/* Line 1792 of yacc.c  */
#line 231 "Syntax.y"
    {
                  fprintf(fi, "ConstDef -> CDefine\n");
                  Reduce("ConstDef", 1);
            }
    break;

  case 17:
/* Line 1792 of yacc.c  */
#line 236 "Syntax.y"
    {
                  (yyvsp[(1) - (3)].var).val = (yyvsp[(3) - (3)].val); 
                  fprintf(fi, "CDefine -> IDENTIFIER = CONSTANT\n");
                  if(if_declared((yyvsp[(1) - (3)].var).str) == 0){ //常量没有被定义,则可以入栈
                        // printf("push: %s (const val: %d)\n", $1.str, $1.val);
                        symtable_push((yyvsp[(1) - (3)].var).str, 1, (yyvsp[(1) - (3)].var).val);
                  }
                  Reduce("CDefine", 3);
            }
    break;

  case 18:
/* Line 1792 of yacc.c  */
#line 246 "Syntax.y"
    {
                  fprintf(fi, "VarDec -> VAR IdentiObj;\n");
                  Reduce("VarDec", 3);
            }
    break;

  case 19:
/* Line 1792 of yacc.c  */
#line 251 "Syntax.y"
    {
                  fprintf(fi, "IdentiObj -> IdentiObj, IDENTIFIER\n");
                  if(if_declared((yyvsp[(3) - (3)].var).str) == 0){ //变量没有被定义,则可以入栈
                        // printf("push: %s (var val: %d)\n", $3.str, -1);
                        symtable_push((yyvsp[(3) - (3)].var).str, 2, -1);
                  }
                  Reduce("IdentiObj", 3);
            }
    break;

  case 20:
/* Line 1792 of yacc.c  */
#line 259 "Syntax.y"
    {
                  fprintf(fi, "IdentiObj -> IDENTIFIER\n");
                  if(if_declared((yyvsp[(1) - (1)].var).str) == 0){ //变量没有被定义,则可以入栈
                        // printf("push: %s (var val: %d)\n", $1.str, -1);
                        symtable_push((yyvsp[(1) - (1)].var).str, 2, -1);
                  }
                  Reduce("IdentiObj", 1);
            }
    break;

  case 21:
/* Line 1792 of yacc.c  */
#line 268 "Syntax.y"
    {
                  fprintf(fi, "ProceDec -> ProceHead subProg;\n");
                  gen(OPR, 0, 0);
                  now_Level --;  //当前层数-1
                  symtable_pop();
                  addr = 2 + symtable_size();  //addr置为过程定义前的位置
                  Reduce("ProceDec", 3);
            }
    break;

  case 22:
/* Line 1792 of yacc.c  */
#line 276 "Syntax.y"
    {
                  fprintf(fi, "ProceDec -> ProceDec ProceHead subProg;\n");
                  gen(OPR, 0, 0);
                  now_Level --;  //当前层数-1
                  symtable_pop();
                  addr = 2 + symtable_size();  //addr置为过程定义前的位置
                  Reduce("ProceDec", 4);
            }
    break;

  case 23:
/* Line 1792 of yacc.c  */
#line 286 "Syntax.y"
    {
                  fprintf(fi, "ProceHead -> PROCEDURE IDENTIFIER;\n");
                  addr = 3;
                  if(if_declared((yyvsp[(2) - (3)].var).str) == 0){ //过程名没有被定义,则可以入栈
                        if(findpro((yyvsp[(2) - (3)].var).str) == -1){
                              // printf("push: %s (procedure)\n", $2.str);
                              symtable_push((yyvsp[(2) - (3)].var).str, 3, -2);  //入符号表栈
                        }
                        else{
                              printf("ProceHead error! Procedure '%s' has been declared!\n", (yyvsp[(2) - (3)].var).str);
                              exit(1);
                        }
                  }
                  now_Level ++;  //当前层数+1
                  // printf("display_top: %d, symtable_size: %d\n", display_stack[display_top], symtable_size());
                  Reduce("ProceHead", 3);
            }
    break;

  case 24:
/* Line 1792 of yacc.c  */
#line 306 "Syntax.y"
    {
                  fprintf(fi, "Statement -> AssignStm\n");
                  Reduce("Statement", 1);
            }
    break;

  case 25:
/* Line 1792 of yacc.c  */
#line 310 "Syntax.y"
    {
                  fprintf(fi, "Statement -> ComplexStm\n");
                  Reduce("Statement", 1);
            }
    break;

  case 26:
/* Line 1792 of yacc.c  */
#line 314 "Syntax.y"
    {
                  fprintf(fi, "Statement -> CondStm\n");
                  Reduce("Statement", 1);
            }
    break;

  case 27:
/* Line 1792 of yacc.c  */
#line 318 "Syntax.y"
    {
                  fprintf(fi, "Statement -> WhilelpStm\n");
                  Reduce("Statement", 1);
            }
    break;

  case 28:
/* Line 1792 of yacc.c  */
#line 322 "Syntax.y"
    {
                  fprintf(fi, "Statement -> CaseStm\n");
                  Reduce("Statement", 1);
            }
    break;

  case 29:
/* Line 1792 of yacc.c  */
#line 326 "Syntax.y"
    {
                  fprintf(fi, "Statement -> CallStm\n");
                  Reduce("Statement", 1);
            }
    break;

  case 30:
/* Line 1792 of yacc.c  */
#line 330 "Syntax.y"
    {
                  fprintf(fi, "Statement -> ReadStm\n");
                  Reduce("Statement", 1);
            }
    break;

  case 31:
/* Line 1792 of yacc.c  */
#line 334 "Syntax.y"
    {
                  fprintf(fi, "Statement -> WriteStm\n");
                  Reduce("Statement", 1);
            }
    break;

  case 32:
/* Line 1792 of yacc.c  */
#line 340 "Syntax.y"
    {
                  if(find_sign((yyvsp[(1) - (3)].var).str) == -1){ //变量没有被定义
                        printf("AssignStm error: '%s' has not been declared!\n", (yyvsp[(1) - (3)].var).str);
                        exit(1);
                  }
                  int temp = find_sign((yyvsp[(1) - (3)].var).str);
                  if(temp == -1){
                        printf("AssignStm: Cannot find the IDENTIFIER '%s'!\n", (yyvsp[(1) - (3)].var).str);
                  }
                  else{
                        symtable.index[temp].val = (yyvsp[(3) - (3)].val);
                  }
                  gen(STO, now_Level - symtable.index[temp].level, symtable.index[temp].addr);
                  fprintf(fi, "AssignStm -> IDENTIFIER := Expr\n");
                  Reduce("AssignStm", 3);
            }
    break;

  case 33:
/* Line 1792 of yacc.c  */
#line 357 "Syntax.y"
    {
                  fprintf(fi, "ComplexStm -> _BEGIN_ Statemt Statement END\n");
                  Reduce("ComplexStm", 3);
            }
    break;

  case 34:
/* Line 1792 of yacc.c  */
#line 362 "Syntax.y"
    {
                  fprintf(fi, "Statemt -> Statement;\n");
                  Reduce("Statemt", 2);
            }
    break;

  case 35:
/* Line 1792 of yacc.c  */
#line 366 "Syntax.y"
    {
                  fprintf(fi, "Statemt -> Statemt Statement;\n");
                  Reduce("Statemt", 3);
            }
    break;

  case 36:
/* Line 1792 of yacc.c  */
#line 372 "Syntax.y"
    {
                  Backpatch(bkpchpos[bkpchpos_top--], code_line);
                  fprintf(fi, "CondStm -> IF Condition THEN Statement\n");
                  Reduce("CondStm", 4);
            }
    break;

  case 37:
/* Line 1792 of yacc.c  */
#line 377 "Syntax.y"
    {
                  Backpatch(bkpchpos[bkpchpos_top--], code_line);
                  fprintf(fi, "Statement -> IF Condition THEN Statement ELSE Statement\n");
                  Reduce("CondStm", 6);
            }
    break;

  case 38:
/* Line 1792 of yacc.c  */
#line 383 "Syntax.y"
    {
                  bkpchpos[++bkpchpos_top] = code_line;  //填入回填栈等待回填
                  gen(JPC, 0, 0);
            }
    break;

  case 39:
/* Line 1792 of yacc.c  */
#line 388 "Syntax.y"
    {
                  Backpatch(bkpchpos[bkpchpos_top--], code_line+1);  //回填条件错误跳转的地址
                  bkpchpos[++bkpchpos_top] = code_line;  //填入回填栈等待回填
                  gen(JMP, 0, 0);
            }
    break;

  case 40:
/* Line 1792 of yacc.c  */
#line 394 "Syntax.y"
    {
                  if(strcmp((yyvsp[(2) - (3)].var).str, "=") == 0) gen(OPR, 0, 8);
                  if(strcmp((yyvsp[(2) - (3)].var).str, "#") == 0) gen(OPR, 0, 9);
                  if(strcmp((yyvsp[(2) - (3)].var).str, "<") == 0) gen(OPR, 0, 10);
                  if(strcmp((yyvsp[(2) - (3)].var).str, ">=") == 0) gen(OPR, 0, 11);
                  if(strcmp((yyvsp[(2) - (3)].var).str, ">") == 0) gen(OPR, 0, 12);
                  if(strcmp((yyvsp[(2) - (3)].var).str, "<=") == 0) gen(OPR, 0, 13);

                  fprintf(fi, "Condition -> Expr RELOP Expr\n");
                  Reduce("Condition", 3);
            }
    break;

  case 41:
/* Line 1792 of yacc.c  */
#line 405 "Syntax.y"
    {
                  gen(OPR, 0, 6);
                  fprintf(fi, "Condition -> ODD Expr\n");
                  Reduce("Condition", 2);
            }
    break;

  case 42:
/* Line 1792 of yacc.c  */
#line 411 "Syntax.y"
    {
                  (yyval.val) = (yyvsp[(1) - (3)].val) + (yyvsp[(3) - (3)].val);
                  gen(OPR, 0, 2);
                  fprintf(fi, "Expr -> Expr + Term\n");
                  Reduce("Expr", 3);
            }
    break;

  case 43:
/* Line 1792 of yacc.c  */
#line 417 "Syntax.y"
    {
                  (yyval.val) = (yyvsp[(1) - (3)].val) - (yyvsp[(3) - (3)].val);
                  gen(OPR, 0, 3);
                  fprintf(fi, "Expr -> Expr - Term\n");
                  Reduce("Expr", 3);
            }
    break;

  case 44:
/* Line 1792 of yacc.c  */
#line 423 "Syntax.y"
    {
                  (yyval.val) = (yyvsp[(2) - (2)].val);
                  fprintf(fi, "Expr -> +Term\n");
                  Reduce("Expr", 2);
            }
    break;

  case 45:
/* Line 1792 of yacc.c  */
#line 428 "Syntax.y"
    {
                  (yyval.val) = -(yyvsp[(2) - (2)].val);
                  gen(OPR, 0, 1);
                  fprintf(fi, "Expr -> -Term\n");
                  Reduce("Expr", 2);
            }
    break;

  case 46:
/* Line 1792 of yacc.c  */
#line 434 "Syntax.y"
    {
                  (yyval.val) = (yyvsp[(1) - (1)].val);
                  fprintf(fi, "Expr -> Term\n");
                  Reduce("Expr", 1);
            }
    break;

  case 47:
/* Line 1792 of yacc.c  */
#line 440 "Syntax.y"
    {
                  (yyval.val) = (yyvsp[(1) - (3)].val) * (yyvsp[(3) - (3)].val);
                  gen(OPR, 0, 4);
                  fprintf(fi, "Term -> Term * Factor\n");
                  Reduce("Term", 3);
            }
    break;

  case 48:
/* Line 1792 of yacc.c  */
#line 446 "Syntax.y"
    {
                  (yyval.val) = (yyvsp[(1) - (3)].val) / (yyvsp[(3) - (3)].val);
                  gen(OPR, 0, 5);
                  fprintf(fi, "Term -> Term / Factor\n");
                  Reduce("Term", 3);
            }
    break;

  case 49:
/* Line 1792 of yacc.c  */
#line 452 "Syntax.y"
    {
                  (yyval.val) = (yyvsp[(1) - (1)].val);
                  fprintf(fi, "Term -> Factor\n");
                  Reduce("Term", 1);
            }
    break;

  case 50:
/* Line 1792 of yacc.c  */
#line 458 "Syntax.y"
    {
                  if(find_sign((yyvsp[(1) - (1)].var).str) == -1){ //变量没有被定义
                        printf("Factor error: '%s' has not been declared!\n", (yyvsp[(1) - (1)].var).str);
                        exit(1);
                  }
                  if(symtable.index[find_sign((yyvsp[(1) - (1)].var).str)].kind == 1){  //如果是常量
                        (yyval.val) = symtable.index[find_sign((yyvsp[(1) - (1)].var).str)].val;
                        gen(LIT, 0, symtable.index[find_sign((yyvsp[(1) - (1)].var).str)].val);
                  }
                  if(symtable.index[find_sign((yyvsp[(1) - (1)].var).str)].kind == 2){  //如果是变量
                        (yyval.val) = symtable.index[find_sign((yyvsp[(1) - (1)].var).str)].val;
                        gen(LOD, now_Level - symtable.index[find_sign((yyvsp[(1) - (1)].var).str)].level, symtable.index[find_sign((yyvsp[(1) - (1)].var).str)].addr);
                  }
                  fprintf(fi, "Factor -> IDENTIFIER\n");
                  Reduce("Factor", 1);
            }
    break;

  case 51:
/* Line 1792 of yacc.c  */
#line 474 "Syntax.y"
    {
                  (yyval.val) = (yyvsp[(1) - (1)].val);
                  gen(LIT, 0, (yyvsp[(1) - (1)].val));
                  fprintf(fi, "Factor -> CONSTANT\n");                
                  Reduce("Factor", 1);
            }
    break;

  case 52:
/* Line 1792 of yacc.c  */
#line 480 "Syntax.y"
    {
                  (yyval.val) = (yyvsp[(2) - (3)].val); fprintf(fi, "Factor -> (Expr)\n");
                  Reduce("Factor", 3);
            }
    break;

  case 53:
/* Line 1792 of yacc.c  */
#line 485 "Syntax.y"
    {
                  gen(JMP, 0, whilepos[whiletop--]);
                  Backpatch(bkpchpos[bkpchpos_top--], code_line);
                  fprintf(fi, "WhilelpStm -> WHILE Condition DO Statement\n");
                  Reduce("WhilelpStm", 4);
            }
    break;

  case 54:
/* Line 1792 of yacc.c  */
#line 492 "Syntax.y"
    {
                  whilepos[++whiletop] = code_line;
            }
    break;

  case 55:
/* Line 1792 of yacc.c  */
#line 496 "Syntax.y"
    {
                  bkpchpos[++bkpchpos_top] = code_line;  //填入回填栈等待回填
                  gen(JPC, 0, 0);                 
            }
    break;

  case 56:
/* Line 1792 of yacc.c  */
#line 501 "Syntax.y"
    {
                  // Backpatch(bkpchpos[bkpchpos_top--], code_line);
                  code_line --;  //回撤最后一次LOD指令
                  fprintf(fi, "CaseStm -> CaseHead CaseBody ENDCASE\n");
                  Reduce("CaseStm", 3);
            }
    break;

  case 57:
/* Line 1792 of yacc.c  */
#line 508 "Syntax.y"
    {
                  if(find_sign((yyvsp[(2) - (3)].var).str) == -1){ //变量没有被定义
                        printf("CaseHead error: '%s' has not been declared!\n", (yyvsp[(2) - (3)].var).str);
                        exit(1);
                  }
                  caseid = strdup((yyvsp[(2) - (3)].var).str);
                  gen(LOD, now_Level - symtable.index[find_sign((yyvsp[(2) - (3)].var).str)].level, symtable.index[find_sign((yyvsp[(2) - (3)].var).str)].addr);
                  fprintf(fi, "CaseHead -> CASE IDENTIFIER COLON\n");
                  Reduce("CaseHead", 3);
            }
    break;

  case 58:
/* Line 1792 of yacc.c  */
#line 519 "Syntax.y"
    {
                  Backpatch(bkpchpos[bkpchpos_top--], code_line);
                  gen(LOD, now_Level - symtable.index[find_sign(caseid)].level, symtable.index[find_sign(caseid)].addr);
                  fprintf(fi, "CaseBody -> CaseBody CONSTANT COLON Statemt\n");
                  Reduce("CaseBody", 4);
            }
    break;

  case 59:
/* Line 1792 of yacc.c  */
#line 525 "Syntax.y"
    {
                  Backpatch(bkpchpos[bkpchpos_top--], code_line);
                  gen(LOD, now_Level - symtable.index[find_sign(caseid)].level, symtable.index[find_sign(caseid)].addr);
                  fprintf(fi, "CaseBody -> CONSTANT COLON Statemt\n");
                  Reduce("CaseBody", 3);
            }
    break;

  case 60:
/* Line 1792 of yacc.c  */
#line 532 "Syntax.y"
    {
                  gen(LIT, 0, (yyvsp[(1) - (1)].val));
                  gen(OPR, 0, 8);
                  bkpchpos[++bkpchpos_top] = code_line;  //填入回填栈等待回填
                  gen(JPC, 0, 0);
            }
    break;

  case 61:
/* Line 1792 of yacc.c  */
#line 539 "Syntax.y"
    {
                  if(findpro((yyvsp[(2) - (2)].var).str) == -1){
                        printf("Procedure '%s' not found!\n", (yyvsp[(2) - (2)].var).str);
                        exit(1);
                  }
                  else{
                        gen(CAL, now_Level - prostack[findpro((yyvsp[(2) - (2)].var).str)].l, prostack[findpro((yyvsp[(2) - (2)].var).str)].pos - 1);
                  }
                  fprintf(fi, "CallStm -> CALL IDENTIFIER\n");
                  Reduce("CallStm", 2);
            }
    break;

  case 62:
/* Line 1792 of yacc.c  */
#line 551 "Syntax.y"
    {
                  if(find_sign((yyvsp[(3) - (4)].var).str) == -1){ //变量没有被定义
                        printf("ReadStm error: '%s' has not been declared!\n", (yyvsp[(3) - (4)].var).str);
                        exit(1);
                  }
                  gen(OPR, 0, 16);
                  gen(STO, now_Level - symtable.index[find_sign((yyvsp[(3) - (4)].var).str)].level, symtable.index[find_sign((yyvsp[(3) - (4)].var).str)].addr);
                  fprintf(fi, "ReadStm -> READ(IdentiObj)\n");
                  Reduce("ReadStm", 4);
            }
    break;

  case 63:
/* Line 1792 of yacc.c  */
#line 562 "Syntax.y"
    {
                  gen(OPR, 0, 14);
                  gen(OPR, 0, 15);
                  fprintf(fi, "WriteStm -> WRITE(ExprObj)\n");
                  Reduce("WriteStm", 4);
            }
    break;

  case 64:
/* Line 1792 of yacc.c  */
#line 569 "Syntax.y"
    {
                  fprintf(fi, "ExprObj -> ExprObj, Expr\n");
                  Reduce("ExprObj", 3);
            }
    break;

  case 65:
/* Line 1792 of yacc.c  */
#line 573 "Syntax.y"
    {
                  fprintf(fi, "ExprObj -> Expr\n");
                  Reduce("ExprObj", 1);
            }
    break;


/* Line 1792 of yacc.c  */
#line 2312 "Syntax.tab.c"
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
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
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
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
      if (!yypact_value_is_default (yyn))
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

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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

#if !defined yyoverflow || YYERROR_VERBOSE
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
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
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


/* Line 2055 of yacc.c  */
#line 579 "Syntax.y"

int main(){
      fi = fopen("E:/CQ/RUC/Compiling Principle/Lab3/SynOutput.txt", "w+");
      fh = fopen("E:/CQ/RUC/Compiling Principle/Lab3/hierarchy.txt", "w+");
      fp = fopen("E:/CQ/RUC/Compiling Principle/Lab3/pcode.txt", "w+");
      stack_init();
      symtable_init();
      init();

      yyparse();

      // printf("top: name: %s, kind: %d, val: %d, level: %d, previous: %d, now_Level: %d\n", symtable_top().name, symtable_top().kind, symtable_top().val, symtable_top().level, symtable_top().previous, now_Level);
      
      OutputCode();

      return 1;
}

void init(){
      display_top ++;
      display_stack[display_top] = 1;
      
      // bkpchpos[++bkpchpos_top] = code_line;  //填入回填栈等待回填
      // gen(JMP, 0, 0);
      
}


int yyerror(char *s){
    printf("%s, (%d,%d)\n", s, row_num, col_num);
    // fprintf(stderr,"%s\n",s);
    return 1;
}


void left_insert(Node* parent, Node* son){
      parent -> left = son;
}

void right_insert(Node* node, Node* bro){
      node -> right = bro;
}

void stack_init(){
      stack.top = -1;
}

elem stack_pop(){
      int i;
      if(stack.top == -1){
            printf("Overflow stack pop size.\n");
            return 0;
      }
      return stack.index[stack.top --];
}

void stack_push(elem p){
      stack.index[++stack.top] = p;
}

int stack_empty(){
      return stack.top == -1;
}

int stack_size(){
      return stack.top + 1;
}

elem stack_top(){
      return stack.index[stack.top];
}

void PreOrderTravel(Node* T, int k){
      if(T==NULL) return;
      fprintf(fh, "%d:|\t", k);
      for(int i=0; i<k-1; i++) fprintf(fh, "|\t");
      fprintf(fh, "%s\n ",T->data);
      PreOrderTravel(T->left, k+1);
      PreOrderTravel(T->right, k);
}


void Process(char* temp){
      // printf("**%s**\n", temp);
      Node* tnode = (Node*)malloc(sizeof(Node));
      // tnode -> data = temp;
      strcpy(tnode -> data, temp);
      tnode -> left = NULL;
      tnode -> right = NULL;
      // printf("---%s---\n", tnode->data);
      stack_push(tnode);
}


void Reduce(char* name, int num){
      elem t[num];
      for (int i = 0; i < num; i++){
            t[i] = stack_pop();
      }
      Node* n = (Node*)malloc(sizeof(Node));
      // n -> data = name;
      strcpy(n -> data, name);
      n -> left = NULL;
      n -> right = NULL;
      left_insert(n, t[num-1]);
      for (int i = num-1; i > 0; i--){
            right_insert(t[i], t[i-1]);
      }
      stack_push(n);
}


/**********Lab3 Part**********/

void symtable_init(){
    symtable.top = 0;
}

void symtable_pop(){    //当前层所有符号出栈, display栈顶出栈
    int offset = display_stack[display_top] - 1;
    if(symtable.top == -1){
        printf("Overflow symtable pop size.\n");
        exit(1);
    }
    int i, j;
    for(i = symtable.top; i > offset; i--){
      symtable.index[symtable.top].name = NULL;
      symtable.index[symtable.top].kind = -1;
      symtable.index[symtable.top].level = -1;
      symtable.index[symtable.top].previous = -1;     
    }
    symtable.top = offset;
    symtable.index[symtable.top].previous = 0;
      //symtable.index[symtable.top].kind = 0;
      display_stack[display_top] = 0;  //display栈顶出栈
      display_top--;
    // return symtable.index[symtable.top --];
}


void symtable_push(char *id_name, int k, int v){ //标识符名字、类型、值
      int preoffset = symtable.top; //前一个符号在符号表中的位置
      symtable.top ++;
      symtable.index[symtable.top].name = id_name;
      symtable.index[symtable.top].kind = k;
      symtable.index[symtable.top].val = v;
      symtable.index[symtable.top].level = now_Level;
      symtable.index[symtable.top].previous = 0;
      if(k < 3){  //当前为变量或常量
            if(symtable.top > 0){
                  symtable.index[preoffset].previous = symtable.top;
            }
            if(k == 2){
                  symtable.index[symtable.top].addr = addr ++;
            }
      }
      if(k == 3){  //当前为过程, 写入过程栈, 记录该过程开始的code_line
            prostktop ++;
            prostack[prostktop].proname = strdup(id_name);
            prostack[prostktop].pos = code_line + 1;
            prostack[prostktop].l = now_Level;
      }
      // printf("------in push: %s, now_Level: %d, last previous: %d, addr: %d\n", symtable.index[symtable.top].name, now_Level, symtable.index[preoffset].previous, symtable.index[symtable.top].addr);
      // symtable.index[++symtable.top] = s;
}


int if_declared(char *sign_name){   //标识符是否被定义过
      int nowtable = display_stack[display_top];
      // printf("nowtable: %d  symtable.top: %d\n", nowtable, symtable.top);
      while(nowtable <= symtable.top){
            //变量名和过程名不能重名
            if(strcmp(symtable.index[nowtable].name, sign_name) == 0){
                  printf("Error! '%s' has been declared!\n", sign_name);
                  exit(1);
            }
            if(symtable.index[nowtable].previous == 0){
                  break;
            }
            nowtable ++;
      }
      return 0;
}


int find_sign(char *sign_name){  //查找标识符在符号栈中的位置
      int nowdistop = display_top;  //当前寻找的display顶
      int symbolpos;  //去符号栈中找的位置
      while(nowdistop > 0){  //display没有找完
            symbolpos = display_stack[nowdistop];
            while(symbolpos <= symtable.top){
                  if(strcmp(sign_name, symtable.index[symbolpos].name) == 0 && symtable.index[symbolpos].kind < 3){  //符号栈中此位置的变量和查找变量相同
                        return symbolpos;  //返回该符号位置
                  }
                  if(symtable.index[symbolpos].previous == 0){  //查找到当前过程底部
                        break;
                  }
                  symbolpos ++;
            }
            nowdistop --;  //查找上一层
      }
      return -1;  //没找到该符号
}

int findpro(char *pname){
      int i;
      for(i = 0; i <= prostktop; i++){
            if(strcmp(pname, prostack[i].proname) == 0){
                  return i;
            }
      }
      return -1;
}

// int symtable_empty(){
//    return symtable.top == -1;
// }

int symtable_size(){
    return symtable.top;
}

symbol symtable_top(){
      return symtable.index[symtable.top];
}


void gen(enum f f, int l, int a){  //生成类pcode代码放到code结构体数组中
    code[code_line].f = f;
    code[code_line].l = l;
    code[code_line].a = a;
    code_line ++;
}

void Backpatch(int p, int l){  //回填函数, 参数为回填位置和回填内容
      // printf("//////////// backpatch: %d %d\n", p, l);
      code[p].a = l;  //将第p条code的a域改为l
}


void OutputCode(){
      int i;
      for(i = 0; i < code_line; i++){
            fprintf(fp, "%s %d %d\n", fname[code[i].f], code[i].l, code[i].a);
      }
}

/**********Lab3 Part**********/
