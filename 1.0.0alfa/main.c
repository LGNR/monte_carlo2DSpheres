/* MAIN 1.0.0alfa1 */
/* Simulación de Monte Carlo con visualización de PGPlot */
/* LGNR, AAHH 2009 */

/*Library headers*/
#include "libmontecarlo.h"
#include "libinicializacion.h"
#include "libsalida.h"
#include "main.h"

/*Global definitions and declarations*/

float part_pos[NM_PART_][2];  //NM_PART particulas

//float ang;
int dato;
int i;
int part_i;

int NM_PART;
int leer;
float tc;
//int sobrepuestas[NM_PART_][NM_PART_];

int main(int argc, char *argv[]) 
{
	if(argc < 9)
	{
		printf("No hay suficientes argumentos\n");
		printf("Uso:\n monte_carlo [particulas] [¿leer configuraciones?] [pared derecha] [pared  izquierda] [pared arriba] [pared abajo] [número de simulaciones] [¿Visualizacion?]\n");	
		exit(0);
	}
	/*if(argc < 5)
	{
		printf("No hay suficientes argumentos\n");
		printf("Sintaxis:\n monte_carlo [particulas] [leer configuraciones] [densidad] [número de simulaciones] [visualizar?]\n");	
                // Si se desea generalizar a rectangular agregue [pared derecha] [pared  iquierda] [pared arriba] [pared abajo]
		exit(0);
	}*/
    float sigma=1;
	if (cpgbeg(0, "/NULL", 1, 1) != 1) {
		exit(1);
	}
	cpgask(0);
    

    /*if(atoi(argv[8]) == 0)
	{
		if (cpgbeg(0, "/NULL", 1, 1) != 1) {
			exit(1);
				}	
		cpgask(0);
	}
	else
	{
        if (cpgbeg(0, "/XWINDOW", 1, 1) != 1) {
		exit(1);
        }
        cpgask(0);
	}*/
	
	int NM_PART = atoi(argv[1]);
	declaracion_de_arrays(NM_PART);
	int leer = atoi(argv[2]);
	float pared_DE = atoi(argv[3]);
	float pared_IZ = atoi(argv[4]);
	float pared_AR = atoi(argv[5]);
	float pared_AB = atoi(argv[6]);
    /*
    float densidad=atof(argv[3]);  
    pared_DE = NM_PART/(2*densidad);
    pared_IZ = -NM_PART/(2*densidad);
    pared_AR = NM_PART/(2*densidad);
    pared_AB = -NM_PART/(2*densidad);
    */

    //Ambiente de PGPlot
	cpgenv(-pared_IZ, pared_DE, -pared_AB, pared_AR, 1, 1);
	
	if (leer==0)
		//Inicialización con posiciones aleatorias	
		inicializacion(0, NM_PART, pared_DE,  pared_IZ,  pared_AR, pared_AB, sigma);  
	else
	{
		leer_datos(); // Leer datos de archivo de configuraciones.txt
		//imprimir_conf(NM_PART);
		//printf("Configuraciones leidas\n");
	}
	int SIM_TOT=atoi(argv[7]);
	
	/******* Ejecutar Monte Carlo *******/
		
    montecarlo(NM_PART,leer,pared_DE,pared_IZ,pared_AR,pared_AB,0.1,sigma,SIM_TOT);
    salida(NM_PART); //Salida que imprime a g_r.txt, configuracion.txt y genera visualizacion

	cpgend(); //Finaliza ambiente de PGPplot
	return 0;

}
