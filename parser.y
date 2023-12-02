%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <ctype.h>

    #define MAX_NUM_LENGTH 50

    char Var_type[200];
    int nblignes=1;
    int col=1;
    char type_VALUE[200];
    char num_VALUE[200];
    char sauvOpr[200];
    char VARAFF[200];
    char type_Calcul[200];
    char type_Expression[200];
    char valeur[200];
    char result[1000];
    char cond[1];

    char* mirrorString(const char* str) {
        int length = strlen(str);
        char* mirroredStr = (char*)malloc((length + 1) * sizeof(char));
        
        if (mirroredStr == NULL) {
            fprintf(stderr, "Memory allocation error\n");
            exit(EXIT_FAILURE);
        }

        for (int i = 0; i < length; ++i) {
            mirroredStr[i] = str[length - 1 - i];
        }

        mirroredStr[length] = '\0'; 
        return mirroredStr;
    }

    int isNumeric(char ch) { return (isdigit(ch) || ch == '.'); }

    int isOperator(char ch) {
        return (ch == '+' || ch == '-' || ch == '*' || ch == '/');
    }

    float performOperation(float operand1, float operand2, char operator) {
        switch (operator) {
            case '+':
                return operand1 + operand2;
            case '-':
                return operand1 - operand2;
            case '*':
                return operand1 * operand2;
            case '/':
                if (operand2 != 0) {
                return operand1 / operand2;
                } else {
                printf("Error: Division by zero\n");
                exit(EXIT_FAILURE);
                }
            default:
                printf("Error: Invalid operator\n");
                exit(EXIT_FAILURE);
        }
    }

    float evaluate(char *expression) {
        int len = strlen(expression);

        float operandStack[len];
        char operatorStack[len];
        int operandTop = -1;
        int operatorTop = -1;

        for (int i = 0; i < len; i++) {
            if (isNumeric(expression[i])) {

            float operand = atof(&expression[i]);
            while (i < len && isNumeric(expression[i])) {
                i++;
            }
            i--; 
            operandStack[++operandTop] = operand;
            } else if (isOperator(expression[i])) {
            
            while (operatorTop >= 0 &&
                    (operatorStack[operatorTop] == '+' ||
                    operatorStack[operatorTop] == '-' ||
                    operatorStack[operatorTop] == '*' ||
                    operatorStack[operatorTop] == '/') &&
                    (expression[i] == '+' || expression[i] == '-')) {
                
                float operand2 = operandStack[operandTop--];
                float operand1 = operandStack[operandTop--];
                char currentOperator = operatorStack[operatorTop--];
                operandStack[++operandTop] =
                    performOperation(operand1, operand2, currentOperator);
            }

            operatorStack[++operatorTop] = expression[i];
            } else if (expression[i] == '(') {
            operatorStack[++operatorTop] = expression[i];
            } else if (expression[i] == ')') {
            while (operatorTop >= 0 && operatorStack[operatorTop] != '(') {
                float operand2 = operandStack[operandTop--];
                float operand1 = operandStack[operandTop--];
                char currentOperator = operatorStack[operatorTop--];
                operandStack[++operandTop] =
                    performOperation(operand1, operand2, currentOperator);
            }
            
            operatorTop--;
            }
        }

        while (operatorTop >= 0) {
            float operand2 = operandStack[operandTop--];
            float operand1 = operandStack[operandTop--];
            char currentOperator = operatorStack[operatorTop--];
            operandStack[++operandTop] =
                performOperation(operand1, operand2, currentOperator);
        }

        return operandStack[operandTop];
    }


    int evaluateCondition(float operand1, char* condition, float operand2 ) {
        int result;
        if (strcmp(condition,"==")==0) {
            result = operand1 == operand2;
        } else if (strcmp(condition,">")==0) {
            result = operand1 > operand2;
        } else if (strcmp(condition,"<")==0) {
            result = operand1 < operand2;
        } else if (strcmp(condition,">=")==0) {
            result = operand1 >= operand2;
        } else if (strcmp(condition,"<=")==0) {
            result = operand1 <= operand2;
        } else if (strcmp(condition,"<>")==0) {
            result = operand1 != operand2;
        } else {
            // Condition non reconnue
            printf("Condition non prise en charge\n");
            result = -1; // Valeur d'erreur
        }
        return result;
    }
    
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
%token <string> const_int <string> const_float <string> const_bool
%token VIRGULE 
%token <string> PLUS <string> SUB <string> MUL <string> DIV
%token SUP SUPEGAL INF INFEGAL DIFF EGAL DPAFF IF ELSE
%token FOR PARG PARD CrochetG CrochetD Commentaire


