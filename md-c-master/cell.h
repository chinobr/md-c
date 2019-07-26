#ifndef CELL_H
#define CELL_H
#include <stdlib.h>
#include "system.h"
#define max(a,b)                \
({ __typeof__ (a) _a = (a);     \
  __typeof__ (b) _b = (b);      \
  _a > _b ? _a : _b; })

#define min(a,b) \
({ __typeof__ (a) _a = (a);     \
  __typeof__ (b) _b = (b);      \
  _a < _b ? _a : _b; })

struct cell_t {
  int *particles;
  int n_particles;
  int *neigh;
  int nneigh;
  int ix, iy, iz;
};

typedef struct cell_t Cell;

struct cell_list_t {
  Cell *list;
  double size;
  int cells_side, ncells;
};

typedef struct cell_list_t CellList;

void init_cells(CellList *clist, System *sys, double size);
void update_cells(CellList *clist, System *sys);
#endif
