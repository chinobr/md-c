#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon Jul 22 20:49:10 2019

Simulador de dinamica molecular
Unidades reducidas: Kb = 1, 1fseg = 1, 1angstrom = 1
Potencial= Lennard Jones
Integrador= V promedio?? 


@author: Sergio
"""
import sys as s

# Inicializacion de la simulacion

# Parametros 
timestep = 0.0005 # Paso de tiempo

# Relacionados con el Potencial de Lennard-Jones
rcut = 2.5 # distancia maxima de corte para el potencial
rsafe = 0.1 # distancia minima para que el potencial no diverja


# variables ingresan como argumento
if (len(s.argv) != 7):
    print("Uso : %s n_steps n_particles\n", s.argv[0]) #Incompleto
    exit(1);

    n_steps = s.argv[1]
    n_particles = s.argv[2]
    distribucion_espacial = s.argv[3]
    distribucion_velocidades = s.argv[4]    
    tipo_potencial = s.argv[5]
    tipo_integrador = s.argv[6]

# !!hya funciones dentro de laos .h como distnicaia dentro de init_cell -> funciones???

# Creacion de la clase sys ()
    
# Creacion de la grilla () (es en funcion de rcut, ver init_cell en md.c)    

# Generacion y carga de Posiciones

# Generacion y carga de Velocidades

#%% Calculo para cada tiempo

for t in range(n_steps):
    # Integracion vel prom RK4 seria distinto
    Integra(tipo_integrador,sys)
    #first_step(integ, sys);
    #update_cells(clist, sys);
    #newton(sys, clist);
    #last_step(integ, sys);

    #Calculo de variables de estado p.e. E cinetica
    
    #salida en pantalla / archivo / gráfica

print ("FIN")
