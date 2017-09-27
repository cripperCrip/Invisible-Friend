#include <stdlib.h>
#include <stdio.h>
#include <string.h>


//The aim of this program, is to calculate,
// in a random way, between all the participants, who has to give a present
// to who the Magic Kings Day. 

#define INITIALMENU 1
#define OPTIONSMENU 2
#define DEFINE_PARTICIPANTS 1
#define SELECT_CONDITIONS 2
#define MAKE_A_DRAW 3
#define EXIT 4

#define ADD_PARTICIPANT 1
#define SHOW_PARTICIPANTS 2
#define EXIT_ADDING 3

#define NUM_PARTICIPANTS 50
#define NAME_LENGTH 50

char participants[NAME_LENGTH][NUM_PARTICIPANTS];
char restrictions[NUM_PARTICIPANTS][NUM_PARTICIPANTS];
char EMPTY[]=" ";
int numParticipants;
char selectionDraw[NUM_PARTICIPANTS];

void menuDefinition (int option){


   	switch (option)
	{
	
		case INITIALMENU:{
		
			printf("\n CALCULO DEL AMIGO INVISIBLE \n");
			printf("=========================== \n");

		};

		case OPTIONSMENU:{
			
			printf("1-INTRODUCIR PARTICIPANTES\n");
			printf("2-SELECCIONAR CONDICIONES ENTRE PARTICIPANTES\n");
			printf("3-REALIZAR SORTEO\n");
			printf("4-SALIR\n");
			printf("\nSELECCIONE UNA OPCIÓN: ");

		}break;

		default:{
		

		}break;
	}

}

int defineParticipants (void){

	int flag=0, option=0;
	int counter=0;

	printf("\nMENU PARTICIPANTES\n");
        printf("==================\n");

	do{

		printf("¿QUÉ DESEA HACER?\n");
		printf("1-AÑADIR NUEVO PARTICIPANTE\n");
		printf("2-VER LISTADO DE PARTICIPANTES\n");
		printf("3-CONTINUAR\n");
		printf("SELECCIONE UNA OPCIÓN: ");

		scanf("%d", &option);

		if (option == ADD_PARTICIPANT)
		{
			if (counter < NUM_PARTICIPANTS)
			{			
				printf("\nINTRODUZCA EL NOMBRE DEL PARTICIPANTE: ");
				scanf("%s", participants[counter]);
				printf("\n PARICIPANTE AÑADIDO: %s\n", participants[counter]);
				counter++;
			}
			else
			{
				printf("\n NO SE PUEDEN AÑADIR MÁS PARTICIPANTES. LÍMITE: %d\n", NUM_PARTICIPANTS);
			}
		}
		else if (option == SHOW_PARTICIPANTS)
		{
			printf("\nLISTADO DE PARTICIPANTES\n");
			printf("------------------------\n");

			int loop=0;

			while (loop<counter)
			{
			   printf("PARTICIPANTE %d: %s\n", loop+1, participants[loop]);
			   loop++;
			}
		}
		else{

		  flag=1;
		}

	   printf("\n");

	}while(flag==0);

	numParticipants=counter;

	return 0;
}

int defineConditions(void)
{
   int counter=0;
   int selection=0, selection2=0;
   int partNumber=0;
   char xSelection ='X';
   char option;

   printf("\nDEFINCIÓN DE CONDICIONES\n");
   printf("========================\n");

   do
   {
	   printf("\nESTOS SON LOS PARTICIPANTES\n");
	   while (counter < numParticipants)
	   {
	      printf("%d-%s\n", counter+1, participants[counter]);
	      counter++;
	   }

	   printf("¿A QUÉ PARTICIPANTE LE QUIERE ASIGNAR UNA RESTRICCIÓN?: ");
	   scanf("%d", &selection);

	  counter=0;

	  printf("\nSELECCIONE A QUIEN NO PUEDE REGALAR %s\n", participants[selection-1]);
	  while (counter < numParticipants)
	  {
	      if ((counter+1)!=selection)
	      {
	      	printf("%d-%s\n", partNumber+1, participants[counter]);
		partNumber++;
	      }
	
	      counter++;
	  }

	  printf("\nPARTICIPANTE: ");
	  scanf("%d", &selection2);

	  //printf("\nSELECTION: %d, SELECTION2: %d\n", selection, selection2);

	  if (selection <= selection2)
	  {
	    restrictions[selection-1][selection2] = xSelection;
	    restrictions[selection2][selection-1] = xSelection;  
	  }
	  else {
	    restrictions[selection-1][selection2-1] = xSelection;
	    restrictions[selection2-1][selection-1] = xSelection;  
	  }
	  
	  /*counter=0;
	  int counter2=0;
	  while (counter < numParticipants)
	  {
	      while (counter2 < numParticipants)
	      {
		 printf("RESTRICC: %c, COUNTER: %d, COUNTER2: %d\n",restrictions[counter][counter2], counter, counter2);
		counter2++;
	      }
	      counter2=0;
	      counter++;
	  }*/

	  printf("\n%s Y %s NO SE PUEDEN REGALAR ENTRE SI\n", participants[selection-1], participants[selection2]);

	  fflush(stdin);	
	  printf("¿QUIERE DEFINIR NUEVAS RESTRICCIONES? (S/N): ");
	  scanf("%s", &option);

	  counter=0;
          partNumber=0, selection=0, selection2=0;
          xSelection ='X';

  }while (option!='N');

  return 0;
  
}

