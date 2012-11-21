#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ces.h"
#include "rom.h"

void printRegistradores(Processador p, char *st){
	char *buffer = (char*) malloc (sizeof(char) * 40*3.5);
	sprintf(buffer,"Registrador P: %hX\nRegistrador T: %X\nResistrador C: %d\n----------------------\n",p.regP,p.regT,p.regC);
	strcat(st,buffer);
}

Processador *init_ces(){
	Processador *p = (Processador*) malloc (sizeof(Processador));
	p->regP = 0x0400;
	p->regT = 0;
	p->regC = 0;
	return p;
}

short int *init_memory(int l){
	if(l > 0x3FF){
	short int *memory = (short int*) malloc (sizeof(short int)*l);
		memset(memory, 0, sizeof(short int)*l);
		init_ROM(memory);
		return memory;
	}else{
		printf("Aloque mais memoria para suportar a ROM\n");
		return NULL;
	}

}

void SUB(Processador* p,short int* memoria, unsigned short int posMemoria){
	
	p->regP++;
	
	if(((short int)memoria[posMemoria]==(short int)0) && ((short int)p->regT!=(short int)0))
		p->regC = 1;
	else if((short int)memoria[posMemoria]==(short int)0xffff)
		p->regC = 0;
	else if((short int)(memoria[posMemoria]-p->regT)<(short int)0)
		p->regC = 1;
	else
		p->regC = 0;

	p->regT = (short int)memoria[posMemoria] - (short int)p->regT;
}

void LE(Processador* p, short int* memoria, unsigned short int posMemoria){
	p->regP++;
	p->regT = (short int)memoria[posMemoria];
}

void ESC(Processador* p, short int* memoria, unsigned short int posMemoria){
	p->regP++;
	memoria[posMemoria] = (short int)p->regT;
}

void DNP(Processador* p, unsigned short int posMemoria){
	if(p->regC == 0)
		p->regP = (unsigned short int)posMemoria;
	else
		p->regP++;
}

void exec(Processador* p, short int* memoria){
	switch(((memoria[p->regP]>>14)-0xFFFFFFFC)%4){
		case 0:
			LE(p,memoria,memoria[p->regP]);
			break;
		case 1:
			ESC(p,memoria,memoria[p->regP]-0x4000);
			break;
		case 2:
			SUB(p,memoria,memoria[p->regP]-0x8000);
			break;
		case 3:
			DNP(p,memoria[p->regP]-0xc000);
			break;
	}
}
