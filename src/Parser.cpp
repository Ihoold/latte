/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 2 "LatteCPP.y" /* yacc.c:339  */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include "Absyn.hpp"

typedef struct yy_buffer_state *YY_BUFFER_STATE;

int yyparse(void);

int yylex(void);

YY_BUFFER_STATE yy_scan_string(const char *str);

void yy_delete_buffer(YY_BUFFER_STATE buf);

int yy_mylinenumber;

int initialize_lexer(FILE *inp);

int yywrap(void) {
    return 1;
}

void yyerror(const char *str) {
    extern char *yytext;
    fprintf(stderr, "error: line %d: %s at %s\n",
            yy_mylinenumber, str, yytext);
}


static Program *YY_RESULT_Program_ = 0;

Program *pProgram(FILE *inp) {
    yy_mylinenumber = 1;
    initialize_lexer(inp);
    if (yyparse()) { /* Failure */
        return 0;
    } else { /* Success */
        return YY_RESULT_Program_;
    }
}

Program *pProgram(const char *str) {
    YY_BUFFER_STATE buf;
    int result;
    yy_mylinenumber = 1;
    initialize_lexer(0);
    buf = yy_scan_string(str);
    result = yyparse();
    yy_delete_buffer(buf);
    if (result) { /* Failure */
        return 0;
    } else { /* Success */
        return YY_RESULT_Program_;
    }
}

static TopDef *YY_RESULT_TopDef_ = 0;

TopDef *pTopDef(FILE *inp) {
    yy_mylinenumber = 1;
    initialize_lexer(inp);
    if (yyparse()) { /* Failure */
        return 0;
    } else { /* Success */
        return YY_RESULT_TopDef_;
    }
}

TopDef *pTopDef(const char *str) {
    YY_BUFFER_STATE buf;
    int result;
    yy_mylinenumber = 1;
    initialize_lexer(0);
    buf = yy_scan_string(str);
    result = yyparse();
    yy_delete_buffer(buf);
    if (result) { /* Failure */
        return 0;
    } else { /* Success */
        return YY_RESULT_TopDef_;
    }
}

static Attribute *YY_RESULT_Attribute_ = 0;

Attribute *pAttribute(FILE *inp) {
    yy_mylinenumber = 1;
    initialize_lexer(inp);
    if (yyparse()) { /* Failure */
        return 0;
    } else { /* Success */
        return YY_RESULT_Attribute_;
    }
}

Attribute *pAttribute(const char *str) {
    YY_BUFFER_STATE buf;
    int result;
    yy_mylinenumber = 1;
    initialize_lexer(0);
    buf = yy_scan_string(str);
    result = yyparse();
    yy_delete_buffer(buf);
    if (result) { /* Failure */
        return 0;
    } else { /* Success */
        return YY_RESULT_Attribute_;
    }
}

static ListAttribute *YY_RESULT_ListAttribute_ = 0;

ListAttribute *pListAttribute(FILE *inp) {
    yy_mylinenumber = 1;
    initialize_lexer(inp);
    if (yyparse()) { /* Failure */
        return 0;
    } else { /* Success */
        return YY_RESULT_ListAttribute_;
    }
}

ListAttribute *pListAttribute(const char *str) {
    YY_BUFFER_STATE buf;
    int result;
    yy_mylinenumber = 1;
    initialize_lexer(0);
    buf = yy_scan_string(str);
    result = yyparse();
    yy_delete_buffer(buf);
    if (result) { /* Failure */
        return 0;
    } else { /* Success */
        return YY_RESULT_ListAttribute_;
    }
}

static ListTopDef *YY_RESULT_ListTopDef_ = 0;

ListTopDef *pListTopDef(FILE *inp) {
    yy_mylinenumber = 1;
    initialize_lexer(inp);
    if (yyparse()) { /* Failure */
        return 0;
    } else { /* Success */
        return YY_RESULT_ListTopDef_;
    }
}

ListTopDef *pListTopDef(const char *str) {
    YY_BUFFER_STATE buf;
    int result;
    yy_mylinenumber = 1;
    initialize_lexer(0);
    buf = yy_scan_string(str);
    result = yyparse();
    yy_delete_buffer(buf);
    if (result) { /* Failure */
        return 0;
    } else { /* Success */
        return YY_RESULT_ListTopDef_;
    }
}

static Arg *YY_RESULT_Arg_ = 0;

Arg *pArg(FILE *inp) {
    yy_mylinenumber = 1;
    initialize_lexer(inp);
    if (yyparse()) { /* Failure */
        return 0;
    } else { /* Success */
        return YY_RESULT_Arg_;
    }
}

Arg *pArg(const char *str) {
    YY_BUFFER_STATE buf;
    int result;
    yy_mylinenumber = 1;
    initialize_lexer(0);
    buf = yy_scan_string(str);
    result = yyparse();
    yy_delete_buffer(buf);
    if (result) { /* Failure */
        return 0;
    } else { /* Success */
        return YY_RESULT_Arg_;
    }
}

static ListArg *YY_RESULT_ListArg_ = 0;

ListArg *pListArg(FILE *inp) {
    yy_mylinenumber = 1;
    initialize_lexer(inp);
    if (yyparse()) { /* Failure */
        return 0;
    } else { /* Success */
        return YY_RESULT_ListArg_;
    }
}

ListArg *pListArg(const char *str) {
    YY_BUFFER_STATE buf;
    int result;
    yy_mylinenumber = 1;
    initialize_lexer(0);
    buf = yy_scan_string(str);
    result = yyparse();
    yy_delete_buffer(buf);
    if (result) { /* Failure */
        return 0;
    } else { /* Success */
        return YY_RESULT_ListArg_;
    }
}

static LVal *YY_RESULT_LVal_ = 0;

LVal *pLVal(FILE *inp) {
    yy_mylinenumber = 1;
    initialize_lexer(inp);
    if (yyparse()) { /* Failure */
        return 0;
    } else { /* Success */
        return YY_RESULT_LVal_;
    }
}

LVal *pLVal(const char *str) {
    YY_BUFFER_STATE buf;
    int result;
    yy_mylinenumber = 1;
    initialize_lexer(0);
    buf = yy_scan_string(str);
    result = yyparse();
    yy_delete_buffer(buf);
    if (result) { /* Failure */
        return 0;
    } else { /* Success */
        return YY_RESULT_LVal_;
    }
}

static Block *YY_RESULT_Block_ = 0;

Block *pBlock(FILE *inp) {
    yy_mylinenumber = 1;
    initialize_lexer(inp);
    if (yyparse()) { /* Failure */
        return 0;
    } else { /* Success */
        return YY_RESULT_Block_;
    }
}

Block *pBlock(const char *str) {
    YY_BUFFER_STATE buf;
    int result;
    yy_mylinenumber = 1;
    initialize_lexer(0);
    buf = yy_scan_string(str);
    result = yyparse();
    yy_delete_buffer(buf);
    if (result) { /* Failure */
        return 0;
    } else { /* Success */
        return YY_RESULT_Block_;
    }
}

static ListStmt *YY_RESULT_ListStmt_ = 0;

ListStmt *pListStmt(FILE *inp) {
    yy_mylinenumber = 1;
    initialize_lexer(inp);
    if (yyparse()) { /* Failure */
        return 0;
    } else { /* Success */
        return YY_RESULT_ListStmt_;
    }
}

