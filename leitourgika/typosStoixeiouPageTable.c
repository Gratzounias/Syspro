#include "typosStoixeiouPageTable.h"

/*
 * Synarthsh h opoia ektypwnei tis selides poy vriskontai sto page table.
 *
 * pt : deikths sto page table
 * mege8osPinaka : to mege8os tou page table
 */
void ektypwseToPageTable(periexomenoPageTable * pt, int mege8osPinaka)
{
	int i = 0;
	printf("ektypwsh page table\n");
	for (i = 0; i < mege8osPinaka; ++i)
	{
		printf("%s\n ",pt[i].ari8mosSelidas);
	}
}

/*
 * Synarthsh pou analamvanei thn anazhthsh kai ean xreiastei th pros8hkh selidas sto page table. Frontizei
 * gia th swsth leitourgia twn me8odwn antikatastashs kai kalei tis katallhles synarthseis se periptwsh
 * pou xreiastei na antikatastas8ei selida sto page table.
 *
 * pt : deikths sto pinaka page table
 * mege8osPinaka : to mege8os tou page table. Pou einai kai to plh8os twn selidwn ths fysikhs mnhmhs
 * ari8mosSelidas : symboloseira me ta 20 bit toy ari8mou ths selidas sto 2adiko apo th die8ynsh pou diavasa.
 * leitourgia : metavlhth pou deixnei an 8elw na grapsw h' na diavasw apo th selida
 * me8odosAntikatastashs : LRU h' WS
 * para8yro : to mege8os tou para8yrou ean h me8odos antikatastash einai WS alliws auth h metavlhth exei th timh -1
 */
