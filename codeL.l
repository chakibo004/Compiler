%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "parser.tab.h"
    #include "ts.h"
    int col=0;
    extern YYSTYPE yylval;
    int nblignes=1;
%}

%option yylineno
commentintr [^-\n{}]*
Commentaire "{*"{commentintr}"*}"
const_bool  "true"|"false"|"vrai"|"faux"
LettreMaj [A-Z]
lettre [a-zA-Z]
chiffre [0-9]
idf [A-Z]|([A-Z](_[a-zA-Z]|_[0-9]|[a-zA-Z0-9]){0,9})
const_int [+-]?{chiffre}+
const_float [+-]?({chiffre}+)"."({chiffre}+)
%%

"INT"|"int" {col+=yyleng; yylval.string=strdup(yytext); col+=yyleng;return INT;}
"FLOAT"|"float" {col+=yyleng;yylval.string=strdup(yytext); col+=yyleng;return FLOAT;}
"BOOL"|"bool" {col+=yyleng;yylval.string=strdup(yytext); col+=yyleng;return BOOL;}
"CONST"|"const" {col+=yyleng;yylval.string=strdup(yytext); col+=yyleng;return CONST;}
"BEGIN" {col+=yyleng; return BEG;}
"END" {col+=yyleng;return END;}
"For" { col+=yyleng; return FOR;}
"If" {col+=yyleng;return IF;}
"else" {col+=yyleng; return ELSE;}

{Commentaire} {
    return Commentaire;
}

{const_bool} {
    yylval.string=strdup(yytext);
    col+=yyleng;
    return const_bool;
}

{idf} {
    if(yyleng>10){
        LXerror("\nUNRECOGNIZED IDF TOO MUCH LONG",yytext,nblignes,col);
    }
    col+=yyleng;
    yylval.string=strdup(yytext);
    return Idf;
}

{const_int} {
    yylval.entier=atoi(yytext);
    col+=yyleng;
    return const_int;
}

{const_float} {
    yylval.reel=atof(yytext);
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
"++"  { col+=yyleng; return INCREM;}
"--"  { col+=yyleng; return DECREM;}
"{"   { col+=yyleng; return CrochetG;}
"}"   { col+=yyleng; return CrochetD;}

[ \t] {col+=yyleng;}
[\n] {col=0;nblignes++;}

. {printf("\nLEXICAL ERROR : %s , at line %d col %d",yytext,nblignes,col);
    exit(EXIT_FAILURE);
    }
%%
yywrap(){}