%left MUL DIV
%left SUB PLUS
%start program

%%

program : Liste_declarations BEG Liste_instructions END {
    printf("\nAnalyse syntaxique valide\n");
    YYACCEPT;
}

OPP : PLUS{push("+");}
|SUB{push("-");}
|MUL{push("*");}
|DIV{push("/");}

OppCond : SUP{push(">");}
|SUPEGAL{push(">=");}
|INF{push("<");}
|INFEGAL{push("<=");}
|DIFF{push("<>");}
|EGAL{push("==");}

type  : FLOAT {strcpy(Var_type,$1);}|BOOL {strcpy(Var_type,$1);}|INT {strcpy(Var_type,$1);}
DEC_VALUES : const_int{strcpy(type_VALUE,"int");strcpy(num_VALUE,$1);}|const_float{strcpy(type_VALUE,"float");strcpy(num_VALUE,$1);}|const_bool{strcpy(type_VALUE,"bool");strcpy(num_VALUE,$1);}
INSTR_VALUES : const_int{strcpy(type_VALUE,"int");push($1);}|const_float{strcpy(type_VALUE,"float");push($1);}|const_bool{strcpy(type_VALUE,"bool");push($1);}

DEC_IDF : Idf {
    if (rechercher($1)!=-1 && strcmp(typeIDF($1),"/")!=0){
        printf("\nERREUR SEMANTIQUE ::: LA VARIABLE %s EST DEJA DECLAREE ligne ::: %d, col ::: %d",$1,nblignes,col);
        exit(EXIT_FAILURE);
    }else{
        UpdateTypeConst($1,Var_type,"non");
    }
}
|Idf AFF DEC_VALUES {
    if (rechercher($1)!=-1 && strcmp(typeIDF($1),"/")!=0){
        printf("\nERREUR SEMANTIQUE ::: LA VARIABLE %s EST DEJA DECLAREE ::: ligne ::: %d, col ::: %d",$1,nblignes,col);
        exit(EXIT_FAILURE);
    }else{
        UpdateTypeConst($1,Var_type,"non");        
        if ((strcmp(Var_type, type_VALUE) == 0) || ((strcmp(Var_type, "float") == 0) && (strcmp(type_VALUE, "int") == 0))){
            insertVALUE(num_VALUE);
        }else{
            printf("\nERREUR SEMANTIQUE ::: Type incompatible pour la variable: %s, TYPE affectee : %s, TYPE attendue : %s, ::: ligne %d\n",$1,type_VALUE,Var_type,nblignes);
            exit(EXIT_FAILURE);
        }
    }
}

CONST_IDF: Idf AFF DEC_VALUES{
        if (rechercher($1)!=-1 && strcmp(typeIDF($1),"/")!=0){
        printf("\nERREUR SEMANTIQUE LA VARIABLE %s EST DEJA DECLAREE ::: ligne %d",$1,nblignes);
        exit(EXIT_FAILURE);
    } else{
        UpdateTypeConst($1,Var_type,"oui");
        if ((strcmp(Var_type, type_VALUE) == 0) || ((strcmp(Var_type, "float") == 0) && (strcmp(type_VALUE, "int") == 0))){
            insertVALUE(num_VALUE);
        }else{
            printf("\nERREUR SEMANTIQUE ::: Type incompatible pour la variable: %s, TYPE affectee : %s, TYPE attendue : %s, ::: ligne %d\n",$1,type_VALUE,Var_type,nblignes);
            exit(EXIT_FAILURE);
        }
    }
}

Liste_declarations : Declaration PVG Liste_declarations 
|Declaration PVG

Declaration : type DEC_VAR
|CONST type DEC_CONST 

DEC_VAR: DEC_IDF VIRGULE DEC_VAR
|DEC_IDF

DEC_CONST: CONST_IDF VIRGULE DEC_CONST
|CONST_IDF

Liste_instructions : Instruction Liste_instructions
|Instruction

Instruction : AFFECTATION PVG
|BOUCLE
|CONDITION
|Commentaire
|AUTOOPERATION PVG

