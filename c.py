""" La clase Condiciones Iniciales presenta posiciones y velocidades iniciales.  
Se panteó un arreglo cúbico con partículas ubicadas una al lado de la otra y un cubo con partículas distribuidas aleatoriamente. 
También permite leer archivos .xyz y .lammpstrj para extraer datos como velocidades, fuerzas, posiciones.  
Las velocidades iniciales son calculadas de forma aleatoria y con una distribución de Boltzmann
"""

import math
import numpy as np

class CondicionesIniciales(object):

#Posiciones iniciales
      def __init__(self, particles, size, temp):
         self.particles   = particles
         self.size        = size
         self.temp        = temp 
         self.names       = None
         self.coords      = None
         self.vel         = None
         self.force       = None 
       
      def cubo(self):
         position    = np.zeros((self.particles, 3))                        #define arreglo posición
         number_side = math.ceil(self.particles)**(1/3)                     #calcula raiz cubica de particulas(Lado de la red cúbica)  
         distance    = self.size/number_side                   
                                                                            #Ubica las particulas una al lado de la otra en eL arreglo cúbico
         index_particle = 0;
         for i in range(self.particles): 
           for j in range(self.particles): 
              for k in range(self.particles): 
                 if index_particle == self.particles:
                   break
                 position[index_particle, 0] = i * distance  
                 position[index_particle, 1] = j * distance
                 position[index_particle, 2] = k * distance
                 index_particle += 1
         self.coords = position


      def cubo_random(self):                                  #Define posiciones random de las partículas en el cubo    
          random   =  np.random.random_sample((self.particles, 3))
          position = self.size * random
          self.coords = position

      def read_coords_xyz(self,nombre_archivo):
         f      = open(nombre_archivo, 'r')                  #abre el archivo 
         lines  = f.readlines()                              #lee el archivo por líneas 
         natoms = int(lines[0].strip())                      #toma el elemento 0 de la lista y lo define como el natoms
         coords = np.zeros((natoms, 3))                      #define arreglo de coords
         names  = [0] * natoms                               #lista de elementos
         for i in range(natoms):
             coords[i, :] = [float(x) for x in lines[i+2].strip().split()[1:4]]   #omito las 2 primeras líneas
             names[i]     = lines[i+2].strip().split()[0]                            
         self.names  = names
         self.coords = coords

      def read_coords_lammpstrj(self,nombre_archivo):
         f        = open(nombre_archivo, 'r')                   #abre el archivo
         lines    = f.readlines()                               #lee el archivo por líneas
         natoms   = int(lines[3].strip())                       #toma el elemento 3 de la lista y lo define como el natoms 
         line_def = str(lines[8].strip())                       #línea que define las variables calculadas en LAMMPS	
         coords   = np.zeros((natoms, 3))                       #define arreglo de coords
         vel      = np.zeros((natoms, 3))                       #define arreglo de velocidad
         force    = np.zeros((natoms,3))                        #define arreglo de fuerza
         names    = [0] * natoms
         if line_def == "ITEM: ATOMS element x y z vx vy vz fx fy fz":
            for i in range(natoms):
                coords[i, :] = [float(x) for x in lines[i+9].strip().split()[1:4]]  #omito las 9 primeras líneas
                vel[i,:]     = [float(x) for x in lines[i+9].strip().split()[4:7]]
                force[i,:]   = [float(x) for x in lines[i+9].strip().split()[7:10]]
                names[i]     = lines[i+9].strip().split()[0]
         else: print("WARNINRG: Sólo lee archivos que contengan: ATOMS element x y z vx vy vz fx fy fz")
         self.names  = names 
         self.coords = coords
         self.vel    = vel
         self.force  = force

#Velocidades Iniciales                 
 
      def vel_random(self):                                                          #Calcula la velocidad aleatoriamente                
         v_in     = np.random.random_sample((self.particles, 3), dtype=np.float64)   #Genera un array random
         v_cm     = v_in - np.mean(v, axis=1, keepdims = True)                       #Le resta el centro de masa a la velocidad
         v_rn     = v_cm * np.sqrt(self.temp)
         self.vel = v_rn
       
      def vel_boltzman(self):                                                        #Calcula la velocidad con la distribución de Boltzman
         v_in      = np.random.normal(loc = 0, scale = 1, size = (self.particles,3)) #Genera un array con distribución gaussiana
         v_cm      = v_in - np.mean(v, axis=1, keepdims = True)
         v_bol     = v_cm * np.sqrt(self.temp)                                       #Considerando masa=1
         self.vel  = v_bol
