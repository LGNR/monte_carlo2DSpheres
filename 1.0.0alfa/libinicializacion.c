/* libinicializacion.c - Inizialization library. */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <cpgplot.h>
#include "main.h"
#include "libinicializacion.h"
#include "buffer.h"

extern float part_pos[NM_PART_][2]; 
int proc_buffer(char* nombre);

float declaracion_de_arrays(int NM_PART)
{
	float part_pos[NM_PART][2];
}

int NM_PART;
int leer;
float tc;
float seed=455;

float posicion_aleatoria(int part_i, float pared_DE, float pared_IZ, float pared_AR, float pared_AB)
{

	part_pos[part_i][0]=2*(pared_DE)*(rand()/((double)RAND_MAX+1))-pared_IZ;       //La posición inicial es aleatoria, definida dentro de [-pared_IZ,pared_DE]
	part_pos[part_i][1]=2*(pared_AR)*(rand()/((double)RAND_MAX+1))-pared_AB;
}

int leer_datos(float sigma)
{
	//Se leen los datos

	proc_buffer("configuracion.txt");

	imprimir_conf(NM_PART);
	int p,i;
	for(p=0; p<NM_PART; p++)
	{
		cpgsci(3);
		cpgcirc(part_pos[p][0],part_pos[p][1], sigma/2);
	}
	for(i=0; i < NM_PART; i++)
		printf("%d,%f,%f\n",  i,   part_pos[0][i],part_pos[1][i]); 
	//getchar();
	return 0;
}

float inicializacion(int part_j, int NM_PART, float pared_DE, float pared_IZ, float pared_AR, float pared_AB, float sigma) 
{
	srand(seed);
	int i=1;
	int j=0;
	//printf("Colocación aleatoria comenzada...\n");
	float L_boxx= pared_DE+pared_IZ;
	float L_boxy= pared_AR+pared_AB;
	posicion_aleatoria(part_j,pared_DE, pared_IZ, pared_AR, pared_AB);
	do 
	{
		posicion_aleatoria(i,pared_DE, pared_IZ, pared_AR, pared_AB);	
		float tras=0;
		for(j=0; j < i; j++ )
		{
			float dx = part_pos[j][0] - part_pos[i][0];
			float dy = part_pos[j][1] - part_pos[i][1];
			
			//condiciones periódicas en chequeo de traslape
			dx=dx-L_boxx*nearbyint(dx/L_boxx);
		    	dy=dy-L_boxy*nearbyint(dy/L_boxy);

			if (dx*dx + dy*dy < sigma*sigma)    
				tras=1;
		}
		if(tras == 0)
			i++;       
	}while(i<NM_PART);

	return 0;
}
