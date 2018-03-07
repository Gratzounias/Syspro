#ifndef TYPOSSTOIXEIOUPAGETABLE_H_
#define TYPOSSTOIXEIOUPAGETABLE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "lista.h"

/*
 * auto to struct antiproswpeuei to typo twn eggrafwn pou exw sto page table
 */
struct periexomenoPageTable
{
		char ari8mosSelidas[21]; // filasete o ari8mos ths selidas sto dyadiko
		int dirtyBit; // flag gia na elegxw an xreiazetai na grapsw th selida sth mnhmh
		int * prohgoumenesKatastaseis; // pinakas apo 0 h' 1 kai deixnei ean mia selida einai sto working set
		int prohgoumenesKatastaseisMege8os; // mege8os tou pinaka twn prohgoumenwn katastasewn
};

int pageFaults; // metrhths twn page faults
int grapsimataStoDisko; // metrhths twn grapsimatwn pou eginan sto disko otan mia selida einai "lerwmenh" kai feugei apo th mnhmh
int metrhthsPara8yrou; // metraei poses dia8ynseis exw diavasei prokeimenou na kserw an prepei na ananewsw to working set

typedef struct periexomenoPageTable periexomenoPageTable;

int katastrofhPageTable(periexomenoPageTable * pt, int mege8osPinaka);
int arxikopoihshPageTable(periexomenoPageTable * pt, int mege8osPinaka, int plh8osKatastasewn);
void vresThSelida(char * ari8mosSelidas,char * die8ynsh);
int pros8eseSelidaStoPageTable(periexomenoPageTable * pt,int mege8osPinaka, char * ari8mosSelidas,char leitourgia,char * me8odosAntikatastashs,int para8yro);
void ektypwseToPageTable(periexomenoPageTable * pt, int mege8osPinaka);
int LRUAntikatastash(periexomenoPageTable * pt,char leitourgia,char *ari8mosSelidas);
int WSAntikatastash(periexomenoPageTable * pt,int mege8osPinaka,char leitourgia,char * ari8mosSelidas);
int ananewseToWs(periexomenoPageTable *pt ,int mege8osPinaka);
void printKatastash(periexomenoPageTable * pt,int mege8osPinaka);


#endif /* TYPOSSTOIXEIOUPAGETABLE_H_ */
