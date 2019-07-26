#ifndef SYSTEM_H
#define SYSTEM_H
#include <stdlib.h>
#include <math.h>

struct system_t {
  double timestep, size;
  double *position, *velocity, *force;
  double potential, kinetic;
  int n_particles;
  int n_steps;
  double rcut, phicut;
  int nthreads; // This might not be the best choice
};

typedef struct system_t System;

void init_system(System *sys);
#endif
