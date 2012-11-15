#include<stdio.h>
#include<stdlib.h>
#include "ces.h"
#include "file.h"

int main(int argc, char* argv){
	Processador *CES;
	FILE *file;
	short int *memoria;
	unsigned short int EOP;
	unsigned short int org;
	
	CES = init_ces();
	memoria = init_memory(16*1024); // 16K palavras de 16 bits
	file = init_file();

	if(file == NULL){
		printf("Erro na leitura do arquivo\n");
		return 0;
	}

	if(!read_instr_of_file(file, memoria)){
		printf("Erro na execução do arquivo\n");
		return -1;
	}else{
		fclose(file);
		exec(CES,memoria,org,memoria);
	}

	return 0;
}
