import numpy as np
import matplotlib.pyplot as plt


out = np.loadtxt("out.dat")
plt.scatter(out[0,0],out[0,1] )
plt.plot(out[:,0], out[:,1])

plt.show()
