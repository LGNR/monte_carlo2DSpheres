/* libmontecarlo.c - Monte Carlo step library. */

#include <stdio.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <cpgplot.h>

#define PI 3.14159265358979323846264338327
#define NM_PART_ 50000000
#define KbT 1

/* Static Libraries includes */

#include "libinicializacion.h"
#include "libsalida.h"
#include "main.h"
 
/*Variable declaration*/

extern float part_pos[NM_PART_][2];  //NM_PART_ as the Upper limit of particles in this version
int i,j,p,l,k,m,n,o,p,q,sim;			  //One counter declaration per source code
int rnd,tr;
int part_i;
int NM_PART;
int leer,impr;
float tc;
int traslape_;
float rn[30000];
float in[30000];
float s[30000];

float part_pos[NM_PART_][2];  //NM_PART particulas
//float ang;
int dato;
int i,tras;
int part_i;
float pared_IZ,pared_DE,pared_AB,pared_AR,D_MAX;
float part_pos[NM_PART_][2];
float mover_x(int part_i, float pared_IZ, float pared_DE, float D_MAX);
float mover_y(int part_i, float pared_AB, float pared_AR, float D_MAX);
int traslape(int part_i, int impr, float L_boxx, float L_boxy, float sigma);

float mover_x(int part_i, float pared_IZ, float pared_DE, float D_MAX)            //Move a random amount in terms of D_Max which should be adjustable. This is the x component
{
	float L_boxx = pared_IZ+pared_DE;
	float sav_x = part_pos[part_i][0]; //Save previous possition
	part_pos[part_i][0]=part_pos[part_i][0]+ 2*(D_MAX)*(rand()/((double)RAND_MAX+1))-D_MAX; //Define new position
	part_pos[part_i][0]=part_pos[part_i][0] - L_boxx*nearbyint(part_pos[part_i][0]/L_boxx);   //Periodical conditions considerations
	return sav_x;  //Give back the saved value
	
}


float mover_y(int part_i, float pared_AB, float pared_AR, float D_MAX)			//This is the y component and the second function related to the MC move
{
	float L_boxy = pared_AR + pared_AB;
	float sav_y = part_pos[part_i][1];
	part_pos[part_i][1]=part_pos[part_i][1]+ 2*(D_MAX)*(rand()/((double)RAND_MAX+1))-D_MAX;
	part_pos[part_i][1]=part_pos[part_i][1] - L_boxy*nearbyint(part_pos[part_i][1]/L_boxy);
	return sav_y;
}


