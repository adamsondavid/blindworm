/* A Bison parser, made by GNU Bison 3.7.6.  */

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
#define YYBISON 30706

/* Bison version string.  */
#define YYBISON_VERSION "3.7.6"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "bisonparser.y"

    #include "bisonparser.h"
    #include "../lexer/token.h"
    #include <string>
    #include <exception>

    // Room for improvement: replace with a std::variant
    struct value_t {
        std::string token_value;
        ast::Program* program;
        std::vector<ast::Statement*> statements;
        ast::Statement* statement;
        ast::LiteralExpression* literal_expression;
        ast::ReturnType* returntype;
        ast::DataType* datatype;
        std::vector<ast::VariableDeclarationStatement*> variable_declaration_statements;
        ast::VariableDeclarationStatement* variable_declaration_statement;
        std::vector<ast::Expression*> expressions;
        ast::Expression* expression;
        ast::FunctionDefinitionStatement* function_definition_statement;
        ast::NativeFunctionDefinitionStatement* native_function_definition_statement;
        ast::AssignmentStatement* assignment_statement;
        ast::FunctionCallExpression* function_call_expression;
        ast::ReturnStatement* return_statement;
        ast::WhileStatement* while_statement;
        ast::IfStatement* if_statement;
        std::vector<ast::ElifStatement*> elif_statements;
        ast::ElifStatement* elif_statement;
        ast::ElseStatement* else_statement;
    };
    #define YYSTYPE value_t

    int yylex(YYSTYPE* lvalp, AbstractLexer* lexer);
    int yyerror(AbstractLexer* lexer, ast::Program** program, const char* msg);

#line 107 "bisonparser.cpp"

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
    NATIVE = 258,                  /* NATIVE  */
    DEF = 259,                     /* DEF  */
    ARROW = 260,                   /* ARROW  */
    RETURN = 261,                  /* RETURN  */
    IF = 262,                      /* IF  */
    ELSE = 263,                    /* ELSE  */
    ELIF = 264,                    /* ELIF  */
    WHILE = 265,                   /* WHILE  */
    COLON = 266,                   /* COLON  */
    COMMA = 267,                   /* COMMA  */
    SEMICOLON = 268,               /* SEMICOLON  */
    LPAREN = 269,                  /* LPAREN  */
    RPAREN = 270,                  /* RPAREN  */
    PLUS = 271,                    /* PLUS  */
    MINUS = 272,                   /* MINUS  */
    MUL = 273,                     /* MUL  */
    DIV = 274,                     /* DIV  */
    NOT_EQUALS = 275,              /* NOT_EQUALS  */
    EQUALS = 276,                  /* EQUALS  */
    GREATER_THAN = 277,            /* GREATER_THAN  */
    GREATER_EQUALS = 278,          /* GREATER_EQUALS  */
    LESS_THAN = 279,               /* LESS_THAN  */
    LESS_EQUALS = 280,             /* LESS_EQUALS  */
    AND = 281,                     /* AND  */
    OR = 282,                      /* OR  */
    NOT = 283,                     /* NOT  */
    IDENTIFIER = 284,              /* IDENTIFIER  */
    NONE = 285,                    /* NONE  */
    BOOL = 286,                    /* BOOL  */
    INT = 287,                     /* INT  */
    FLOAT = 288,                   /* FLOAT  */
    STR = 289,                     /* STR  */
    INT_LITERAL = 290,             /* INT_LITERAL  */
    FLOAT_LITERAL = 291,           /* FLOAT_LITERAL  */
    STR_LITERAL = 292,             /* STR_LITERAL  */
    BOOL_LITERAL = 293,            /* BOOL_LITERAL  */
    ASSIGN = 294                   /* ASSIGN  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */



int yyparse (AbstractLexer* lexer, ast::Program** program);


