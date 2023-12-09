typedef struct{
    char NomEntite[20];
    char CodeEntite[20];
    char TypeEntite[20];
    char isConstant[20];
    char Value[20];
}TypeTS;

TypeTS TS[1000];
int cptTS=0; // Compteur de la TS


#define STACK_SIZE 100
#define MAX_STRING_LENGTH 50
#define STRING_SIZE 50

char* stack[STACK_SIZE];
int top = 0; // top de la PILE

int isEmpty(){
    return (top == 0);
}

void push(char* str){
    if (top < STACK_SIZE) {
        stack[top++] = str;
    } else {
        printf("Error: Stack overflow\n");
    }
}

char* pop() {
    if (top >= 0) {
        return stack[--top];
    } else {
        fprintf(stderr, "Stack underflow\n");
        exit(EXIT_FAILURE);
    }
}

void printStack(){
  if (top == 0) {
    printf("La pile est vide.\n");
    return;
  }

  printf("\nLa pile contient : \n");

  for (int i = top-1 ; i >=0; i--) {
    printf("    cellule %d : %-20s\n", i, stack[i]);
  }
}

int rechercher(char entite[]){
    int i=0;
    while(i<cptTS){
        if(strcmp(entite,TS[i].NomEntite)==0){
            return i;
        }
        i++;
    }
    return -1;
}

void inserer(char entite[],char code[],char type[], char isconstant[]){
    if(rechercher(entite)==-1){
        strcpy(TS[cptTS].NomEntite,entite);
        strcpy(TS[cptTS].CodeEntite,code);
        strcpy(TS[cptTS].TypeEntite,type);
        strcpy(TS[cptTS].isConstant,isconstant);
        strcpy(TS[cptTS].Value,"/");
        cptTS++;
    }
}

int isconst(char entite[]){
	int i=0; 
  	while(i<cptTS){
  		if (strcmp(entite,TS[i].NomEntite) == 0 && strcmp("oui",TS[i].isConstant) == 0)
  		return 1; 
  	    i++;
  	}
  	return 0;
}

char *getValue(char entite[]){
	int i=0; 
  	while(i<cptTS){ 
        if (strcmp(entite,TS[i].NomEntite)==0) 
  	        return TS[i].Value; 
  	    i++; 
  	}
  	return "";
}

char *typeIDF(char entite[]){
	int i=0; 
  	while(i<cptTS){ 
        if (strcmp(entite,TS[i].NomEntite)==0) 
  	        return TS[i].TypeEntite; 
  	    i++; 
  	}
  	return "";
}

void updateIDFValue(char entite[],char value[]){
    if (cptTS > 0){
        int index = rechercher(entite);
        strcpy(TS[index].Value, value);
    }
}

void UpdateTypeConst(char entite[],char type[],char isconstant[]){ 
    int index = rechercher(entite);
    if(index!=-1){
        strcpy(TS[index].TypeEntite,type);
        strcpy(TS[index].isConstant,isconstant);  
    }
}

void afficher(){

    if (cptTS==0){
        printf("Table des symboles VIDE");
    }else{
        int i=0;
            printf("\n======================================================================");
            printf("\n| Nom Entite | Code Entite  | Type Entite | Constant |    Valeur     |");
            printf("\n======================================================================");

        while(i<cptTS){
            printf("\n| %10s | %12s | %11s | %8s | %13s |",TS[i].NomEntite,TS[i].CodeEntite,TS[i].TypeEntite,TS[i].isConstant,TS[i].Value);
            i++;
        }
            printf("\n======================================================================");

    }
}
