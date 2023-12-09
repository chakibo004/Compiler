%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "parser.tab.h"
    #include "ts.h"
    extern YYSTYPE yylval;
    extern int nblignes;
    extern int col;
%}

%option yylineno 
Commentaire "/*"[^/*]*"*/"
const_bool  "true"|"false"|"vrai"|"faux"
chiffre [0-9]
idf [A-Z]|([A-Z](_[a-zA-Z]|_[0-9]|[a-zA-Z0-9])*)
const_int [-]?{chiffre}+
const_float [-]?({chiffre}+)"."({chiffre}+)
const_char '[a-zA-Z]'
const_string \"[0-9a-zA-Z ]+\"

%%
"CHAR"|"char" {col+=yyleng;yylval.string="char";return CHAR;}
"STRING"|"string" {col+=yyleng; yylval.string="string";return STRING;}
"INT"|"int" {col+=yyleng; yylval.string="int";return INT;}
"FLOAT"|"float" {col+=yyleng;yylval.string="float";return FLOAT;}
"BOOL"|"bool" {col+=yyleng;yylval.string="bool";return BOOL;}
"CONST"|"const" {col+=yyleng;yylval.string="const";return CONST;}
"BEGIN" {col+=yyleng; return BEG;}
"END" {col+=yyleng;return END;}
"For" {col+=yyleng; return FOR;}
"While" {col+=yyleng; return WHILE;}
"Do" {col+=yyleng; return DO;}
"If" {col+=yyleng;return IF;}
"else" {col+=yyleng; return ELSE;}

{Commentaire} {
    col+=yyleng;
    return Commentaire;
}

{const_bool} {
    yylval.string=strdup(yytext);
    col+=yyleng;
    return const_bool;
}

{idf} {
    if(yyleng>10){
        LXerror("\nUNRECOGNIZED IDF : TOO MUCH LONG\n",yytext,nblignes,col);
    }
    col+=yyleng;
    yylval.string=strdup(yytext);
    inserer(yytext,"IDF","/","/");
    return Idf;
}

{const_int} {
    yylval.string=strdup(yytext);
    col+=yyleng;
    return const_int;
}

{const_char} {
    yylval.string=strdup(yytext);
    col+=yyleng;
    return const_char;
}

{const_string} {
    yylval.string=strdup(yytext);
    col+=yyleng;
    return const_string;
}

{const_float} {
    yylval.string=strdup(yytext);
    col+=yyleng;
    return const_float;
}

"+"   { col+=yyleng; return PLUS;}
"*"   { col+=yyleng; return MUL;}
"/"   { col+=yyleng; return DIV;}
"-"   { col+=yyleng; return SUB;}
"="   { col+=yyleng; return AFF;}
";"   { col+=yyleng; return PVG;}
","   { col+=yyleng; return VIRGULE;}

">"   { col+=yyleng; return SUP;}
"<"   { col+=yyleng; return INF;}
">="  { col+=yyleng; return SUPEGAL;}
"<="  { col+=yyleng; return INFEGAL;}
"=="  { col+=yyleng; return EGAL;}
"<>"  { col+=yyleng; return DIFF;}
":="  { col+=yyleng; return DPAFF;}

"("   { col+=yyleng; return PARG;}
")"   { col+=yyleng; return PARD;}
"{"   { col+=yyleng; return CrochetG;}
"}"   { col+=yyleng; return CrochetD;}

[ \t] {col+=yyleng;}
[\n] {col=0;nblignes++;}

. {printf("\nLEXICAL ERROR : %s , at line %d col %d",yytext,nblignes,col);
    exit(EXIT_FAILURE);
    }
%%
yywrap(){}