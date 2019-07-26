import matplotlib.pyplot as plt
import numpy as np

class Plotter(object):            #  This class creates a plot. It defines values.

    def __init__(self):
        self.fig=None
        self.axes=None
        self.energy=[]              
        self.temperature=[]
        self.energy_k=[]
        self.energy_p=[]
        self.n_step=100

  # Update values of de simulation for plot

    def update(self, Energy=None, Temperature=None, Energy_k=None, Energy_p=None):    
        print(self.energy)
        self.energy.append(Energy)
        self.temperature.append(Temperature)
        self.energy_k.append(Energy_k)
        self.energy_p.append(Energy_p)
        self.live_plotter()

   #  This function make a dyinamic plot.

    def live_plotter(self, identifier='',pause_time=0.8):
    
     
        for i in range(self.n_step): 
            x = i

        
        if self.fig is None:
	            
            plt.style.use('ggplot')  # use ggplot style 
            plt.ion()          # this is the call allows dynamic plotting
            self.fig, self.ax = plt.subplots(figsize=(13,6))         
            self.ax.set_xlim((0,self.n_step))   # adjust limits of data
            self.ax.set_ylim((0,100))
            self.ax.set_title('E vs Time: {}'.format(identifier))
            self.ax.plot(x,self.energy,'red')            
            self.ax.plot(x,self.temperature,'blue')
            self.ax.plot(x,self.energy_k,'black')
            self.ax.plot(x,self.energy_p,'green')
            plt.show()
            plt.pause(pause_time) #this pauses the data so the figure/axis can catch up - the amount of pause can be altered above























