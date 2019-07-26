"""
.. module:: velocidades_iniciales
"""
import random as rnd
import numpy as np


def random(n_particles):

    """ 
    
    velocities (numpy.array (dim=3*n_particles) )

    """

    rnd.seed(6000)
    velocities = np.zeros((3 * n_particles),  dtype=np.float64)
    for i in range(3*n_particles):
        velocities[i] = (rnd.random() - 0.0)
    return velocities