int pros8eseSelidaStoPageTable(periexomenoPageTable * pt,int mege8osPinaka, char * ari8mosSelidas,char leitourgia,char * me8odosAntikatastashs,int para8yro)
{

	int i = 0;

	/* elegkse tis selides tou page table gia na dw ean h selida einai hdh fortwmenh sth mnhmh. H'
	 * ean exw kenh 8esh sto page table se periptwsh pou eimai sth arxh tou programmatos
	 */
	for (i = 0; i < mege8osPinaka; ++i)
	{

		/* elegxw ean exw th selida sth mnhmh sygrinontas thn symboloseira pou exw sto page table
		 * sth 8esh i (antistoixa kai sth mnhmh sto plaisio i ) me ayth pou mou zhth8hke apo th main
		 * */
		if(strcmp(pt[i].ari8mosSelidas,ari8mosSelidas) == 0)
		{
			/*
			 * gia na eimai se auto to shmeio tou kwdika shmainei oti h selida einai sto page
			 * table ara antistoixa kai sth mnhmh opote an h me8odos antikatastashs einai h LRU
			 * vazw ton ari8mo tou plaisiou (i) sth koryfh ths listasLRU afou h selida molis xrhsimopoih8hke.
			 * An h me8odos antikatastashs einai h WS pros8etw sth listaWS, pou fylaei poies selides
			 * xrhsimopoih8hkan se auto to para8yro tou xronou, ton ari8mo tou plaisiou (i) kai elegxw ean einai
			 * wra na ananaiwsw to working set pou symvainei otan diavasa die8ynseis ises se plh8os
			 *  me to mege8os tou para8yrou.
			 */

			if(strcmp(me8odosAntikatastashs,"LRU") == 0)
				topo8ethseSthKoryfh(i); // xrhsh listas gia LRU
			// alliws xrhsimopoiw mia lista gia to WS
			else
			{
				topo8ethseSthKoryfhWS(i);
				metrhthsPara8yrou++;

				if( metrhthsPara8yrou == para8yro )
				{
					ananewseToWs(pt,mege8osPinaka);
					metrhthsPara8yrou = 0;
				}
			}

			/* elegxw ean prokeitai na diavasw h' na grapsw sth selida prokeimenou na ananewsw kai to
			 * dirty bit antistoixa
			 */
			if(leitourgia == 'W')
				pt[i].dirtyBit = 1;
			else
				pt[i].dirtyBit = 0;

			return 0; // teleiwsa me auth th dia8ynsh phgaine sth main kai fere mou epomenh
		}

		/* Se auto to shmeio tou kwdika 8a vre8w an o ari8mos selidas
		 * den einai idios me to ari8mo selidas pou exei apo8hkeumeno to page table
		 * sth 8esh i. Opote elegxw an h 8esh tou page table einai kenh. To page table
		 * arxikopoieitai sth synarthsh arxikopoihshPageTable opou oi symboloseires tou ginontai -1,
		 * ara elegxontas an o ari8mos selidas sth 8esh i tou page table einai -1 mporw na katalavw an
		 * yparxei selida se auth th 8esh h oxi.
		 * */
		if(strcmp(pt[i].ari8mosSelidas,"-1") == 0 )
		{
			// auksanw ton ari8mo twn page faults giati h selida den einai sth mnhmh
			pageFaults++;

			/* 
			 * efoson vrhka kenh 8esh fortwnw th selida apo th mnhmh kai thn apo8hkeuw sth 8esh i tou page
			 * table.
			 */
			strcpy(pt[i].ari8mosSelidas,ari8mosSelidas);

			/* kai kanw tis aparaithtes enhmerwseis stis antistoixes listes gia th swsth leitourgia
			 * twn me8odwn antikatastashs
			 */
			if(strcmp(me8odosAntikatastashs,"LRU") == 0)
				topo8ethseSthKoryfh(i);
			else
			{
				topo8ethseSthKoryfhWS(i);
				metrhthsPara8yrou++;

				if( metrhthsPara8yrou == para8yro )
				{
					ananewseToWs(pt,mege8osPinaka);
					metrhthsPara8yrou = 0;
				}

			}

			// analoga me th leitourgia ths die8ynshs enhmerwnetai antistoixa to dirty bit ths selidas
			if(leitourgia == 'W')
				pt[i].dirtyBit = 1;
			else
				pt[i].dirtyBit = 0;

			return 0; // epistrofh sth main gia nea die8ynsh mnhmhs
		}

	}

	/* efoson eimai eksw apo th parapanw for shmainei oti den exw kenh 8esh sto page table kai
	 * h selida pou zhtaw den vrisketai sto page table opote xreiazetai na dialeksw selida gia
	 * antikatastash. Ara to plh8os twn pageFaults prepei na auksh8ei
	 */

	pageFaults++;

	// analwga me th me8odo antikatastashs epilegw kalw kai thn antistoixh synarthsh
	if( strcmp(me8odosAntikatastashs,"LRU") == 0 )
		LRUAntikatastash(pt,leitourgia,ari8mosSelidas);
	else
	{
		WSAntikatastash(pt,mege8osPinaka,leitourgia,ari8mosSelidas);

		/*
		 * H selida antikatasta8hke alla emeis den gnwrizoume se poia xronikh stigmh auto htan aparaithto.
		 * Afou diavasame nea di8ynsh perase mia "xronikh monada" kai o metrhths para8yrou prepei na auksh8ei
		 * Ystera prepei na elegksoume ean hr8e h "wra" na ananewsoume th katastash twn selidwn sto page table
		 */
		metrhthsPara8yrou++;

		if( metrhthsPara8yrou == para8yro )
		{
			ananewseToWs(pt,mege8osPinaka);
			metrhthsPara8yrou = 0; // shmatodotei oti arxizei neo para8yro
		}
	}

	return 0; // epistrofh sth main gia nea die8ynsh selidas
}

/*
 * Ananewnei tis eggrafes tou page table etsi wste ean xrhsimopoih8hkan na mpoun sto working set
 * Efoson ena para8yro tou xronou perase oi times twn prohgoumenwn para8yrwn ginontai shift pros ta deksia.
 */
