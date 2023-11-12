typedef struct{
    char NomEntite[20];
    char CodeEntite[20];
    char TypeEntite[20];
    char isConstant[20];

}TypeTS;

TypeTS TS[1000];
int cptTS=0;

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
        cptTS++;
    }
}

int isconst(char entite[]){
	int i=0; 
  	while(i<cptTS) { 
  		if (strcmp(entite,TS[i].NomEntite) == 0 && strcmp("oui",TS[i].isConstant) == 0)
  		return 1; 
  	    i++;
  	}
  	return 0;
}


void afficher(){

    if (cptTS==0){
        printf("Table des symboles VIDE");
    }else{
        int i=0;
            printf("\n======================================================");
            printf("\n| Nom Entite | Code Entite  | Type Entite | Constant |");
            printf("\n======================================================");

        while(i<cptTS){
            printf("\n| %10s | %12s | %11s | %8s |",TS[i].NomEntite,TS[i].CodeEntite,TS[i].TypeEntite,TS[i].isConstant);
            i++;
        }
            printf("\n======================================================");

    }
}