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
    char type_Calcul[200];
    char valeur[200];
    char result[1000];
    
    char* mirrorString(const char* str) { // Fonction MIRROIR Pour inversion des chaines de la PILE
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

    float evaluate(char *expression){
        int len = strlen(expression);

        float operandStack[len];
        char operatorStack[len];
        int operandTop = -1;
        int operatorTop = -1;

        for (int i = 0; i < len; i++) {
            if (expression[i] == '-' && (i == 0 || !isNumeric(expression[i - 1]))) {
                i++;
                float operand = -atof(&expression[i]);
                operandStack[++operandTop] = operand;
                while (i < len && (isNumeric(expression[i]) || expression[i] == '.')) {
                    i++;
                }
                i--;
            }else if (isNumeric(expression[i])) {
                float operand = atof(&expression[i]);
                while (i < len && (isNumeric(expression[i]) || expression[i] == '.')) {
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
                    operandStack[++operandTop] = performOperation(operand1, operand2, currentOperator);
                }

                operatorStack[++operatorTop] = expression[i];
            } else if (expression[i] == '(') {
                operatorStack[++operatorTop] = expression[i];
            } else if (expression[i] == ')') {
                while (operatorTop >= 0 && operatorStack[operatorTop] != '(') {
                    float operand2 = operandStack[operandTop--];
                    float operand1 = operandStack[operandTop--];
                    char currentOperator = operatorStack[operatorTop--];
                    operandStack[++operandTop] = performOperation(operand1, operand2, currentOperator);
                }
                
                operatorTop--;
            }
        }

        while (operatorTop >= 0) {
            float operand2 = operandStack[operandTop--];
            float operand1 = operandStack[operandTop--];
            char currentOperator = operatorStack[operatorTop--];
            operandStack[++operandTop] = performOperation(operand1, operand2, currentOperator);
        }
        return operandStack[operandTop];
    }


    int evaluateCondition(float operand1, char* condition, float operand2 ){
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

    char* getCalculType(float nombre) {
        if (nombre == (int)nombre) {
            return "int";
        } else {
            return "float";
        }
    }
    
%}

%union {
    int entier; //
    char* string;
    float reel; //
}

%token AFF
%token PVG
%token <string> INT <string> FLOAT <string> BOOL <string> CHAR <string> STRING
%token BEG END 
%token <string> CONST
%token <string> Idf 
%token <string> const_int <string> const_float <string> const_bool <string> const_char <string> const_string
%token VIRGULE 
%token <string> PLUS <string> SUB <string> MUL <string> DIV
%token SUP SUPEGAL INF INFEGAL DIFF EGAL DPAFF IF ELSE
%token FOR PARG PARD CrochetG CrochetD Commentaire WHILE DO


%left MUL DIV //
%left SUB PLUS //
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

type  : FLOAT {strcpy(Var_type,$1);}|BOOL {strcpy(Var_type,$1);}|INT {strcpy(Var_type,$1);}|CHAR {strcpy(Var_type,$1);}|STRING {strcpy(Var_type,$1);}
DEC_VALUES : const_int{strcpy(type_VALUE,"int");strcpy(num_VALUE,$1);}|const_float{strcpy(type_VALUE,"float");strcpy(num_VALUE,$1);}|const_bool{strcpy(type_VALUE,"bool");strcpy(num_VALUE,$1);}|const_char{strcpy(type_VALUE,"char");strcpy(num_VALUE,$1);}|const_string{strcpy(type_VALUE,"string"); strcpy(num_VALUE,$1);}
INSTR_VALUES : const_int{push("int");push($1);}|const_float{push("float");push($1);}|const_bool{push("bool");push($1);}|const_char{push("char");push($1);}|const_string{push("string"); push($1);}

DEC_IDF : Idf {
    if (rechercher($1)!=-1 && strcmp(typeIDF($1),"/")!=0){
        printf("\nERREUR SEMANTIQUE ::: LA VARIABLE %s EST DEJA DECLAREE ligne ::: %d, col ::: %d\n",$1,nblignes,col);
        exit(EXIT_FAILURE);
    }else{
        UpdateTypeConst($1,Var_type,"non");
    }
}
|Idf AFF DEC_VALUES {
    if (rechercher($1)!=-1 && strcmp(typeIDF($1),"/")!=0){
        printf("\nERREUR SEMANTIQUE ::: LA VARIABLE %s EST DEJA DECLAREE ::: ligne ::: %d, col ::: %d\n",$1,nblignes,col);
        exit(EXIT_FAILURE);
    }else{
        UpdateTypeConst($1,Var_type,"non");        
        if ((strcmp(Var_type, type_VALUE) == 0) || ((strcmp(Var_type, "float") == 0) && (strcmp(type_VALUE, "int") == 0))){
            updateIDFValue($1,num_VALUE);
        }else{
            printf("\nERREUR SEMANTIQUE ::: Type incompatible pour la variable: %s, TYPE affectee : %s, TYPE attendue : %s, ::: ligne %d, col ::: %d\n",$1,type_VALUE,Var_type,nblignes,col);
            exit(EXIT_FAILURE);
        }
    }
}

CONST_IDF: Idf AFF DEC_VALUES{
        if (rechercher($1)!=-1 && strcmp(typeIDF($1),"/")!=0){
        printf("\nERREUR SEMANTIQUE LA VARIABLE %s EST DEJA DECLAREE ::: ligne %d, col ::: %d\n",$1,nblignes,col);
        exit(EXIT_FAILURE);
    } else{
        UpdateTypeConst($1,Var_type,"oui");
        if ((strcmp(Var_type, type_VALUE) == 0) || ((strcmp(Var_type, "float") == 0) && (strcmp(type_VALUE, "int") == 0))){
            updateIDFValue($1,num_VALUE);
        }else{
            printf("\nERREUR SEMANTIQUE ::: Type incompatible pour la variable: %s, TYPE affectee : %s, TYPE attendue : %s, ::: ligne %d, col ::: %d\n",$1,type_VALUE,Var_type,nblignes,col);
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

/* PARTIE INSTRUCTIONS */

Liste_instructions : Instruction Liste_instructions
|Instruction

Instruction : AFFECTATION PVG
|BOUCLE
|CONDITION
|Commentaire
|AUTOOPERATION PVG

AFFECTATION: Idf DPAFF Expression{
    if (rechercher($1)!=-1 && strcmp(typeIDF($1),"/")==0){
        printf("\nERREUR SEMANTIQUE LA VARIABLE %s N'EST PAS DECLAREE ::: ligne %d, col ::: %d",$1,nblignes,col);
        exit(EXIT_FAILURE);
    }else if(isconst($1)){
        printf("\nERREUR SEMANTIQUE ::: MODIFICATION DE CONSTANTE %s INTERDITE ::: ligne %d, col ::: %d",$1,nblignes,col);
        exit(EXIT_FAILURE);
    }else{
        if(strcmp(type_Calcul,"bool")==0 || strcmp(type_Calcul,"char")==0 || strcmp(type_Calcul,"string")==0){
            if(strcmp(typeIDF($1),type_Calcul)!=0){
                printf("\nERREUR SEMANTIQUE ::: INCOMPATIBILTE DE TYPE -> VARIABLE: %s, TYPE affectee : %s, TYPE attendue : %s, ::: ligne %d, col ::: %d\n",$1,type_Calcul,typeIDF($1),nblignes,col);
                pop(); // Libérer la pile
                exit(EXIT_FAILURE);
            }else{
                char* AFF = mirrorString(pop());
                printf("\n Expression : %s := %s\n",$1,AFF);

                updateIDFValue($1,AFF);
            }
        }else{
            strcpy(result,pop());
            char* ret = mirrorString(result);
            float value = evaluate(ret);
            char* type_value = getCalculType(value);

            printf("\n Expression : %s := %s => %s = %g\n",$1,ret,$1,value);

            if(strcmp(typeIDF($1),type_value)==0 || (strcmp(typeIDF($1),"float")==0 && strcmp(type_value,"int")==0)){
                sprintf(ret,"%g",value);
                updateIDFValue($1,ret);
            }else{
                printf("\nERREUR SEMANTIQUE ::: INCOMPATIBILTE DE TYPE -> VARIABLE: %s, TYPE affectee : %s, TYPE attendue : %s, ::: ligne %d, col ::: %d\n",$1,type_value,typeIDF($1),nblignes,col);
                exit(EXIT_FAILURE);
            }
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
    char* right = pop();
    char* OPR = pop();
    strcpy(valeur,getValue($1));

        if (rechercher($1) != -1 && strcmp(typeIDF($1), "/") == 0) {
            printf("\nERREUR SEMANTIQUE LA VARIABLE %s N'EST PAS DECLAREE ::: ligne %d, col ::: %d", $1, nblignes,col);
            exit(EXIT_FAILURE);
        }else if (strcmp(getValue($1), "/") == 0) {
            printf("\nERREUR SEMANTIQUE LA VARIABLE %s N'A PAS DE VALEUR ASSIGNEE ::: ligne %d, col ::: %d", $1, nblignes,col);
            exit(EXIT_FAILURE);
        }else if (strcmp(typeIDF($1),"bool") == 0 || strcmp(type_Calcul,"bool") == 0){
            printf("\nERREUR SEMANTIQUE ::: OPERATION IMPOSSIBLE SUR DES OPERANDES BOOLEEN ::: ligne %d, col ::: %d\n", nblignes,col);
            exit(EXIT_FAILURE);
        }else if(strcmp(typeIDF($1),"char") == 0 || strcmp(type_Calcul,"char") == 0){
            printf("\nERREUR SEMANTIQUE ::: OPERATION IMPOSSIBLE SUR DES CARACTERES ::: ligne %d, col ::: %d\n", nblignes,col);
            exit(EXIT_FAILURE);
        }else if (strcmp(type_Calcul, "string") == 0 && strcmp(typeIDF($1), "string") == 0){

            if(strcmp(OPR,"+")!=0){
                printf("\nERREUR SEMANTIQUE ::: OPERATION IMPOSSIBLE SUR DES CHAINES DE CARACTERES ::: ligne %d, col ::: %d\n", nblignes,col);
                exit(EXIT_FAILURE);
            }else{
                //Faire La concaténation

                if (right[0] == '\"' && right[strlen(right) - 1] == '\"' && valeur[0] == '\"' && valeur[strlen(valeur) - 1] == '\"') {
                        
                    char NewStr1[100],NewStr2[100];
                    strncpy(NewStr1, right + 1, strlen(right) - 2);
                    strncpy(NewStr2, valeur + 1, strlen(valeur) - 2);

                    NewStr1[strlen(right) - 2] = '\0';
                    NewStr2[strlen(valeur) - 2] = '\0';

                    char* result = (char*)malloc(( strlen(NewStr1) + strlen(NewStr2) + 1) * sizeof(char));
                    char* ret = mirrorString(NewStr2);
                    
                    strcpy(result,"\"");
                    strcat(result,NewStr1);
                    strcat(result,ret);
                    strcat(result,"\"");

                    push(result);
                }
            }
        }else if((strcmp(typeIDF($1),"string") != 0 && strcmp(type_Calcul,"string")== 0) || (strcmp(typeIDF($1),"string") == 0 && strcmp(type_Calcul,"string")!= 0)){
                printf("\nERREUR SEMANTIQUE ::: OPERATION IMPOSSIBLE SUR DES CHAINES DE CARACTERES ::: ligne %d, col ::: %d\n", nblignes,col);
                exit(EXIT_FAILURE);
        }else{


            char* ret = mirrorString(valeur);
            char* result = (char*)malloc((strlen(right) + strlen(valeur) + strlen(OPR) + 1) * sizeof(char));

            strcpy(result,right);
            strcat(result,OPR);

            strcat(result,ret);

            push(result);
        }
}
|Idf {
    if (rechercher($1) != -1 && strcmp(typeIDF($1), "/") == 0) {
        printf("\nERREUR SEMANTIQUE LA VARIABLE %s N'EST PAS DECLAREE ::: ligne %d, col ::: %d", $1, nblignes,col);
        exit(EXIT_FAILURE);
    }else if (strcmp(getValue($1), "/") == 0) {
        printf("\nERREUR SEMANTIQUE LA VARIABLE %s N'A PAS DE VALEUR ASSIGNEE ::: ligne %d, col ::: %d", $1, nblignes,col);
        exit(EXIT_FAILURE);
    }else{

        strcpy(type_Calcul,typeIDF($1));

        strcpy(result,getValue($1));
        char* ret = mirrorString(result);
        push(ret);
    }
}
|INSTR_VALUES OPP Expression{

    char* right = pop();
    char* OPR = pop();
    char* valeur = pop();
    char* type = pop();


    if (strcmp(type,"bool") == 0 || strcmp(type_Calcul,"bool") == 0){
        printf("\nERREUR SEMANTIQUE ::: OPERATION IMPOSSIBLE SUR DES OPERANDES BOOLEEN ::: ligne %d, col ::: %d\n", nblignes,col);
        exit(EXIT_FAILURE);
    }else if(strcmp(type,"char") == 0 || strcmp(type_Calcul,"char") == 0){
        printf("\nERREUR SEMANTIQUE ::: OPERATION IMPOSSIBLE SUR DES CARACTERES ::: ligne %d, col ::: %d\n", nblignes,col);
        exit(EXIT_FAILURE);
    }else if (strcmp(type_Calcul, "string") == 0 && strcmp(type, "string") == 0){

        if(strcmp(OPR,"+")!=0){
            printf("\nERREUR SEMANTIQUE ::: OPERATION IMPOSSIBLE SUR DES CHAINES DE CARACTERES ::: ligne %d, col ::: %d\n", nblignes,col);
            exit(EXIT_FAILURE);
        }else{
        //Faire La concaténation

            if (right[0] == '\"' && right[strlen(right) - 1] == '\"' && valeur[0] == '\"' && valeur[strlen(valeur) - 1] == '\"') {
                    
                char NewStr1[100],NewStr2[100];
                strncpy(NewStr1, right + 1, strlen(right) - 2);
                strncpy(NewStr2, valeur + 1, strlen(valeur) - 2);

                NewStr1[strlen(right) - 2] = '\0';
                NewStr2[strlen(valeur) - 2] = '\0';

                char* result = (char*)malloc(( strlen(NewStr1) + strlen(NewStr2) + 1) * sizeof(char));
                char* ret = mirrorString(NewStr2);
                
                strcpy(result,"\"");
                strcat(result,NewStr1);
                strcat(result,ret);
                strcat(result,"\"");

                push(result);
            }
        }
    }else if((strcmp(type,"string") != 0 && strcmp(type_Calcul,"string")== 0) || (strcmp(type,"string") == 0 && strcmp(type_Calcul,"string")!= 0)){
            printf("\nERREUR SEMANTIQUE ::: OPERATION IMPOSSIBLE SUR DES CHAINES DE CARACTERES ::: ligne %d, col ::: %d\n", nblignes,col);
            exit(EXIT_FAILURE);
    }else{
        char* result = (char*)malloc((strlen(right) + strlen(valeur) + strlen(OPR) + 1) * sizeof(char));

        char* ret = mirrorString(valeur);

        strcpy(result,right);
        strcat(result,OPR);
        strcat(result,ret);


        push(result);

    }
}
|INSTR_VALUES{
    strcpy(result,pop());

    char* type = pop();
    strcpy(type_Calcul,type);

    char* ret = mirrorString(result);

    push(ret);
}
|PARG COMPARE_EXPR PARD
|ExpressionParenthese

COMPAREOPERANDS : Idf{
    if (rechercher($1) != -1 && strcmp(typeIDF($1), "/") == 0) {
        printf("\nERREUR SEMANTIQUE LA VARIABLE %s N'EST PAS DECLAREE ::: ligne %d, col ::: %d", $1, nblignes,col);
        exit(EXIT_FAILURE);
    }else if (strcmp(getValue($1), "/") == 0) {
        printf("\nERREUR SEMANTIQUE LA VARIABLE %s N'A PAS DE VALEUR ASSIGNEE ::: ligne %d, col ::: %d", $1, nblignes,col);
        exit(EXIT_FAILURE);
    }else{
        if (strcmp(typeIDF($1),"bool") == 0){
            printf("\nERREUR SEMANTIQUE ::: OPERATION IMPOSSIBLE SUR DES OPERANDES BOOLEEN ::: ligne %d, col ::: %d\n", nblignes,col);
            exit(EXIT_FAILURE);
        }else if(strcmp(typeIDF($1),"char") == 0){
            printf("\nERREUR SEMANTIQUE ::: OPERATION IMPOSSIBLE SUR DES CARACTERES ::: ligne %d, col ::: %d\n", nblignes,col);
            exit(EXIT_FAILURE);
        }else if(strcmp(typeIDF($1),"string") == 0){
            printf("\nERREUR SEMANTIQUE ::: OPERATION IMPOSSIBLE SUR DES CHAINES DE CARACTERES ::: ligne %d, col ::: %d\n", nblignes,col);
            exit(EXIT_FAILURE);
        }


        strcpy(result,getValue($1));
        char* ret = mirrorString(result);
        push(ret);
    }
}
|INSTR_VALUES{
    strcpy(result,pop());
    char* type = pop();
    if (strcmp(type, "bool") == 0) {
        printf("\nERREUR SEMANTIQUE ::: OPERATION IMPOSSIBLE SUR DES OPERANDES BOOLEEN ::: ligne %d, col ::: %d\n", nblignes,col);
        exit(EXIT_FAILURE);
    }
    else{
        strcpy(type_Calcul,type);

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
        printf("\nERREUR SEMANTIQUE LA VARIABLE %s N'EST PAS DECLAREE ::: ligne %d, col ::: %d", $1, nblignes,col);
        exit(EXIT_FAILURE);
    }else if (strcmp(getValue($1), "/") == 0) {
        printf("\nERREUR SEMANTIQUE LA VARIABLE %s N'A PAS DE VALEUR ASSIGNEE ::: ligne %d, col ::: %d", $1, nblignes,col);
        exit(EXIT_FAILURE);
    }else{
        char* valeur = getValue($1);

        strcpy(result,valeur);
        strcat(result,"+");
        strcat(result,"1");
        printf("\n Expression : %s := %s\n",$1,result);

        sprintf(result,"%g",evaluate(result));
        updateIDFValue($1,result);
    }
}
|Idf SUB SUB{
    if (rechercher($1) != -1 && strcmp(typeIDF($1), "/") == 0) {
        printf("\nERREUR SEMANTIQUE LA VARIABLE %s N'EST PAS DECLAREE ::: ligne %d, col ::: %d", $1, nblignes,col);
        exit(EXIT_FAILURE);
    }else if (strcmp(getValue($1), "/") == 0) {
        printf("\nERREUR SEMANTIQUE LA VARIABLE %s N'A PAS DE VALEUR ASSIGNEE ::: ligne %d, col ::: %d", $1, nblignes,col);
        exit(EXIT_FAILURE);
    }else{
        char* valeur = getValue($1);

        strcpy(result,valeur);
        strcat(result,"-");
        strcat(result,"1");
        printf("\n Expression : %s := %s\n",$1,result);
        sprintf(result,"%.2f",evaluate(result));
        updateIDFValue($1,result);
    }
}

BOUCLE: FOR PARG AFFECTATION PVG COMPARAISON PVG Compteur PARD CrochetG Liste_instructions CrochetD
|WHILE PARG COMPARAISON PARD CrochetG Liste_instructions CrochetD
|DO CrochetG Liste_instructions CrochetD WHILE PARG COMPARAISON PARD

CONDITION: IF PARG COMPARAISON PARD CrochetG Liste_instructions CrochetD ELSE CrochetG Liste_instructions CrochetD
|IF PARG COMPARAISON PARD CrochetG Liste_instructions CrochetD 
|IF PARG COMPARAISON PARD CrochetG Liste_instructions CrochetD ELSE CONDITION


COMPARAISON : Expression OppCond Expression{

    char* OPR1 = pop();
    OPR1 = mirrorString(OPR1);
    float value1 = evaluate(OPR1);

    char* OPR = pop();

    char* OPR2 = pop();
    OPR2 = mirrorString(OPR2);
    float value2 = evaluate(OPR2);

    char* result = (char*)malloc(sizeof(char));
    int valeur = evaluateCondition(value2,OPR,value1);
    if(valeur==1){
        printf("\n Condition verifiee ::: line %d\n",nblignes);
    }else{
        printf("\n Condition non verifiee ::: line %d\n",nblignes);
    }
    sprintf(result,"%d",valeur);
    
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
    printf("\n\nSYNTAX ERROR at line ::: %d, col ::: %d",nblignes,col);
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