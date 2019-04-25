#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct celula celula, *lista;
struct celula{
	int linha;
	lista posterior;
};

typedef struct arvore_no arvore_no, *arvore;
struct arvore_no{
	char conteudo[20];
	arvore direita;
	arvore esquerda;
	arvore pai;
	lista lin;
};

typedef enum {ERROR, OK} status;
typedef enum {FALSE=0, TRUE=1 } bool;

#define ESQUERDA(T) ((T)->esquerda)
#define DIREITA(T)  ((T)->direita)
#define PAI(T) 		((T)->pai)
#define DADO(T)     ((T)->conteudo)
#define LINHA(T)    ((T)->linha)
#define LIN(T)		((T)->lin)
#define POST(T)		((T)->posterior)

//########## Prototipos de funcoes ##########
status alocar(arvore *p_T, char dado[], int lin);
status insere(arvore *p_T, char dado[], int lin);
bool arvore_vazia(arvore T);
status inicia_arvore(arvore *p_T);
status caminharEmOrdem(arvore T,FILE *arquivo);
int Leitura_Arquivo_Inteiros(char *nome_arquivo, arvore *p_T);
void show(arvore T, int b);
void printnode(char c[], int b);
void imprime(arvore T,FILE *arquivo);
//###########################################

status inicia_arvore(arvore *p_T)
{
	*p_T = NULL;
	return OK;
}

bool arvore_vazia(arvore T)
{
	return(T == NULL) ? TRUE : FALSE;
}

status alocar_lista(lista *p_L, int linha){
	lista L = (lista) malloc (sizeof(celula));
	if(L == NULL) return ERROR;
	LINHA(L) = linha;
	POST(L) = NULL;
	*p_L = L;
return OK;
}

status alocar(arvore *p_T, char dado[], int lin){
	arvore T = (arvore) malloc (sizeof(arvore_no));
	if(T == NULL) return ERROR;
	strcpy(DADO(T), dado);
	ESQUERDA(T) = NULL;
	DIREITA(T) = NULL;
	PAI(T) = NULL;

	lista L;
	if(alocar_lista(&L,lin) == ERROR) return ERROR;
	LIN(T) = L;
	*p_T = T;
return OK;
}

status insere_lista(lista *p_L, int lin){
lista L;
lista tmp;
	if(alocar_lista(&L, lin) == ERROR) return ERROR;
	for(tmp = *p_L; POST(tmp) != NULL; tmp = POST(tmp));
	POST(tmp) = L;
return OK;
}

status insere(arvore *p_T, char dado[], int lin)
{arvore T;
	if(arvore_vazia(*p_T) == TRUE){
		if(alocar(&T, dado, lin) == ERROR) return ERROR;
		*p_T = T;
	}
	
	else{
		if(strcmp(dado,DADO(*p_T)) == -1){
			if(ESQUERDA(*p_T) == NULL){
				if(alocar(&T, dado, lin) == ERROR) return ERROR;
				ESQUERDA(*p_T) = T;
				PAI(ESQUERDA(*p_T)) = *p_T;
				}
				else 
				insere(&ESQUERDA(*p_T), dado, lin);	
			}
		else if (strcmp(dado,DADO(*p_T)) == 0){
				insere_lista(&LIN(*p_T), lin);
		
			}
			else{ 
				if(DIREITA(*p_T) == NULL){
					if(alocar(&T, dado, lin) == ERROR) return ERROR;
					DIREITA(*p_T) = T;
					PAI(DIREITA(*p_T)) = *p_T;
					}
					else
					insere(&DIREITA(*p_T), dado, lin);
				}
		}

	return OK;
}
/*
void caminharEmOrdem(arvore T) {
	if (T != NULL) {
		caminharEmOrdem(ESQUERDA(T));
		printf("\n%s linha:  ", DADO(T));
		for(;LIN(T) != NULL; LIN(T) = POST(LIN(T)))
		printf("%d  ",LINHA(LIN(T)));
		caminharEmOrdem(DIREITA(T));
	}
}*/

status caminharEmOrdem(arvore T,FILE *arquivo){
status rc;
	if(T == NULL) return OK;
	rc = caminharEmOrdem(ESQUERDA(T),arquivo);
	if(ESQUERDA(T) == NULL || DIREITA(T) == NULL)
		imprime(T,arquivo);
	rc = caminharEmOrdem(DIREITA(T),arquivo);
return rc;
}

void imprime(arvore T, FILE *arquivo){
		fprintf(arquivo,"\n%s linha: ", DADO(T));
		for(;LIN(T) != NULL; LIN(T) = POST(LIN(T)))
		fprintf(arquivo,"%d ",LINHA(LIN(T)));
	
} 
 
 bool caracter_valido(char c){
    if(c=='-') return TRUE;
    else if (c>='0'&& c<='9') return TRUE;
    else if (c>='a'&& c<='z') return TRUE;
    else if (c>='A'&& c<='Z') return TRUE;
    else return FALSE;
}

int Leitura_Arquivo_Inteiros(char *nome_arquivo, arvore* p_T){
	FILE *arquivo;
    char c;
    int linha = 1;
    char palavra[21];
    int i = 0;
    arvore *aux;
	
	if((arquivo = fopen(nome_arquivo,"r")) == NULL)
	{
		printf("Erro ao abrir arquivo!!!\n\n");
		exit(1);
	}
    
	while(c != EOF){
        while(c !='\n' && c!= EOF){
            i = 0;
            while(caracter_valido(c) == TRUE){
                palavra[i] = c;
                i++;
                c = fgetc(arquivo);
            }
            palavra[i] = '\0';
            i=0;
            strlwr(palavra);
			if(palavra[i] != '\0')
				insere(&*p_T, palavra, linha);
            if(c!='\n')
				c = fgetc(arquivo);
        }
		if(c=='\n'){
			linha++;
			c = fgetc(arquivo);
		}
    }
}

void show(arvore T, int b) {
    if (arvore_vazia(T)) {
        printnode(" ", b);
        return;
    }
    show(DIREITA(T), b+1);    
    printnode(DADO(T), b);
    show(ESQUERDA(T), b+1);    
}

void printnode(char c[], int b) {
    int i;
    for (i = 0; i < b; i++) printf("---");
    printf("%s\n", c);
}