float montecarlo(int NM_PART, int leer, float pared_DE, float pared_IZ, float pared_AR, float pared_AB, float D_MAX, float sigma, int SIM_TOT) 
{
	/*Local variable declaration*/
	int sel;
	float acc;
	float intentos;
	float cociente;
	float anterior_x,anterior_y;
	float rho;      //Packing fraction
	float stepz;   //The size of the g_r rings is in terms of this parameter
	/*Local variable initialization */
	sim=0;int buffer(char* nombre);
	acc=0;
	intentos=0;
	float L_boxx = pared_IZ+pared_DE;
	float L_boxy = pared_AB+pared_AR;
	/* Consider previous configurations */
	rho=NM_PART/(L_boxx*L_boxy);
	//printf("Simulación comenzada:\nrho=%f fracción de empacamiento=%f \nNúmero de partículas=%d \nIteraciones programadas=%d\n", rho,(PI*rho)/4,NM_PART, SIM_TOT );
	stepz=0.01;
	
	/*Squared boxes are considered */

	int size_g=(int)(((sqrt(L_boxx*L_boxx+L_boxy*L_boxy)/sqrt(2))/2)*(1/stepz));   //Size of ring of the g(r) function as in Allen P.
	float g[(int)(((sqrt(L_boxx*L_boxx+L_boxy*L_boxy)/sqrt(2))/2)*(1/stepz))];	   //g(r) array declaration
	/* g(r) intialization */
	for(i=0; i<size_g; i++)
		g[i]=0;
	

	/*Monte Carlo main loop */
	
	do
	{
		k=0;
		do
		{
			rnd = (int)(NM_PART-1)*(rand()/((double)RAND_MAX+1)); //Select a particle
				
			anterior_x = mover_x(rnd, pared_IZ, pared_DE,D_MAX);							  //Move in both directions saving previous position
			anterior_y = mover_y(rnd, pared_AB, pared_AR,D_MAX);
			
			//printf("Movida la %d\n", rnd);
	
			/*Begins cheking of overlap of the selected particle */

			tr=0;
			for(p=0; p < NM_PART; p++)
			tr+=traslape(p,0,L_boxx,L_boxy,sigma);
			
			dibujar(NM_PART, pared_IZ, pared_DE, pared_AB, pared_AR, sigma);
			//getchar();


			intentos++; //One more try to count
			if(tr>=1)   //If overlap is true return the particle to the previous position
			{
				//printf("regresada\n");
				part_pos[rnd][0] = anterior_x;
				part_pos[rnd][1] = anterior_y;

				//imprimir_coord(rnd);
				//getchar();
										
			}
			else             //If no overlap the particle counts as accepted
			{
				acc++;
			}
			dibujar(NM_PART, pared_IZ, pared_DE, pared_AB, pared_AR, sigma);
			k++;
		}while(k<NM_PART); //Do this process 'number of particles' times.
		
		
		/* Radial distribution function of the simulation calculation */ 
		
		/* This code takes all particles as reference to which the others are distributed */
		/* Then sums up all distributions for all particles. Normalization is needed */
		i=0;
				
		do
		{
			j=i+1;
			do
			{	
				float dx = part_pos[j][0] - part_pos[i][0];
				float dy = part_pos[j][1] - part_pos[i][1];
				dx=dx-L_boxx*nearbyint(dx/L_boxx);
				dy=dy-L_boxy*nearbyint(dy/L_boxy);
				float r;
				r = sqrt(dx*dx+dy*dy);
				/* This conditional checks for debugging needs */
				if(abs(r) < sigma)
				{
					printf("pos_y_i=%f pos_y_j=%f\n", part_pos[i][0],part_pos[j][0]);
					printf("dx=%f  dy=%f\n i=%d j=%d ", dx, dy, i,j);
					cpgsci(8);
					cpgcirc(part_pos[i][0],part_pos[i][1], sigma/2);
					cpgsci(2);
					cpgcirc(part_pos[j][0],part_pos[j][1], sigma/2);
					printf("Traslape!!\n");
					getchar();
				}
				if((int)(r/stepz) < size_g)
					g[(int)(r/stepz)]=g[(int)(r/stepz)]+1;   //Sum a particle to count of the corresponding ring
				j++;
			}while(j<=NM_PART-1);
			i++;
		}
		while(i<=NM_PART-2);
		//These counters were used to check all particles avoiding themselves
		
		sim++; //This counter increases as a MonteCarlo simulation is done
		//printf("%d\n", sim);
		//salida(NM_PART);
		//printf("%d  %d", contador1,sim);	
		//printf(" Aceptación=%f\n", acc/intentos);
		//getchar();
	 //There is an upper bound for the number of simulations
	 
	 // Calcula el Factor de esctructura
	 factor_de_estructura(NM_PART, L_boxx, L_boxy, SIM_TOT);
     
	}while(sim<SIM_TOT);
	/* Ends all iterations of MonteCarlo */
	
	//Note: This piece of code can be adapted to an independent MC library

	/*Preassure calculation */

	float suma;	
	float beta_presion__rho;
	float beta=1/KbT;
	float r1,r2,oar;
	for(l = 1; l < size_g ; l++)
	{
		if ((g[(l-1)]==0) && (g[l]!=0))
		{ 
			r1=l*stepz;
			r2=(l+1)*stepz;
			oar=1/((r2*r2-r1*r1)*PI);
			beta_presion__rho=1+(PI*sigma*sigma*g[l]*oar)/(SIM_TOT*(NM_PART-1));
			l=size_g;
		}
	}
    ////SALIDA FINAL////
    /// Presión vs. densidad ///
	printf("%f %f\n",beta_presion__rho,(PI*rho)/4);  //Preasure output after SIM_TOT MC iterations
	

	/* g(r) output to text file */
	FILE * pFile;
	pFile = freopen ("g_r.txt","w",stdout);
  	if (pFile!=NULL)
  	{
    		
		for(i=0; i < size_g; i++)
		{	
			r1=i*stepz;
			r2=(i+1)*stepz;
			oar=1/((r2*r2-r1*r1)*PI);
			printf("%f  %f \n",  i*stepz,    (2*g[i]*oar)/(SIM_TOT*rho*(NM_PART-1))); 
		
		}
  	}
	fclose (pFile);

    /* Salida del factor de estructura */	
	int ki;
	FILE * pFile2;
	pFile2 = freopen ("s_k.txt","w",stdout);
  	if (pFile2!=NULL)
  	{
	for(ki=0 ; ki < 300 ; ki++)
		printf("\n%f, %f", 2*PI*ki/(L_boxx), s[ki]/SIM_TOT);

  	}
	fclose (pFile2);
	//getchar();

	//printf("Simulación terminada. Aceptación=%f", acc/intentos);
	return acc/intentos;
}