ListStmt *pListStmt(const char *str) {
    YY_BUFFER_STATE buf;
    int result;
    yy_mylinenumber = 1;
    initialize_lexer(0);
    buf = yy_scan_string(str);
    result = yyparse();
    yy_delete_buffer(buf);
    if (result) { /* Failure */
        return 0;
    } else { /* Success */
        return YY_RESULT_ListStmt_;
    }
}

static Stmt *YY_RESULT_Stmt_ = 0;

Stmt *pStmt(FILE *inp) {
    yy_mylinenumber = 1;
    initialize_lexer(inp);
    if (yyparse()) { /* Failure */
        return 0;
    } else { /* Success */
        return YY_RESULT_Stmt_;
    }
}

Stmt *pStmt(const char *str) {
    YY_BUFFER_STATE buf;
    int result;
    yy_mylinenumber = 1;
    initialize_lexer(0);
    buf = yy_scan_string(str);
    result = yyparse();
    yy_delete_buffer(buf);
    if (result) { /* Failure */
        return 0;
    } else { /* Success */
        return YY_RESULT_Stmt_;
    }
}

static Item *YY_RESULT_Item_ = 0;

Item *pItem(FILE *inp) {
    yy_mylinenumber = 1;
    initialize_lexer(inp);
    if (yyparse()) { /* Failure */
        return 0;
    } else { /* Success */
        return YY_RESULT_Item_;
    }
}

Item *pItem(const char *str) {
    YY_BUFFER_STATE buf;
    int result;
    yy_mylinenumber = 1;
    initialize_lexer(0);
    buf = yy_scan_string(str);
    result = yyparse();
    yy_delete_buffer(buf);
    if (result) { /* Failure */
        return 0;
    } else { /* Success */
        return YY_RESULT_Item_;
    }
}

static ListItem *YY_RESULT_ListItem_ = 0;

ListItem *pListItem(FILE *inp) {
    yy_mylinenumber = 1;
    initialize_lexer(inp);
    if (yyparse()) { /* Failure */
        return 0;
    } else { /* Success */
        return YY_RESULT_ListItem_;
    }
}

ListItem *pListItem(const char *str) {
    YY_BUFFER_STATE buf;
    int result;
    yy_mylinenumber = 1;
    initialize_lexer(0);
    buf = yy_scan_string(str);
    result = yyparse();
    yy_delete_buffer(buf);
    if (result) { /* Failure */
        return 0;
    } else { /* Success */
        return YY_RESULT_ListItem_;
    }
}

static Type *YY_RESULT_Type_ = 0;

Type *pType(FILE *inp) {
    yy_mylinenumber = 1;
    initialize_lexer(inp);
    if (yyparse()) { /* Failure */
        return 0;
    } else { /* Success */
        return YY_RESULT_Type_;
    }
}

Type *pType(const char *str) {
    YY_BUFFER_STATE buf;
    int result;
    yy_mylinenumber = 1;
    initialize_lexer(0);
    buf = yy_scan_string(str);
    result = yyparse();
    yy_delete_buffer(buf);
    if (result) { /* Failure */
        return 0;
    } else { /* Success */
        return YY_RESULT_Type_;
    }
}

static ListType *YY_RESULT_ListType_ = 0;

ListType *pListType(FILE *inp) {
    yy_mylinenumber = 1;
    initialize_lexer(inp);
    if (yyparse()) { /* Failure */
        return 0;
    } else { /* Success */
        return YY_RESULT_ListType_;
    }
}

ListType *pListType(const char *str) {
    YY_BUFFER_STATE buf;
    int result;
    yy_mylinenumber = 1;
    initialize_lexer(0);
    buf = yy_scan_string(str);
    result = yyparse();
    yy_delete_buffer(buf);
    if (result) { /* Failure */
        return 0;
    } else { /* Success */
        return YY_RESULT_ListType_;
    }
}

static Expr *YY_RESULT_Expr_ = 0;

Expr *pExpr(FILE *inp) {
    yy_mylinenumber = 1;
    initialize_lexer(inp);
    if (yyparse()) { /* Failure */
        return 0;
    } else { /* Success */
        return YY_RESULT_Expr_;
    }
}

Expr *pExpr(const char *str) {
    YY_BUFFER_STATE buf;
    int result;
    yy_mylinenumber = 1;
    initialize_lexer(0);
    buf = yy_scan_string(str);
    result = yyparse();
    yy_delete_buffer(buf);
    if (result) { /* Failure */
        return 0;
    } else { /* Success */
        return YY_RESULT_Expr_;
    }
}

static ListExpr *YY_RESULT_ListExpr_ = 0;

ListExpr *pListExpr(FILE *inp) {
    yy_mylinenumber = 1;
    initialize_lexer(inp);
    if (yyparse()) { /* Failure */
        return 0;
    } else { /* Success */
        return YY_RESULT_ListExpr_;
    }
}

ListExpr *pListExpr(const char *str) {
    YY_BUFFER_STATE buf;
    int result;
    yy_mylinenumber = 1;
    initialize_lexer(0);
    buf = yy_scan_string(str);
    result = yyparse();
    yy_delete_buffer(buf);
    if (result) { /* Failure */
        return 0;
    } else { /* Success */
        return YY_RESULT_ListExpr_;
    }
}

static AddOp *YY_RESULT_AddOp_ = 0;

AddOp *pAddOp(FILE *inp) {
    yy_mylinenumber = 1;
    initialize_lexer(inp);
    if (yyparse()) { /* Failure */
        return 0;
    } else { /* Success */
        return YY_RESULT_AddOp_;
    }
}

AddOp *pAddOp(const char *str) {
    YY_BUFFER_STATE buf;
    int result;
    yy_mylinenumber = 1;
    initialize_lexer(0);
    buf = yy_scan_string(str);
    result = yyparse();
    yy_delete_buffer(buf);
    if (result) { /* Failure */
        return 0;
    } else { /* Success */
        return YY_RESULT_AddOp_;
    }
}

static MulOp *YY_RESULT_MulOp_ = 0;

MulOp *pMulOp(FILE *inp) {
    yy_mylinenumber = 1;
    initialize_lexer(inp);
    if (yyparse()) { /* Failure */
        return 0;
    } else { /* Success */
        return YY_RESULT_MulOp_;
    }
}

MulOp *pMulOp(const char *str) {
    YY_BUFFER_STATE buf;
    int result;
    yy_mylinenumber = 1;
    initialize_lexer(0);
    buf = yy_scan_string(str);
    result = yyparse();
    yy_delete_buffer(buf);
    if (result) { /* Failure */
        return 0;
    } else { /* Success */
        return YY_RESULT_MulOp_;
    }
}

static RelOp *YY_RESULT_RelOp_ = 0;

RelOp *pRelOp(FILE *inp) {
    yy_mylinenumber = 1;
    initialize_lexer(inp);
    if (yyparse()) { /* Failure */
        return 0;
    } else { /* Success */
        return YY_RESULT_RelOp_;
    }
}

RelOp *pRelOp(const char *str) {
    YY_BUFFER_STATE buf;
    int result;
    yy_mylinenumber = 1;
    initialize_lexer(0);
    buf = yy_scan_string(str);
    result = yyparse();
    yy_delete_buffer(buf);
    if (result) { /* Failure */
        return 0;
    } else { /* Success */
        return YY_RESULT_RelOp_;
    }
}


