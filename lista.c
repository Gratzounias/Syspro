#include "lista.h"

/*
 * Topo8etai sth koryfh ths listas, pou xrhsimpoieitai gia th me8odo antikatastashs WS ,
 * to stoixeio theshPageTable
 */
int topo8ethseSthKoryfhWS(int theshPageTable)
{

	//ean h lista einai null
	if( arxhListasWS == NULL )
	{
		// desmeuse mnhmh gia neo komvo
		komvos * temp = malloc(sizeof(komvos));

		// o neos komvos pernei th timh theshPageTable
		temp->theshPageTable = theshPageTable;

		// afou exw mono ena stoixeio sth lista o deikths ston epomeno komvo ginetai null
		temp->next = NULL;

		// kai h arxh ths listas deixnei se auto to neo komvo
		arxhListasWS = temp;

	}
	// diaforetika exw toulaxiston ena komvo sth lista
	else
	{
		// desmeuse mnhmh gia neo komvo
		komvos * temp = malloc(sizeof(komvos));

		// o neos komvos pernei th timh theshPageTable
		temp->theshPageTable = theshPageTable;

		/* o neos komvos pou ftiaxthke 8a mpei sth koryfh ths listas opote h prohgoumenh koryfh
		 * ths listas 8a ginei twra o 2os komvos sth lista
		 */
		temp->next = arxhListasWS;

		// kai o deikths pou deixnei thn arxh ths listas 8a deixnei sto neo komvo o opoios einai o 1os sth lista
		arxhListasWS = temp;
	}

	return 0;
}

/*
 * Pros8etei th metavlhth theshPageTable sth arxh ths listas pou xrhsimopoieitai gia th me8odo LRU.
 * Ean auth h timh tou plaisiou yparxei hdh sth lista. Afaireitai o komvos apo to shmeio sto opoio vriksetai
 * sth lista kai prostei8etai sth koryfh diathrwntas th swsth seira stous ypoloipous komvous
 */
int topo8ethseSthKoryfh(int theshPageTable)
{
	if( arxhListas == NULL )
	{
		komvos * temp = malloc(sizeof(komvos));
		temp->theshPageTable = theshPageTable;
		temp->next = NULL;
		arxhListas = temp;

	}
	else
	{
		//allies 8elw na apofygw tis diplotypes times
		int yparxei = elegkseAnYparxeiSthLista(theshPageTable);

		// an den yparxei sth lista pros8ese neo komvo sth lista
		if( yparxei == -1 )
		{
			komvos * temp = malloc(sizeof(komvos));
			temp->theshPageTable = theshPageTable;
			temp->next = arxhListas;
			arxhListas = temp;
		}
	}

	return 0;
}

/*
 * Elegxei ean yparxei h timh theshPageTable sth lista LRU
 */
int elegkseAnYparxeiSthLista(int theshPageTable)
{
	/*
	 * xreiazomai ena deikth pou diatrexei th lista kai ena pou deixnei sto prohgoumeno komvo tou diatrexonta
	 */
	komvos * temp = arxhListas, *prohgoumenos = NULL;

	/*
	 * metrhths pou vlepei se poio komvo vrisketai o diatrexontas.
	 * Yparxei h periptwsh h timh theshPageTable na vriksetai sth koryfh ths listas. H koryfh den exei prohgoumeno
	 * Ean omws den einai sth koryfh xreiazomai ena tropo na to katalavw gia na ksekinhsw pisw apo to diatrexonta
	 * deikth (temp) , na akolou8ei o deikths pou deixnei sto prohgoumeno tou temp (prohgoumenos).
	 */
	int theshSthLista = 0;

	// oso den exw ftasei sto telos ths listas
	while (temp != NULL)
	{
		/*
		 * to temp den vrhke th timh theshPageTable sth koryfh ths listas arxikopoiw to deikth prohgoumenos
		 * na deixnei enan akrivos komvo prin to temp, opou autos einai o deikths pou deixnei h arxh ths listas
		 */
		if( theshSthLista == 1 )
			prohgoumenos = arxhListas;

		if( temp->theshPageTable == theshPageTable)
		{
			/*
			 * an isxyei auth h syn8hkh h pio prosfata xrhsimopoihmenh selida einai sth koryfh opote
			 * den xreiazetai na alaksw kati kai epistrew th timh mhden pou shmainei oti vrhka th timh
			 * theshPageTable sth lista
			 */
			if( theshSthLista == 0 )
				return 0 ;

			/* an exw th 8esh tou pageTable sth teleutaia 8esh ths listas */
			if( temp->next == NULL )
			{
				// to proteleutaio stoixeio ths listas ginetai teleutaio
				prohgoumenos->next = NULL;
				// o teleutaios paei sthn arxh
				temp->next = arxhListas;
				// kai h arxh ths lists deixnei sth nea kefalh
				arxhListas = temp;

				return 0;
			}

			/*
			 * ean exw ftasei se auto to shmeio tou kwdika shmainei oti an exw th 8esh tou
			 * page table tote auth vrisketai kapou endiamesa sth lista. Opote:
			 */

			// vazw ton prohgoumeno na deixnei meta ton torino
			prohgoumenos->next = temp->next;

			// o torinos ginetai prwtos
			temp->next = arxhListas;

			// h arxh ths listas deixnei to prwto
			arxhListas = temp;

			return 0;
		}

		temp = temp->next;

		if(prohgoumenos != NULL)
			prohgoumenos = prohgoumenos->next;

		theshSthLista++;
	}
	return -1; // den vrhka th timh theshPageTable sth lista
}

/*
 * Vriskei to teleutaio komvo sth lista, epistrefh th timh tou komvou sto pedio theshPageTable
 * kai apodesmeuei th mnhmh gia auto to komvo
 */
int vresTeleutaio()
{
	komvos * temp = arxhListas, *prohgoumenos = NULL;

	// phgaine sto telos ths listas
	while (temp->next != NULL)
	{
		prohgoumenos = temp;
		temp = temp->next;
	}

	// o proteuleutaios ginetai teleutaios
	prohgoumenos->next = NULL;

	//krata thn epistrefomenh timh
	int epistrefomenhTimh = temp->theshPageTable;

	// apodesmeuse th mnhmh gia auto to komvo
	free(temp);

	return epistrefomenhTimh;
}

void printLista(komvos * kefalh)
{
	komvos * temp = kefalh;
	while (temp != NULL)
	{
		printf("%d ",temp->theshPageTable);
		temp = temp->next;
	}
}

/*
 * apeleu8erwnei th mnhmh pou desmeuei h opoiadhopote lista
 */
void katastrofhListas()
{
	komvos * temp = arxhListas;
	while (temp != NULL)
	{
		komvos * temp2 = temp;
		temp = temp->next;
		free(temp2);
	}

	temp = arxhListasWS;
	while (temp != NULL)
	{
		komvos * temp2 = temp;
		temp = temp->next;
		free(temp2);
	}
	arxhListasWS = NULL;
}

void arxikopoihseLista()
{
	arxhListas = NULL;
	arxhListasWS = NULL;
}
