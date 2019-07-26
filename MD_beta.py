import ctypes as C
import numpy as np
import matplotlib.animation as animation
import posiciones_iniciales as pos
import velocidades_iniciales as vels

from pylive_beta import live_plotter
import time 

import matplotlib.pyplot as plt 

c_float = C.c_float
c_double = C.c_double
c_int = C.c_int
c_fl_pointer = C.POINTER(C.c_float)
c_db_pointer = C.POINTER(C.c_double)
c_int_pointer = C.POINTER(C.c_int)


mdc = C.CDLL('./libmymd.so')


class CellList(C.Structure):

    _fields_=[("list", C.c_void_p),
              ("size",c_double),
              ("cells_side",c_int),
              ("ncells",c_int)]


class Integrator(C.Structure):
    
    _fields_=[("timestep", c_double)]

    

class System(C.Structure):

    _fields_ = [
            ("timestep", c_double),
            ("size", c_double), 
            ("position", c_db_pointer),
            ("velocity", c_db_pointer),
            ("force", c_db_pointer), 
            ("potential", c_double),
            ("kinetic", c_double),
            ("n_particles", c_int),
            ("n_steps", c_int), 
            ("rcut", c_double), 
            ("phicut", c_double),
            ("nthreads", c_int)]
           
    def __init__(self, size, n_particles, n_steps=1, timestep=0.0005, rcut=2.5):
    
        self.n_steps = n_steps
        self.n_particles = n_particles        
        self.timestep = timestep
        self.size = size #(self.n_particles/density)**(1./3.)
        self.potential = 0.0
        self.kinetic = 0.0
        self.rcut = rcut
        self.phicut = 4 * (self.rcut**(-12) - self.rcut**(-6))

        self.nthreads = 4 

        
        self.position_t = pos.simple(self.size, self.n_particles)
        self.velocity_t = vels.random(self.n_particles)
        self.force_t = np.zeros((3 * self.n_particles * self.nthreads), dtype=np.float64)

        
        self.position = self.position_t.ctypes.data_as(c_db_pointer)
        self.velocity = self.velocity_t.ctypes.data_as(c_db_pointer) 
        self.force = self.force_t.ctypes.data_as(c_db_pointer)


def init_cell(clist,sys,size):
    mdc.init_cells.argtypes = [C.c_void_p, C.c_void_p, C.c_double]
    mdc.init_cells(clist, sys, size)


# aca ....

n_particles = 50
size =(n_particles/0.45)**(1./3.)
print(size)
n_pasos = 50
temp =20.

# creo el objeto systema
sys =  System(size,n_particles)

# Declaro el objeto clist
clist  = CellList()

init_cell(C.byref(clist),C.byref(sys),size)


# Declaro el objeto integ
integ =  Integrator()


# crear el objeto para visualizar

#rt_plot = live_plotter()


# lista de energías

e_list = []
k_list = []
p_list = []
t_list = []

################### Para graficar real time

fig = plt.figure()
ax = fig.add_subplot(1,1,1)


x, y = [], []

def animate(i):
    

    mdc.first_step(C.byref(integ), C.byref(sys))
    mdc.update_cells(C.byref(clist), C.byref(sys))
    mdc.newton(C.byref(sys), C.byref(clist))
    mdc.last_step(C.byref(integ), C.byref(sys))
    mdc.kinetic(C.byref(sys))

    print(sys.kinetic,sys.potential,sys.kinetic+sys.potential)
    

    t_i =  float(i)*0.0005
    x.append(i)
    y.append(sys.kinetic+sys.potential)
    #k_list.append(sys.kinetic)
    #p_list.append(sys.potential)
    
    ax.plot(x, y, color='b')
    plt.xlabel("$Time$")
    plt.ylabel("Energy")   # 
    fig.canvas.draw()
    
    ax.set_ylim(-130,-131)
    ax.set_xlim(left=max(0, i-50), right=i+50)
    
   
ani = animation.FuncAnimation(fig, animate,frames=n_pasos, repeat=False, interval=100)
plt.show()

#for i in range (100):
#   i+=1
#   plt.close()

ani.save("myplot.mp4",fps=20)


#######################################################################

Energ = np.asarray(e_list)
#Cinet = np.asarray(k_list)
#Poten = np.asarray(p_list)
tiemp = np.asarray(t_list)





plt.plot(tiemp,Energ,"bo-", linewidth=1, markersize=1 , label="E_Total" );
#plt.plot(CP,"gd-", linewidth=1, markersize=1 , label="Preferenciales" );
plt.xlabel("$t(minutos)$") # LaTeX Code 
plt.ylabel("Energía: 0.0005")   # 
plt.legend(loc="upper left") # 
plt.savefig("myplot_0_0005.pdf")

    #time.sleep(0.1)
    #rt_plot.update(sys.kinetic+sys.potential,temp,sys.kinetic,sys.potential)