#line 757 "Parser.cpp" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif


/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
enum yytokentype {
    _ERROR_ = 258,
    _SYMB_0 = 259,
    _SYMB_1 = 260,
    _SYMB_2 = 261,
    _SYMB_3 = 262,
    _SYMB_4 = 263,
    _SYMB_5 = 264,
    _SYMB_6 = 265,
    _SYMB_7 = 266,
    _SYMB_8 = 267,
    _SYMB_9 = 268,
    _SYMB_10 = 269,
    _SYMB_11 = 270,
    _SYMB_12 = 271,
    _SYMB_13 = 272,
    _SYMB_14 = 273,
    _SYMB_15 = 274,
    _SYMB_16 = 275,
    _SYMB_17 = 276,
    _SYMB_18 = 277,
    _SYMB_19 = 278,
    _SYMB_20 = 279,
    _SYMB_21 = 280,
    _SYMB_22 = 281,
    _SYMB_23 = 282,
    _SYMB_24 = 283,
    _SYMB_25 = 284,
    _SYMB_26 = 285,
    _SYMB_27 = 286,
    _SYMB_28 = 287,
    _SYMB_29 = 288,
    _SYMB_30 = 289,
    _SYMB_31 = 290,
    _SYMB_32 = 291,
    _SYMB_33 = 292,
    _SYMB_34 = 293,
    _SYMB_35 = 294,
    _SYMB_36 = 295,
    _SYMB_37 = 296,
    _SYMB_38 = 297,
    _SYMB_39 = 298,
    _SYMB_40 = 299,
    _SYMB_41 = 300,
    _STRING_ = 301,
    _INTEGER_ = 302,
    _IDENT_ = 303
};
#endif

/* Value type.  */
#if !defined YYSTYPE && !defined YYSTYPE_IS_DECLARED

union YYSTYPE {
#line 694 "LatteCPP.y" /* yacc.c:355  */

