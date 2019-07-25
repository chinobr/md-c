#ifndef FORCE_H
#define FORCE_H
#include <omp.h>
#include "system.h"
#include "cell.h"

void newton(System *sys, CellList *clist);
void minimum_images(System *sys, double *dr);
double calculate_force_LJ(System *sys, int i, int j, double *dr, int tid);
double calculate_force_MO(System *sys, int i, int j, double *dr, int tid);
void kinetic(System *sys);
void tally_force(System *sys);
#endif