/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_NATIVE = 3,                     /* NATIVE  */
  YYSYMBOL_DEF = 4,                        /* DEF  */
  YYSYMBOL_ARROW = 5,                      /* ARROW  */
  YYSYMBOL_RETURN = 6,                     /* RETURN  */
  YYSYMBOL_IF = 7,                         /* IF  */
  YYSYMBOL_ELSE = 8,                       /* ELSE  */
  YYSYMBOL_ELIF = 9,                       /* ELIF  */
  YYSYMBOL_WHILE = 10,                     /* WHILE  */
  YYSYMBOL_COLON = 11,                     /* COLON  */
  YYSYMBOL_COMMA = 12,                     /* COMMA  */
  YYSYMBOL_SEMICOLON = 13,                 /* SEMICOLON  */
  YYSYMBOL_LPAREN = 14,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 15,                    /* RPAREN  */
  YYSYMBOL_PLUS = 16,                      /* PLUS  */
  YYSYMBOL_MINUS = 17,                     /* MINUS  */
  YYSYMBOL_MUL = 18,                       /* MUL  */
  YYSYMBOL_DIV = 19,                       /* DIV  */
  YYSYMBOL_NOT_EQUALS = 20,                /* NOT_EQUALS  */
  YYSYMBOL_EQUALS = 21,                    /* EQUALS  */
  YYSYMBOL_GREATER_THAN = 22,              /* GREATER_THAN  */
  YYSYMBOL_GREATER_EQUALS = 23,            /* GREATER_EQUALS  */
  YYSYMBOL_LESS_THAN = 24,                 /* LESS_THAN  */
  YYSYMBOL_LESS_EQUALS = 25,               /* LESS_EQUALS  */
  YYSYMBOL_AND = 26,                       /* AND  */
  YYSYMBOL_OR = 27,                        /* OR  */
  YYSYMBOL_NOT = 28,                       /* NOT  */
  YYSYMBOL_IDENTIFIER = 29,                /* IDENTIFIER  */
  YYSYMBOL_NONE = 30,                      /* NONE  */
  YYSYMBOL_BOOL = 31,                      /* BOOL  */
  YYSYMBOL_INT = 32,                       /* INT  */
  YYSYMBOL_FLOAT = 33,                     /* FLOAT  */
  YYSYMBOL_STR = 34,                       /* STR  */
  YYSYMBOL_INT_LITERAL = 35,               /* INT_LITERAL  */
  YYSYMBOL_FLOAT_LITERAL = 36,             /* FLOAT_LITERAL  */
  YYSYMBOL_STR_LITERAL = 37,               /* STR_LITERAL  */
  YYSYMBOL_BOOL_LITERAL = 38,              /* BOOL_LITERAL  */
  YYSYMBOL_ASSIGN = 39,                    /* ASSIGN  */
  YYSYMBOL_YYACCEPT = 40,                  /* $accept  */
  YYSYMBOL_program = 41,                   /* program  */
  YYSYMBOL_statements = 42,                /* statements  */
  YYSYMBOL_statement = 43,                 /* statement  */
  YYSYMBOL_literal = 44,                   /* literal  */
  YYSYMBOL_returntype = 45,                /* returntype  */
  YYSYMBOL_datatype = 46,                  /* datatype  */
  YYSYMBOL_formal_parameters = 47,         /* formal_parameters  */
  YYSYMBOL_formal_parameter = 48,          /* formal_parameter  */
  YYSYMBOL_call_parameters = 49,           /* call_parameters  */
  YYSYMBOL_expression = 50,                /* expression  */
  YYSYMBOL_or_expression = 51,             /* or_expression  */
  YYSYMBOL_and_expression = 52,            /* and_expression  */
  YYSYMBOL_not_expression = 53,            /* not_expression  */
  YYSYMBOL_comparison_expression = 54,     /* comparison_expression  */
  YYSYMBOL_arithmetic_expression = 55,     /* arithmetic_expression  */
  YYSYMBOL_term = 56,                      /* term  */
  YYSYMBOL_factor = 57,                    /* factor  */
  YYSYMBOL_atom = 58,                      /* atom  */
  YYSYMBOL_function_definition = 59,       /* function_definition  */
  YYSYMBOL_native_function_definition = 60, /* native_function_definition  */
  YYSYMBOL_variable_assignment = 61,       /* variable_assignment  */
  YYSYMBOL_variable_declaration = 62,      /* variable_declaration  */
  YYSYMBOL_function_call = 63,             /* function_call  */
  YYSYMBOL_return_statement = 64,          /* return_statement  */
  YYSYMBOL_while_statement = 65,           /* while_statement  */
  YYSYMBOL_if_statement = 66,              /* if_statement  */
  YYSYMBOL_elif_statements = 67,           /* elif_statements  */
  YYSYMBOL_elif_statement = 68,            /* elif_statement  */
  YYSYMBOL_else_statement = 69             /* else_statement  */
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

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
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
#define YYFINAL  45
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   158

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  40
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  30
/* YYNRULES -- Number of rules.  */
#define YYNRULES  74
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  149

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   294


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
      35,    36,    37,    38,    39
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,   114,   114,   116,   117,   119,   120,   121,   122,   123,
     124,   125,   126,   127,   129,   130,   131,   132,   134,   135,
     137,   138,   139,   140,   142,   143,   144,   146,   147,   148,
     150,   151,   152,   154,   156,   157,   159,   160,   162,   163,
     165,   166,   167,   168,   169,   170,   171,   173,   174,   175,
     177,   178,   179,   181,   182,   184,   185,   186,   187,   189,
     191,   193,   195,   196,   198,   200,   201,   203,   205,   207,
     208,   210,   211,   213,   214
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
  "\"end of file\"", "error", "\"invalid token\"", "NATIVE", "DEF",
  "ARROW", "RETURN", "IF", "ELSE", "ELIF", "WHILE", "COLON", "COMMA",
  "SEMICOLON", "LPAREN", "RPAREN", "PLUS", "MINUS", "MUL", "DIV",
  "NOT_EQUALS", "EQUALS", "GREATER_THAN", "GREATER_EQUALS", "LESS_THAN",
  "LESS_EQUALS", "AND", "OR", "NOT", "IDENTIFIER", "NONE", "BOOL", "INT",
  "FLOAT", "STR", "INT_LITERAL", "FLOAT_LITERAL", "STR_LITERAL",
  "BOOL_LITERAL", "ASSIGN", "$accept", "program", "statements",
  "statement", "literal", "returntype", "datatype", "formal_parameters",
  "formal_parameter", "call_parameters", "expression", "or_expression",
  "and_expression", "not_expression", "comparison_expression",
  "arithmetic_expression", "term", "factor", "atom", "function_definition",
  "native_function_definition", "variable_assignment",
  "variable_declaration", "function_call", "return_statement",
  "while_statement", "if_statement", "elif_statements", "elif_statement",
  "else_statement", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294
};
#endif

