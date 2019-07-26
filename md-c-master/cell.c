#include "cell.h"

void init_cells(CellList *clist, System *sys, double size) {
  clist->cells_side = ceil(sys->size / size);
  clist->size = sys->size/clist->cells_side;
  clist->ncells = clist->cells_side * clist->cells_side * clist->cells_side;
  clist->list = (Cell *) malloc(clist->ncells * sizeof(Cell));

  int index = 0;
  for (int i = 0; i < clist->cells_side; i++) {
    for (int j = 0; j < clist->cells_side; j++) {
      for (int k = 0; k < clist->cells_side; k++) {
        Cell this_cell;
        this_cell.ix = i;
        this_cell.iy = j;
        this_cell.iz = k;
        this_cell.nneigh = 0;
        this_cell.neigh = (int *) malloc(clist->ncells * sizeof(int));
        this_cell.particles = (int *) malloc(sys->n_particles * sizeof(int));
        this_cell.n_particles = 0;
        clist->list[index] = this_cell;
        index += 1;
      }
    }
  }

  for (int i = 0; i < clist->ncells; i++) {
    for (int j = i + 1; j < clist->ncells; j++) {
      Cell *ci = &(clist->list[i]);
      Cell *cj = &(clist->list[j]);
      int dx = abs(ci->ix - cj->ix) * clist->size;
      if (dx > sys->size/2) dx -= sys->size;
      else if (dx < -sys->size/2) dx += sys->size;
      dx = max(dx - clist->size, 0);

      int dy = abs(ci->iy - cj->iy) * clist->size;
      if (dy > sys->size/2) dy -= sys->size;
      else if (dy < -sys->size/2) dy += sys->size;
      dy = max(dy - clist->size, 0);

      int dz = abs(ci->iz - cj->iz) * clist->size;
      if (dz > sys->size/2) dz -= sys->size;
      else if (dz < -sys->size/2) dz += sys->size;
      dz = max(dz - clist->size, 0);

      double d2 = dx * dx + dy * dy + dz * dz;
      if (d2 < (sys->rcut * sys->rcut)) {
        ci->neigh[ci->nneigh] = j;
        ci->nneigh++;
      }
    }
  }
}


void update_cells(CellList *clist, System *sys) {
  for (int i = 0; i < clist->ncells; i++)
    clist->list[i].n_particles = 0;
  for (int i = 0; i < sys->n_particles; i++) {
    int ix = floor(sys->position[3*i + 0]/clist->size);
    int iy = floor(sys->position[3*i + 1]/clist->size);
    int iz = floor(sys->position[3*i + 2]/clist->size);
    int cell_index = ix * clist->cells_side * clist->cells_side + iy * clist->cells_side + iz;
    Cell *cell = &(clist->list[cell_index]);
    cell->particles[cell->n_particles] = i;
    cell->n_particles += 1;
  }
}
