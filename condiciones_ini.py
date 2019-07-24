#arreglo cubico
import math
import numpy as np

def cubo(particles,size):
#------------------------- posiciones iniciales
  position = np.zeros((particles, 3))          #define arreglo posición
  number_side = math.ceil(particles)**(1/3)    #calcula raiz cubica de particulas(Lado de la red cúbica)  
  distance = size/number_side                   


                                               #Ubica las particulas en eL arreglo cúbico
  index_particle = 0;
  for i in range(particles): 
    for j in range(particles): 
      for k in range(particles): 
        if index_particle == n_particles:
          break
        position[index_particle, 0] = i * distance
        position[index_particle, 1] = j * distance;
        position[index_particle, 2] = k * distance;
        index_particle += 1
  return index_particle


def cubo_random(particles,size):
  number_side = math.ceil(particles)**(1/3)    
  distance = size/number_side
  position = np.random.random_sample((particles, 3))
  random = position * distance
 

def read_coords(nombre_archivo):
    f = open(nombre_archivo, 'r')             #abre el archivo 
    lines = f.readlines()                     #lee el archivo por líneas 
    natoms = int(lines[0].strip())            #toma el elemento 0 de la lista y lo define como el natoms
    coords = np.zeros((natoms, 3))            #define arreglo de coords
    names = [0] * natoms                      #lista de elementos
    for i in range(natoms):
        coords[i, :] = [float(x) for x in lines[i+2].strip().split()[1:4]]   #omito las 2 primera líneas
        names[i] = lines[i+2].strip().split()[0]                            
    return names, coords

#--------------------------velocidades iniciales

def vel_random(particles):
    v_in = np.random.random_sample((particles, 3))
    v_cm = v_in - np.mean(v, axis=1, keepdims = True)

def vel_boltzman(particles, T, masa):
    v_in  = np.random.normal(loc = 0, scale = 1, size = (particles,3))
    v_bol = v_in * np.sqrt( T / masa)