#define YYPACT_NINF (-72)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-30)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       7,     1,   -17,     9,     5,    17,    -7,    21,    64,     7,
     -72,   -72,   -72,   -72,    52,   -72,   -72,   -72,    39,    55,
     -72,    13,    42,    13,    56,   -72,   -72,   -72,   -72,   -72,
      53,   -72,    45,    75,   -72,    37,     8,    -3,   -72,   -72,
      13,    13,    61,    13,    13,   -72,   -72,   -72,   -72,    88,
       6,    89,   -72,   -72,   -72,    13,    13,    38,    38,    38,
      38,    38,    38,    38,    38,    38,    38,    92,    93,   -72,
     -72,   -72,   -72,    -5,    94,    91,    97,     6,   100,   101,
     103,   -72,   -72,   -72,   -72,   -72,   -72,   -72,   -72,   -72,
     -72,   -72,   -72,   -72,   106,   107,   -72,    13,   -72,    13,
     -72,   104,    61,   115,     6,    98,   108,   110,   -72,   119,
      86,    57,   -72,     7,     7,   -72,    57,    62,   -72,   116,
     -72,   111,   113,   117,   -72,   118,   122,   -72,   -72,     7,
     121,   128,   122,   123,    13,   129,   -72,   -72,   -72,   124,
     127,   132,     7,   130,   131,     7,   -72,   133,   -72
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       4,     0,     0,     0,     0,     0,     0,     0,     0,     4,
       5,     6,     7,     8,     0,    10,    11,    12,     0,     0,
      66,     0,     0,     0,    56,    15,    16,    17,    14,    55,
       0,    33,    35,    37,    39,    46,    49,    52,    54,    57,
       0,     0,     0,    32,     0,     1,     2,     3,     9,     0,
      26,     0,    53,    38,    65,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    20,
      21,    22,    23,     0,     0,    30,     0,    26,     0,     0,
      25,    58,    34,    36,    40,    41,    42,    43,    44,    45,
      47,    48,    50,    51,     0,     0,    63,     0,    64,    32,
      61,     0,     0,     0,    26,     0,     0,     0,    31,     0,
      27,     0,    24,     4,     4,    62,     0,     0,    19,     0,
      18,     0,     0,     0,    28,     0,    70,    67,    60,     4,
       0,    74,    70,     0,     0,     0,    68,    69,    59,     0,
       0,     0,     4,     0,     0,     4,    73,     0,    71
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -72,   -72,    -8,   -72,    30,    33,   -39,   -71,   -72,    51,
      -1,    96,    99,   134,    24,   -35,   -12,   -72,   136,   -72,
     -72,   -72,   -72,     0,   -72,   -72,   -72,    20,   -72,   -72
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     7,     8,     9,    29,   119,   120,    79,    80,    74,
      75,    31,    32,    33,    34,    35,    36,    37,    38,    10,
      11,    12,    13,    39,    15,    16,    17,   131,   132,   136
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      14,    47,    30,    73,    42,    18,   101,    43,    96,    14,
       1,     2,    19,     3,     4,    65,    66,     5,   -29,    40,
      51,    45,    20,    21,    63,    64,    22,    21,    90,    91,
      22,    41,    44,   112,    97,    78,     6,    23,    24,    67,
      68,    23,    24,    76,    25,    26,    27,    28,    25,    26,
      27,    28,    21,    92,    93,    22,    21,    57,    58,    59,
      60,    61,    62,   110,    46,    48,    54,    24,    49,    50,
      43,    24,    55,    25,    26,    27,    28,    25,    26,    27,
      28,    84,    85,    86,    87,    88,    89,   118,    69,    70,
      71,    72,    69,    70,    71,    72,   107,    25,    26,    27,
      28,    56,    77,    99,    81,   121,   122,    94,    95,    98,
     100,   102,   113,    14,    14,   104,   103,   105,   106,   109,
     111,   133,   114,   115,   116,   117,   126,   125,   127,    14,
     128,   130,   129,   139,   144,   134,   135,   147,   138,   141,
     140,   142,    14,   143,   145,    14,   146,   124,   148,   123,
     108,    82,   137,     0,     0,    83,     0,    53,    52
};

