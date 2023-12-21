%{

#include "decl.h"
#include "y.tab.h"
void yyerror (char *s);
%}
%%
"update"               {yylval.str = strdup(yytext); return UPDATE;}
"remove_element"       {yylval.str = strdup(yytext); return REMOVE_EL;}
"remove_scheme"        {yylval.str = strdup(yytext); return REMOVE_SCH;}
"create_element"       {yylval.str = strdup(yytext); return CREATE_EL;}
"create_scheme"        {yylval.str = strdup(yytext); return CREATE_SCH;}
"select_all"                      {yylval.str = strdup(yytext); return ASTERISK;}

"type=int32"     {yylval.number = 0; return INT32_TYPE;}
"type=double"    {yylval.number = 1; return DOUBLE_TYPE;}
"type=string"    {yylval.number = 2; return STRING_TYPE;}
"type=bool"      {yylval.number = 3; return BOOLEAN_TYPE;}

"true"                           {yylval.bool_value = 1; return BOOL;}
"false"                          {yylval.bool_value = 0; return BOOL;}
([+-]?[0-9])+                    {yylval.number = atoi(yytext); return NUMBER;}
[+-]?([0-9]*[.])?[0-9]+          {yylval.number = atof(yytext); return DOUBLE_NUM;}
[a-zA-Z][a-zA-Z0-9_]*             {yylval.str = strdup(yytext); return WORD;}

"="                      {yylval.number = 0; return EQUAL;}
"!="                     {yylval.number = 1; return NOT_EQUAL;}
">"                      {yylval.number = 2; return MORE;}
"<"                      {yylval.number = 3; return LESS;}
"/"                      {return SLASH;}
@                        {return IS_ATTRIBUTE;}
"*"                      {return STAR;}
"["                      {return START_FILTER;}
"]"                      {return END_FILTER;}
"("                      {return OPEN_BRACKET;}
")"                      {return CLOSE_BRACKET;}
";"                      {return SEMICOLON;}
\n                      /* skip */;
[ \t]+                  /* skip */;
.					{ECHO; yyerror ("unexpected character");}
%%
