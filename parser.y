%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    char TYPE[200];
%}

%union {
    int entier;
    char* string;
    float reel;
}

%token AFF
%token PVG
%token <string> INT
%token <string> FLOAT
%token <string> BOOL
%token BEG END 
%token <string> CONST
%token <string> Idf 
%token <entier> const_int <reel> const_float <string> const_bool
%token VIRGULE 
%token PLUS SUB MUL DIV INCREM DECREM
%token SUP SUPEGAL INF INFEGAL DIFF EGAL DPAFF IF ELSE
%token FOR PARG PARD CrochetG CrochetD Commentaire

%start program

%%

program : Liste_declarations BEG Liste_instructions END {
  printf("Analyse syntaxique valide\n");
  YYACCEPT;
}

OPP : PLUS|SUB|MUL|DIV 
OppCond : SUP|SUPEGAL|INF|INFEGAL|DIFF|EGAL
type  : FLOAT {strcpy(TYPE,$1);}|BOOL {strcpy(TYPE,$1);}|INT {strcpy(TYPE,$1);}

DEC_IDF : Idf {
    if (rechercher($1)!=-1){
        printf("\nERREUR SEMANTIQUE LA VARIABLE %s EST DEJA DECLAREE",$1);
    } else{
        inserer($1,"IDF",TYPE,"non");
    }
}

CONST_IDF: Idf {
    if (rechercher($1)!=-1){
        printf("\nERREUR SEMANTIQUE LA VARIABLE %s EST DEJA DECLAREE",$1);
    } else{
        inserer($1,"IDF",TYPE,"oui");
    }
}

VALUES : const_int
|const_float 
|const_bool 

Liste_declarations : Declaration PVG Liste_declarations 
|Declaration PVG

Declaration : type DEC_VAR
|CONST type DEC_CONST 

DEC_VAR: DEC_IDF VIRGULE DEC_VAR 
|DEC_IDF AFF VALUES VIRGULE DEC_VAR
|DEC_IDF AFF VALUES
|DEC_IDF

DEC_CONST: CONST_IDF AFF VALUES VIRGULE DEC_CONST
|CONST_IDF AFF VALUES

Liste_instructions : Instruction Liste_instructions|
Instruction

Instruction : AFFECTATION PVG
|BOUCLE
|CONDITION
|Commentaire

AFFECTATION : Idf DPAFF Expression

Expression : Idf OPP Idf
|Idf OPP Expression
|Expression OPP Expression
|Expression OPP Idf
|Idf
|VALUES
|COMPARAISON
|Idf INCREM // a revoir
|Idf DECREM // a revoir

BOUCLE: FOR PARG AFFECTATION PVG COMPARAISON PVG Compteur PARD CrochetG Liste_instructions CrochetD{
    printf("\nBoucle valide\n");
}

COMPARAISON: Expression OppCond Expression
Compteur : AFFECTATION
|Idf INCREM
|Idf DECREM

CONDITION: IF PARG COMPARAISON PARD CrochetG Liste_instructions CrochetD ELSE CrochetG Liste_instructions CrochetD
{
    printf("\nCondition valide avec ELSE\n");
}
|IF PARG COMPARAISON PARD CrochetG Liste_instructions CrochetD 
{
    printf("\nCondition valide sans ELSE\n");
}

%%  

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    FILE *file = freopen(argv[1], "r", stdin);
    if (file == NULL) {
        perror("Error");
        return 1;
    }

    yyparse();

    fclose(file);

    afficher();
    return 0;
}

void yyerror() {
    printf("\n\nSYNTAX ERROR:");
    exit(EXIT_FAILURE);
}

void LXerror(char *error, char *msg,int line, int col){
    if (error != NULL && msg != NULL) {
        printf("\n\nLEXICAL ERROR: %s IN %s at line ::: %d col ::: %d\n", error, msg, line, col);
        exit(EXIT_FAILURE);
    }
}

void SNerror(char *error, char *msg,int line, int col) {
    if (error != NULL && msg != NULL) {
        printf("\n\nSYNTAX ERROR: %s IN %s at line ::: %d col ::: %d\n", error, msg, line, col);
    }
    exit(EXIT_FAILURE);
}

