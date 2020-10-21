%{
    #include <iostream>
    #include "grammar.tab.h"
%}

%option noyywrap

DIGITS      [0-9]
ALPHABET    [a-zA-Z]

%%
"exit"                                       return '\0';
"var"                                        return VARKEYWORD;
"s.t."                                       return STKEYWORD;
("minimize"|"maximize")                      return RESTWORD;
(">="|"<="|"=")                              {strcpy(yylval.name, yytext);return REL;}
"binary"                                     return BIN;
"integer"                                    return INT;
";"                                          return LINEEND;
"#!"                                         return SCOMMENT;
[0-9]({DIGITS})*                             {yylval.val = std::atoi(yytext); return NUMBER;}
{ALPHABET}({ALPHABET}|{DIGITS})*             {strcpy(yylval.name, yytext); return ID;}
\n                                           return '\n';/*skip newline*/
[ \t]                                        ;
%%
