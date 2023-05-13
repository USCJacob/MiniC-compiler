
/*定义部分，直接被复制到词法分析源程序中*/
%{
#include "parser.tab.h"
#include "string.h"
#include "def.h"
int yycolumn=1;
#define YY_USER_ACTION    	yylloc.first_line=yylloc.last_line=yylineno; \
	yylloc.first_column=yycolumn;	yylloc.last_column=yycolumn+yyleng-1; yycolumn+=yyleng;
typedef union {
	int type_int;
	int type_float;
	char type_id[32];
	struct node *ptr;
} YYLVAL;
#define YYSTYPE YYLVAL

%}
/*定义了一个表示标识符的宏名id，这些宏名在后面的规则部分会用到*/
%option yylineno

id   [A-Za-z][A-Za-z0-9]*  
int    [0-9]+
float  ([0-9]*\.[0-9]+)|([0-9]+\.)
char   \'.\'
/*注释行匹配*/
annotation  (\/\/(\s|.)*?)|(\/\*(\s|.)*?\*\/)
/*规则部分： 正则表达式 动作*/
%%
{int}        {yylval.type_int=atoi(yytext);printf("(INT,%d)\n",yylval.type_int); return INT;}
{float}      {yylval.type_float=atof(yytext);printf("(INT,%f)\n",yylval.type_float); return FLOAT;}
{char}      {yylval.type_char=yytext[1];printf("(CHAR,%c)\n",yylval.type_char); return CHAR;}
"int"        {strcpy(yylval.type_id,  yytext);printf("(TYPE,%s)\n",yylval.type_id);return TYPE;}
"float"      {strcpy(yylval.type_id,  yytext);printf("(TYPE,%s)\n",yylval.type_id);return TYPE;}
"char"       {strcpy(yylval.type_id,  yytext);printf("(TYPE,%s)\n",yylval.type_id);return TYPE;}

"return"     {return RETURN;}
"if"         {return IF;}
"else"       {return ELSE;}
"while"      {return WHILE;}
"for"		 {return FOR;}
{annotation} {}
{id}       {strcpy(yylval.type_id,  yytext);printf("(ID,%s)\n",yylval.type_id); return ID;/*由于关键字的形式也符合标识符的规则，所以把关键字的处理全部放在标识符的前面，优先识别*/}
";"			{return SEMI;}
","			{return COMMA;}
">"|"<"|">="|"<="|"=="|"!=" {strcpy(yylval.type_id, yytext);;return RELOP;}
"="			{return ASSIGNOP;}
"+"			{return PLUS;}
"-"			{return MINUS;}
"*"			{return STAR;}
"/"			{return DIV;}
"+="		{return COMADD;}
"-="		{return COMSUB;}
"--"		{return AUTOSUB;}
"++"		{return AUTOADD;}
"&&"         {return AND;}
"||"            {return OR;}
"!"			{return NOT;}
"("			{return LP;}
")"			{return RP;}
"["			{return LB;}
"]"			{return RB;}
"{"			{return LC;}
"}"			{return RC;}
[\n]           {yycolumn=1;}   
[ \r\t]          {}   
.			{printf("Error type A :Mysterious character \"%s\"\n\t at Line %d\n",yytext,yylineno);}
%%
/*作为实验内容，还需要考虑识别出2种形式的注释注释部分时，直接舍弃，户子程序部分，这部分代码会原封不动的被复制到词法分析器源程序lex.yy.c中。*/

/* 和bison联用时，不需要这部分
void main()
{
yylex();
return 0;
}

*/
int yywrap()
{
return 1;
}