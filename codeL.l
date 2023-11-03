%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "parser.tab.h"
    extern int yylineo;
    int col;
    extern YYSTYPE yylval;
    int nblignes=1;
%}

%option yylineno
comentIntr [^-\n]*|("\\-")*
Commentaire "{"{comentIntr}*"}"

const_bool  "true"|"false"|"vrai"|"faux"
lettreMaj [A-Z]
lettre [a-zA-Z]
chiffre [0-9]
idf {lettre}({lettre}|{chiffre}|_)*
const_int [+-]?{chiffre}+
const_float [+-]?({chiffre}+)"."({chiffre}+)
%%

"INT"|"int" {printf("INT: ");yylval.string=strdup(yytext);col=0;col+=yyleng;return INT;}
"FLOAT"|"float" {printf("FLOAT: ");yylval.string=strdup(yytext);col=0;col+=yyleng;return FLOAT;}
"BOOL"|"bool" {printf("BOOL: ");yylval.string=strdup(yytext);col=0;col+=yyleng;return BOOL;}
"CONST"|"const" {printf("Constante: ");yylval.string=strdup(yytext);col=0;col+=yyleng;return CONST;}
"BEGIN" {printf("\nDébut du programme\n");return BEG;}
"END" {printf("\nFin du programme\n");return END;}
"For" { printf(" BOUCLE FOR "); return FOR;}
"If" {printf("If"); return IF;}
"else" {printf("else"); return ELSE;}

{Commentaire} {yylval.string=strdup(yytext);col+=yyleng;printf("\n%s est un commentaire\n",yytext);}

{const_bool} {
    yylval.string=strdup(yytext);
    printf("%s ",yytext);
    col = col + strlen(yytext);
    return const_bool;
}

{idf} {
    if(yyleng<=10 && yytext[yyleng - 1]!='_' && !strstr(yytext, "__") ){
        printf("VAR:%s" ,yytext);
        col = col + strlen(yytext);
        yylval.string=strdup(yytext);
        return IDF;
    }else{
        printf("Pas Idf:%s\n",yytext);
    }
}

{const_int} {
    yylval.entier=atoi(yytext);
    printf("%d",atoi(yytext));
    col = col + strlen(yytext);
    return const_int;
}

{const_float} {
    yylval.reel=atof(yytext);
    printf("%f",atof(yytext));
    col = col + strlen(yytext);
    return const_float;
}


"+"   { printf(" + ");return PLUS;}
"*"   { printf(" * ");return MUL;}
"/"   { printf(" / ");return DIV;}
"-"   { printf(" - ");return SUB;}
"="   { printf(" = ");return AFF;}
";"   { printf("\n");return PVG;}
","   { printf(", ");return VIRGULE;}

">"   { printf(" SUP "); return SUP;}
"<"   { printf(" INF "); return INF;}
">="  { printf(" SUPEGAL "); return SUPEGAL;}
"<="  { printf(" INFEGAL "); return INFEGAL;}
"=="  { printf(" EGAL "); return EGAL;}
"<>"  { printf(" DIFF "); return DIFF;}
":="  { printf(" = "); return DPAFF;}

"("   { printf(" ( "); return PARG;}
")"   { printf(" ) "); return PARD;}
"++"  { printf(" + 1"); return INCREM;}
"--"  { printf(" - 1"); return DECREM;}
"{"   { printf("{\n\t"); return CrochetG;}
"}"   { printf("\t}"); return CrochetD;}

[ \t] {}
[\n] {nblignes++;}
. {printf("\nErreur lexicale au niveau de la ligne Num = %d , la colonne Num = %d , l'entite : %s . \n",nblignes, col, yytext); col=0;col=col+strlen(yytext);}

%%
yywrap(){}