int makeADraw(void)
{
   int random;
   int counter=0, counter2=0;
   char xSelection ='X';
   char option;

   printf("\nSORTEO\n");
   printf("=====\n");

   printf("RESUMEN DEL SORTEO\n");
   printf("------------------\n");
   printf("NUMERO DE PARTICIPANTES: %d\n", numParticipants);
   printf("PARTICIPANTES: \n");
   while (counter < numParticipants)
   {
      printf("%d-%s\n", counter+1, participants[counter]);
      counter++;
   }
   counter=0;
   printf("\nRESTRICCIONES: \n");
   while (counter < numParticipants)
   {
      while (counter2 < numParticipants)
      {
         //printf("RESTRICC: %c, COUNTER: %d, COUNTER2: %d\n",restrictions[counter][counter2], counter, counter2);
         if ((restrictions[counter][counter2] == xSelection) && (counter < counter2))
         {
              
		printf("%s y %s NO SE PUEDEN REGALAR ENTRE SI\n", participants[counter], participants[counter2]);
	 }
        
        counter2++;
      }
      counter2=0;
      counter++;
   }

   printf("¿ESTA SEGURO DE REALIZAR EL SORTEO? (S/N)?\n");
   scanf("%s", &option);

   counter=0;

   if (option == 'S')
   {
	printf("\nRESULTADO SORTEO\n");
        printf("----------------\n");
        while (counter < numParticipants)
	{
		do
		{
		    srand(time(NULL));
		    random=rand()%(numParticipants);
		    
		}while ((selectionDraw[random]=='X'));


		if ((random==counter) || (restrictions[counter][random]=='X'))
		{
		   printf("\nERROR - SE REPITE EL SORTEO\n");
		   
		   int counter2=0;

		   while (counter2 < numParticipants)
		   {
		     selectionDraw[counter2]='V';
		     counter=0;
		     counter2++;
                   }
		}
		else
		{
			printf("EL CANDIDATO DE %s ES: %s\n", participants[counter], participants[random]);
			selectionDraw[random]='X';
                        counter++;
		}

	}

   }
   
}

int main (int argc, char * argv[]){

  int option, counter=0;

  while (counter<NUM_PARTICIPANTS)
  { 
     strcpy(participants[counter], EMPTY);
     counter++;
  }

  do
  {

	 menuDefinition(1);
	 scanf("%d", &option);
	  

	  switch(option)
	  {

	     case DEFINE_PARTICIPANTS:{

		defineParticipants();

	     }break;

	     case SELECT_CONDITIONS:{

		if (strcmp(participants[0], EMPTY) == 0)
		{
		
			printf("\nINTRODUZCA PRIMERO LOS PARTICIPANTES\n");
		}
		else
		{
			defineConditions();
		}

	     }break;

	     case MAKE_A_DRAW:{

		if (strcmp(participants[0], EMPTY) == 0)
		{
		
			printf("\nINTRODUZCA PRIMERO LOS PARTICIPANTES\n");
		}
		else
		{
			makeADraw();
		}

	     }break;

	     case EXIT:{

		printf("\n C'EST FINI \n");

	     }break;


	 }

   }while(option!=EXIT);

}
