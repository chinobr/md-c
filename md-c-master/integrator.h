#ifndef INTEGRATOR_H
#define INTEGRATOR_H
#include "system.h"

struct integrator_t {
  double timestep;
};

typedef struct integrator_t Integrator;

void first_step(Integrator *integ, System *sys);
void last_step(Integrator *integ, System *sys);
#endif
