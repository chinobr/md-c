#include "system.h"

void init_system(System *sys) {
  //  srand(time(NULL));
  srand(6000);
  sys->position = (double *)malloc(sys->n_particles*3*sizeof(double));
  sys->velocity = (double *)malloc(sys->n_particles*3*sizeof(double));
  sys->force = (double *)malloc(sys->n_particles * sys->nthreads*3*sizeof(double));
  int number_side = ceil(cbrt(sys->n_particles));
  double distance = sys->size / number_side;
  int index_particle = 0;
  for (int i = 0; i < number_side; i++) {
    for (int j = 0; j < number_side; j++) {
      for (int k = 0; k < number_side; k++) {
        if (index_particle == sys->n_particles) break;
        sys->position[3*index_particle + 0] = i * distance;
        sys->position[3*index_particle + 1] = j * distance;
        sys->position[3*index_particle + 2] = k * distance;
        index_particle++;
      }
    }
  }
  for (int i = 0; i < 3 * sys->n_particles; i++)
    sys->velocity[i] = (double)rand()/RAND_MAX;
}