    int int_;
    char char_;
    double double_;
    char *string_;
    Program *program_;
    TopDef *topdef_;
    Attribute *attribute_;
    ListAttribute *listattribute_;
    ListTopDef *listtopdef_;
    Arg *arg_;
    ListArg *listarg_;
    LVal *lval_;
    Block *block_;
    ListStmt *liststmt_;
    Stmt *stmt_;
    Item *item_;
    ListItem *listitem_;
    Type *type_;
    ListType *listtype_;
    Expr *expr_;
    ListExpr *listexpr_;
    AddOp *addop_;
    MulOp *mulop_;
    RelOp *relop_;

#line 870 "Parser.cpp" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse(void);



/* Copy the second part of user declarations.  */

#line 887 "Parser.cpp" /* yacc.c:358  */

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
#else
typedef signed char yytype_int8;
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
# elif ! defined YYSIZE_T
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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
 || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if !defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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


#if !defined yyoverflow || YYERROR_VERBOSE

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
#  if (defined __cplusplus && !defined EXIT_SUCCESS \
       && !((defined YYMALLOC || defined malloc) \
 && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if !defined malloc && !defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if !defined free && !defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (!defined yyoverflow \
     && (!defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc {
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
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

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
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  12
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   224

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  49
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  26
/* YYNRULES -- Number of rules.  */
#define YYNRULES  80
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  142

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   303

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
        {
                0, 2, 2, 2, 2, 2, 2, 2, 2, 2,
                2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
                2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
                2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
                2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
                2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
                2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
                2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
                2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
                2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
                2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
                2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
                2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
                2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
                2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
                2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
                2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
                2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
                2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
                2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
                2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
                2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
                2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
                2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
                2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
                2, 2, 2, 2, 2, 2, 1, 2, 3, 4,
                5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
                15, 16, 17, 18, 19, 20, 21, 22, 23, 24,
                25, 26, 27, 28, 29, 30, 31, 32, 33, 34,
                35, 36, 37, 38, 39, 40, 41, 42, 43, 44,
                45, 46, 47, 48
        };

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
     0,   798,   798,   800,   801,   803,   805,   806,   807,   809,
   810,   812,   814,   815,   816,   818,   819,   820,   822,   824,
   825,   827,   828,   829,   830,   831,   832,   833,   834,   835,
   836,   837,   838,   839,   841,   842,   844,   845,   847,   848,
   849,   850,   851,   852,   858,   859,   860,   861,   862,   863,
   864,   865,   866,   867,   869,   870,   871,   873,   874,   876,
   877,   879,   880,   882,   883,   885,   886,   888,   889,   890,
   892,   893,   895,   896,   897,   899,   900,   901,   902,   903,
   904
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "_ERROR_", "_SYMB_0", "_SYMB_1",
  "_SYMB_2", "_SYMB_3", "_SYMB_4", "_SYMB_5", "_SYMB_6", "_SYMB_7",
  "_SYMB_8", "_SYMB_9", "_SYMB_10", "_SYMB_11", "_SYMB_12", "_SYMB_13",
  "_SYMB_14", "_SYMB_15", "_SYMB_16", "_SYMB_17", "_SYMB_18", "_SYMB_19",
  "_SYMB_20", "_SYMB_21", "_SYMB_22", "_SYMB_23", "_SYMB_24", "_SYMB_25",
  "_SYMB_26", "_SYMB_27", "_SYMB_28", "_SYMB_29", "_SYMB_30", "_SYMB_31",
  "_SYMB_32", "_SYMB_33", "_SYMB_34", "_SYMB_35", "_SYMB_36", "_SYMB_37",
  "_SYMB_38", "_SYMB_39", "_SYMB_40", "_SYMB_41", "_STRING_", "_INTEGER_",
  "_IDENT_", "$accept", "Program", "TopDef", "Attribute", "ListAttribute",
  "ListTopDef", "Arg", "ListArg", "LVal", "Block", "ListStmt", "Stmt",
  "Item", "ListItem", "Type", "Expr6", "Expr5", "Expr4", "Expr3", "Expr2",
  "Expr1", "Expr", "ListExpr", "AddOp", "MulOp", "RelOp", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303
};
# endif

#define YYPACT_NINF -54

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-54)))

#define YYTABLE_NINF -44

#define yytable_value_is_error(Yytable_value) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
        {
                100, -54, -20, -54, -54, -54, -54, 33, 100, -54,
                -16, 43, -54, -54, -54, 35, -19, -19, 47, 54,
                -12, 60, 71, -10, -19, -54, -54, -19, 81, -54,
                -54, -54, -54, -54, 76, 151, -54, -54, 20, 20,
                -54, 84, 86, 59, 11, -54, 90, -54, -54, 4,
                137, -54, -54, -5, -54, -54, 49, 27, 192, 75,
                92, 52, -14, 97, 102, -54, -54, -19, 169, -4,
                -1, -54, 103, 169, 169, 169, 62, 169, 118, 120,
                95, 122, 124, -54, -54, -54, 169, -54, -54, 169,
                169, -54, -54, -54, -54, -54, -54, 169, 169, -54,
                -54, -54, 0, 125, 169, -54, 130, 127, 132, 134,
                -54, 135, -54, -54, 169, 98, -54, -54, 49, -54,
                27, -54, 140, 121, 142, 121, 169, -54, -54, -54,
                -54, -54, 169, 139, -54, -54, -54, 133, 121, 121,
                -54, -54
        };

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
        {
                0, 40, 0, 38, 39, 41, 43, 0, 9, 2,
                0, 0, 1, 10, 42, 0, 6, 12, 7, 0,
                0, 13, 0, 0, 6, 4, 5, 12, 0, 11,
                8, 14, 19, 3, 0, 0, 18, 21, 0, 0,
                48, 0, 0, 0, 0, 47, 0, 50, 46, 15,
                44, 22, 20, 0, 56, 58, 60, 62, 64, 66,
                0, 44, 0, 0, 15, 54, 55, 0, 0, 52,
                0, 28, 0, 0, 67, 0, 0, 0, 0, 0,
                34, 36, 0, 72, 73, 74, 0, 71, 70, 0,
                0, 75, 76, 77, 78, 79, 80, 0, 0, 33,
                45, 53, 0, 0, 0, 27, 0, 68, 0, 0,
                17, 0, 25, 26, 0, 0, 23, 57, 59, 63,
                61, 65, 0, 0, 0, 0, 67, 49, 16, 24,
                35, 37, 0, 29, 51, 31, 69, 0, 0, 0,
                30, 32
        };

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
        {
                -54, -54, -54, -54, 148, 167, -54, 149, -34, 150,
                -54, -53, -54, 64, 10, 40, 91, 93, 83, -54,
                96, -33, 55, -54, -54, -54
        };

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
        {
                -1, 7, 8, 18, 19, 9, 21, 22, 61, 51,
                34, 52, 81, 82, 53, 54, 55, 56, 57, 58,
                59, 60, 108, 89, 86, 97
        };

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
        {
                50, 14, 63, 14, 100, 14, -43, 14, 74, 104,
                10, 72, 14, -43, 1, 35, 14, 14, 10, 71,
                3, -43, -43, 4, 35, 5, 20, 23, 11, 6,
                38, 39, 15, 12, 20, 103, 26, 23, 29, 17,
                106, 107, 109, 80, 111, 62, 87, 40, 122, 16,
                88, 43, -43, 70, 45, 24, 40, 47, 48, 64,
                43, 25, 75, 45, 76, 121, 47, 48, 64, 27,
                133, 124, 135, 83, 84, 85, 28, 102, 65, 66,
                35, 130, 32, 36, 37, 140, 141, 32, 67, 50,
                68, 50, 1, 107, 73, 38, 39, 98, 3, 137,
                99, 4, 101, 5, 50, 50, 74, 69, 114, 1,
                110, 105, 40, 41, 42, 3, 43, 44, 4, 45,
                5, 46, 47, 48, 49, 35, 112, 32, 113, 37,
                123, 115, 116, 1, 2, 125, 126, 127, 139, 3,
                38, 39, 4, 129, 5, 128, 80, 75, 6, 76,
                77, 78, 79, 134, 1, 35, 132, 40, 41, 42,
                3, 43, 44, 4, 45, 5, 46, 47, 48, 49,
                38, 39, 30, 35, 138, 13, 31, 117, 33, 131,
                120, 136, 118, 0, 1, 0, 119, 40, 38, 39,
                3, 43, 0, 4, 45, 5, 0, 47, 48, 49,
                0, 0, 0, 0, 0, 40, 0, 0, 0, 43,
                0, 0, 45, 90, 0, 47, 48, 64, 0, 91,
                92, 93, 94, 95, 96
        };

static const yytype_int16 yycheck[] =
        {
                34, 17, 35, 17, 18, 17, 10, 17, 4, 10,
                0, 44, 17, 17, 33, 4, 17, 17, 8, 8,
                39, 17, 18, 42, 4, 44, 16, 17, 48, 48,
                19, 20, 48, 0, 24, 68, 48, 27, 48, 4,
                73, 74, 75, 48, 77, 35, 19, 36, 48, 6,
                23, 40, 48, 43, 43, 8, 36, 46, 47, 48,
                40, 7, 10, 43, 12, 98, 46, 47, 48, 9,
                123, 104, 125, 24, 25, 26, 5, 67, 38, 39,
                4, 114, 6, 7, 8, 138, 139, 6, 4, 123,
                4, 125, 33, 126, 4, 19, 20, 22, 39, 132,
                8, 42, 5, 44, 138, 139, 4, 48, 13, 33,
                48, 8, 36, 37, 38, 39, 40, 41, 42, 43,
                44, 45, 46, 47, 48, 4, 8, 6, 8, 8,
                5, 9, 8, 33, 34, 5, 9, 5, 5, 39,
                19, 20, 42, 8, 44, 11, 48, 10, 48, 12,
                13, 14, 15, 11, 33, 4, 16, 36, 37, 38,
                39, 40, 41, 42, 43, 44, 45, 46, 47, 48,
                19, 20, 24, 4, 35, 8, 27, 86, 28, 115,
                97, 126, 89, -1, 33, -1, 90, 36, 19, 20,
                39, 40, -1, 42, 43, 44, -1, 46, 47, 48,
                -1, -1, -1, -1, -1, 36, -1, -1, -1, 40,
                -1, -1, 43, 21, -1, 46, 47, 48, -1, 27,
                28, 29, 30, 31, 32
        };

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
        {
                0, 33, 34, 39, 42, 44, 48, 50, 51, 54,
                63, 48, 0, 54, 17, 48, 6, 4, 52, 53,
                63, 55, 56, 63, 8, 7, 48, 9, 5, 48,
                53, 56, 6, 58, 59, 4, 7, 8, 19, 20,
                36, 37, 38, 40, 41, 43, 45, 46, 47, 48,
                57, 58, 60, 63, 64, 65, 66, 67, 68, 69,
                70, 57, 63, 70, 48, 64, 64, 4, 4, 48,
                63, 8, 70, 4, 4, 10, 12, 13, 14, 15,
                48, 61, 62, 24, 25, 26, 73, 19, 23, 72,
                21, 27, 28, 29, 30, 31, 32, 74, 22, 8,
                18, 5, 63, 70, 10, 8, 70, 70, 71, 70,
                48, 70, 8, 8, 13, 9, 8, 65, 66, 69,
                67, 70, 48, 5, 70, 5, 9, 5, 11, 8,
                70, 62, 16, 60, 11, 60, 71, 70, 35, 5,
                60, 60
        };

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
        {
                0, 49, 50, 51, 51, 52, 53, 53, 53, 54,
                54, 55, 56, 56, 56, 57, 57, 57, 58, 59,
                59, 60, 60, 60, 60, 60, 60, 60, 60, 60,
                60, 60, 60, 60, 61, 61, 62, 62, 63, 63,
                63, 63, 63, 63, 64, 64, 64, 64, 64, 64,
                64, 64, 64, 64, 65, 65, 65, 66, 66, 67,
                67, 68, 68, 69, 69, 70, 70, 71, 71, 71,
                72, 72, 73, 73, 73, 74, 74, 74, 74, 74,
                74
        };

/* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
        {
                0, 2, 1, 6, 5, 2, 0, 1, 3, 1,
                2, 2, 0, 1, 3, 1, 4, 3, 3, 0,
                2, 1, 1, 3, 4, 3, 3, 3, 2, 5,
                7, 5, 8, 2, 1, 3, 1, 3, 1, 1,
                1, 1, 2, 1, 1, 3, 1, 1, 1, 4,
                1, 5, 2, 3, 2, 2, 1, 3, 1, 3,
                1, 3, 1, 3, 1, 3, 1, 0, 1, 3,
                1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                1
        };


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


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
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
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
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
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
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
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

static void
yydestruct(const char *yymsg, int yytype, YYSTYPE *yyvaluep) {
    YYUSE (yyvaluep);
    if (!yymsg)
        yymsg = "Deleting";
    YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

    YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
    YYUSE (yytype);
    YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse(void) {
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

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

    if (yyss + yystacksize - 1 <= yyssp) {
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
                    (union yyalloc *) YYSTACK_ALLOC(YYSTACK_BYTES (yystacksize));
            if (!yyptr)
                goto yyexhaustedlab;
            YYSTACK_RELOCATE (yyss_alloc, yyss);
            YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
            if (yyss1 != yyssa)
                YYSTACK_FREE(yyss1);
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
    if (yychar == YYEMPTY) {
        YYDPRINTF ((stderr, "Reading a token: "));
        yychar = yylex();
    }

    if (yychar <= YYEOF) {
        yychar = yytoken = YYEOF;
        YYDPRINTF ((stderr, "Now at end of input.\n"));
    } else {
        yytoken = YYTRANSLATE (yychar);
        YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

    /* If the proper action on seeing token YYTOKEN is to reduce or to
       detect an error, take that action.  */
    yyn += yytoken;
    if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
        goto yydefault;
    yyn = yytable[yyn];
    if (yyn <= 0) {
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
       '$$ = $1'.

       Otherwise, the following line sets YYVAL to garbage.
       This behavior is undocumented and Bison
       users should not rely upon it.  Assigning to YYVAL
       unconditionally makes the parser a bit smaller, and it avoids a
       GCC warning that YYVAL may be used uninitialized.  */
    yyval = yyvsp[1 - yylen];


    YY_REDUCE_PRINT (yyn);
    switch (yyn) {
        case 2:
#line 798 "LatteCPP.y" /* yacc.c:1646  */
        {
            std::reverse((yyvsp[0].listtopdef_)->begin(), (yyvsp[0].listtopdef_)->end());
            (yyval.program_) = new Prog((yyvsp[0].listtopdef_));
            (yyval.program_)->line_number = yy_mylinenumber;
            YY_RESULT_Program_ = (yyval.program_);
        }
#line 2085 "Parser.cpp" /* yacc.c:1646  */
            break;

        case 3:
#line 800 "LatteCPP.y" /* yacc.c:1646  */
        {
            std::reverse((yyvsp[-2].listarg_)->begin(), (yyvsp[-2].listarg_)->end());
            (yyval.topdef_) = new FnDef((yyvsp[-5].type_), (yyvsp[-4].string_), (yyvsp[-2].listarg_),
                                        (yyvsp[0].block_));
            (yyval.topdef_)->line_number = yy_mylinenumber;
        }
#line 2091 "Parser.cpp" /* yacc.c:1646  */
            break;

        case 4:
#line 801 "LatteCPP.y" /* yacc.c:1646  */
        {
            std::reverse((yyvsp[-1].listattribute_)->begin(), (yyvsp[-1].listattribute_)->end());
            (yyval.topdef_) = new StructDef((yyvsp[-3].string_), (yyvsp[-1].listattribute_));
            (yyval.topdef_)->line_number = yy_mylinenumber;
        }
#line 2097 "Parser.cpp" /* yacc.c:1646  */
            break;

        case 5:
#line 803 "LatteCPP.y" /* yacc.c:1646  */
        {
            (yyval.attribute_) = new Attr((yyvsp[-1].type_), (yyvsp[0].string_));
            (yyval.attribute_)->line_number = yy_mylinenumber;
        }
#line 2103 "Parser.cpp" /* yacc.c:1646  */
            break;

        case 6:
#line 805 "LatteCPP.y" /* yacc.c:1646  */
        {
            (yyval.listattribute_) = new ListAttribute();
        }
#line 2109 "Parser.cpp" /* yacc.c:1646  */
            break;

        case 7:
#line 806 "LatteCPP.y" /* yacc.c:1646  */
        {
            (yyval.listattribute_) = new ListAttribute();
            (yyval.listattribute_)->push_back((yyvsp[0].attribute_));
        }
#line 2115 "Parser.cpp" /* yacc.c:1646  */
            break;

        case 8:
#line 807 "LatteCPP.y" /* yacc.c:1646  */
        {
            (yyvsp[0].listattribute_)->push_back((yyvsp[-2].attribute_));
            (yyval.listattribute_) = (yyvsp[0].listattribute_);
        }
#line 2121 "Parser.cpp" /* yacc.c:1646  */
            break;

        case 9:
#line 809 "LatteCPP.y" /* yacc.c:1646  */
        {
            (yyval.listtopdef_) = new ListTopDef();
            (yyval.listtopdef_)->push_back((yyvsp[0].topdef_));
        }
#line 2127 "Parser.cpp" /* yacc.c:1646  */
            break;

        case 10:
#line 810 "LatteCPP.y" /* yacc.c:1646  */
        {
            (yyvsp[0].listtopdef_)->push_back((yyvsp[-1].topdef_));
            (yyval.listtopdef_) = (yyvsp[0].listtopdef_);
        }
#line 2133 "Parser.cpp" /* yacc.c:1646  */
            break;

        case 11:
#line 812 "LatteCPP.y" /* yacc.c:1646  */
        {
            (yyval.arg_) = new Ar((yyvsp[-1].type_), (yyvsp[0].string_));
            (yyval.arg_)->line_number = yy_mylinenumber;
        }
#line 2139 "Parser.cpp" /* yacc.c:1646  */
            break;

        case 12:
#line 814 "LatteCPP.y" /* yacc.c:1646  */
        {
            (yyval.listarg_) = new ListArg();
        }
#line 2145 "Parser.cpp" /* yacc.c:1646  */
            break;

        case 13:
#line 815 "LatteCPP.y" /* yacc.c:1646  */
        {
            (yyval.listarg_) = new ListArg();
            (yyval.listarg_)->push_back((yyvsp[0].arg_));
        }
#line 2151 "Parser.cpp" /* yacc.c:1646  */
            break;

        case 14:
#line 816 "LatteCPP.y" /* yacc.c:1646  */
        {
            (yyvsp[0].listarg_)->push_back((yyvsp[-2].arg_));
            (yyval.listarg_) = (yyvsp[0].listarg_);
        }
#line 2157 "Parser.cpp" /* yacc.c:1646  */
            break;

        case 15:
#line 818 "LatteCPP.y" /* yacc.c:1646  */
        {
            (yyval.lval_) = new LIdent((yyvsp[0].string_));
            (yyval.lval_)->line_number = yy_mylinenumber;
        }
#line 2163 "Parser.cpp" /* yacc.c:1646  */
            break;

        case 16:
#line 819 "LatteCPP.y" /* yacc.c:1646  */
        {
            (yyval.lval_) = new LArray((yyvsp[-3].lval_), (yyvsp[-1].expr_));
            (yyval.lval_)->line_number = yy_mylinenumber;
        }
#line 2169 "Parser.cpp" /* yacc.c:1646  */
            break;

        case 17:
#line 820 "LatteCPP.y" /* yacc.c:1646  */
        {
            (yyval.lval_) = new LStruct((yyvsp[-2].lval_), (yyvsp[0].string_));
            (yyval.lval_)->line_number = yy_mylinenumber;
        }
#line 2175 "Parser.cpp" /* yacc.c:1646  */
            break;

        case 18:
#line 822 "LatteCPP.y" /* yacc.c:1646  */
        {
            (yyval.block_) = new Blk((yyvsp[-1].liststmt_));
            (yyval.block_)->line_number = yy_mylinenumber;
        }
#line 2181 "Parser.cpp" /* yacc.c:1646  */
            break;

        case 19:
#line 824 "LatteCPP.y" /* yacc.c:1646  */
        {
            (yyval.liststmt_) = new ListStmt();
        }
#line 2187 "Parser.cpp" /* yacc.c:1646  */
            break;

        case 20:
#line 825 "LatteCPP.y" /* yacc.c:1646  */
        {
            (yyvsp[-1].liststmt_)->push_back((yyvsp[0].stmt_));
            (yyval.liststmt_) = (yyvsp[-1].liststmt_);
        }
#line 2193 "Parser.cpp" /* yacc.c:1646  */
            break;

        case 21:
#line 827 "LatteCPP.y" /* yacc.c:1646  */
        {
            (yyval.stmt_) = new Empty();
            (yyval.stmt_)->line_number = yy_mylinenumber;
        }
#line 2199 "Parser.cpp" /* yacc.c:1646  */
            break;

        case 22:
#line 828 "LatteCPP.y" /* yacc.c:1646  */
        {
            (yyval.stmt_) = new BStmt((yyvsp[0].block_));
            (yyval.stmt_)->line_number = yy_mylinenumber;
        }
#line 2205 "Parser.cpp" /* yacc.c:1646  */
            break;

        case 23:
#line 829 "LatteCPP.y" /* yacc.c:1646  */
        {
            std::reverse((yyvsp[-1].listitem_)->begin(), (yyvsp[-1].listitem_)->end());
            (yyval.stmt_) = new Decl((yyvsp[-2].type_), (yyvsp[-1].listitem_));
            (yyval.stmt_)->line_number = yy_mylinenumber;
        }
#line 2211 "Parser.cpp" /* yacc.c:1646  */
            break;

        case 24:
#line 830 "LatteCPP.y" /* yacc.c:1646  */
        {
            (yyval.stmt_) = new Ass((yyvsp[-3].lval_), (yyvsp[-1].expr_));
            (yyval.stmt_)->line_number = yy_mylinenumber;
        }
#line 2217 "Parser.cpp" /* yacc.c:1646  */
            break;

        case 25:
#line 831 "LatteCPP.y" /* yacc.c:1646  */
        {
            (yyval.stmt_) = new Incr((yyvsp[-2].lval_));
            (yyval.stmt_)->line_number = yy_mylinenumber;
        }
#line 2223 "Parser.cpp" /* yacc.c:1646  */
            break;

        case 26:
#line 832 "LatteCPP.y" /* yacc.c:1646  */
        {
            (yyval.stmt_) = new Decr((yyvsp[-2].lval_));
            (yyval.stmt_)->line_number = yy_mylinenumber;
        }
#line 2229 "Parser.cpp" /* yacc.c:1646  */
            break;

        case 27:
#line 833 "LatteCPP.y" /* yacc.c:1646  */
        {
            (yyval.stmt_) = new Ret((yyvsp[-1].expr_));
            (yyval.stmt_)->line_number = yy_mylinenumber;
        }
#line 2235 "Parser.cpp" /* yacc.c:1646  */
            break;

        case 28:
#line 834 "LatteCPP.y" /* yacc.c:1646  */
        {
            (yyval.stmt_) = new VRet();
            (yyval.stmt_)->line_number = yy_mylinenumber;
        }
#line 2241 "Parser.cpp" /* yacc.c:1646  */
            break;

        case 29:
#line 835 "LatteCPP.y" /* yacc.c:1646  */
        {
            (yyval.stmt_) = new Cond((yyvsp[-2].expr_), (yyvsp[0].stmt_));
            (yyval.stmt_)->line_number = yy_mylinenumber;
        }
#line 2247 "Parser.cpp" /* yacc.c:1646  */
            break;

        case 30:
#line 836 "LatteCPP.y" /* yacc.c:1646  */
        {
            (yyval.stmt_) = new CondElse((yyvsp[-4].expr_), (yyvsp[-2].stmt_), (yyvsp[0].stmt_));
            (yyval.stmt_)->line_number = yy_mylinenumber;
        }
#line 2253 "Parser.cpp" /* yacc.c:1646  */
            break;

        case 31:
#line 837 "LatteCPP.y" /* yacc.c:1646  */
        {
            (yyval.stmt_) = new While((yyvsp[-2].expr_), (yyvsp[0].stmt_));
            (yyval.stmt_)->line_number = yy_mylinenumber;
        }
#line 2259 "Parser.cpp" /* yacc.c:1646  */
            break;

        case 32:
#line 838 "LatteCPP.y" /* yacc.c:1646  */
        {
            (yyval.stmt_) = new For((yyvsp[-5].type_), (yyvsp[-4].string_), (yyvsp[-2].expr_), (yyvsp[0].stmt_));
            (yyval.stmt_)->line_number = yy_mylinenumber;
        }
#line 2265 "Parser.cpp" /* yacc.c:1646  */
            break;

        case 33:
#line 839 "LatteCPP.y" /* yacc.c:1646  */
        {
            (yyval.stmt_) = new SExp((yyvsp[-1].expr_));
            (yyval.stmt_)->line_number = yy_mylinenumber;
        }
#line 2271 "Parser.cpp" /* yacc.c:1646  */
            break;

        case 34:
#line 841 "LatteCPP.y" /* yacc.c:1646  */
        {
            (yyval.item_) = new NoInit((yyvsp[0].string_));
            (yyval.item_)->line_number = yy_mylinenumber;
        }
#line 2277 "Parser.cpp" /* yacc.c:1646  */
            break;

        case 35:
#line 842 "LatteCPP.y" /* yacc.c:1646  */
        {
            (yyval.item_) = new Init((yyvsp[-2].string_), (yyvsp[0].expr_));
            (yyval.item_)->line_number = yy_mylinenumber;
        }
#line 2283 "Parser.cpp" /* yacc.c:1646  */
            break;

        case 36:
#line 844 "LatteCPP.y" /* yacc.c:1646  */
        {
            (yyval.listitem_) = new ListItem();
            (yyval.listitem_)->push_back((yyvsp[0].item_));
        }
#line 2289 "Parser.cpp" /* yacc.c:1646  */
            break;

        case 37:
#line 845 "LatteCPP.y" /* yacc.c:1646  */
        {
            (yyvsp[0].listitem_)->push_back((yyvsp[-2].item_));
            (yyval.listitem_) = (yyvsp[0].listitem_);
        }
#line 2295 "Parser.cpp" /* yacc.c:1646  */
            break;

        case 38:
#line 847 "LatteCPP.y" /* yacc.c:1646  */
        {
            (yyval.type_) = new Int();
            (yyval.type_)->line_number = yy_mylinenumber;
        }
#line 2301 "Parser.cpp" /* yacc.c:1646  */
            break;

        case 39:
#line 848 "LatteCPP.y" /* yacc.c:1646  */
        {
            (yyval.type_) = new Str();
            (yyval.type_)->line_number = yy_mylinenumber;
        }
#line 2307 "Parser.cpp" /* yacc.c:1646  */
            break;

        case 40:
#line 849 "LatteCPP.y" /* yacc.c:1646  */
        {
            (yyval.type_) = new Bool();
            (yyval.type_)->line_number = yy_mylinenumber;
        }
#line 2313 "Parser.cpp" /* yacc.c:1646  */
            break;

        case 41:
#line 850 "LatteCPP.y" /* yacc.c:1646  */
        {
            (yyval.type_) = new Void();
            (yyval.type_)->line_number = yy_mylinenumber;
        }
#line 2319 "Parser.cpp" /* yacc.c:1646  */
            break;

        case 42:
#line 851 "LatteCPP.y" /* yacc.c:1646  */
        {
            (yyval.type_) = new Array((yyvsp[-1].type_));
            (yyval.type_)->line_number = yy_mylinenumber;
        }
#line 2325 "Parser.cpp" /* yacc.c:1646  */
            break;

        case 43:
#line 852 "LatteCPP.y" /* yacc.c:1646  */
        {
            (yyval.type_) = new Struct((yyvsp[0].string_));
            (yyval.type_)->line_number = yy_mylinenumber;
        }
#line 2331 "Parser.cpp" /* yacc.c:1646  */
            break;

        case 44:
#line 858 "LatteCPP.y" /* yacc.c:1646  */
        {
            (yyval.expr_) = new EVar((yyvsp[0].lval_));
            (yyval.expr_)->line_number = yy_mylinenumber;
        }
#line 2337 "Parser.cpp" /* yacc.c:1646  */
            break;

        case 45:
#line 859 "LatteCPP.y" /* yacc.c:1646  */
        {
            (yyval.expr_) = new ENull((yyvsp[-1].type_));
            (yyval.expr_)->line_number = yy_mylinenumber;
        }
#line 2343 "Parser.cpp" /* yacc.c:1646  */
            break;

        case 46:
#line 860 "LatteCPP.y" /* yacc.c:1646  */
        {
            (yyval.expr_) = new ELitInt((yyvsp[0].int_));
            (yyval.expr_)->line_number = yy_mylinenumber;
        }
#line 2349 "Parser.cpp" /* yacc.c:1646  */
            break;

        case 47:
#line 861 "LatteCPP.y" /* yacc.c:1646  */
        {
            (yyval.expr_) = new ELitTrue();
            (yyval.expr_)->line_number = yy_mylinenumber;
        }
#line 2355 "Parser.cpp" /* yacc.c:1646  */
            break;

        case 48:
#line 862 "LatteCPP.y" /* yacc.c:1646  */
        {
            (yyval.expr_) = new ELitFalse();
            (yyval.expr_)->line_number = yy_mylinenumber;
        }
#line 2361 "Parser.cpp" /* yacc.c:1646  */
            break;

        case 49:
#line 863 "LatteCPP.y" /* yacc.c:1646  */
        {
            std::reverse((yyvsp[-1].listexpr_)->begin(), (yyvsp[-1].listexpr_)->end());
            (yyval.expr_) = new EApp((yyvsp[-3].string_), (yyvsp[-1].listexpr_));
            (yyval.expr_)->line_number = yy_mylinenumber;
        }
#line 2367 "Parser.cpp" /* yacc.c:1646  */
            break;

        case 50:
#line 864 "LatteCPP.y" /* yacc.c:1646  */
        {
            (yyval.expr_) = new EString((yyvsp[0].string_));
            (yyval.expr_)->line_number = yy_mylinenumber;
        }
#line 2373 "Parser.cpp" /* yacc.c:1646  */
            break;

        case 51:
#line 865 "LatteCPP.y" /* yacc.c:1646  */
        {
            (yyval.expr_) = new EArray((yyvsp[-3].type_), (yyvsp[-1].expr_));
            (yyval.expr_)->line_number = yy_mylinenumber;
        }
#line 2379 "Parser.cpp" /* yacc.c:1646  */
            break;

        case 52:
#line 866 "LatteCPP.y" /* yacc.c:1646  */
        {
            (yyval.expr_) = new EStruct((yyvsp[0].string_));
            (yyval.expr_)->line_number = yy_mylinenumber;
        }
#line 2385 "Parser.cpp" /* yacc.c:1646  */
            break;

        case 53:
#line 867 "LatteCPP.y" /* yacc.c:1646  */
        {
            (yyval.expr_) = (yyvsp[-1].expr_);
        }
#line 2391 "Parser.cpp" /* yacc.c:1646  */
            break;

        case 54:
#line 869 "LatteCPP.y" /* yacc.c:1646  */
        {
            (yyval.expr_) = new Neg((yyvsp[0].expr_));
            (yyval.expr_)->line_number = yy_mylinenumber;
        }
#line 2397 "Parser.cpp" /* yacc.c:1646  */
            break;

        case 55:
#line 870 "LatteCPP.y" /* yacc.c:1646  */
        {
            (yyval.expr_) = new Not((yyvsp[0].expr_));
            (yyval.expr_)->line_number = yy_mylinenumber;
        }
#line 2403 "Parser.cpp" /* yacc.c:1646  */
            break;

        case 56:
#line 871 "LatteCPP.y" /* yacc.c:1646  */
        {
            (yyval.expr_) = (yyvsp[0].expr_);
        }
#line 2409 "Parser.cpp" /* yacc.c:1646  */
            break;

        case 57:
#line 873 "LatteCPP.y" /* yacc.c:1646  */
        {
            (yyval.expr_) = new EMul((yyvsp[-2].expr_), (yyvsp[-1].mulop_), (yyvsp[0].expr_));
            (yyval.expr_)->line_number = yy_mylinenumber;
        }
#line 2415 "Parser.cpp" /* yacc.c:1646  */
            break;

        case 58:
#line 874 "LatteCPP.y" /* yacc.c:1646  */
        {
            (yyval.expr_) = (yyvsp[0].expr_);
        }
#line 2421 "Parser.cpp" /* yacc.c:1646  */
            break;

        case 59:
#line 876 "LatteCPP.y" /* yacc.c:1646  */
        {
            (yyval.expr_) = new EAdd((yyvsp[-2].expr_), (yyvsp[-1].addop_), (yyvsp[0].expr_));
            (yyval.expr_)->line_number = yy_mylinenumber;
        }
#line 2427 "Parser.cpp" /* yacc.c:1646  */
            break;

        case 60:
#line 877 "LatteCPP.y" /* yacc.c:1646  */
        {
            (yyval.expr_) = (yyvsp[0].expr_);
        }
#line 2433 "Parser.cpp" /* yacc.c:1646  */
            break;

        case 61:
#line 879 "LatteCPP.y" /* yacc.c:1646  */
        {
            (yyval.expr_) = new ERel((yyvsp[-2].expr_), (yyvsp[-1].relop_), (yyvsp[0].expr_));
            (yyval.expr_)->line_number = yy_mylinenumber;
        }
#line 2439 "Parser.cpp" /* yacc.c:1646  */
            break;

        case 62:
#line 880 "LatteCPP.y" /* yacc.c:1646  */
        {
            (yyval.expr_) = (yyvsp[0].expr_);
        }
#line 2445 "Parser.cpp" /* yacc.c:1646  */
            break;

        case 63:
#line 882 "LatteCPP.y" /* yacc.c:1646  */
        {
            (yyval.expr_) = new EAnd((yyvsp[-2].expr_), (yyvsp[0].expr_));
            (yyval.expr_)->line_number = yy_mylinenumber;
        }
#line 2451 "Parser.cpp" /* yacc.c:1646  */
            break;

        case 64:
#line 883 "LatteCPP.y" /* yacc.c:1646  */
        {
            (yyval.expr_) = (yyvsp[0].expr_);
        }
#line 2457 "Parser.cpp" /* yacc.c:1646  */
            break;

        case 65:
#line 885 "LatteCPP.y" /* yacc.c:1646  */
        {
            (yyval.expr_) = new EOr((yyvsp[-2].expr_), (yyvsp[0].expr_));
            (yyval.expr_)->line_number = yy_mylinenumber;
        }
#line 2463 "Parser.cpp" /* yacc.c:1646  */
            break;

        case 66:
#line 886 "LatteCPP.y" /* yacc.c:1646  */
        {
            (yyval.expr_) = (yyvsp[0].expr_);
        }
#line 2469 "Parser.cpp" /* yacc.c:1646  */
            break;

        case 67:
#line 888 "LatteCPP.y" /* yacc.c:1646  */
        {
            (yyval.listexpr_) = new ListExpr();
        }
#line 2475 "Parser.cpp" /* yacc.c:1646  */
            break;

        case 68:
#line 889 "LatteCPP.y" /* yacc.c:1646  */
        {
            (yyval.listexpr_) = new ListExpr();
            (yyval.listexpr_)->push_back((yyvsp[0].expr_));
        }
#line 2481 "Parser.cpp" /* yacc.c:1646  */
            break;

        case 69:
#line 890 "LatteCPP.y" /* yacc.c:1646  */
        {
            (yyvsp[0].listexpr_)->push_back((yyvsp[-2].expr_));
            (yyval.listexpr_) = (yyvsp[0].listexpr_);
        }
#line 2487 "Parser.cpp" /* yacc.c:1646  */
            break;

        case 70:
#line 892 "LatteCPP.y" /* yacc.c:1646  */
        {
            (yyval.addop_) = new Plus();
            (yyval.addop_)->line_number = yy_mylinenumber;
        }
#line 2493 "Parser.cpp" /* yacc.c:1646  */
            break;

        case 71:
#line 893 "LatteCPP.y" /* yacc.c:1646  */
        {
            (yyval.addop_) = new Minus();
            (yyval.addop_)->line_number = yy_mylinenumber;
        }
#line 2499 "Parser.cpp" /* yacc.c:1646  */
            break;

        case 72:
#line 895 "LatteCPP.y" /* yacc.c:1646  */
        {
            (yyval.mulop_) = new Times();
            (yyval.mulop_)->line_number = yy_mylinenumber;
        }
#line 2505 "Parser.cpp" /* yacc.c:1646  */
            break;

        case 73:
#line 896 "LatteCPP.y" /* yacc.c:1646  */
        {
            (yyval.mulop_) = new Div();
            (yyval.mulop_)->line_number = yy_mylinenumber;
        }
#line 2511 "Parser.cpp" /* yacc.c:1646  */
            break;

        case 74:
#line 897 "LatteCPP.y" /* yacc.c:1646  */
        {
            (yyval.mulop_) = new Mod();
            (yyval.mulop_)->line_number = yy_mylinenumber;
        }
#line 2517 "Parser.cpp" /* yacc.c:1646  */
            break;

        case 75:
#line 899 "LatteCPP.y" /* yacc.c:1646  */
        {
            (yyval.relop_) = new LTH();
            (yyval.relop_)->line_number = yy_mylinenumber;
        }
#line 2523 "Parser.cpp" /* yacc.c:1646  */
            break;

        case 76:
#line 900 "LatteCPP.y" /* yacc.c:1646  */
        {
            (yyval.relop_) = new LE();
            (yyval.relop_)->line_number = yy_mylinenumber;
        }
#line 2529 "Parser.cpp" /* yacc.c:1646  */
            break;

        case 77:
#line 901 "LatteCPP.y" /* yacc.c:1646  */
        {
            (yyval.relop_) = new GTH();
            (yyval.relop_)->line_number = yy_mylinenumber;
        }
#line 2535 "Parser.cpp" /* yacc.c:1646  */
            break;

        case 78:
#line 902 "LatteCPP.y" /* yacc.c:1646  */
        {
            (yyval.relop_) = new GE();
            (yyval.relop_)->line_number = yy_mylinenumber;
        }
#line 2541 "Parser.cpp" /* yacc.c:1646  */
            break;

        case 79:
#line 903 "LatteCPP.y" /* yacc.c:1646  */
        {
            (yyval.relop_) = new EQU();
            (yyval.relop_)->line_number = yy_mylinenumber;
        }
#line 2547 "Parser.cpp" /* yacc.c:1646  */
            break;

        case 80:
#line 904 "LatteCPP.y" /* yacc.c:1646  */
        {
            (yyval.relop_) = new NE();
            (yyval.relop_)->line_number = yy_mylinenumber;
        }
#line 2553 "Parser.cpp" /* yacc.c:1646  */
            break;


#line 2557 "Parser.cpp" /* yacc.c:1646  */
        default:
            break;
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

    /* Now 'shift' the result of the reduction.  Determine what state
       that goes to, based on the state we popped back to and the rule
       number reduced by.  */

    yyn = yyr1[yyn];

    yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
    if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
        yystate = yytable[yystate];
    else
        yystate = yydefgoto[yyn - YYNTOKENS];

    goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
    yyerrlab:
    /* Make sure we have latest lookahead translation.  See comments at
       user semantic actions for why this is necessary.  */
    yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

    /* If not already recovering from an error, report this error.  */
    if (!yyerrstatus) {
        ++yynerrs;
#if !YYERROR_VERBOSE
        yyerror(YY_("syntax error"));
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


    if (yyerrstatus == 3) {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        if (yychar <= YYEOF) {
            /* Return failure if at end of input.  */
            if (yychar == YYEOF)
                YYABORT;
        } else {
            yydestruct("Error: discarding",
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

    for (;;) {
        yyn = yypact[yystate];
        if (!yypact_value_is_default (yyn)) {
            yyn += YYTERROR;
            if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR) {
                yyn = yytable[yyn];
                if (0 < yyn)
                    break;
            }
        }

        /* Pop the current state because it cannot handle the error token.  */
        if (yyssp == yyss)
            YYABORT;


        yydestruct("Error: popping",
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
    yyerror(YY_("memory exhausted"));
    yyresult = 2;
    /* Fall through.  */
#endif

    yyreturn:
    if (yychar != YYEMPTY) {
        /* Make sure we have latest lookahead translation.  See comments at
           user semantic actions for why this is necessary.  */
        yytoken = YYTRANSLATE (yychar);
        yydestruct("Cleanup: discarding lookahead",
                   yytoken, &yylval);
    }
    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    YYPOPSTACK (yylen);
    YY_STACK_PRINT (yyss, yyssp);
    while (yyssp != yyss) {
        yydestruct("Cleanup: popping",
                   yystos[*yyssp], yyvsp);
        YYPOPSTACK (1);
    }
#ifndef yyoverflow
    if (yyss != yyssa)
        YYSTACK_FREE(yyss);
#endif
#if YYERROR_VERBOSE
    if (yymsg != yymsgbuf)
      YYSTACK_FREE (yymsg);
#endif
    return yyresult;
}