int traslape(int part_i, int impr, float L_boxx, float L_boxy, float sigma)
{
			traslape_=0;
			int i=part_i;
/*Begins cheking of overlap of the selected particle */
			j=0;
			if (i==0)
			{
				j=1;
				do
				{
					float dx = part_pos[j][0] - part_pos[i][0];
					float dy = part_pos[j][1] - part_pos[i][1];			
					dx=dx-L_boxx*nearbyint(dx/L_boxx);
					dy=dy-L_boxy*nearbyint(dy/L_boxy);
					//printf(" dx = %f, dy = %f", dx,dy);
					if (dx*dx + dy*dy < sigma*sigma)
					{
						if(impr == 1){
							printf(" dx = %f - dy = %f r=%f ", dx,dy,dx*dx+dy*dy);
							printf("%d, ", j); }
						traslape_=1;
					}
					j++;
				}while(j<NM_PART);
			}
			else
			{
				do
				{
					float dx = part_pos[j][0] - part_pos[i][0];
					float dy = part_pos[j][1] - part_pos[i][1];
					dx=dx-L_boxx*nearbyint(dx/L_boxx);
					dy=dy-L_boxy*nearbyint(dy/L_boxy);
					//printf(" dx = %f, dy = %f", dx,dy);
					if (dx*dx + dy*dy < sigma*sigma)
					{
						if(impr == 1){
							printf(" dx = %f - dy = %f r=%f ", dx,dy,dx*dx+dy*dy);
							printf("%d, ", j); }
						traslape_=1;
					}
					j++;
				}while(j<i);
				j=i+1;
				do
				{
					float dx = part_pos[j][0] - part_pos[i][0];
					float dy = part_pos[j][1] - part_pos[i][1];
					dx=dx-L_boxx*nearbyint(dx/L_boxx);
					dy=dy-L_boxy*nearbyint(dy/L_boxy);
					//printf(" dx = %f, dy = %f", dx,dy);
					if (dx*dx + dy*dy < sigma*sigma)
					{
						if(impr == 1){
							printf(" dx = %f - dy = %f r=%f ", dx,dy,dx*dx+dy*dy);
							printf("%d, ", j); }
						traslape_=1;
					}
					j++;
				}while (j<NM_PART);
			}
			/*Ends cheking of overlap with selected particle */

	return traslape_;
	
}

int coloca_nueva(float stepx, float stepy, float pared_DE, float pared_IZ, float pared_AR, float pared_AB, int index, float sigma)
{
	float x,y;
	int i,traslape_;
	float L_boxx= pared_DE + pared_IZ;
	float L_boxy= pared_AR + pared_AB;
	extern float part_pos[NM_PART_][2];


	part_pos[index][0] = - pared_IZ;
	part_pos[index][1] = - pared_AB;
	do
	{
		do
		{
			if (traslape(index, 0, L_boxx, L_boxy, sigma) == 1)
				part_pos[index][0] = part_pos[index][0] + stepx;
			else
				return 0;
		}
		while(part_pos[index][0] < pared_DE);
	
	part_pos[index][0]= - pared_IZ;
	if (traslape(index, 0, L_boxx, L_boxy, sigma) == 1)
		part_pos[index][1] =part_pos[index][1] + stepy;
	else
		return 0;
	}while (part_pos[index][1] < pared_AR);
	
	return 1;

}

int factor_de_estructura(int NM_PART, int SIM_TOT)
{

	int n,ki;
	float kx,ky;
	float r;
	int j;
	ki=1;
    float L_boxx = pared_IZ+pared_DE;
    float L_boxy = pared_AR + pared_AB;
	do	
	{
		
		kx=2*PI*(ki)/(L_boxx);
		ky=2*PI*(ki)/(L_boxy);	
	
		for(i=0 ; i < NM_PART ; i++)
                {
		       
                       rn[ki]=cos(kx*part_pos[i][0]+ky*part_pos[i][1])+rn[ki];
                       in[ki]=sin(kx*part_pos[i][0]+ky*part_pos[i][1])+in[ki];
                }

	
		rn[ki]=rn[ki]/sqrt(NM_PART);
		in[ki]=in[ki]/sqrt(NM_PART);
	
		s[ki]=s[ki] + rn[ki]*rn[ki] + in[ki]*in[ki];
		ki=ki++;

	}while(ki<NM_PART);	

	

	return 0;	
}




