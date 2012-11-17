#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "ces.h"
#include "file.h"

void printModoDeUso(char* execFile){
	printf("Uso: %s -f file.hex [--org origem] [-i qtd_iteracoes]",execFile);
	printf("\n\torigem e qtd_iteracoes são valores inteiros.");
	printf("\n\torigem deve ser um valor em HEXADECIMAL.\n\n");
}

int main(int argc, char** argv){
	Processador *CES;
	FILE *file;
	short int *memoria;
	unsigned short int eop = 4098; // Programa de 4K
	unsigned short int k;
	char* p;
	int output_file = 0;
	
	if(argc>=3){
		CES = init_ces();
		memoria = init_memory(16*1024); // 16K palavras de 16 bits
		for(k=1;k<argc;k++){
				if(strcmp(argv[k],"-f")==0)
					file = init_file(argv[k+1]);
				else if(strcmp(argv[k],"--org")==0)
					CES->regP = (unsigned short int) strtoul(argv[k+1],&p,16);
				else if(strcmp(argv[k],"-i")==0)
					eop = (unsigned short int) atoi(argv[k+1]);
				else if(strcmp(argv[k],"-o")==0) 
					output_file = 1;
		}
	}else{
		printModoDeUso(argv[0]);
		return 0;
	}
	
	if(file == NULL){
		printf("Erro na leitura do arquivo\n");
		return 0;
	}

	if(!read_instr_of_file(file, memoria)){
		printf("Erro na execução do arquivo\n");
		return -1;
	}
	
	fclose(file);
	
	//Loop principal do processador
	for(k=0;k<eop;k++){
		// Processador sendo executado neste instante
		exec(CES,memoria);
		// Fim da execução do processador
	}
	printRegistradores(*CES);
	
	return 0;
}
