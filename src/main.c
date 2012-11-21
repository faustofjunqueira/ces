#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "ces.h"
#include "file.h"

void printModoDeUso(char* execFile){
	printf("Uso: %s -f file.hex [opcoes]\n\n",execFile);
	printf("OPCOES:\n");
	printf("\t--org origem\tValor inteiro positivo HEXADECIMAL que define a posicao inicial de execucao\n");
	printf("\t-i iteracoes\tValor inteiro positivo que define o numero de instrucoes que serao executadas\n");
	printf("\t-o saida\tDefine um arquivo que vai conter a saida\n");
	printf("\t--interactive \tExibe a execucao passo a passo para o usuario.\n");
	printf("\t--IO \t\tAtiva o input e output do CES.\n\n");
}

int main(int argc, char** argv){
	Processador *CES;
	FILE *file = NULL;
	FILE *output = NULL;
	short int *memoria = NULL;
	unsigned short int eop = 4098; // Programa de 4K
	unsigned short int k;
	char* p = NULL;
	char* output_file = NULL;
	int interactive = 0;
	int inputOutput = 0;

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
					output_file = argv[k+1];
				else if(strcmp(argv[k],"--interactive")==0)
					interactive = 1;
				else if(strcmp(argv[k],"--IO")==0)
					inputOutput = 1;
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

	char* out = (char*) malloc (sizeof(char)*(40*3.5*eop));

	if(output_file!=NULL) output = fopen(output_file,"w");

	//Loop principal do processador
	for(k=0;k<eop;k++){
		//Inicio do tratamento do IO
		if(inputOutput){
			printf("%c",memoria[0x3ffe]);
			memoria[0x3ffe] = 0x0000;
			if(memoria[CES->regP]==0x3fff){
				memoria[0x3fff] = getchar();
			}
		}
		//Fim do tratamento do IO
		
		// Processador sendo executado neste instante
		exec(CES,memoria);
		// Fim da execução do processador
		
		if(output_file==NULL) memset(out,0,sizeof(char)*strlen(out));
		printRegistradores(*CES,out);

		if(interactive){
			printf("%s",out);
			if(output_file!=NULL) fprintf(output,"%s",out);
			getchar();
		}
	}

	if(output_file!=NULL){
		if(!interactive) fprintf(output,"%s",out);
		fclose(output);
	}
	else if(!inputOutput){
		printf("%s",out);
	}

	return 0;
}
