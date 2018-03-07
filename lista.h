#ifndef LISTA_H_
#define LISTA_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct komvos
{
	int theshPageTable; // ari8mos ths 8eshs tou page table pou fylaei h lista
	struct komvos * next; // deikths ston epomeno komvo ths listas
};

typedef struct komvos komvos;

komvos * arxhListas; // lista pou xrhsimopoieitai sth me8odo antikatastashs LRU
komvos * arxhListasWS; // lista pou xrhsimopoieitai sth me8odo antikatastashs WS

int topo8ethseSthKoryfh(int theshPageTable);
int topo8ethseSthKoryfhWS(int theshPageTable);
int elegkseAnYparxeiSthLista(int theshPageTable);
int vresTeleutaio();
void arxikopoihseLista();
void katastrofhListas();
void printLista(komvos * arxhListas);

#endif /* LISTA_H_ */