static const yytype_int16 yycheck[] =
{
       0,     9,     3,    42,    11,     4,    77,    14,    13,     9,
       3,     4,    29,     6,     7,    18,    19,    10,    12,    14,
      21,     0,    13,    14,    16,    17,    17,    14,    63,    64,
      17,    14,    39,   104,    39,    29,    29,    28,    29,    40,
      41,    28,    29,    44,    35,    36,    37,    38,    35,    36,
      37,    38,    14,    65,    66,    17,    14,    20,    21,    22,
      23,    24,    25,   102,     0,    13,    13,    29,    29,    14,
      14,    29,    27,    35,    36,    37,    38,    35,    36,    37,
      38,    57,    58,    59,    60,    61,    62,    30,    31,    32,
      33,    34,    31,    32,    33,    34,    97,    35,    36,    37,
      38,    26,    14,    12,    15,   113,   114,    15,    15,    15,
      13,    11,    14,   113,   114,    12,    15,    11,    11,    15,
       5,   129,    14,    13,     5,    39,    15,    11,    15,   129,
      13,     9,    14,   134,   142,    14,     8,   145,    15,    15,
      11,    14,   142,    11,    14,   145,    15,   117,    15,   116,
      99,    55,   132,    -1,    -1,    56,    -1,    23,    22
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     6,     7,    10,    29,    41,    42,    43,
      59,    60,    61,    62,    63,    64,    65,    66,     4,    29,
      13,    14,    17,    28,    29,    35,    36,    37,    38,    44,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    63,
      14,    14,    11,    14,    39,     0,     0,    42,    13,    29,
      14,    50,    58,    53,    13,    27,    26,    20,    21,    22,
      23,    24,    25,    16,    17,    18,    19,    50,    50,    31,
      32,    33,    34,    46,    49,    50,    50,    14,    29,    47,
      48,    15,    51,    52,    54,    54,    54,    54,    54,    54,
      55,    55,    56,    56,    15,    15,    13,    39,    15,    12,
      13,    47,    11,    15,    12,    11,    11,    50,    49,    15,
      46,     5,    47,    14,    14,    13,     5,    39,    30,    45,
      46,    42,    42,    45,    44,    11,    15,    15,    13,    14,
       9,    67,    68,    42,    14,     8,    69,    67,    15,    50,
      11,    15,    14,    11,    42,    14,    15,    42,    15
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    40,    41,    42,    42,    43,    43,    43,    43,    43,
      43,    43,    43,    43,    44,    44,    44,    44,    45,    45,
      46,    46,    46,    46,    47,    47,    47,    48,    48,    48,
      49,    49,    49,    50,    51,    51,    52,    52,    53,    53,
      54,    54,    54,    54,    54,    54,    54,    55,    55,    55,
      56,    56,    56,    57,    57,    58,    58,    58,    58,    59,
      60,    61,    62,    62,    63,    64,    64,    65,    66,    67,
      67,    68,    68,    69,    69
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     2,     0,     1,     1,     1,     1,     2,
       1,     1,     1,     0,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     1,     0,     3,     5,     0,
       1,     3,     0,     1,     3,     1,     3,     1,     2,     1,
       3,     3,     3,     3,     3,     3,     1,     3,     3,     1,
       3,     3,     1,     2,     1,     1,     1,     1,     3,    11,
       9,     4,     6,     4,     4,     3,     2,     8,    10,     2,
       0,     8,     0,     5,     0
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


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
        yyerror (lexer, program, YY_("syntax error: cannot back up")); \
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

/* This macro is provided for backward compatibility. */
# ifndef YY_LOCATION_PRINT
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, lexer, program); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, AbstractLexer* lexer, ast::Program** program)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (lexer);
  YY_USE (program);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yykind < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yykind], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, AbstractLexer* lexer, ast::Program** program)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep, lexer, program);
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
                 int yyrule, AbstractLexer* lexer, ast::Program** program)
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
                       &yyvsp[(yyi + 1) - (yynrhs)], lexer, program);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule, lexer, program); \
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
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, AbstractLexer* lexer, ast::Program** program)
{
  YY_USE (yyvaluep);
  YY_USE (lexer);
  YY_USE (program);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}






/*----------.
| yyparse.  |
`----------*/

