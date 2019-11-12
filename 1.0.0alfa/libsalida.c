/* libsalida.c - Output library. */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <cpgplot.h>
#include "main.h"
#include "libmontecarlo.h"
#include "libinicializacion.h"

extern float part_pos[NM_PART_][2];
//NM_PART particulas

//float ang;
int dato;
int i;
int part_i;

//Anotaciones:
/* 


NM_PART es argumento desde la terminal
En futuras aplicaciones será necesario poder meter desde la terminal PARED_IZ y PARED_DE

*/

int NM_PART;
int leer;
float tc;
//int sobrepuestas[NM_PART_][NM_PART_];


int imprimir_conf(int NM_PART);
int imprimir_coord(int part_i);
int imprimir_traslapes(int part_i, float L_boxx, float L_boxy, float sigma);
int dibujar(int NM_PART, float pared_IZ, float pared_DE, float pared_AB, float pared_AR, float sigma);

int salida(int NM_PART)
{
	
	//La función salida debe ser generalizada. En esta versión sólo la salida es a un archivo de configuraciones
	
	FILE * pFile;
	pFile = freopen ("configuracion.txt","w",stdout);
	
  	if (pFile!=NULL)
  	{
    	int i;
		imprimir_conf(NM_PART);
    		fclose (pFile);
  	}
		
	return 0;	
}



int imprimir_coord(int part_i)
{
	printf("%d: %f,%f \n", part_i, part_pos[part_i][0], part_pos[part_i][1]);
	return 0;
}


int imprimir_traslapes(int part_i, float L_boxx, float L_boxy, float sigma)
{
	printf("Traslapes de %d: ", part_i);
	int tras=traslape(part_i,1,L_boxx,L_boxy,sigma);
	printf("\n");
	return tras;
}


int imprimir_conf(int NM_PART)
{
	int l;
	for(l = 0; l < NM_PART; l++)
	printf("%d, %f, %f\n", l, part_pos[l][0], part_pos[l][1]);
	return 0;
}

int dibujar(int NM_PART, float pared_IZ, float pared_DE, float pared_AB, float pared_AR, float sigma)
{
	int p;
	cpgenv(-pared_IZ, pared_DE, -pared_AB, pared_AR, 1, 1);
	for(p=0; p<NM_PART; p++)
	{
		cpgsci(3);
		cpgcirc(part_pos[p][0],part_pos[p][1], sigma/2);
	}
	return 0;
}

