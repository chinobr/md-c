#include "integrator.h"
/*
void first_step(Integrator *integ, System *sys) {
  for (int i = 0; i < 3 * sys->n_particles; i++) {
    sys->position[i] += sys->velocity[i] * integ->timestep + sys->force[i]/2 * (integ->timestep * integ->timestep);
    sys->velocity[i] += sys->force[i]/2 * integ->timestep;
  }
  for (int i = 0; i < 3 * sys->n_particles; i++) {
    if (sys->position[i] > sys->size)
      sys->position[i] -= sys->size;
    else if (sys->position[i] < 0)
      sys->position[i] += sys->size;
  }
}

void last_step(Integrator *integ, System *sys) {
  for (int i = 0; i < 3 * sys->n_particles; i++) {
    sys->velocity[i] += sys->force[i]/2 * integ->timestep;
  }
  printf("%e",integ->timestep);
}

*/


void first_step(Integrator *integ, System *sys) {
  double tiempo = 0.0005;
  for (int i = 0; i < 3 * sys->n_particles; i++) {
    sys->position[i] += sys->velocity[i] * tiempo + sys->force[i]/2 * (tiempo * tiempo);
    sys->velocity[i] += sys->force[i]/2 * tiempo;
  }
  for (int i = 0; i < 3 * sys->n_particles; i++) {
    if (sys->position[i] > sys->size)
      sys->position[i] -= sys->size;
    else if (sys->position[i] < 0)
      sys->position[i] += sys->size;
  }
}

void last_step(Integrator *integ, System *sys) {
  double tiempo = 0.0005;
  for (int i = 0; i < 3 * sys->n_particles; i++) {
    sys->velocity[i] += sys->force[i]/2 * tiempo;
  }
}

