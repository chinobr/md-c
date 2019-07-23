#include "md.h"


float timedifference_msec(struct timeval t0, struct timeval t1)
{
    return (t1.tv_sec - t0.tv_sec) + (t1.tv_usec - t0.tv_usec) / 1000000.0f;	// anota los seg+mileseg/1E6 actuales del tiempo de clock
}



int main(int argc, char** argv) {	// argc=cantidad de argumentos; argv=texto de los argumentos
  FILE *file_time, *file_energy;	// puntero de los archivos a abrir y escribir ("w")

  struct timeval start, now	   // inicializa start (t de inicio) y now (t de finalización)	

  file_time = fopen("time.dat", "w");
  file_energy = fopen("energy.dat", "w");
  fprintf(file_energy, "#Potential, Kinetic, Total\n");		//crea el archivo e imprime en 1era linea eso
  System *sys = (System *) malloc(sizeof(System));		//crea el puntero sys a la estructura System y le asigna espacio en memoria 


#pragma omp parallel				// The omp parallel directive explicitly instructs the compiler to parallelize the chosen block of code.
    sys->nthreads = omp_get_num_threads();


  if (argc != 3) {
    fprintf(stderr, "usage: %s n_steps n_particles\n", argv[0]);		// imprime cuando ingreso 2 parámetros extras al correr .e
    exit(1);
  }


  sys->n_particles = atoi(argv[2]);		// convierte la 2da str ingresada (n de particulas) a int y la guarda en la estruc a la que apunta *sys
  sys->n_steps = atoi(argv[1]);
  sys->size = cbrt(sys->n_particles/0.45);	// calcula raiz cubica de n de particulas (LADO de la red cubica) 
  sys->rcut = 2.5;					// corto el potencial de LJ en 2,5
  sys->phicut = 4.0*(pow(2.5, -12) - pow (2.5, -6));	// y calculo el valor en ese punto


  init_system(sys);		// inicializa las variables guardadas donde apunta *sys (ver system.h) y las CONDICIONES INICIALES


  CellList *clist = (CellList *) malloc(sizeof(CellList));	//crea el puntero clist a la estructura CellList y le asigna espacio en memoria
  init_cells(clist, sys, 2.5);					// crea el arreglo donde apunta "*clist" con las variables de "sys" y de tamaño 2,5 (ver cell.c)


  Integrator *integ = (Integrator *) malloc(sizeof(Integrator));	// ver integrador.c
  integ->timestep = 0.0005;

  printf("%d threads\n", sys->nthreads);
  


  update_cells(clist, sys); // actualiza los sitios de las particulas, y les aplica la interaccion 
  newton(sys, clist);
  kinetic(sys);


  gettimeofday(&start, NULL); 		// toma el tiempo inicial
  
  
  for (int i = 0; i < sys->n_steps; i++) {
    first_step(integ, sys);		
    update_cells(clist, sys);
    newton(sys, clist);
    last_step(integ, sys);
    kinetic(sys);

    fprintf(file_energy, "%g, %g, %g\n", sys->potential, sys->kinetic, sys->potential+sys->kinetic);		// guarda el archivo con las energías
    gettimeofday(&now, NULL);
    double elapsed = timedifference_msec(start, now);
    fprintf(file_time, "%i, %g\n", i, elapsed);
    printf("%i, %g\n", i, elapsed);
  }


  gettimeofday(&now, NULL); 	// tiempo final
  double elapsed = timedifference_msec(start, now);		// duracion de la corrida
  printf("Steps: %d, Part: %d, Time: %f\n", sys->n_steps, sys->n_particles, elapsed);		// va poniendo en pantalla el tiempo y pasos

  return 0;
}
