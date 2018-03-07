#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "typosStoixeiouPageTable.h"

int main(int argc, char * argv[])
{

	if( argc < 5)
	{
		printf("La8os kata thn eisagwgh stoixeiwn. Termatismos...\n");
		exit(3);
	}
	FILE *fp1, *fp2;
	char * methodosAntikatastashs = malloc(4*sizeof(char));
	int plh8osSelidwnMnhmhs,para8yro,q,megistoPlh8osDieu8ynsewn;

	fp1 = fopen("bzip.trace","r");
	fp2 = fopen("gcc.trace","r");

	strcpy(methodosAntikatastashs,argv[1]);
	plh8osSelidwnMnhmhs = atoi(argv[2]);
	q = atoi(argv[3]);
	megistoPlh8osDieu8ynsewn = atoi(argv[4]);

	if( strcmp(methodosAntikatastashs,"WS") == 0 )
	{
		if( argc == 6 )
			para8yro = atoi(argv[5]);
		else
			printf("Lathos kata thn eisodo parametrwn");
	}
	else
		para8yro = -1;

	printf("Dwsate ta ekseis orimsata\n");
	printf("Me8odos antikatastashs : %s\n",methodosAntikatastashs);
	printf("Plh8os selidwn sth mnhmh : %d\n",plh8osSelidwnMnhmhs);
	printf("q : %d\n",q);
	printf("Plh8os die8ynsewn pou diavazetai apo ka8e arxeio : %d\n",megistoPlh8osDieu8ynsewn);
	if(para8yro != -1)
		printf("Para8yro : %d\n", para8yro);

	periexomenoPageTable pageTable[plh8osSelidwnMnhmhs];

	arxikopoihshPageTable(pageTable,plh8osSelidwnMnhmhs,3);

	char dieu8ynsh[8];
	char leitourgia;

	int plh8osDieu8ynsewnPouExwDiavasei = 0;

	char * ari8mosSelidas = malloc(21*sizeof(char));

	do{

		int metrhthsGiaToQ = 0;

		while( metrhthsGiaToQ < q )
		{
			
			fscanf(fp1,"%s",dieu8ynsh); // diavase th die8ynsh
			fgetc(fp1); // diavazei to keno gia na mporesw meta na diavasw to R h' to W
			fscanf(fp1,"%c",&leitourgia); // diavase th leitourgia auths ths die8ynshs

			vresThSelida(ari8mosSelidas,dieu8ynsh); // vres ton ari8mo ths selidas
			pros8eseSelidaStoPageTable(pageTable,plh8osSelidwnMnhmhs,ari8mosSelidas,leitourgia,methodosAntikatastashs,para8yro); // pros8ese th selida sth mnhmh

			plh8osDieu8ynsewnPouExwDiavasei++;
			metrhthsGiaToQ++;
		}

		metrhthsGiaToQ = 0;

		while( metrhthsGiaToQ < q )
		{
			fscanf(fp2,"%s",dieu8ynsh); // diavase th die8ynsh
			fgetc(fp2); // diavazei to keno gia na mporesw meta na diavasw to R h' to W
			fscanf(fp2,"%c",&leitourgia); // diavase th leitourgia auths ths die8ynshs

			// char * ari8mosSelidas = vresThSelida(dieu8ynsh); // vres ton ari8mo ths selidas
			vresThSelida(ari8mosSelidas, dieu8ynsh); // vres ton ari8mo ths selidas
			pros8eseSelidaStoPageTable(pageTable,plh8osSelidwnMnhmhs,ari8mosSelidas,leitourgia,methodosAntikatastashs,para8yro); // pros8ese th selida sth mnhmh

			plh8osDieu8ynsewnPouExwDiavasei++;
			metrhthsGiaToQ++;
		}

		//to 2*megistoPlh8osDieu8ynsewn shmainei oti diavase megistoPlh8osDieu8ynsewn apo ka8e arxeio
	}while(plh8osDieu8ynsewnPouExwDiavasei < 2*megistoPlh8osDieu8ynsewn);

	printf(" Page faults : %d\n" , pageFaults);
	/*
	 * ta diavasmata pou ginane apo to disko einai oso sto plh8os twn page faults afou mono
	 * tote xreiazotan na paw kai na diavasw apo to disko
	 */
	printf("Diavasmata pou ginane apo to disko : %d\n",pageFaults);
	printf("Grapsimata pou ginane sto disko : %d\n", grapsimataStoDisko);
	printf("Diavasthkan synolika %d eggrafes\n",plh8osDieu8ynsewnPouExwDiavasei);
	/*
	 * apo ton orismo tou anastrofou pinaka oses 8eseis exei o anastrofos page table
	 * tosa plaisia exw sth mnhmh
	 */
	printf("Ari8mos plaisiwn mnhmhs : %d\n", plh8osSelidwnMnhmhs);

	katastrofhPageTable(pageTable,plh8osSelidwnMnhmhs);

	fclose(fp1);
	fclose(fp2);

	return 0;
}