int ananewseToWs(periexomenoPageTable *pt ,int mege8osPinaka)
{
	int i;
	/* kane ena shift prs ta deksia tis prwhgoumenes katastaseis
	 * kai arxikopoihse th twrinh katastash se 0
	 */
	for (i = 0; i < mege8osPinaka; ++i)
	{
		int j;
		for (j = pt[i].prohgoumenesKatastaseisMege8os; j > 0; --j) {
			pt[i].prohgoumenesKatastaseis[j] = pt[i].prohgoumenesKatastaseis[j-1];
		}
		pt[i].prohgoumenesKatastaseis[0] = 0;
	}

	komvos * temp = arxhListasWS;

	/*
	 * kane 1 thn twrinh katastash stis selides pou xrhsimopoih8hkan se auto to para8yro.
	 * Opote oi selides pou den xrhsimopoih8hkan exoun 0 se auto to para8yro tou xronou. Enw oi
	 * selides pou xrhsimopoih8hkan 8a apokthsoun timh 1 pou ypodhlwnei oti xrhsimopoih8hkan
	 */
	while( temp != NULL )
	{
		/*
		 * h twrinh katastash antiproswpeuetai apo th prwth 8esh tou pinaka prohgoumenesKatastaseis
		 * twn eggrafwn tou page table
		 */
		pt[temp->theshPageTable].prohgoumenesKatastaseis[0] = 1;
		temp = temp->next;
	}

	/*
	 * apodesmeuw th mnhmh gia th lista kai na mhn auksanei synaixeia se mege8os. Kanontas to auto
	 * h lista mou 8a ftanei panta max mege8os oso einai to mege8os tou para8yrou.
	 */
	katastrofhListas();

	return 0;
}

/*
 * synarthsh pou xrhsimpoieitai gia na doume to pinaka prohgoumenesKatastaseis ka8e eggrafhs tou page table
 * Xrhsimopoih8hke kyriws gia ton elegxo ths swsths leitourgias autou tou pinaka
 */
void printKatastash(periexomenoPageTable * pt,int mege8osPinaka)
{
	int i;
	for (i = 0; i < mege8osPinaka; ++i)
	{
		int j;
		for (j = 0; j < 3; ++j) {
			printf("%d ",pt[i].prohgoumenesKatastaseis[j]);
		}
		putchar('\n');
	}
}

/*
 * Synarthsh h opoia analamvanei thn antikatastash ths selidas me th me8odo WS. Dhladh 8a afairesei apo to
 * page table th selida h opoia den exei xrhsimopoih8ei sta prohgoumena para8yra ara den anhkei sto working set.
 *
 * pt : deikths sto page table
 * mege8osPageTable : to plh8os twn 8esewn tou page table.
 * leitourgia : W h' S gia th leitourgia pou 8elei ginetai se auth th selida
 * ari8mosSelidas : symboloseira me ton dyadiko ari8mo ths selidas poy 8eloume na apo8hkeusoume sto page table
 */
