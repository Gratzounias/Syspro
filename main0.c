#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char * argv[])
{

	if( argc < 5) //plithos orismatwn
	{
		printf("La8os kata thn eisagwgh stoixeiwn. Termatismos...\n");
		exit(1);
	}
	FILE *fp1, *fp2;
	char * methodos = malloc(4*sizeof(char));
	int orisma0,orisma1,orisma2;

	fp1 = fopen("text1","r");
	//fp2 = fopen("text2","r");
	
	if (fp1 == NULL) 	
	{
        	printf("Error: file pointer is null.");
        	exit(2);
	}	

	strcpy(methodos,argv[1]);//allazoume to plithos
	orisma0 = atoi(argv[2]); 
	orisma1 = atoi(argv[3]);
	orisma2 = atoi(argv[4]);

	

	printf("Dwsate ta ekseis orimsata\n"); //elegxos
	printf("Me8odos : %s\n",methodos);
	printf("orisma0 : %d\n",orisma0);
	printf("orisma1 : %d\n",orisma1);
	printf("orisma2 : %d\n",orisma2);
	
	int id;
	int metrhths=0;
	
	while( metrhths < 15 ) //eof
		{
			
			fscanf(fp1,"%d",&id); // diavase id
			fgetc(fp1); // diavazei to keno
			//fscanf(fp1,"%c",&leksi); 
			printf("Success: file id.:%d\n", id);
			
			if(metrhths!=id)
			{
				printf("Error: file id error.");
        			exit(3);
			}
			metrhths++; 
	//https://stackoverflow.com/questions/3501338/c-read-file-line-by-line
		}




	fclose(fp1);
	//fclose(fp2);

	return 0;
}

