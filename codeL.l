%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "parser.tab.h"
    #include "ts.h"
    int col=0;
    extern YYSTYPE yylval;
    extern int nblignes;
%}

%option yylineno
commentintr [^-\n{}]*
Commentaire "{*"{commentintr}"*}"
const_bool  "true"|"false"|"vrai"|"faux"
chiffre [0-9]
idf [A-Z]|([A-Z](_[a-zA-Z]|_[0-9]|[a-zA-Z0-9]){0,9})
const_int [+-]?{chiffre}+
const_float [+-]?({chiffre}+)"."({chiffre}+)
%%

"INT"|"int" {col+=yyleng; yylval.string=strdup(yytext); col+=yyleng;return INT;}
"FLOAT"|"float" {col+=yyleng;yylval.string=strdup(yytext); col+=yyleng;return FLOAT;}
"BOOL"|"bool" {col+=yyleng;yylval.string=strdup(yytext); col+=yyleng;return BOOL;}
"CONST"|"const" {col+=yyleng;yylval.string=strdup(yytext); col+=yyleng;return CONST;}
"BEGIN" {inserer(yytext,"KEYWORD","/","/");col+=yyleng; return BEG;}
"END" {inserer(yytext,"KEYWORD","/","/");col+=yyleng;return END;}
"For" {inserer(yytext,"KEYWORD","/","/");col+=yyleng; return FOR;}
"If" {inserer(yytext,"KEYWORD","/","/");col+=yyleng;return IF;}
"else" {inserer(yytext,"KEYWORD","/","/");col+=yyleng; return ELSE;}

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

"+"   { inserer(yytext,"OPP","/","/");col+=yyleng; return PLUS;}
"*"   { inserer(yytext,"OPP","/","/");col+=yyleng; return MUL;}
"/"   { inserer(yytext,"OPP","/","/");col+=yyleng; return DIV;}
"-"   { inserer(yytext,"OPP","/","/");col+=yyleng; return SUB;}
"="   { inserer(yytext,"OPP","/","/");col+=yyleng; return AFF;}
";"   { inserer(yytext,"SEP","/","/");col+=yyleng; return PVG;}
","   { inserer(yytext,"SEP","/","/");col+=yyleng; return VIRGULE;}

">"   { inserer(yytext,"OPP","/","/");col+=yyleng; return SUP;}
"<"   { inserer(yytext,"OPP","/","/");col+=yyleng; return INF;}
">="  { inserer(yytext,"OPP","/","/");col+=yyleng; return SUPEGAL;}
"<="  { inserer(yytext,"OPP","/","/");col+=yyleng; return INFEGAL;}
"=="  { inserer(yytext,"OPP","/","/");col+=yyleng; return EGAL;}
"<>"  { inserer(yytext,"OPP","/","/");col+=yyleng; return DIFF;}
":="  { inserer(yytext,"OPP AFF","/","/");col+=yyleng; return DPAFF;}

"("   { inserer(yytext,"SEP","/","/");col+=yyleng; return PARG;}
")"   { inserer(yytext,"SEP","/","/");col+=yyleng; return PARD;}
"++"  { inserer(yytext,"OPP","/","/");col+=yyleng; return INCREM;}
"--"  { inserer(yytext,"OPP","/","/");col+=yyleng; return DECREM;}
"{"   { inserer(yytext,"SEP","/","/");col+=yyleng; return CrochetG;}
"}"   { inserer(yytext,"SEP","/","/");col+=yyleng; return CrochetD;}

[ \t] {col+=yyleng;}
[\n] {col=0;nblignes++;}

. {printf("\nLEXICAL ERROR : %s , at line %d col %d",yytext,nblignes,col);
    exit(EXIT_FAILURE);
    }
%%
yywrap(){}