AFFECTATION: Idf DPAFF Expression{
    if (rechercher($1)!=-1 && strcmp(typeIDF($1),"/")==0){
        printf("\nERREUR SEMANTIQUE LA VARIABLE %s N'EST PAS DECLAREE ::: ligne %d",$1,nblignes);
        exit(EXIT_FAILURE);
    }else if(isconst($1)){
        printf("\nERREUR SEMANTIQUE ::: MODIFICATION DE CONSTANTE %s INTERDITE ::: ligne %d",$1,nblignes);
        exit(EXIT_FAILURE);
    }else{
        if(strcmp(type_Calcul,"bool")==0){
            updateIDFValue($1,mirrorString(pop()));
        }
        else if(strcmp(type_Calcul,typeIDF($1))==0 || strcmp(typeIDF($1),"float")==0){
            strcpy(result,pop());
            char* ret = mirrorString(result);
            printf("\n Expression : %s",ret);
            sprintf(ret,"%g",evaluate(ret));
            updateIDFValue($1,ret);
        }else{
            printf("\nERREUR SEMANTIQUE ::: INCOMPATIBILTE DE TYPE -> VARIABLE: %s, TYPE affectee : %s, TYPE attendue : %s, ::: ligne %d\n",$1,type_Calcul,typeIDF($1),nblignes);
            exit(EXIT_FAILURE);
        }
    }
}

ExpressionParenthese : PARG Expression PARD{
    char* value = pop();
    char* result = (char*)malloc((strlen("(") + strlen(value) + strlen(")") + 1) * sizeof(char));
    strcpy(result, ")");
    strcat(result, value);
    strcat(result, "(");
    push(result);
}

Expression : Expression OPP Expression {
    char *right = pop();
    char *OPR = pop();
    char *left = pop();

    char* expression = right; 
    strcat(expression, OPR);
    strcat(expression, left);
    push(expression);
}
|Idf OPP Expression {

    if (rechercher($1) != -1 && strcmp(typeIDF($1), "/") == 0) {
        printf("\nERREUR SEMANTIQUE LA VARIABLE %s N'EST PAS DECLAREE ::: ligne %d", $1, nblignes);
        exit(EXIT_FAILURE);
    }else if (strcmp(getValue($1), "/") == 0) {
        printf("\nERREUR SEMANTIQUE LA VARIABLE %s N'A PAS DE VALEUR ASSIGNEE ::: ligne %d", $1, nblignes);
        exit(EXIT_FAILURE);
    }else{

        if (strcmp(typeIDF($1),"bool") == 0 || strcmp(type_Calcul,"bool") == 0) {
            printf("\nERREUR SEMANTIQUE ::: OPERATION IMPOSSIBLE SUR DES OPERANDES BOOLEEN ::: ligne %d\n", nblignes);
            exit(EXIT_FAILURE);
        }
        char* right = pop();
        strcpy(sauvOpr, pop());
        strcpy(valeur,getValue($1));
        char* ret = mirrorString(valeur);

        strcpy(result,right);
        strcat(result,sauvOpr);

        strcat(result,ret);

        if(strcmp(typeIDF($1),type_Expression)==0){
            strcpy(type_Calcul,type_Expression);
        }else{
            strcpy(type_Calcul,"float");
        }

        push(result);
    }
}
|Idf {
    if (rechercher($1) != -1 && strcmp(typeIDF($1), "/") == 0) {
        printf("\nERREUR SEMANTIQUE LA VARIABLE %s N'EST PAS DECLAREE ::: ligne %d", $1, nblignes);
        exit(EXIT_FAILURE);
    }else if (strcmp(getValue($1), "/") == 0) {
        printf("\nERREUR SEMANTIQUE LA VARIABLE %s N'A PAS DE VALEUR ASSIGNEE ::: ligne %d", $1, nblignes);
        exit(EXIT_FAILURE);
    }else{

        strcpy(type_Calcul,typeIDF($1));
        strcpy(type_Expression,typeIDF($1));

        strcpy(result,getValue($1));
        char* ret = mirrorString(result);
        push(ret);
    }
}
|INSTR_VALUES OPP Expression{

    char* right = pop();
    char* OPR = pop();

    if (strcmp(type_VALUE,"bool") == 0 || strcmp(type_Calcul,"bool") == 0) {
        printf("\nERREUR SEMANTIQUE ::: OPERATION IMPOSSIBLE SUR DES OPERANDES BOOLEEN ::: ligne %d\n", nblignes);
        exit(EXIT_FAILURE);
    }

    if(strcmp(type_VALUE,type_Expression)==0){
        strcpy(type_Calcul,type_Expression);
    }else{
        strcpy(type_Calcul,"float");
    }


    char* valeur = pop();
    char* ret = mirrorString(valeur);

    strcpy(result,right);
    strcat(result,OPR);
    strcat(result,ret);
    push(result);

}
|INSTR_VALUES{
    strcpy(type_Calcul,type_VALUE);
    strcpy(type_Expression,type_VALUE);

    strcpy(result,pop());
    char* ret = mirrorString(result);

    push(ret);
}
|PARG COMPARE_EXPR PARD
|ExpressionParenthese