int
yyparse (AbstractLexer* lexer, ast::Program** program)
{
/* Lookahead token kind.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

    /* Number of syntax errors so far.  */
    int yynerrs = 0;

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
    goto yyexhaustedlab;
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
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
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
      yychar = yylex (&yylval, lexer);
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
  case 2: /* program: statements $end  */
#line 114 "bisonparser.y"
                                                                        { *program = new ast::Program((yyvsp[-1].statements)); }
#line 1348 "bisonparser.cpp"
    break;

  case 3: /* statements: statement statements  */
#line 116 "bisonparser.y"
                                                                        { (yyvsp[0].statements).insert((yyvsp[0].statements).begin(), (yyvsp[-1].statement)); (yyval.statements) = (yyvsp[0].statements); }
#line 1354 "bisonparser.cpp"
    break;

  case 4: /* statements: %empty  */
#line 117 "bisonparser.y"
                                                                        { (yyval.statements) = std::vector<ast::Statement*>(); }
#line 1360 "bisonparser.cpp"
    break;

  case 5: /* statement: function_definition  */
#line 119 "bisonparser.y"
                                                                        { (yyval.statement) = (yyvsp[0].function_definition_statement); }
#line 1366 "bisonparser.cpp"
    break;

  case 6: /* statement: native_function_definition  */
#line 120 "bisonparser.y"
                                                                        { (yyval.statement) = (yyvsp[0].native_function_definition_statement); }
#line 1372 "bisonparser.cpp"
    break;

  case 7: /* statement: variable_assignment  */
#line 121 "bisonparser.y"
                                                                        { (yyval.statement) = (yyvsp[0].assignment_statement); }
#line 1378 "bisonparser.cpp"
    break;

  case 8: /* statement: variable_declaration  */
#line 122 "bisonparser.y"
                                                                        { (yyval.statement) = (yyvsp[0].variable_declaration_statement); }
#line 1384 "bisonparser.cpp"
    break;

  case 9: /* statement: function_call SEMICOLON  */
#line 123 "bisonparser.y"
                                                                        { (yyval.statement) = new ast::FunctionCallStatement((yyvsp[-1].function_call_expression)); }
#line 1390 "bisonparser.cpp"
    break;

  case 10: /* statement: return_statement  */
#line 124 "bisonparser.y"
                                                                        { (yyval.statement) = (yyvsp[0].return_statement); }
#line 1396 "bisonparser.cpp"
    break;

  case 11: /* statement: while_statement  */
#line 125 "bisonparser.y"
                                                                        { (yyval.statement) = (yyvsp[0].while_statement); }
#line 1402 "bisonparser.cpp"
    break;

  case 12: /* statement: if_statement  */
#line 126 "bisonparser.y"
                                                                        { (yyval.statement) = (yyvsp[0].if_statement); }
#line 1408 "bisonparser.cpp"
    break;

  case 13: /* statement: %empty  */
#line 127 "bisonparser.y"
                                                                        { (yyval.statement) = NO_STMT; }
#line 1414 "bisonparser.cpp"
    break;

  case 14: /* literal: BOOL_LITERAL  */
#line 129 "bisonparser.y"
                                                                        { (yyval.literal_expression) = new ast::BoolLiteralExpression((yyvsp[0].token_value) == "True" || (yyvsp[0].token_value) == "On"); }
#line 1420 "bisonparser.cpp"
    break;

  case 15: /* literal: INT_LITERAL  */
#line 130 "bisonparser.y"
                                                                        { (yyval.literal_expression) = new ast::IntLiteralExpression(std::stoi((yyvsp[0].token_value))); }
#line 1426 "bisonparser.cpp"
    break;

  case 16: /* literal: FLOAT_LITERAL  */
#line 131 "bisonparser.y"
                                                                        { (yyval.literal_expression) = new ast::FloatLiteralExpression(std::stof((yyvsp[0].token_value))); }
#line 1432 "bisonparser.cpp"
    break;

  case 17: /* literal: STR_LITERAL  */
#line 132 "bisonparser.y"
                                                                        { (yyval.literal_expression) = new ast::StrLiteralExpression((yyvsp[0].token_value)); }
#line 1438 "bisonparser.cpp"
    break;

  case 18: /* returntype: datatype  */
#line 134 "bisonparser.y"
                                                                        { (yyval.returntype) = (yyvsp[0].datatype); }
#line 1444 "bisonparser.cpp"
    break;

  case 19: /* returntype: NONE  */
#line 135 "bisonparser.y"
                                                                        { (yyval.returntype) = new ast::NoneType(); }
#line 1450 "bisonparser.cpp"
    break;

  case 20: /* datatype: BOOL  */
#line 137 "bisonparser.y"
                                                                        { (yyval.datatype) = new ast::BoolType(); }
#line 1456 "bisonparser.cpp"
    break;

  case 21: /* datatype: INT  */
#line 138 "bisonparser.y"
                                                                        { (yyval.datatype) = new ast::IntType(); }
#line 1462 "bisonparser.cpp"
    break;

  case 22: /* datatype: FLOAT  */
#line 139 "bisonparser.y"
                                                                        { (yyval.datatype) = new ast::FloatType(); }
#line 1468 "bisonparser.cpp"
    break;

  case 23: /* datatype: STR  */
#line 140 "bisonparser.y"
                                                                        { (yyval.datatype) = new ast::StrType(); }
#line 1474 "bisonparser.cpp"
    break;

  case 24: /* formal_parameters: formal_parameter COMMA formal_parameters  */
#line 142 "bisonparser.y"
                                                                        { (yyvsp[0].variable_declaration_statements).insert((yyvsp[0].variable_declaration_statements).begin(), (yyvsp[-2].variable_declaration_statement)); (yyval.variable_declaration_statements) = (yyvsp[0].variable_declaration_statements); }
#line 1480 "bisonparser.cpp"
    break;

  case 25: /* formal_parameters: formal_parameter  */
#line 143 "bisonparser.y"
                                                                        { (yyval.variable_declaration_statements) = std::vector<ast::VariableDeclarationStatement*>{(yyvsp[0].variable_declaration_statement)}; }
#line 1486 "bisonparser.cpp"
    break;

  case 26: /* formal_parameters: %empty  */
#line 144 "bisonparser.y"
                                                                        { (yyval.variable_declaration_statements) = std::vector<ast::VariableDeclarationStatement*>(); }
#line 1492 "bisonparser.cpp"
    break;

  case 27: /* formal_parameter: IDENTIFIER COLON datatype  */
#line 146 "bisonparser.y"
                                                                        { (yyval.variable_declaration_statement) = new ast::VariableDeclarationStatement((yyvsp[-2].token_value), (yyvsp[0].datatype), NO_EXPR); }
#line 1498 "bisonparser.cpp"
    break;

  case 28: /* formal_parameter: IDENTIFIER COLON datatype ASSIGN literal  */
#line 147 "bisonparser.y"
                                                                        { (yyval.variable_declaration_statement) = new ast::VariableDeclarationStatement((yyvsp[-4].token_value), (yyvsp[-2].datatype), (yyvsp[0].literal_expression)); }
#line 1504 "bisonparser.cpp"
    break;

  case 29: /* formal_parameter: %empty  */
#line 148 "bisonparser.y"
                                                                        { (yyval.variable_declaration_statement) = nullptr; }
#line 1510 "bisonparser.cpp"
    break;

  case 30: /* call_parameters: expression  */
#line 150 "bisonparser.y"
                                                                        { (yyval.expressions) = std::vector<ast::Expression*>{(yyvsp[0].expression)}; }
#line 1516 "bisonparser.cpp"
    break;

  case 31: /* call_parameters: expression COMMA call_parameters  */
#line 151 "bisonparser.y"
                                                                        { (yyvsp[0].expressions).insert((yyvsp[0].expressions).begin(), (yyvsp[-2].expression)); (yyval.expressions) = (yyvsp[0].expressions); }
#line 1522 "bisonparser.cpp"
    break;

  case 32: /* call_parameters: %empty  */
#line 152 "bisonparser.y"
                                                                        { (yyval.expressions) = std::vector<ast::Expression*>(); }
#line 1528 "bisonparser.cpp"
    break;

  case 33: /* expression: or_expression  */
#line 154 "bisonparser.y"
                                                                        { (yyval.expression) = (yyvsp[0].expression); }
#line 1534 "bisonparser.cpp"
    break;

  case 34: /* or_expression: and_expression OR or_expression  */
#line 156 "bisonparser.y"
                                                                        { (yyval.expression) = new ast::OrExpression((yyvsp[-2].expression), (yyvsp[0].expression)); }
#line 1540 "bisonparser.cpp"
    break;

  case 35: /* or_expression: and_expression  */
#line 157 "bisonparser.y"
                                                                        { (yyval.expression) = (yyvsp[0].expression); }
#line 1546 "bisonparser.cpp"
    break;

  case 36: /* and_expression: not_expression AND and_expression  */
#line 159 "bisonparser.y"
                                                                        { (yyval.expression) = new ast::AndExpression((yyvsp[-2].expression), (yyvsp[0].expression)); }
#line 1552 "bisonparser.cpp"
    break;

  case 37: /* and_expression: not_expression  */
#line 160 "bisonparser.y"
                                                                        { (yyval.expression) = (yyvsp[0].expression); }
#line 1558 "bisonparser.cpp"
    break;

  case 38: /* not_expression: NOT not_expression  */
#line 162 "bisonparser.y"
                                                                        { (yyval.expression) = new ast::NotExpression((yyvsp[0].expression)); }
#line 1564 "bisonparser.cpp"
    break;

  case 39: /* not_expression: comparison_expression  */
#line 163 "bisonparser.y"
                                                                        { (yyval.expression) = (yyvsp[0].expression); }
#line 1570 "bisonparser.cpp"
    break;

  case 40: /* comparison_expression: arithmetic_expression NOT_EQUALS comparison_expression  */
#line 165 "bisonparser.y"
                                                                                { (yyval.expression) = new ast::NotEqualsExpression((yyvsp[-2].expression), (yyvsp[0].expression)); }
#line 1576 "bisonparser.cpp"
    break;

  case 41: /* comparison_expression: arithmetic_expression EQUALS comparison_expression  */
#line 166 "bisonparser.y"
                                                                        { (yyval.expression) = new ast::EqualsExpression((yyvsp[-2].expression), (yyvsp[0].expression)); }
#line 1582 "bisonparser.cpp"
    break;

  case 42: /* comparison_expression: arithmetic_expression GREATER_THAN comparison_expression  */
#line 167 "bisonparser.y"
                                                                        { (yyval.expression) = new ast::GreaterThanExpression((yyvsp[-2].expression), (yyvsp[0].expression)); }
#line 1588 "bisonparser.cpp"
    break;

  case 43: /* comparison_expression: arithmetic_expression GREATER_EQUALS comparison_expression  */
#line 168 "bisonparser.y"
                                                                        { (yyval.expression) = new ast::GreaterEqualsExpression((yyvsp[-2].expression), (yyvsp[0].expression)); }
#line 1594 "bisonparser.cpp"
    break;

  case 44: /* comparison_expression: arithmetic_expression LESS_THAN comparison_expression  */
#line 169 "bisonparser.y"
                                                                        { (yyval.expression) = new ast::LessThanExpression((yyvsp[-2].expression), (yyvsp[0].expression)); }
#line 1600 "bisonparser.cpp"
    break;

  case 45: /* comparison_expression: arithmetic_expression LESS_EQUALS comparison_expression  */
#line 170 "bisonparser.y"
                                                                        { (yyval.expression) = new ast::LessEqualsExpression((yyvsp[-2].expression), (yyvsp[0].expression)); }
#line 1606 "bisonparser.cpp"
    break;

  case 46: /* comparison_expression: arithmetic_expression  */
#line 171 "bisonparser.y"
                                                                        { (yyval.expression) = (yyvsp[0].expression); }
#line 1612 "bisonparser.cpp"
    break;

  case 47: /* arithmetic_expression: term PLUS arithmetic_expression  */
#line 173 "bisonparser.y"
                                                                        { (yyval.expression) = new ast::AdditionExpression((yyvsp[-2].expression), (yyvsp[0].expression)); }
#line 1618 "bisonparser.cpp"
    break;

  case 48: /* arithmetic_expression: term MINUS arithmetic_expression  */
#line 174 "bisonparser.y"
                                                                        { (yyval.expression) = new ast::SubtractionExpression((yyvsp[-2].expression), (yyvsp[0].expression)); }
#line 1624 "bisonparser.cpp"
    break;

  case 49: /* arithmetic_expression: term  */
#line 175 "bisonparser.y"
                                                                        { (yyval.expression) = (yyvsp[0].expression); }
#line 1630 "bisonparser.cpp"
    break;

  case 50: /* term: factor MUL term  */
#line 177 "bisonparser.y"
                                                                        { (yyval.expression) = new ast::MultiplicationExpression((yyvsp[-2].expression), (yyvsp[0].expression)); }
#line 1636 "bisonparser.cpp"
    break;

  case 51: /* term: factor DIV term  */
#line 178 "bisonparser.y"
                                                                        { (yyval.expression) = new ast::DivisionExpression((yyvsp[-2].expression), (yyvsp[0].expression)); }
#line 1642 "bisonparser.cpp"
    break;

  case 52: /* term: factor  */
#line 179 "bisonparser.y"
                                                                        { (yyval.expression) = (yyvsp[0].expression); }
#line 1648 "bisonparser.cpp"
    break;

  case 53: /* factor: MINUS atom  */
#line 181 "bisonparser.y"
                                                                        { (yyval.expression) = new ast::MultiplicationExpression(new ast::IntLiteralExpression(-1), (yyvsp[0].expression)); }
#line 1654 "bisonparser.cpp"
    break;

  case 54: /* factor: atom  */
#line 182 "bisonparser.y"
                                                                        { (yyval.expression) = (yyvsp[0].expression); }
#line 1660 "bisonparser.cpp"
    break;

  case 55: /* atom: literal  */
#line 184 "bisonparser.y"
                                                                        { (yyval.expression) = (yyvsp[0].literal_expression); }
#line 1666 "bisonparser.cpp"
    break;

  case 56: /* atom: IDENTIFIER  */
#line 185 "bisonparser.y"
                                                                        { (yyval.expression) = new ast::IdentifierExpression((yyvsp[0].token_value)); }
#line 1672 "bisonparser.cpp"
    break;

  case 57: /* atom: function_call  */
#line 186 "bisonparser.y"
                                                                        { (yyval.expression) = (yyvsp[0].function_call_expression); }
#line 1678 "bisonparser.cpp"
    break;

  case 58: /* atom: LPAREN expression RPAREN  */
#line 187 "bisonparser.y"
                                                                        { (yyval.expression) = (yyvsp[-1].expression); }
#line 1684 "bisonparser.cpp"
    break;

  case 59: /* function_definition: DEF IDENTIFIER LPAREN formal_parameters RPAREN ARROW returntype COLON LPAREN statements RPAREN  */
#line 189 "bisonparser.y"
                                                                                                                    { (yyval.function_definition_statement) = new ast::FunctionDefinitionStatement((yyvsp[-9].token_value), (yyvsp[-4].returntype), (yyvsp[-7].variable_declaration_statements), (yyvsp[-1].statements));}
#line 1690 "bisonparser.cpp"
    break;

  case 60: /* native_function_definition: NATIVE DEF IDENTIFIER LPAREN formal_parameters RPAREN ARROW returntype SEMICOLON  */
#line 191 "bisonparser.y"
                                                                                                             { (yyval.native_function_definition_statement) = new ast::NativeFunctionDefinitionStatement((yyvsp[-6].token_value), (yyvsp[-1].returntype), (yyvsp[-4].variable_declaration_statements)); }
#line 1696 "bisonparser.cpp"
    break;

  case 61: /* variable_assignment: IDENTIFIER ASSIGN expression SEMICOLON  */
#line 193 "bisonparser.y"
                                                                        { (yyval.assignment_statement) = new ast::AssignmentStatement((yyvsp[-3].token_value), (yyvsp[-1].expression)); }
#line 1702 "bisonparser.cpp"
    break;

  case 62: /* variable_declaration: IDENTIFIER COLON datatype ASSIGN expression SEMICOLON  */
#line 195 "bisonparser.y"
                                                                            { (yyval.variable_declaration_statement) = new ast::VariableDeclarationStatement((yyvsp[-5].token_value), (yyvsp[-3].datatype), (yyvsp[-1].expression)); }
#line 1708 "bisonparser.cpp"
    break;

  case 63: /* variable_declaration: IDENTIFIER COLON datatype SEMICOLON  */
#line 196 "bisonparser.y"
                                                                        { (yyval.variable_declaration_statement) = new ast::VariableDeclarationStatement((yyvsp[-3].token_value), (yyvsp[-1].datatype), NO_EXPR); }
#line 1714 "bisonparser.cpp"
    break;

  case 64: /* function_call: IDENTIFIER LPAREN call_parameters RPAREN  */
#line 198 "bisonparser.y"
                                                                        { (yyval.function_call_expression) = new ast::FunctionCallExpression((yyvsp[-3].token_value), (yyvsp[-1].expressions)); }
#line 1720 "bisonparser.cpp"
    break;

  case 65: /* return_statement: RETURN expression SEMICOLON  */
#line 200 "bisonparser.y"
                                                                        { (yyval.return_statement) = new ast::ReturnStatement((yyvsp[-1].expression)); }
#line 1726 "bisonparser.cpp"
    break;

  case 66: /* return_statement: RETURN SEMICOLON  */
#line 201 "bisonparser.y"
                                                                        { (yyval.return_statement) = new ast::ReturnStatement(NO_EXPR); }
#line 1732 "bisonparser.cpp"
    break;

  case 67: /* while_statement: WHILE LPAREN expression RPAREN COLON LPAREN statements RPAREN  */
#line 203 "bisonparser.y"
                                                                                { (yyval.while_statement) = new ast::WhileStatement((yyvsp[-5].expression), (yyvsp[-1].statements)); }
#line 1738 "bisonparser.cpp"
    break;

  case 68: /* if_statement: IF LPAREN expression RPAREN COLON LPAREN statements RPAREN elif_statements else_statement  */
#line 205 "bisonparser.y"
                                                                                                        { (yyval.if_statement) = new ast::IfStatement((yyvsp[-7].expression), (yyvsp[-3].statements), (yyvsp[-1].elif_statements), (yyvsp[0].else_statement)); }
#line 1744 "bisonparser.cpp"
    break;

  case 69: /* elif_statements: elif_statement elif_statements  */
#line 207 "bisonparser.y"
                                                                        { (yyvsp[0].elif_statements).insert((yyvsp[0].elif_statements).begin(), (yyvsp[-1].elif_statement)); (yyval.elif_statements) = (yyvsp[0].elif_statements); }
#line 1750 "bisonparser.cpp"
    break;

  case 70: /* elif_statements: %empty  */
#line 208 "bisonparser.y"
                                                                        { (yyval.elif_statements) = std::vector<ast::ElifStatement*>(); }
#line 1756 "bisonparser.cpp"
    break;

  case 71: /* elif_statement: ELIF LPAREN expression RPAREN COLON LPAREN statements RPAREN  */
#line 210 "bisonparser.y"
                                                                                { (yyval.elif_statement) = new ast::ElifStatement((yyvsp[-5].expression), (yyvsp[-1].statements)); }
#line 1762 "bisonparser.cpp"
    break;

  case 72: /* elif_statement: %empty  */
#line 211 "bisonparser.y"
                                                                        { (yyval.elif_statement) = NO_STMT; }
#line 1768 "bisonparser.cpp"
    break;

  case 73: /* else_statement: ELSE COLON LPAREN statements RPAREN  */
#line 213 "bisonparser.y"
                                                                        { (yyval.else_statement) = new ast::ElseStatement((yyvsp[-1].statements)); }
#line 1774 "bisonparser.cpp"
    break;

  case 74: /* else_statement: %empty  */
#line 214 "bisonparser.y"
                                                                        { (yyval.else_statement) = NO_STMT; }
#line 1780 "bisonparser.cpp"
    break;


#line 1784 "bisonparser.cpp"

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
      yyerror (lexer, program, YY_("syntax error"));
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
                      yytoken, &yylval, lexer, program);
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, lexer, program);
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
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (lexer, program, YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturn;
#endif


/*-------------------------------------------------------.
| yyreturn -- parsing is finished, clean up and return.  |
`-------------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, lexer, program);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, lexer, program);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 216 "bisonparser.y"


int toBisonToken(Token::Type t) {
    if(Token::Type::UNKNOWN == t)           return YYUNDEF;
    if(Token::Type::END_OF_FILE == t)       return YYEOF;
    if(Token::Type::NATIVE == t)            return NATIVE;
    if(Token::Type::DEF == t)               return DEF;
    if(Token::Type::ARROW == t)             return ARROW;
    if(Token::Type::RETURN == t)            return RETURN;
    if(Token::Type::IF == t)                return IF;
    if(Token::Type::ELSE == t)              return ELSE;
    if(Token::Type::ELIF == t)              return ELIF;
    if(Token::Type::WHILE == t)             return WHILE;
    if(Token::Type::COLON == t)             return COLON;
    if(Token::Type::COMMA == t)             return COMMA;
    if(Token::Type::SEMICOLON == t)         return SEMICOLON;
    if(Token::Type::LPAREN == t)            return LPAREN;
    if(Token::Type::RPAREN == t)            return RPAREN;
    if(Token::Type::PLUS == t)              return PLUS;
    if(Token::Type::MINUS == t)             return MINUS;
    if(Token::Type::MUL == t)               return MUL;
    if(Token::Type::DIV == t)               return DIV;
    if(Token::Type::NOT_EQUALS == t)        return NOT_EQUALS;
    if(Token::Type::EQUALS == t)            return EQUALS;
    if(Token::Type::GREATER_THAN == t)      return GREATER_THAN;
    if(Token::Type::GREATER_EQUALS == t)    return GREATER_EQUALS;
    if(Token::Type::LESS_THAN == t)         return LESS_THAN;
    if(Token::Type::LESS_EQUALS == t)       return LESS_EQUALS;
    if(Token::Type::AND == t)               return AND;
    if(Token::Type::OR == t)                return OR;
    if(Token::Type::NOT == t)               return NOT;
    if(Token::Type::IDENTIFIER == t)        return IDENTIFIER;
    if(Token::Type::NONE == t)              return NONE;
    if(Token::Type::BOOL == t)              return BOOL;
    if(Token::Type::INT == t)               return INT;
    if(Token::Type::FLOAT == t)             return FLOAT;
    if(Token::Type::STR == t)               return STR;
    if(Token::Type::INT_LITERAL == t)       return INT_LITERAL;
    if(Token::Type::FLOAT_LITERAL == t)     return FLOAT_LITERAL;
    if(Token::Type::STR_LITERAL == t)       return STR_LITERAL;
    if(Token::Type::BOOL_LITERAL == t)      return BOOL_LITERAL;
    if(Token::Type::ASSIGN == t)            return ASSIGN;
    return YYUNDEF;
}

int yylex(YYSTYPE* lvalp, AbstractLexer* lexer) {
    Token token = lexer->next();
    lvalp->token_value = token.getValue();
    return toBisonToken(token.getTokenType());
}

int yyerror(AbstractLexer* lexer, ast::Program** program, const char* msg) {
    throw std::runtime_error(msg);
    return 0;
}

BisonParser::BisonParser(AbstractLexer *lexer) : AbstractParser(lexer) { }

BisonParser::~BisonParser() { }

ast::Program* BisonParser::parse() {
    ast::Program* program = nullptr;
    yyparse(this->lexer, &program);
    return program;
}
