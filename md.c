#include "md.h"

float timedifference_msec(struct timeval t0, struct timeval t1)
{
    return (t1.tv_sec - t0.tv_sec) + (t1.tv_usec - t0.tv_usec) / 1000000.0f;
}

int main(int argc, char** argv) {
  FILE *file_time, *file_energy;
  struct timeval start, now;
  file_time = fopen("time.dat", "w");
  file_energy = fopen("energy.dat", "w");
  fprintf(file_energy, "#Potential, Kinetic, Total\n");
  System *sys = (System *) malloc(sizeof(System));
#pragma omp parallel
    sys->nthreads = omp_get_num_threads();
  if (argc != 4) {
    fprintf(stderr, "usage: %s n_steps n_particles type_of_pontential(LJ/MO)"\n", argv[0]);
    exit(1);
  }
  sys->n_particles = atoi(argv[2]);
  sys->n_steps = atoi(argv[1]);
  sys->size = cbrt(sys->n_particles/0.45);

 potential = argv[3]; // ingreso acá el tipo de potencial
    if (potential = "LJ")
        sys->rcut = 2.5;
        sys->phicut = 4.0*(pow(2.5, -12) - pow (2.5, -6));
    else if (potential = "MO")
        sys->rcut = 6.0;
        sys->phicut = exp(-12.0 + 2.0) - 2 * exp(-12.0 + 1.0 );
    else exit(1);


  init_system(sys);
  CellList *clist = (CellList *) malloc(sizeof(CellList));
  init_cells(clist, sys, 2.5);
  Integrator *integ = (Integrator *) malloc(sizeof(Integrator));
  integ->timestep = 0.0005;

  printf("%d threads\n", sys->nthreads);
  update_cells(clist, sys);

  newton(sys, clist);  // ACA DEBERIA PONERLE UN INPUT MAS, EL CUAL ELEGIS QUE TIPO DE POTENCIAL CALCULAR
  kinetic(sys);
  gettimeofday(&start, NULL);
  for (int i = 0; i < sys->n_steps; i++) {
    first_step(integ, sys);
    update_cells(clist, sys);
    newton(sys, clist);
    last_step(integ, sys);
    kinetic(sys);
    fprintf(file_energy, "%g, %g, %g\n", sys->potential, sys->kinetic, sys->potential+sys->kinetic);
    gettimeofday(&now, NULL);
    double elapsed = timedifference_msec(start, now);
    fprintf(file_time, "%i, %g\n", i, elapsed);
    printf("%i, %g\n", i, elapsed);
  }
  gettimeofday(&now, NULL);
  double elapsed = timedifference_msec(start, now);
  printf("Steps: %d, Part: %d, Time: %f\n", sys->n_steps, sys->n_particles, elapsed);

  return 0;
}
