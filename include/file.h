/**
* REGRAS DO ARQUIVO
** CODIGO DE MAQUINA
***************************************************************
*TABULAÇÃO A VONTADE ENTRE O INICIO DA LINHA E O CODIGO	      *
* 																													  *
* CODIFICAÇÃO: XXXX:XXXX																			*
* endereco da instrucao(dois pontos)codigo da instrucao 			*
* Cada instrução em uma linha														 			*
* ENDEREÇO: quatro numero hexdecimais                         *
* CODIGO: quatro numero hexdecimais														*
* EXEMPLO																											*
* 	0400:1002																									*
* 	0401:9002 																								*
***************************************************************
Comentarios:
	Para comentar o codigo nao eh nescessario nenhum caracter especial
	como // ; # etc... pode escrever em qualquer lugar do codigo, porem
	soh nao pode quebrar a regra de numero :numero
	OBS: Nao pode escrever entre o : e o segundo numero
	OBS: Para comentar uma linha inteira ai sim eh nescessario a utilização
			 do caracter ; no inicio da linha.
*/
#ifndef FILE_H
#define FILE_H
int read_instr_of_file(FILE *file, short int *memory);
void printArray(short int *memory, int n);
FILE *init_file(char* file_name);
#endif // FILE_H
