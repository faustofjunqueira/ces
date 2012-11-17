#ifndef CES_H
#define CES_H
typedef struct{
	short unsigned int regP; //prox instrucao a ser executada
	short int regT; //trabalho
	short int regC; //vai um
}Processador;
void printRegistradores(Processador p);
Processador *init_ces();
short int *init_memory(int l);
void SUB(Processador* p,short int* memoria, unsigned short int posMemoria);
void LE(Processador* p, short int* memoria, unsigned short int posMemoria);
void ESC(Processador* p, short int* memoria, unsigned short int posMemoria);
void DNP(Processador* p, unsigned short int posMemoria);
void exec(Processador* p, short int* memoria);
#endif // CES_H
