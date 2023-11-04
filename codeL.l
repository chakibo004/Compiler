%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "parser.tab.h"
    int col=0;
    extern YYSTYPE yylval;
    int nblignes=1;
%}

%option yylineno
commentintr [^-\n]*
Commentaire "{"{commentintr}"}"
const_bool  "true"|"false"|"vrai"|"faux"
lettre [a-zA-Z]
chiffre [0-9]
idf {lettre}({lettre}|{chiffre}|_)*
const_int [+-]?{chiffre}+
const_float [+-]?({chiffre}+)"."({chiffre}+)
%%

"INT"|"int" {col+=yyleng; printf("INT: ");col+=yyleng;return INT;}
"FLOAT"|"float" {col+=yyleng; printf("FLOAT: ");col+=yyleng;return FLOAT;}
"BOOL"|"bool" {col+=yyleng; printf("BOOL: ");col+=yyleng;return BOOL;}
"CONST"|"const" {col+=yyleng; printf("Constante: ");col+=yyleng;return CONST;}
"BEGIN" {col+=yyleng; printf("\nDébut du programme\n");return BEG;}
"END" {col+=yyleng; printf("\nFin du programme\n");return END;}
"For" { col+=yyleng; printf(" BOUCLE FOR "); return FOR;}
"If" {col+=yyleng; printf("If"); return IF;}
"else" {col+=yyleng; printf("else"); return ELSE;}

{Commentaire} {if(!find_char(yytext,'{') && !find_char(yytext,'}')){
        return Commentaire;
    }else{
        SNerror("BAD SYNTAX COMMENT",yytext,nblignes,col);
    }
}

{const_bool} {
    yylval.string=strdup(yytext);
    printf("%s ",yytext);
    col+=yyleng;
    return const_bool;
}

{idf} {
    if(yyleng<=10 && yytext[yyleng - 1]!='_' && !strstr(yytext, "__") && isupper(yytext[0])){
        printf("VAR:%s" ,yytext);
        col+=yyleng;
        yylval.string=strdup(yytext);
        return IDF;
    }else{
        LXerror("UNRECOGNIZED ENTITY",yytext,nblignes,col);
    }
}

{const_int} {
    yylval.entier=atoi(yytext);
    printf("%d",atoi(yytext));
    col+=yyleng;
    return const_int;
}

{const_float} {
    yylval.reel=atof(yytext);
    printf("%f",atof(yytext));
    col+=yyleng;
    return const_float;
}

"+"   { col+=yyleng;printf(" + ");return PLUS;}
"*"   { col+=yyleng;printf(" * ");return MUL;}
"/"   { col+=yyleng;printf(" / ");return DIV;}
"-"   { col+=yyleng;printf(" - ");return SUB;}
"="   { col+=yyleng;printf(" = ");return AFF;}
";"   { col+=yyleng;printf("\n");return PVG;}
","   { col+=yyleng;printf(", ");return VIRGULE;}

">"   { col+=yyleng;printf(" SUP "); return SUP;}
"<"   { col+=yyleng;printf(" INF "); return INF;}
">="  { col+=yyleng;printf(" SUPEGAL "); return SUPEGAL;}
"<="  { col+=yyleng;printf(" INFEGAL "); return INFEGAL;}
"=="  { col+=yyleng;printf(" EGAL "); return EGAL;}
"<>"  { col+=yyleng;printf(" DIFF "); return DIFF;}
":="  { col+=yyleng;printf(" = "); return DPAFF;}

"("   { col+=yyleng;printf(" ( "); return PARG;}
")"   { col+=yyleng;printf(" ) "); return PARD;}
"++"  { col+=yyleng;printf(" + 1"); return INCREM;}
"--"  { col+=yyleng;printf(" - 1"); return DECREM;}
"{"   { col+=yyleng;printf("{\n\t"); return CrochetG;}
"}"   { col+=yyleng;printf("\t}"); return CrochetD;}

[ \t] {col+=yyleng;}
[\n] {col=1;nblignes++;}

%%
yywrap(){}