#include "integrator.h"

void first_step(Integrator *integ, System *sys) {
  for (int i = 0; i < 3 * sys->n_particles; i++) {		// sobre las 3 coordendas de c/ particula
    sys->position[i] += sys->velocity[i] * integ->timestep + sys->force[i]/2 * (integ->timestep * integ->timestep);	//  x=v*t
    sys->velocity[i] += sys->force[i]/2 * integ->timestep;		// v = f/2 * t (con m=1)
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
    sys->velocity[i] += sys->force[i]/2 * integ->timestep;		// en el ultimo paso no reacomoda las posiciones
  }
}
