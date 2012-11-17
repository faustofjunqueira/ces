#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "ces.h"
#include "file.h"

void printModoDeUso(char* execFile){
	printf("\tUso: %s -f file.hex --org origem -i qtd_iteracoes [output-opcional]",execFile);
	printf("\n\t\t\torigem e qtd_iteracoes são valores inteiros.");
	printf("\n\t\t\torigem deve ser um valor em HEXADECIMAL.\n");
	printf("\n\tOutput:\n\t\t\t-o\tgera um arquivo de output, chamado output.ces\n\n");
}

int main(int argc, char** argv){
	Processador *CES;
	FILE *file;
	short int *memoria;
	unsigned short int eop;
	unsigned short int org;
	int k;
	char* p;
	int output_file = 0;
	
	if(argc>=7){
		CES = init_ces();
		memoria = init_memory(16*1024); // 16K palavras de 16 bits
		for(k=1;k<argc;k++){
				if(strcmp(argv[k],"-f")==0)
					file = init_file(argv[k+1]);
				else if(strcmp(argv[k],"--org")==0)
					org = (unsigned short int) strtoul(argv[k+1],&p,16);
				else if(strcmp(argv[k],"-i")==0)
					eop = (unsigned short int) atoi(argv[k+1]);
				else if(strcmp(argv[k],"-o")==0) 
					output_file = 1;
		}
		if(file == NULL){
			printf("Erro na leitura do arquivo\n");
			return 0;
		}

		if(!read_instr_of_file(file, memoria)){
			printf("Erro na execução do arquivo\n");
			return -1;
		}else{
			fclose(file);
			char *out = exec(CES,memoria,org,eop);
			if(output_file){
				FILE *output = fopen("output.ces","w");
				fprintf(output,"%s",out);
				fclose(output);
			}
			printf("%s",out);
		}
	}else	printModoDeUso(argv[0]);
	
	return 0;
}