int WSAntikatastash(periexomenoPageTable * pt,int mege8osPageTable,char leitourgia,char * ari8mosSelidas)
{
	int i;

	// ksekina thn anazhthsh stis eggrafes tou page table
	for (i = 0; i < mege8osPageTable; ++i)
	{
		int j;
		int allZeros = 1; // flag pou mou leei an mia selida tou page table anhkei sto working set

		// elegkse ean sta prohgoumena para8yra xrhsimopoih8hke h selida.
		for (j = 0; j < pt[i].prohgoumenesKatastaseisMege8os; ++j)
		{
			/* ena xrhsimopoih8hke h selida estw kai mia fora anhkei sto working set kai to flag mhdenizete
			 * deixnontas oti h selida anhkei sto working set
			 */
			if(pt[i].prohgoumenesKatastaseis[j] == 1)
				allZeros = 0;
		}

		/* an vrhka mia selida sto page table pou den anhkei sto working set afou to allZeros einai 1.
		 * tote auth th selida 8a paw na antikatasthsw me th nea.
		 */
		if( allZeros == 1 )
		{

			/* afou apomakrynetai h selida prepei na elegxei ean eina lerwmenh.
			 * Efoson einai prepei na graftei sto disko kai na auksh8ei o metrhths twn grapsimatwn.
			 */
			if(pt[i].dirtyBit == 1)
				grapsimataStoDisko++;

			// apo8hkeuw th nea selida sth 'mnhmh'
			strcpy(pt[i].ari8mosSelidas,ari8mosSelidas);

			// apeleu8erwnw to deikth gia na mhn desmeuw mnhmh askopa

			if(leitourgia == 'W')
				pt[i].dirtyBit = 1;
			else
				pt[i].dirtyBit = 0;

			int j;
			for (j = 0; j < pt[i].prohgoumenesKatastaseisMege8os; ++j) {
				pt[i].prohgoumenesKatastaseis[j] = 0;
			}

			// enhmerwnw th lista tou WS.
			topo8ethseSthKoryfhWS(i);

			return 0;
		}
	}

	time_t t;

	srand((unsigned) time(&t));

	i = rand() % pt[0].prohgoumenesKatastaseisMege8os - 1;

	if(pt[i].dirtyBit == 1)
		grapsimataStoDisko++;

	// apo8hkeuw th nea selida sth 'mnhmh'
	strcpy(pt[i].ari8mosSelidas,ari8mosSelidas);

	// apeleu8erwnw to deikth gia na mhn desmeuw mnhmh askopa

	if(leitourgia == 'W')
		pt[i].dirtyBit = 1;
	else
		pt[i].dirtyBit = 0;

	int j;
	for (j = 0; j < pt[i].prohgoumenesKatastaseisMege8os; ++j) {
		pt[i].prohgoumenesKatastaseis[j] = 0;
	}

	// enhmerwnw th lista tou WS.
	topo8ethseSthKoryfhWS(i);

	return 0;
}

/*
 * Synarthsh h opoia analamvanei thn antikatastash selidas sto page table gia th me8odo antikatastash LRU
 *
 * pt : deikths sto page table
 * leitourgia : W h' S gia th leitourgia pou 8elei ginetai se auth th selida
 * ari8mosSelidas : symboloseira me ton dyadiko ari8mo ths selidas poy 8eloume na apo8hkeusoume sto page table
 */
int LRUAntikatastash(periexomenoPageTable * pt,char leitourgia,char *ari8mosSelidas)
{
	// metavlhth sth opoia fylasetai h 8esh tou page table sthn opoia 8a ginei h antikatastash
	int theshStoPageTableTouTeleutaiouSthLista;


	theshStoPageTableTouTeleutaiouSthLista = vresTeleutaio();

	/* ean h selida eiani lerwmenh tote prepei na ginei eggrafh ths sth mnhmh kai auksanetai o
	 * antistoixos metrhths
	 */
	if(pt[theshStoPageTableTouTeleutaiouSthLista].dirtyBit == 1)
		grapsimataStoDisko++;

	/* edw "fortw8hke" h selida sth mnhmh. 8ymh8eitai oti to page fault to exoume aukshsei prin mpoume
	 * se auth th synarthsh
	 */
	strcpy(pt[theshStoPageTableTouTeleutaiouSthLista].ari8mosSelidas,ari8mosSelidas);

	// enhmerwsh tou dirty bit ths selidas
	if( leitourgia == 'W' )
		pt[theshStoPageTableTouTeleutaiouSthLista].dirtyBit = 1;
	else
		pt[theshStoPageTableTouTeleutaiouSthLista].dirtyBit = 0;

	/* parathrhste oti gia na vriskomaste se auth th synarthsh exoume hdh elegksei gia th me8odo antikatastashs
	 * kai auth einai h LRU opote gnwrizw oti 8a ananewsw th lista LRU
	 */
	topo8ethseSthKoryfh(theshStoPageTableTouTeleutaiouSthLista);

	return 0;
}

