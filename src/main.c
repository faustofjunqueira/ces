#include<stdio.h>
#include<stdlib.h>
#include "ces.h"
#include "file.h"

int main(){
	short int *memoria = init_memory(16*1024); // 16K palavras de 16 bits
	Processador *CES = init_ces();
	FILE *file = init_file();
	int n_clocks;
	short int end_start;
	printf("Numero de clocks: ");
	scanf("%d", &n_clocks);
	printf("\n");
	printf("Endereco Inicial: ");
	scanf("%hX", &end_start);
	printf("\n");
	if(file == NULL){
		printf("Erro na leitura do arquivo\n");
		return 0;
	}

	if(!read_instr_of_file(file, memoria)){
		printf("Erro na execução do arquivo\n");
		return -1;
	}else{
		fclose(file);
		exec(CES,memoria,end_start,n_clocks);
	}

	return 0;
}
