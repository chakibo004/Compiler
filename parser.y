%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    # define YYSTYPE float
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
%token <string> IDF <entier> const_int <reel> const_float <string> const_bool
%token VIRGULE 
%token PLUS SUB MUL DIV INCREM DECREM
%token SUP SUPEGAL INF INFEGAL DIFF EGAL DPAFF IF ELSE
%token FOR PARG PARD CrochetG CrochetD Commentaire
%start program

%%

program : Liste_declarations BEG Liste_instructions END {
  printf("Programme valide\n");
}

OPP : PLUS|SUB|MUL|DIV
OppCond : SUP|SUPEGAL|INF|INFEGAL|DIFF|EGAL
type  : FLOAT|BOOL|INT

VALUES : const_int
|const_float
|const_bool

Liste_declarations : Declaration PVG Liste_declarations 
|Declaration PVG

Declaration : type DEC_VAR  
|CONST type DEC_CONST 

DEC_VAR: IDF VIRGULE DEC_VAR 
|IDF AFF VALUES VIRGULE DEC_VAR
|IDF AFF VALUES
|IDF

DEC_CONST: IDF AFF VALUES VIRGULE DEC_CONST
|IDF AFF VALUES

Liste_instructions : Instruction Liste_instructions|
Instruction

Instruction : AFFECTATION PVG
|BOUCLE
|CONDITION
|Commentaire {printf("\nCommentaire\n");}

AFFECTATION : IDF DPAFF Expression

Expression : IDF OPP IDF
|IDF OPP Expression
|Expression OPP Expression
|Expression OPP IDF
|IDF
|VALUES
|COMPARAISON
|IDF INCREM // a revoir
|IDF DECREM // a revoir

BOUCLE: FOR PARG AFFECTATION PVG COMPARAISON PVG Compteur PARD CrochetG Liste_instructions CrochetD{
    printf("\nBoucle valide\n");
}

COMPARAISON: Expression OppCond Expression
Compteur : AFFECTATION
|IDF INCREM
|IDF DECREM

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

int find_char(const char* chaine, char caractere) {
    int longueur = strlen(chaine);

    for (int i = 1; i < longueur - 1; i++) {
        if (chaine[i] == caractere) {
            return 1; 
        }
    }
    return 0; 
}
