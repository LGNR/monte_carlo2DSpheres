/* fread example: read a complete file */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "buffer.h"
#include "main.h"

long lSize;
char * buffer;
int s,s2,k;

extern float part_pos[NM_PART_][2]; 

int proc_buffer(char* nombre) {
  FILE * pFile;
  
  pFile = fopen ( nombre , "rb" );
  if (pFile==NULL) exit (1);

  // obtain file size.
  fseek (pFile , 0 , SEEK_END);
  lSize = ftell (pFile);
  rewind (pFile);

  // allocate memory to contain the whole file.
  buffer = (char*) malloc (lSize);
  if (buffer == NULL) exit (2);

  // copy the file into the buffer.
  fread (buffer,1,lSize,pFile);

  /*** the whole file is loaded in the buffer. ***/

  //getchar();
   
  char num[5];
  char pos_x[20];
  char pos_y[20];
	
  int s1=0;
  int s2,s3;

  for(s=0; s < strlen(buffer); s++)
  {
	if (buffer[s] == 10)
	{
	//Extrae el número indice
	for (k=s1 ; k < prox_comma(s1,s) ; k++)
	num[k-s1]=buffer[k]; 
	
	s2=prox_comma(s1,s)+1;	

	//Extrae la coordenada en x
	for (k=s2 ; k < prox_comma(s2,s) ; k++)
	pos_x[k-s2]=buffer[k];

	s3=prox_comma(s2,s)+1;	

	//Extrae la coordenada en y
	for (k=s3 ; k < s ; k++)
	pos_y[k-s3]=buffer[k];
	
	part_pos[atoi(num)][0] = atof(pos_x);
	part_pos[atoi(num)][1] = atof(pos_y);

	s1=s+1;
	
	}
  
  }	
  
  // terminate
  fclose (pFile);
  free (buffer);
  return 0;
}

int prox_comma(int inicial, int final)
{

int l,g;
for(l = inicial ; l < final; l++)
	if (buffer[l] == 44)
		{		
		g = l;
		l = final;
		}
return g;
}

