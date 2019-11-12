/* libmontecarlo.h - library using header. */

#include "libinicializacion.h"

float montecarlo(int NM_PART, int leer, float pared_DE, float pared_IZ, float pared_AR, float pared_AB, float D_MAX, float sigma, int SIM_TOT);
int traslape(int part_i, int impr, float L_boxx, float L_boxy, float sigma);
int coloca_nueva(float stepx, float stepy, float pared_DE, float pared_IZ, float pared_AR, float pared_AB, int index, float sigma);


