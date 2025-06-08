/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 4 "compiler.y"

    #include "compiler_common.h"
    // #define YYDEBUG 1
    // int yydebug = 1;

    extern int yylineno;
    extern int yylex();
    extern FILE *yyin;

    int yylex_destroy ();
    void yyerror (char const *s)
    {
        printf("error:%d: %s\n", yylineno + 1, s);
    }

    extern int yylineno;
    extern int yylex();
    extern FILE *yyin;
    

    /* Define symbol table node */
    typedef struct symbol {
        int index;
        char *name;
        int mut;
        char *type;
        int addr;
        int lineno;
        char *func_sig;
        struct symbol *next;
        struct symbol *prev;
    } symbol_t;

    typedef struct symbol_table {
        int scope_level;
        symbol_t *element;
        struct symbol_table *next;
    } symbol_table_t;

    /* Current Symbol Table alway dummy_table->next */
    symbol_table_t *dummy_table;


    /* Record next address */
    int next_addr = -1;

    /* Symbol table function - you can add new functions if needed. */
    /* parameters and return type can be changed */
    static void create_symbol();
    static void insert_symbol(char *name, int mut, char *type, char *func_sig);
    symbol_t* lookup_symbol(char *name);
    static void dump_symbol();

    /* Global variables */
    bool HAS_ERROR = false;


#line 129 "y.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    LET = 258,                     /* LET  */
    MUT = 259,                     /* MUT  */
    NEWLINE = 260,                 /* NEWLINE  */
    INT = 261,                     /* INT  */
    FLOAT = 262,                   /* FLOAT  */
    BOOL = 263,                    /* BOOL  */
    STR = 264,                     /* STR  */
    TRUE = 265,                    /* TRUE  */
    FALSE = 266,                   /* FALSE  */
    GEQ = 267,                     /* GEQ  */
    LEQ = 268,                     /* LEQ  */
    EQL = 269,                     /* EQL  */
    NEQ = 270,                     /* NEQ  */
    LOR = 271,                     /* LOR  */
    LAND = 272,                    /* LAND  */
    ADD_ASSIGN = 273,              /* ADD_ASSIGN  */
    SUB_ASSIGN = 274,              /* SUB_ASSIGN  */
    MUL_ASSIGN = 275,              /* MUL_ASSIGN  */
    DIV_ASSIGN = 276,              /* DIV_ASSIGN  */
    REM_ASSIGN = 277,              /* REM_ASSIGN  */
    IF = 278,                      /* IF  */
    ELSE = 279,                    /* ELSE  */
    FOR = 280,                     /* FOR  */
    WHILE = 281,                   /* WHILE  */
    LOOP = 282,                    /* LOOP  */
    PRINT = 283,                   /* PRINT  */
    PRINTLN = 284,                 /* PRINTLN  */
    FUNC = 285,                    /* FUNC  */
    RETURN = 286,                  /* RETURN  */
    BREAK = 287,                   /* BREAK  */
    ARROW = 288,                   /* ARROW  */
    AS = 289,                      /* AS  */
    IN = 290,                      /* IN  */
    DOTDOT = 291,                  /* DOTDOT  */
    RSHIFT = 292,                  /* RSHIFT  */
    LSHIFT = 293,                  /* LSHIFT  */
    INT_LIT = 294,                 /* INT_LIT  */
    FLOAT_LIT = 295,               /* FLOAT_LIT  */
    STRING_LIT = 296,              /* STRING_LIT  */
    ID = 297,                      /* ID  */
    IFX = 298,                     /* IFX  */
    UMINUS = 299                   /* UMINUS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define LET 258
#define MUT 259
#define NEWLINE 260
#define INT 261
#define FLOAT 262
#define BOOL 263
#define STR 264
#define TRUE 265
#define FALSE 266
#define GEQ 267
#define LEQ 268
#define EQL 269
#define NEQ 270
#define LOR 271
#define LAND 272
#define ADD_ASSIGN 273
#define SUB_ASSIGN 274
#define MUL_ASSIGN 275
#define DIV_ASSIGN 276
#define REM_ASSIGN 277
#define IF 278
#define ELSE 279
#define FOR 280
#define WHILE 281
#define LOOP 282
#define PRINT 283
#define PRINTLN 284
#define FUNC 285
#define RETURN 286
#define BREAK 287
#define ARROW 288
#define AS 289
#define IN 290
#define DOTDOT 291
#define RSHIFT 292
#define LSHIFT 293
#define INT_LIT 294
#define FLOAT_LIT 295
#define STRING_LIT 296
#define ID 297
#define IFX 298
#define UMINUS 299

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 73 "compiler.y"

    int i_val;
    float f_val;
    char *s_val;
    /* ... */