/*
 * pernei mia die8ynsh sto 16adiko kai epistrefei ta 20 shmantikotera bit
 * sto dyadiko pou antiproswpeuoun ton ari8mo ths selidas
 */
void vresThSelida(char * ari8mosSelidas, char * die8ynsh)
{
	char diadikhDie8ynsh[32];

	int i;
	char dyadikhAnaparastash[4];
	for (i = 0; i < 8; ++i) {

		switch(die8ynsh[i])
		{
		case '0': strcpy(dyadikhAnaparastash,"0000"); break;
		case '1': strcpy(dyadikhAnaparastash,"0001"); break;
		case '2': strcpy(dyadikhAnaparastash,"0010"); break;
		case '3': strcpy(dyadikhAnaparastash,"0011"); break;
		case '4': strcpy(dyadikhAnaparastash,"0100"); break;
		case '5': strcpy(dyadikhAnaparastash,"0101"); break;
		case '6': strcpy(dyadikhAnaparastash,"0110"); break;
		case '7': strcpy(dyadikhAnaparastash,"0111"); break;
		case '8': strcpy(dyadikhAnaparastash,"1000"); break;
		case '9': strcpy(dyadikhAnaparastash,"1001"); break;
		case 'a': strcpy(dyadikhAnaparastash,"1010"); break;
		case 'b': strcpy(dyadikhAnaparastash,"1011"); break;
		case 'c': strcpy(dyadikhAnaparastash,"1100"); break;
		case 'd': strcpy(dyadikhAnaparastash,"1101"); break;
		case 'e': strcpy(dyadikhAnaparastash,"1110"); break;
		case 'f': strcpy(dyadikhAnaparastash,"1111"); break;
		default: printf("la8os sth die8ynsh\n"); exit(2);
		}

		diadikhDie8ynsh[4*i] = dyadikhAnaparastash[0];
		diadikhDie8ynsh[4*i+1] = dyadikhAnaparastash[1];
		diadikhDie8ynsh[4*i+2] = dyadikhAnaparastash[2];
		diadikhDie8ynsh[4*i+3] = dyadikhAnaparastash[3];
	}

	strncpy(ari8mosSelidas,diadikhDie8ynsh,20);
	ari8mosSelidas[20] ='\0';

}

/*
 * Arxikopoiei to page table kai tis aparaiththes times tou progrmammatos .
 * Kanei tis aparethtes dynamikes desmeuseis pou xreiazetai to page table.
 */
int arxikopoihshPageTable(periexomenoPageTable * pt, int mege8osPinaka, int plh8osKatastasewn)
{
	grapsimataStoDisko = 0;
	pageFaults = 0;
	metrhthsPara8yrou = 0;

	arxikopoihseLista();

	int i;
	for (i = 0; i < mege8osPinaka; ++i) {

		strcpy(pt[i].ari8mosSelidas,"-1");

		pt[i].dirtyBit = 0;

		pt[i].prohgoumenesKatastaseisMege8os = plh8osKatastasewn;

		pt[i].prohgoumenesKatastaseis = (int*) malloc(plh8osKatastasewn*sizeof(int));

		if(pt[i].prohgoumenesKatastaseis == NULL)
		{
			printf("Den katafera na desmeusw mnhmh gia ton pinaka twn prohgoumenwn katastasewn. Bye...\n");
			exit(1);
		}

		int j;
		for (j = 0; j < plh8osKatastasewn; ++j) {
			/* arxikopoiw se mhden tis prohgoumenes katastaseis tou working set */
			pt[i].prohgoumenesKatastaseis[j] = 0;
		}
	}
	return 0;
}

/*
 * Xrhsimopoieitai gia thn apodesmeush ths mnhmhs pou katanalwnei to programma
 */
int katastrofhPageTable(periexomenoPageTable * pt, int mege8osPinaka)
{

	katastrofhListas();

	return 0;
}