COMPAREOPERANDS : Idf{
    if (rechercher($1) != -1 && strcmp(typeIDF($1), "/") == 0) {
        printf("\nERREUR SEMANTIQUE LA VARIABLE %s N'EST PAS DECLAREE ::: ligne %d", $1, nblignes);
        exit(EXIT_FAILURE);
    }else if (strcmp(getValue($1), "/") == 0) {
        printf("\nERREUR SEMANTIQUE LA VARIABLE %s N'A PAS DE VALEUR ASSIGNEE ::: ligne %d", $1, nblignes);
        exit(EXIT_FAILURE);
    }else{
        if (strcmp(typeIDF($1), "bool") == 0) {
            printf("\nERREUR SEMANTIQUE ::: OPERATION IMPOSSIBLE SUR DES OPERANDES BOOLEEN ::: ligne %d\n", nblignes);
            exit(EXIT_FAILURE);
        }
        strcpy(result,getValue($1));
        char* ret = mirrorString(result);
        push(ret);
    }
}
|INSTR_VALUES{
    if (strcmp(type_VALUE, "bool") == 0) {
        printf("\nERREUR SEMANTIQUE ::: OPERATION IMPOSSIBLE SUR DES OPERANDES BOOLEEN ::: ligne %d\n", nblignes);
        exit(EXIT_FAILURE);
    }
    else{
        strcpy(type_Calcul,type_VALUE);
        strcpy(type_Expression,type_VALUE);

        strcpy(result,pop());
        char* ret = mirrorString(result);

        push(ret);
    }
}

COMPARE_EXPR: COMPAREOPERANDS OppCond COMPAREOPERANDS{
    int valeur = evaluateCondition(atof(pop()),pop(),atof(pop()));
    char* result = (char*)malloc(sizeof(char));

    sprintf(result,"%d",valeur);
    push(result);
}

AUTOOPERATION : Idf PLUS PLUS{
    if (rechercher($1) != -1 && strcmp(typeIDF($1), "/") == 0) {
        printf("\nERREUR SEMANTIQUE LA VARIABLE %s N'EST PAS DECLAREE ::: ligne %d", $1, nblignes);
        exit(EXIT_FAILURE);
    }else if (strcmp(getValue($1), "/") == 0) {
        printf("\nERREUR SEMANTIQUE LA VARIABLE %s N'A PAS DE VALEUR ASSIGNEE ::: ligne %d", $1, nblignes);
        exit(EXIT_FAILURE);
    }else{
        char* valeur = getValue($1);

        strcpy(result,valeur);
        strcat(result,"+");
        strcat(result,"1");
        printf("\n%s\n",result);

        sprintf(result,"%g",evaluate(result));
        updateIDFValue($1,result);
    }
}
|Idf SUB SUB{
    if (rechercher($1) != -1 && strcmp(typeIDF($1), "/") == 0) {
        printf("\nERREUR SEMANTIQUE LA VARIABLE %s N'EST PAS DECLAREE ::: ligne %d", $1, nblignes);
        exit(EXIT_FAILURE);
    }else if (strcmp(getValue($1), "/") == 0) {
        printf("\nERREUR SEMANTIQUE LA VARIABLE %s N'A PAS DE VALEUR ASSIGNEE ::: ligne %d", $1, nblignes);
        exit(EXIT_FAILURE);
    }else{
        char* valeur = getValue($1);

        strcpy(result,valeur);
        strcat(result,"-");
        strcat(result,"1");
        printf("\n%s\n",result);
        sprintf(result,"%.2f",evaluate(result));
        updateIDFValue($1,result);
    }
}

BOUCLE: FOR PARG AFFECTATION PVG COMPARAISON PVG Compteur PARD CrochetG Liste_instructions CrochetD

CONDITION: IF PARG COMPARAISON PARD CrochetG Liste_instructions CrochetD ELSE CrochetG Liste_instructions CrochetD
|IF PARG COMPARAISON PARD CrochetG Liste_instructions CrochetD 

COMPARAISON : Expression OppCond Expression{
    printf("\nligne ::: %d",nblignes);
    printStack();
}

Compteur : AFFECTATION
|AUTOOPERATION
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
    printf("\n\nSYNTAX ERROR at line ::: %d",nblignes);
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

