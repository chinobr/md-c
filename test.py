from pylive import Plotter
import numpy as np
import time

Energy = np.linspace(1,6,2)
Temperature = np.linspace(1,6,2)
Energy_k = np.linspace(1,6,2)
Energy_p = np.linspace(1,6,2)
plt = Plotter()

for i in range(2):
  time.sleep(0.1)
  e = Energy[i]
  t = Temperature[i]
  k = Energy_k[i]
  v = Energy_p[i]
  plt.update(e, t, k, v)

	