#line 277 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_LET = 3,                        /* LET  */
  YYSYMBOL_MUT = 4,                        /* MUT  */
  YYSYMBOL_NEWLINE = 5,                    /* NEWLINE  */
  YYSYMBOL_INT = 6,                        /* INT  */
  YYSYMBOL_FLOAT = 7,                      /* FLOAT  */
  YYSYMBOL_BOOL = 8,                       /* BOOL  */
  YYSYMBOL_STR = 9,                        /* STR  */
  YYSYMBOL_TRUE = 10,                      /* TRUE  */
  YYSYMBOL_FALSE = 11,                     /* FALSE  */
  YYSYMBOL_GEQ = 12,                       /* GEQ  */
  YYSYMBOL_LEQ = 13,                       /* LEQ  */
  YYSYMBOL_EQL = 14,                       /* EQL  */
  YYSYMBOL_NEQ = 15,                       /* NEQ  */
  YYSYMBOL_LOR = 16,                       /* LOR  */
  YYSYMBOL_LAND = 17,                      /* LAND  */
  YYSYMBOL_ADD_ASSIGN = 18,                /* ADD_ASSIGN  */
  YYSYMBOL_SUB_ASSIGN = 19,                /* SUB_ASSIGN  */
  YYSYMBOL_MUL_ASSIGN = 20,                /* MUL_ASSIGN  */
  YYSYMBOL_DIV_ASSIGN = 21,                /* DIV_ASSIGN  */
  YYSYMBOL_REM_ASSIGN = 22,                /* REM_ASSIGN  */
  YYSYMBOL_IF = 23,                        /* IF  */
  YYSYMBOL_ELSE = 24,                      /* ELSE  */
  YYSYMBOL_FOR = 25,                       /* FOR  */
  YYSYMBOL_WHILE = 26,                     /* WHILE  */
  YYSYMBOL_LOOP = 27,                      /* LOOP  */
  YYSYMBOL_PRINT = 28,                     /* PRINT  */
  YYSYMBOL_PRINTLN = 29,                   /* PRINTLN  */
  YYSYMBOL_FUNC = 30,                      /* FUNC  */
  YYSYMBOL_RETURN = 31,                    /* RETURN  */
  YYSYMBOL_BREAK = 32,                     /* BREAK  */
  YYSYMBOL_ARROW = 33,                     /* ARROW  */
  YYSYMBOL_AS = 34,                        /* AS  */
  YYSYMBOL_IN = 35,                        /* IN  */
  YYSYMBOL_DOTDOT = 36,                    /* DOTDOT  */
  YYSYMBOL_RSHIFT = 37,                    /* RSHIFT  */
  YYSYMBOL_LSHIFT = 38,                    /* LSHIFT  */
  YYSYMBOL_INT_LIT = 39,                   /* INT_LIT  */
  YYSYMBOL_FLOAT_LIT = 40,                 /* FLOAT_LIT  */
  YYSYMBOL_STRING_LIT = 41,                /* STRING_LIT  */
  YYSYMBOL_ID = 42,                        /* ID  */
  YYSYMBOL_IFX = 43,                       /* IFX  */
  YYSYMBOL_44_ = 44,                       /* '!'  */
  YYSYMBOL_45_ = 45,                       /* '>'  */
  YYSYMBOL_46_ = 46,                       /* '<'  */
  YYSYMBOL_47_ = 47,                       /* '+'  */
  YYSYMBOL_48_ = 48,                       /* '-'  */
  YYSYMBOL_49_ = 49,                       /* '*'  */
  YYSYMBOL_50_ = 50,                       /* '/'  */
  YYSYMBOL_51_ = 51,                       /* '%'  */
  YYSYMBOL_UMINUS = 52,                    /* UMINUS  */
  YYSYMBOL_53_ = 53,                       /* '('  */
  YYSYMBOL_54_ = 54,                       /* ')'  */
  YYSYMBOL_55_ = 55,                       /* '{'  */
  YYSYMBOL_56_ = 56,                       /* '}'  */
  YYSYMBOL_57_ = 57,                       /* '"'  */
  YYSYMBOL_58_ = 58,                       /* '['  */
  YYSYMBOL_59_ = 59,                       /* ']'  */
  YYSYMBOL_60_ = 60,                       /* ','  */
  YYSYMBOL_61_ = 61,                       /* ';'  */
  YYSYMBOL_62_ = 62,                       /* ':'  */
  YYSYMBOL_63_ = 63,                       /* '='  */
  YYSYMBOL_64_ = 64,                       /* '&'  */
  YYSYMBOL_YYACCEPT = 65,                  /* $accept  */
  YYSYMBOL_Program = 66,                   /* Program  */
  YYSYMBOL_67_1 = 67,                      /* $@1  */
  YYSYMBOL_GlobalStatementList = 68,       /* GlobalStatementList  */
  YYSYMBOL_GlobalStatement = 69,           /* GlobalStatement  */
  YYSYMBOL_FunctionDeclStmt = 70,          /* FunctionDeclStmt  */
  YYSYMBOL_71_2 = 71,                      /* $@2  */
  YYSYMBOL_StmtList = 72,                  /* StmtList  */
  YYSYMBOL_Stmt = 73,                      /* Stmt  */
  YYSYMBOL_Block = 74,                     /* Block  */
  YYSYMBOL_75_3 = 75,                      /* $@3  */
  YYSYMBOL_Expr = 76,                      /* Expr  */
  YYSYMBOL_ArrayElements = 77,             /* ArrayElements  */
  YYSYMBOL_PrintStmt = 78,                 /* PrintStmt  */
  YYSYMBOL_DeclarationStmt = 79,           /* DeclarationStmt  */
  YYSYMBOL_AssignmentStmt = 80,            /* AssignmentStmt  */
  YYSYMBOL_IfStmt = 81,                    /* IfStmt  */
  YYSYMBOL_WhileStmt = 82,                 /* WhileStmt  */
  YYSYMBOL_Type = 83,                      /* Type  */
  YYSYMBOL_PrintType = 84,                 /* PrintType  */
  YYSYMBOL_MutType = 85,                   /* MutType  */
  YYSYMBOL_AssignmentOperatorType = 86,    /* AssignmentOperatorType  */
  YYSYMBOL_FunctionArguments = 87          /* FunctionArguments  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

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


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
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
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   409

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  65
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  23
/* YYNRULES -- Number of rules.  */
#define YYNRULES  76
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  137

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   299


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    44,    57,     2,     2,    51,    64,     2,
      53,    54,    49,    47,    60,    48,     2,    50,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    62,    61,
      46,    63,    45,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    58,     2,    59,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    55,     2,    56,     2,     2,     2,     2,
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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    52
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   125,   125,   125,   129,   130,   134,   135,   139,   139,
     148,   149,   153,   154,   155,   156,   157,   158,   162,   162,
     166,   180,   184,   188,   192,   196,   200,   204,   207,   214,
     218,   222,   223,   227,   231,   235,   239,   243,   255,   264,
     268,   272,   282,   293,   304,   314,   325,   335,   343,   344,
     348,   354,   355,   356,   360,   380,   381,   385,   389,   390,
     391,   392,   393,   394,   398,   399,   403,   404,   408,   409,
     410,   411,   412,   413,   417,   422,   423
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "LET", "MUT",
  "NEWLINE", "INT", "FLOAT", "BOOL", "STR", "TRUE", "FALSE", "GEQ", "LEQ",
  "EQL", "NEQ", "LOR", "LAND", "ADD_ASSIGN", "SUB_ASSIGN", "MUL_ASSIGN",
  "DIV_ASSIGN", "REM_ASSIGN", "IF", "ELSE", "FOR", "WHILE", "LOOP",
  "PRINT", "PRINTLN", "FUNC", "RETURN", "BREAK", "ARROW", "AS", "IN",
  "DOTDOT", "RSHIFT", "LSHIFT", "INT_LIT", "FLOAT_LIT", "STRING_LIT", "ID",
  "IFX", "'!'", "'>'", "'<'", "'+'", "'-'", "'*'", "'/'", "'%'", "UMINUS",
  "'('", "')'", "'{'", "'}'", "'\"'", "'['", "']'", "','", "';'", "':'",
  "'='", "'&'", "$accept", "Program", "$@1", "GlobalStatementList",
  "GlobalStatement", "FunctionDeclStmt", "$@2", "StmtList", "Stmt",
  "Block", "$@3", "Expr", "ArrayElements", "PrintStmt", "DeclarationStmt",
  "AssignmentStmt", "IfStmt", "WhileStmt", "Type", "PrintType", "MutType",
  "AssignmentOperatorType", "FunctionArguments", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-74)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-64)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -74,     5,    12,   -74,   -74,   -17,    12,   -74,   -74,   -14,
     -74,     3,   -74,   -74,   -74,     6,    28,    14,   -53,    -3,
     -74,   -74,   -74,     6,    49,    10,    26,   -74,   -74,   -74,
     -74,    19,    49,    49,    49,    16,    49,   187,   -74,   -74,
     -74,    35,   340,    44,   241,    33,   -74,   295,   -16,    49,
      49,    49,    49,    49,    49,     6,    49,    49,    49,    49,
      49,    49,    49,    49,    49,   -74,   -74,    36,   -74,   -74,
     -74,    49,   358,   358,   358,   358,   313,   340,   -74,    99,
      99,   358,   358,     4,     4,    44,    44,    44,    43,   -74,
     295,    92,    49,    49,   -74,   -74,    29,   -74,   -74,   -74,
     -74,   -74,   -74,   -74,   -74,    47,   -74,    68,   214,   214,
     -74,   -74,   -74,   -74,   -74,   -74,    49,    49,    13,    85,
     -74,    67,   268,     6,    49,    10,   -74,    50,   -45,   107,
     -74,   -74,   -74,    49,   -74,   147,   -74
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     0,     1,     7,     0,     3,     5,     6,     0,
       4,    76,    58,    59,    60,    63,     0,     0,     0,     0,
      61,    75,     8,    63,     0,     0,     0,    25,    26,    21,
      22,    20,     0,     0,     0,     0,     0,     0,    18,     9,
      74,     0,    30,    29,     0,     0,    24,    49,     0,     0,
       0,     0,     0,     0,     0,    63,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    62,    11,     0,    31,    23,
      27,     0,    41,    42,    43,    44,    40,    39,    47,    38,
      37,    45,    46,    35,    36,    32,    33,    34,     0,    28,
      48,    67,     0,     0,    64,    65,     0,    19,    10,    15,
      12,    13,    14,    16,    17,     0,    66,     0,     0,     0,
      69,    70,    71,    72,    73,    68,     0,     0,     0,    55,
      57,     0,     0,    63,     0,     0,    54,     0,     0,     0,
      56,    50,    52,     0,    53,     0,    51
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -74,   -74,   -74,   -74,   119,   -74,   -74,   -74,   -74,   -73,
     -74,   -30,   -74,   -74,   -74,   -74,   -74,   -74,   -15,   -74,
     -74,   -74,   -74
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     1,     2,     6,     7,     8,    25,    88,    98,    39,
      66,    37,    48,   100,   101,   102,   103,   104,    17,   105,
     107,   116,    18
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      19,    22,    42,    43,    44,     3,    47,    23,    26,    12,
      13,    14,    12,    13,    14,    99,   132,     4,   133,    72,
      73,    74,    75,    76,    77,     9,    79,    80,    81,    82,
      83,    84,    85,    86,    87,   119,   120,    20,    55,    11,
      78,    90,     5,    70,    71,   -63,    91,   110,   111,   112,
     113,   114,   130,    62,    63,    64,    21,    45,    24,    27,
      28,    15,   108,   109,    15,    38,    92,    16,    40,    93,
      16,    94,    95,    46,    67,   123,   124,    41,    55,    49,
      50,    51,    52,    53,    54,    96,   121,   122,    29,    30,
      69,    31,   115,    32,   129,    89,   106,    33,    38,    97,
     117,    55,    34,   135,    56,    57,    35,    36,   128,   125,
     118,   131,    58,    59,    60,    61,    62,    63,    64,    49,
      50,    51,    52,    53,    54,    10,     0,     0,   126,     0,
       0,     0,     0,    55,     0,     0,     0,     0,     0,     0,
       0,    55,     0,     0,    56,    57,    60,    61,    62,    63,
      64,     0,    58,    59,    60,    61,    62,    63,    64,    49,
      50,    51,    52,    53,    54,     0,     0,     0,   134,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    55,     0,     0,    56,    57,     0,     0,     0,     0,
       0,     0,    58,    59,    60,    61,    62,    63,    64,    49,
      50,    51,    52,    53,    54,     0,     0,     0,   136,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    55,     0,     0,    56,    57,    49,    50,    51,    52,
      53,    54,    58,    59,    60,    61,    62,    63,    64,     0,
       0,     0,     0,     0,     0,     0,    65,     0,    55,     0,
       0,    56,    57,    49,    50,    51,    52,    53,    54,    58,
      59,    60,    61,    62,    63,    64,     0,     0,     0,    38,
       0,     0,     0,     0,     0,    55,     0,     0,    56,    57,
      49,    50,    51,    52,    53,    54,    58,    59,    60,    61,
      62,    63,    64,     0,     0,    68,     0,     0,     0,     0,
       0,     0,    55,     0,     0,    56,    57,    49,    50,    51,
      52,    53,    54,    58,    59,    60,    61,    62,    63,    64,
       0,     0,   127,     0,     0,    49,    50,    51,    52,    55,
      54,     0,    56,    57,     0,     0,     0,     0,     0,     0,
      58,    59,    60,    61,    62,    63,    64,    55,     0,     0,
      56,    57,    49,    50,    51,    52,     0,     0,    58,    59,
      60,    61,    62,    63,    64,     0,     0,     0,     0,     0,
     -64,   -64,   -64,   -64,    55,     0,     0,    56,    57,     0,
       0,     0,     0,     0,     0,    58,    59,    60,    61,    62,
      63,    64,    55,     0,     0,    56,    57,     0,     0,     0,
       0,     0,     0,   -64,   -64,    60,    61,    62,    63,    64
};

