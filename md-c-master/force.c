#include "force.h"

void newton(System *sys, CellList *clist) {
  double epot = 0.0;
  for (int i = 0; i < 3 * sys->nthreads * sys->n_particles; i++)
    sys->force[i] = 0.0;
#pragma omp parallel reduction(+:epot)
  {
    for (int cc = 0; cc < clist->ncells; cc+=sys->nthreads) {
      int tid = omp_get_thread_num();
      int c = cc + tid;
      if (c >= clist->ncells) continue;
      Cell cell = clist->list[c];
      for (int ii = 0; ii < cell.n_particles; ii++) {
        for (int jj = ii + 1; jj < cell.n_particles; jj++) {
          int i = cell.particles[ii];
          int j = cell.particles[jj];
          double dr[3];
          for (int k = 0; k < 3; k++)
            dr[k] = sys->position[3*i+k] - sys->position[3*j+k];
          minimum_images(sys, dr);
          epot += calculate_force(sys, i, j, dr, tid);
        }
      }
      for (int d = 0; d < cell.nneigh; d++) {
        Cell cell2 = clist->list[cell.neigh[d]];
        for (int ii = 0; ii < cell.n_particles; ii++) {
          for (int jj = 0; jj < cell2.n_particles; jj++) {
            int i = cell.particles[ii];
            int j = cell2.particles[jj];
            double dr[3];
            for (int k = 0; k < 3; k++)
              dr[k] = sys->position[3*i+k] - sys->position[3*j+k];
            minimum_images(sys, dr);
            epot += calculate_force(sys, i, j, dr, tid);
          }
        }
      }
    }
  }
  sys->potential = epot;
  for (int i = 1; i < sys->nthreads; i++) {
    int offset = 3 * i * sys->n_particles;
    for (int j = 0; j < 3 * sys->n_particles; j++) {
      sys->force[j] += sys->force[j + offset];
    }
  }
}
__attribute__((always_inline,pure))
inline void minimum_images(System *sys, double *dr) {
  for (int k = 0; k < 3; k++) {
    if (dr[k] > 0.5 * sys->size)
      dr[k] -= sys->size;
    else if (dr[k] < -0.5 * sys->size)
      dr[k] += sys->size;
  }
}

//__attribute__((always_inline,pure))
inline double calculate_force(System *sys, int i, int j, double *dr, int tid) {
  double distance = 0.0;
  for (int k = 0; k < 3; k++) {
    distance += dr[k] * dr[k];
  }
  if (distance < sys->rcut * sys->rcut) {
    int offset = tid * 3 * sys->n_particles;
    double rm2 = 1.0/distance;
    double rm6 = rm2 * rm2 * rm2;
    double rm12 = rm6 * rm6;
    double phi  = 4.0 * (rm12 - rm6);
    double dphi = 24.0*rm2*(2.0*rm12 - rm6);
    for (int k = 0; k < 3; k++) {
      sys->force[3*i+k+offset] += dphi * dr[k];
      sys->force[3*j+k+offset] -= dphi * dr[k];
    }
    return phi - sys->phicut;
  }
  else
    return 0.0;
}

void kinetic(System *sys) {
  double kin = 0.0;
  for (int i = 0; i < 3 * sys->n_particles; i++) {
    kin += sys->velocity[i] * sys->velocity[i];
  }
  sys->kinetic = kin/2;
}
