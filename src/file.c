#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"

void printArray(short int *memory, int n){
	int i;
	for ( i = 0; i < n; i++) printf("%d) %hX : %hX\n", i, i, memory[i]);
}

int read_instr_of_file(FILE *file, short int *memory){
	int l_buffer = 65536;//2^16
	char *buffer = (char*) malloc (sizeof(char)*l_buffer);
	int line_read = 0;
	while (!feof(file)){

		line_read++;
		if(fgets(buffer, l_buffer, file) != NULL){
			short int temp1, temp2;
			char *st = buffer;
			while( *st == ' ' || *st =='\t' || *st =='\r') st++;
			if(*st == '\n' || *st == ';') continue;
			if(sscanf(st,"%hX",(unsigned short int*)&temp1) > 0){
				if( temp1 < 0x3FF){
					printf("temp1: %hX\n", temp1);
					printf("Voce tentou mudar area proibida da memoria\n");
					return 0;
				}
				st = strstr(st, ":");
				if(*st == 'j') continue;
				if(st != NULL){
					st++;
					if(sscanf(st,"%hX",(unsigned short int*)&temp2) > 0){
						memory[temp1] = temp2;
					}else{
						printf("ERRO: %d Nao foi encontrado o segundo numero em Hexdecimal\n", line_read);
						return 0;
					}
				}else{
					printf("ERRO: %d Nao foi encontrado :\n", line_read);
					return 0;
				}
			}else{
				printf("ERRO: %d Nao foi encontrado o primeiro numero em Hexdecimal\n", line_read);
				return 0;
			}
		}
	}

	return 1;
}

FILE *init_file(){
	char file_name[64];
	printf("Nome do arquivo de entrada: ");
	gets(file_name);
	printf("\n");
	if ( strstr(file_name, ".ces") == NULL){
		printf("Erro na inicialização do Arquivo\n");
		return NULL;
	}
	FILE *f = fopen(file_name, "r");
	return f;
}
