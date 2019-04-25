#include"trabalhov2.h"
#include<windows.h>

int main(int argc, char *argv[])
{ arvore teste;
	int inicio, final, tempo;
	inicio = GetTickCount(); 
inicia_arvore(&teste);
	if(argc < 2)
  	{
		printf("\nErro: Digite o nome do arquivo !!!\n\n");
        	exit(1);
	}
	inicia_arvore(&teste);
	if (Leitura_Arquivo_Inteiros(argv[1], &teste)){ //se memoria alocada?
	FILE *arquivo;
	char url[] = "resultado.txt";
	if((arquivo = fopen(url,"w"))== NULL)
	{	printf("Erro ao abrir arquivo!!!\n\n");
        exit(1);
	}
	caminharEmOrdem(teste,arquivo);
	final = GetTickCount();
    tempo = final - inicio;
	fprintf(arquivo,"\n\nO tempo total da execucao foi : %d segundos",tempo/1000);
	fclose(arquivo);
	
	}
}
