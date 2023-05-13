/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

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

#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
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
  enum yytokentype
  {
    INT = 258,
    CHAR = 259,
    ID = 260,
    RELOP = 261,
    TYPE = 262,
    FLOAT = 263,
    DPLUS = 264,
    LP = 265,
    RP = 266,
    LC = 267,
    RC = 268,
    LB = 269,
    RB = 270,
    SEMI = 271,
    COMMA = 272,
    PLUS = 273,
    MINUS = 274,
    STAR = 275,
    DIV = 276,
    ASSIGNOP = 277,
    AND = 278,
    OR = 279,
    NOT = 280,
    IF = 281,
    ELSE = 282,
    WHILE = 283,
    RETURN = 284,
    FOR = 285,
    SWITCH = 286,
    CASE = 287,
    COLON = 288,
    DEFAULT = 289,
    AUTOADD = 290,
    AUTOSUB = 291,
    COMADD = 292,
    COMSUB = 293,
    EXT_DEF_LIST = 294,
    EXT_VAR_DEF = 295,
    FUNC_DEF = 296,
    ARRAY_DEF = 297,
    FUNC_DEC = 298,
    ARRAY_DEC = 299,
    EXT_DEC_LIST = 300,
    PARAM_LIST = 301,
    PARAM_DEC = 302,
    VAR_DEF = 303,
    DEC_LIST = 304,
    DEF_LIST = 305,
    COMP_STM = 306,
    STM_LIST = 307,
    EXP_STMT = 308,
    IF_THEN = 309,
    IF_THEN_ELSE = 310,
    AUTOADD_L = 311,
    AUTOSUB_L = 312,
    AUTOADD_R = 313,
    AUTOSUB_R = 314,
    PRE_CONDITION = 315,
    FOR_LIST = 316,
    ARRAY_CALL = 317,
    FUNC_CALL = 318,
    ARGS = 319,
    FUNCTION = 320,
    PARAM = 321,
    ARG = 322,
    CALL = 323,
    LABEL = 324,
    GOTO = 325,
    JLT = 326,
    JLE = 327,
    JGT = 328,
    JGE = 329,
    EQ = 330,
    NEQ = 331,
    UMINUS = 332,
    LOWER_THEN_ELSE = 333
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 16 "parser.y" /* yacc.c:1909  */

	int    type_int;
	float  type_float;
        char type_char;
	char   type_id[32];
	struct ASTNode *ptr;

#line 141 "parser.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