static const yytype_int16 yycheck[] =
{
      15,    54,    32,    33,    34,     0,    36,    60,    23,     6,
       7,     8,     6,     7,     8,    88,    61,     5,    63,    49,
      50,    51,    52,    53,    54,    42,    56,    57,    58,    59,
      60,    61,    62,    63,    64,   108,   109,     9,    34,    53,
      55,    71,    30,    59,    60,    42,     3,    18,    19,    20,
      21,    22,   125,    49,    50,    51,    42,    41,    61,    10,
      11,    58,    92,    93,    58,    55,    23,    64,    42,    26,
      64,    28,    29,    57,    39,    62,    63,    58,    34,    12,
      13,    14,    15,    16,    17,    42,   116,   117,    39,    40,
      57,    42,    63,    44,   124,    59,     4,    48,    55,    56,
      53,    34,    53,   133,    37,    38,    57,    58,   123,    24,
      42,    61,    45,    46,    47,    48,    49,    50,    51,    12,
      13,    14,    15,    16,    17,     6,    -1,    -1,    61,    -1,
      -1,    -1,    -1,    34,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    34,    -1,    -1,    37,    38,    47,    48,    49,    50,
      51,    -1,    45,    46,    47,    48,    49,    50,    51,    12,
      13,    14,    15,    16,    17,    -1,    -1,    -1,    61,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    34,    -1,    -1,    37,    38,    -1,    -1,    -1,    -1,
      -1,    -1,    45,    46,    47,    48,    49,    50,    51,    12,
      13,    14,    15,    16,    17,    -1,    -1,    -1,    61,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    34,    -1,    -1,    37,    38,    12,    13,    14,    15,
      16,    17,    45,    46,    47,    48,    49,    50,    51,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    59,    -1,    34,    -1,
      -1,    37,    38,    12,    13,    14,    15,    16,    17,    45,
      46,    47,    48,    49,    50,    51,    -1,    -1,    -1,    55,
      -1,    -1,    -1,    -1,    -1,    34,    -1,    -1,    37,    38,
      12,    13,    14,    15,    16,    17,    45,    46,    47,    48,
      49,    50,    51,    -1,    -1,    54,    -1,    -1,    -1,    -1,
      -1,    -1,    34,    -1,    -1,    37,    38,    12,    13,    14,
      15,    16,    17,    45,    46,    47,    48,    49,    50,    51,
      -1,    -1,    54,    -1,    -1,    12,    13,    14,    15,    34,
      17,    -1,    37,    38,    -1,    -1,    -1,    -1,    -1,    -1,
      45,    46,    47,    48,    49,    50,    51,    34,    -1,    -1,
      37,    38,    12,    13,    14,    15,    -1,    -1,    45,    46,
      47,    48,    49,    50,    51,    -1,    -1,    -1,    -1,    -1,
      12,    13,    14,    15,    34,    -1,    -1,    37,    38,    -1,
      -1,    -1,    -1,    -1,    -1,    45,    46,    47,    48,    49,
      50,    51,    34,    -1,    -1,    37,    38,    -1,    -1,    -1,
      -1,    -1,    -1,    45,    46,    47,    48,    49,    50,    51
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    66,    67,     0,     5,    30,    68,    69,    70,    42,
      69,    53,     6,     7,     8,    58,    64,    83,    87,    83,
       9,    42,    54,    60,    61,    71,    83,    10,    11,    39,
      40,    42,    44,    48,    53,    57,    58,    76,    55,    74,
      42,    58,    76,    76,    76,    41,    57,    76,    77,    12,
      13,    14,    15,    16,    17,    34,    37,    38,    45,    46,
      47,    48,    49,    50,    51,    59,    75,    39,    54,    57,
      59,    60,    76,    76,    76,    76,    76,    76,    83,    76,
      76,    76,    76,    76,    76,    76,    76,    76,    72,    59,
      76,     3,    23,    26,    28,    29,    42,    56,    73,    74,
      78,    79,    80,    81,    82,    84,     4,    85,    76,    76,
      18,    19,    20,    21,    22,    63,    86,    53,    42,    74,
      74,    76,    76,    62,    63,    24,    61,    54,    83,    76,
      74,    61,    61,    63,    61,    76,    61
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    65,    67,    66,    68,    68,    69,    69,    71,    70,
      72,    72,    73,    73,    73,    73,    73,    73,    75,    74,
      76,    76,    76,    76,    76,    76,    76,    76,    76,    76,
      76,    76,    76,    76,    76,    76,    76,    76,    76,    76,
      76,    76,    76,    76,    76,    76,    76,    76,    77,    77,
      78,    79,    79,    79,    80,    81,    81,    82,    83,    83,
      83,    83,    83,    83,    84,    84,    85,    85,    86,    86,
      86,    86,    86,    86,    87,    87,    87
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     2,     1,     1,     1,     0,     7,
       2,     0,     1,     1,     1,     1,     1,     1,     0,     4,
       1,     1,     1,     3,     2,     1,     1,     3,     4,     2,
       2,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     1,
       5,     8,     6,     6,     4,     3,     5,     3,     1,     1,
       1,     2,     5,     0,     1,     1,     1,     0,     1,     1,
       1,     1,     1,     1,     4,     2,     0
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
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
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* $@1: %empty  */
#line 125 "compiler.y"
      { create_symbol(); }
#line 1488 "y.tab.c"
    break;

  case 3: /* Program: $@1 GlobalStatementList  */
#line 125 "compiler.y"
                                               { dump_symbol(); }
#line 1494 "y.tab.c"
    break;

  case 8: /* $@2: %empty  */
#line 139 "compiler.y"
                                        { 
        printf("func: %s\n", (yyvsp[-3].s_val)); 
        char *sig = (char *)malloc(strlen((yyvsp[-1].s_val)) + 10);
        sprintf(sig, "(%s)V", (yyvsp[-1].s_val));
        insert_symbol((yyvsp[-3].s_val), -1, "func", sig);
    }
#line 1505 "y.tab.c"
    break;

  case 18: /* $@3: %empty  */
#line 162 "compiler.y"
          { create_symbol(); }
#line 1511 "y.tab.c"
    break;

  case 19: /* Block: '{' $@3 StmtList '}'  */
#line 162 "compiler.y"
                                            { dump_symbol(); }
#line 1517 "y.tab.c"
    break;

  case 20: /* Expr: ID  */
#line 166 "compiler.y"
         {
        symbol_t *tmp = lookup_symbol((yyvsp[0].s_val));
        if (tmp == NULL) {
            char msg[100];
            sprintf(msg, "undefined: %s", (yyvsp[0].s_val));
            yyerror(msg);
            HAS_ERROR = TRUE;
            (yyval.s_val) = "undefined";
        } else {
            printf("IDENT (name=%s, address=%d)\n", (yyvsp[0].s_val), tmp->addr);
            (yyval.s_val) = tmp->type; 
        }
        
    }
#line 1536 "y.tab.c"
    break;

  case 21: /* Expr: INT_LIT  */
#line 180 "compiler.y"
              {
        printf("INT_LIT %d\n", (yyvsp[0].i_val));
        (yyval.s_val) = "i32";
    }
#line 1545 "y.tab.c"
    break;

  case 22: /* Expr: FLOAT_LIT  */
#line 184 "compiler.y"
                {
        printf("FLOAT_LIT %f\n", (yyvsp[0].f_val));
        (yyval.s_val) = "f32";
    }
#line 1554 "y.tab.c"
    break;

  case 23: /* Expr: '"' STRING_LIT '"'  */
#line 188 "compiler.y"
                         {
        printf("STRING_LIT \"%s\"\n", (yyvsp[-1].s_val));
        (yyval.s_val) = "str";
    }
#line 1563 "y.tab.c"
    break;

  case 24: /* Expr: '"' '"'  */
#line 192 "compiler.y"
              {
        printf("STRING_LIT \"\"\n");
        (yyval.s_val) = "str";
    }
#line 1572 "y.tab.c"
    break;

  case 25: /* Expr: TRUE  */
#line 196 "compiler.y"
           {
        printf("bool TRUE\n");
        (yyval.s_val) = "bool";
    }
#line 1581 "y.tab.c"
    break;

  case 26: /* Expr: FALSE  */
#line 200 "compiler.y"
            {
        printf("bool FALSE\n");
        (yyval.s_val) = "bool";
    }
#line 1590 "y.tab.c"
    break;

  case 27: /* Expr: '[' ArrayElements ']'  */
#line 204 "compiler.y"
                            {
        (yyval.s_val) = (yyvsp[-1].s_val);
    }
#line 1598 "y.tab.c"
    break;

  case 28: /* Expr: ID '[' INT_LIT ']'  */
#line 207 "compiler.y"
                         {
        symbol_t *tmp = lookup_symbol((yyvsp[-3].s_val));
        printf("IDENT (name=%s, address=%d)\n", (yyvsp[-3].s_val), tmp->addr);
        (yyval.s_val) = tmp->type; 
        printf("INT_LIT %d\n", (yyvsp[-1].i_val));
        (yyval.s_val) = "array";
    }
#line 1610 "y.tab.c"
    break;

  case 29: /* Expr: '-' Expr  */
#line 214 "compiler.y"
                            {
        printf("NEG\n");
        (yyval.s_val) = (yyvsp[0].s_val);
    }
#line 1619 "y.tab.c"
    break;

  case 30: /* Expr: '!' Expr  */
#line 218 "compiler.y"
               {
        printf("NOT\n");
        (yyval.s_val) = (yyvsp[0].s_val);
    }
#line 1628 "y.tab.c"
    break;

  case 31: /* Expr: '(' Expr ')'  */
#line 222 "compiler.y"
                   { (yyval.s_val) = (yyvsp[-1].s_val); }
#line 1634 "y.tab.c"
    break;

  case 32: /* Expr: Expr '*' Expr  */
#line 223 "compiler.y"
                    {
        printf("MUL\n");
        (yyval.s_val) = (strcmp((yyvsp[-2].s_val), "f32") == 0 || strcmp((yyvsp[0].s_val), "f32") == 0) ? "f32" : "i32";
    }
#line 1643 "y.tab.c"
    break;

  case 33: /* Expr: Expr '/' Expr  */
#line 227 "compiler.y"
                    {
        printf("DIV\n");
        (yyval.s_val) = (strcmp((yyvsp[-2].s_val), "f32") == 0 || strcmp((yyvsp[0].s_val), "f32") == 0) ? "f32" : "i32";
    }
#line 1652 "y.tab.c"
    break;

  case 34: /* Expr: Expr '%' Expr  */
#line 231 "compiler.y"
                    {
        printf("REM\n");
        (yyval.s_val) = (strcmp((yyvsp[-2].s_val), "f32") == 0 || strcmp((yyvsp[0].s_val), "f32") == 0) ? "f32" : "i32";
    }
#line 1661 "y.tab.c"
    break;

  case 35: /* Expr: Expr '+' Expr  */
#line 235 "compiler.y"
                    {
        printf("ADD\n");
        (yyval.s_val) = (strcmp((yyvsp[-2].s_val), "f32") == 0 || strcmp((yyvsp[0].s_val), "f32") == 0) ? "f32" : "i32";
    }
#line 1670 "y.tab.c"
    break;

  case 36: /* Expr: Expr '-' Expr  */
#line 239 "compiler.y"
                    {
        printf("SUB\n");
        (yyval.s_val) = (strcmp((yyvsp[-2].s_val), "f32") == 0 || strcmp((yyvsp[0].s_val), "f32") == 0) ? "f32" : "i32";
    }
#line 1679 "y.tab.c"
    break;

  case 37: /* Expr: Expr LSHIFT Expr  */
#line 243 "compiler.y"
                       {
        
        if (strcmp((yyvsp[-2].s_val), "i32") != 0 || strcmp((yyvsp[0].s_val), "i32") != 0) {
            char msg[100];
            sprintf(msg, "invalid operation: LSHIFT (mismatched types %s and %s)", (yyvsp[-2].s_val), (yyvsp[0].s_val));
            yyerror(msg);
            HAS_ERROR = true;
        }
        printf("LSHIFT\n");
        (yyval.s_val) = (yyvsp[-2].s_val);
        
    }
#line 1696 "y.tab.c"
    break;

  case 38: /* Expr: Expr RSHIFT Expr  */
#line 255 "compiler.y"
                       {
        printf("RSHIFT\n");
        if (strcmp((yyvsp[-2].s_val), "i32") == 0 && strcmp((yyvsp[0].s_val), "i32") == 0) {
            (yyval.s_val) = (yyvsp[-2].s_val);
        } else {
            char msg[100];
            sprintf(msg, "invalid operation: RSHIFT (mismatched types %s and %s)\n", (yyvsp[-2].s_val), (yyvsp[0].s_val));
        }
    }
#line 1710 "y.tab.c"
    break;

  case 39: /* Expr: Expr LAND Expr  */
#line 264 "compiler.y"
                     {
        printf("LAND\n");
        (yyval.s_val) = "bool";
    }
#line 1719 "y.tab.c"
    break;

  case 40: /* Expr: Expr LOR Expr  */
#line 268 "compiler.y"
                    {
        printf("LOR\n");
        (yyval.s_val) = "bool";
    }
#line 1728 "y.tab.c"
    break;

  case 41: /* Expr: Expr GEQ Expr  */
#line 272 "compiler.y"
                    {
        if (strcmp((yyvsp[-2].s_val), (yyvsp[0].s_val)) != 0) {
            char msg[100];
            sprintf(msg, "invalid operation: GEQ (mismatched types %s and %s)", (yyvsp[-2].s_val), (yyvsp[0].s_val));
            yyerror(msg);
            HAS_ERROR = true;
        }
        printf("GEQ\n");
        (yyval.s_val) = "bool";
    }
#line 1743 "y.tab.c"
    break;

  case 42: /* Expr: Expr LEQ Expr  */
#line 282 "compiler.y"
                    {
        if (strcmp((yyvsp[-2].s_val), (yyvsp[0].s_val)) != 0) {
            char msg[100];
            sprintf(msg, "invalid operation: LEQ (mismatched types %s and %s)", (yyvsp[-2].s_val), (yyvsp[0].s_val));
            yyerror(msg);
            HAS_ERROR = true;
        }
        printf("LEQ\n");
        (yyval.s_val) = "bool";
    }
#line 1758 "y.tab.c"
    break;

  case 43: /* Expr: Expr EQL Expr  */
#line 293 "compiler.y"
                    {
        if (strcmp((yyvsp[-2].s_val), (yyvsp[0].s_val)) != 0) {
            char msg[100];
            sprintf(msg, "invalid operation: EQL (mismatched types %s and %s)", (yyvsp[-2].s_val), (yyvsp[0].s_val));
            yyerror(msg);
            HAS_ERROR = true;
        }
        printf("EQL\n");
        (yyval.s_val) = "bool";
    }
#line 1773 "y.tab.c"
    break;

  case 44: /* Expr: Expr NEQ Expr  */
#line 304 "compiler.y"
                    {
        if (strcmp((yyvsp[-2].s_val), (yyvsp[0].s_val)) != 0) {
            char msg[100];
            sprintf(msg, "invalid operation: NEQ (mismatched types %s and %s)", (yyvsp[-2].s_val), (yyvsp[0].s_val));
            yyerror(msg);
            HAS_ERROR = true;
        }
        printf("NEQ\n");
        (yyval.s_val) = "bool";
    }
#line 1788 "y.tab.c"
    break;

  case 45: /* Expr: Expr '>' Expr  */
#line 314 "compiler.y"
                    {
        if (strcmp((yyvsp[-2].s_val), (yyvsp[0].s_val)) != 0) {
            char msg[100];
            sprintf(msg, "invalid operation: GTR (mismatched types %s and %s)", (yyvsp[-2].s_val), (yyvsp[0].s_val));
            yyerror(msg);
            HAS_ERROR = true;
        }
        printf("GTR\n");
        (yyval.s_val) = "bool";
    }
#line 1803 "y.tab.c"
    break;

  case 46: /* Expr: Expr '<' Expr  */
#line 325 "compiler.y"
                    {
        if (strcmp((yyvsp[-2].s_val), (yyvsp[0].s_val)) != 0) {
            char msg[100];
            sprintf(msg, "invalid operation: LSS (mismatched types %s and %s)", (yyvsp[-2].s_val), (yyvsp[0].s_val));
            yyerror(msg);
            HAS_ERROR = true;
        }
        printf("LSS\n");
        (yyval.s_val) = "bool";
    }
#line 1818 "y.tab.c"
    break;

  case 47: /* Expr: Expr AS Type  */
#line 335 "compiler.y"
                   { 
        printf("%c2%c\n", (yyvsp[-2].s_val)[0], (yyvsp[0].s_val)[0]);
        (yyval.s_val) = (yyvsp[0].s_val);
    }
#line 1827 "y.tab.c"
    break;

  case 48: /* ArrayElements: ArrayElements ',' Expr  */
#line 343 "compiler.y"
                             { (yyval.s_val) = (yyvsp[0].s_val); }
#line 1833 "y.tab.c"
    break;

  case 49: /* ArrayElements: Expr  */
#line 344 "compiler.y"
           { (yyval.s_val) = (yyvsp[0].s_val); }
#line 1839 "y.tab.c"
    break;

  case 50: /* PrintStmt: PrintType '(' Expr ')' ';'  */
#line 348 "compiler.y"
                                 {
        printf("%s %s\n", (yyvsp[-4].s_val), (yyvsp[-2].s_val));
    }
#line 1847 "y.tab.c"
    break;

  case 51: /* DeclarationStmt: LET MutType ID ':' Type '=' Expr ';'  */
#line 354 "compiler.y"
                                           { insert_symbol((yyvsp[-5].s_val), (yyvsp[-6].i_val), (yyvsp[-3].s_val), "-"); }
#line 1853 "y.tab.c"
    break;

  case 52: /* DeclarationStmt: LET MutType ID ':' Type ';'  */
#line 355 "compiler.y"
                                  { insert_symbol((yyvsp[-3].s_val), (yyvsp[-4].i_val), (yyvsp[-1].s_val), "-"); }
#line 1859 "y.tab.c"
    break;

  case 53: /* DeclarationStmt: LET MutType ID '=' Expr ';'  */
#line 356 "compiler.y"
                                  { insert_symbol((yyvsp[-3].s_val), (yyvsp[-4].i_val), (yyvsp[-1].s_val), "-"); }
#line 1865 "y.tab.c"
    break;

  case 54: /* AssignmentStmt: ID AssignmentOperatorType Expr ';'  */
#line 360 "compiler.y"
                                         { 
        symbol_t *target = lookup_symbol((yyvsp[-3].s_val));
        if (target == NULL) {
            char msg[100];
            sprintf(msg, "undefined: %s", (yyvsp[-3].s_val));
            yyerror(msg);
            HAS_ERROR = true;
        }else {
            printf("%s\n", (yyvsp[-2].s_val));
            if (target->mut != 1) {
                char msg[100];
                sprintf(msg, "cannot borrow immutable borrowed content `%s` as mutable", (yyvsp[-3].s_val));
                yyerror(msg);
                HAS_ERROR = true;
            }
        } 
    }
#line 1887 "y.tab.c"
    break;

  case 58: /* Type: INT  */
#line 389 "compiler.y"
          { (yyval.s_val) = "i32"; }
#line 1893 "y.tab.c"
    break;

  case 59: /* Type: FLOAT  */
#line 390 "compiler.y"
            { (yyval.s_val) = "f32"; }
#line 1899 "y.tab.c"
    break;

  case 60: /* Type: BOOL  */
#line 391 "compiler.y"
           { (yyval.s_val) = "bool"; }
#line 1905 "y.tab.c"
    break;

  case 61: /* Type: '&' STR  */
#line 392 "compiler.y"
              { (yyval.s_val) = "str"; }
#line 1911 "y.tab.c"
    break;

  case 62: /* Type: '[' Type ';' Expr ']'  */
#line 393 "compiler.y"
                            { (yyval.s_val) = "array"; }
#line 1917 "y.tab.c"
    break;

  case 63: /* Type: %empty  */
#line 394 "compiler.y"
                  { (yyval.s_val) = "V"; }
#line 1923 "y.tab.c"
    break;

  case 64: /* PrintType: PRINT  */
#line 398 "compiler.y"
            { (yyval.s_val) = "PRINT"; }
#line 1929 "y.tab.c"
    break;

  case 65: /* PrintType: PRINTLN  */
#line 399 "compiler.y"
              { (yyval.s_val) = "PRINTLN"; }
#line 1935 "y.tab.c"
    break;

  case 66: /* MutType: MUT  */
#line 403 "compiler.y"
          { (yyval.i_val) = 1; }
#line 1941 "y.tab.c"
    break;

  case 67: /* MutType: %empty  */
#line 404 "compiler.y"
                  { (yyval.i_val) = 0; }
#line 1947 "y.tab.c"
    break;

  case 68: /* AssignmentOperatorType: '='  */
#line 408 "compiler.y"
          { (yyval.s_val) = "ASSIGN"; }
#line 1953 "y.tab.c"
    break;

  case 69: /* AssignmentOperatorType: ADD_ASSIGN  */
#line 409 "compiler.y"
                 { (yyval.s_val) = "ADD_ASSIGN"; }
#line 1959 "y.tab.c"
    break;

  case 70: /* AssignmentOperatorType: SUB_ASSIGN  */
#line 410 "compiler.y"
                 { (yyval.s_val) = "SUB_ASSIGN"; }
#line 1965 "y.tab.c"
    break;

  case 71: /* AssignmentOperatorType: MUL_ASSIGN  */
#line 411 "compiler.y"
                 { (yyval.s_val) = "MUL_ASSIGN"; }
#line 1971 "y.tab.c"
    break;

  case 72: /* AssignmentOperatorType: DIV_ASSIGN  */
#line 412 "compiler.y"
                 { (yyval.s_val) = "DIV_ASSIGN"; }
#line 1977 "y.tab.c"
    break;

  case 73: /* AssignmentOperatorType: REM_ASSIGN  */
#line 413 "compiler.y"
                 { (yyval.s_val) = "REM_ASSIGN"; }
#line 1983 "y.tab.c"
    break;

  case 74: /* FunctionArguments: FunctionArguments ',' Type ID  */
#line 417 "compiler.y"
                                    {
        char *buf = malloc(strlen((yyvsp[-3].s_val)) + strlen((yyvsp[-1].s_val)) + 10);
        sprintf(buf, "%s%s", (yyvsp[-3].s_val), (yyvsp[-1].s_val));
        (yyval.s_val) = buf;
    }
#line 1993 "y.tab.c"
    break;

  case 75: /* FunctionArguments: Type ID  */
#line 422 "compiler.y"
              { (yyval.s_val) = (yyvsp[-1].s_val); }
#line 1999 "y.tab.c"
    break;

  case 76: /* FunctionArguments: %empty  */
#line 423 "compiler.y"
                  { (yyval.s_val) = "V"; }
#line 2005 "y.tab.c"
    break;


#line 2009 "y.tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 426 "compiler.y"


/* C code section */
int main(int argc, char *argv[])
{
    /* Initialize symbol table */
    dummy_table = (symbol_table_t*) malloc(sizeof(symbol_table_t));
    dummy_table->scope_level = -1;
    dummy_table->element = NULL;
    dummy_table->next = dummy_table;

    if (argc == 2) {
        yyin = fopen(argv[1], "r");
    } else {
        yyin = stdin;
    }

    yylineno = 0;
    yyparse();

	printf("Total lines: %d\n", yylineno);
    fclose(yyin);
    return 0;
}


static void create_symbol() {
    /* Create dummy symbol */
    symbol_t *dummy_symbol = (symbol_t*) malloc(sizeof(symbol_t));
    dummy_symbol->index = -1;
    dummy_symbol->name = NULL;
    dummy_symbol->mut = -1;
    dummy_symbol->type = NULL;
    dummy_symbol->addr = -1;
    dummy_symbol->lineno = -1;
    dummy_symbol->func_sig = NULL;
    dummy_symbol->next = dummy_symbol;
    dummy_symbol->prev = dummy_symbol;

    /* Create symbol table */
    symbol_table_t *new_symbol_table = (symbol_table_t*) malloc(sizeof(symbol_table_t));
    new_symbol_table->scope_level = dummy_table->next->scope_level + 1;
    new_symbol_table->element = dummy_symbol;
    new_symbol_table->next = dummy_table->next;
    dummy_table->next = new_symbol_table;

    printf("> Create symbol table (scope level %d)\n", dummy_table->next->scope_level);
}

static void insert_symbol(char *name, int mut, char *type, char *func_sig) {
    printf("> Insert `%s` (addr: %d) to scope level %d\n", name, next_addr, dummy_table->next->scope_level);
    symbol_t *new_symbol = (symbol_t*) malloc(sizeof(symbol_t));
    new_symbol->index = dummy_table->next->element->prev->index + 1;
    new_symbol->name = strdup(name);
    new_symbol->mut = mut;
    new_symbol->type = strdup(type);
    new_symbol->addr = next_addr++;
    new_symbol->lineno = yylineno + 1;
    new_symbol->func_sig = strdup(func_sig);
    new_symbol->next = dummy_table->next->element;
    new_symbol->prev = dummy_table->next->element->prev;

    dummy_table->next->element->prev->next = new_symbol;
    dummy_table->next->element->prev = new_symbol;

}

symbol_t* lookup_symbol(char *name) {
    symbol_table_t *temp_table = dummy_table->next;
    while (temp_table != dummy_table) {
        symbol_t *tmp = temp_table->element->next;
        while (tmp != temp_table->element) {
            if (strcmp(tmp->name, name) == 0) {
                return tmp;
            }
            tmp = tmp->next;
        }
        temp_table = temp_table->next;
    }

    return NULL;
}

static void dump_symbol() {
    /* printf("\n> Dump symbol table (scope level: %d)\n", 0);
    printf("%-10s%-10s%-10s%-10s%-10s%-10s%-10s\n",
        "Index", "Name", "Mut","Type", "Addr", "Lineno", "Func_sig"); */
    /* printf("%-10d%-10s%-10d%-10s%-10d%-10d%-10s\n",
            0, "name", 0, "type", 0, 0, "func_sig"); */

    printf("\n> Dump symbol table (scope level: %d)\n", dummy_table->next->scope_level);
    printf("%-10s%-10s%-10s%-10s%-10s%-10s%-10s\n",
        "Index", "Name", "Mut","Type", "Addr", "Lineno", "Func_sig");
    symbol_t *cur = dummy_table->next->element->next;
    while (cur != dummy_table->next->element) {
        printf("%-10d%-10s%-10d%-10s%-10d%-10d%-10s\n",
            cur->index, cur->name, cur->mut, cur->type, cur->addr, cur->lineno, cur->func_sig);
        symbol_t *tmp = cur->next;

        free(cur->name);
        free(cur->type);
        free(cur->func_sig);
        free(cur);

        cur = tmp;
    }

    symbol_table_t *temp = dummy_table->next;
    dummy_table->next = temp->next;
    free(temp->element);
    free(temp);
    
}
