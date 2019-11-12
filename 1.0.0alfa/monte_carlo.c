/*
  monte_carlo-1.0.0alfa - Hard disk monte carlo simulation.

  Copyright (C) 2009 Luis G. Navarro <email: lgnr.archive@gmail.com>

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/


/* MAIN */


/*Include headers*/ 


#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <cpgplot.h>

/*Library headers*/

#include "libmontecarlo.h"
#include "libinicializacion.h"
#include "libsalida.h"
#include "main.h"


/*Global definitions and declarations*/

#define PI 3.14159265358979323846264338327
#define NM_PART_ 50000000
#define RADIO_PART 0.5
#define SEMILLA 500
#define SIM_TOT 500
#define KbT 1



float part_pos[NM_PART_][2];  //NM_PART particulas


int seed=SEMILLA;
//float ang;
int dato;
int i,traslape;
int part_i;
float sigma=2*RADIO_PART;

float L_box = PARED_IZ+PARED_DE;

//Anotaciones:
/* 


NM_PART es argumento desde la terminal
En futuras aplicaciones será necesario poder meter desde la terminal PARED_IZ y PARED_DE

*/

int NM_PART;
int leer;
float tc;
//int sobrepuestas[NM_PART_][NM_PART_];


float declaracion_de_arrays(int NM_PART)
{


float part_pos[NM_PART][2];
/*
float b[NM_PART][NM_PART];
float t[NM_PART][NM_PART];
float v[NM_PART][NM_PART];
float vx[NM_PART][NM_PART];
float vy[NM_PART][NM_PART];
float r[NM_PART][NM_PART];
float rx[NM_PART][NM_PART];
float ry[NM_PART][NM_PART];
*/

}


main(int argc, char *argv[]);
