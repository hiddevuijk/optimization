import numpy as np
import matplotlib.pyplot as plt


def f(x): return 1. - 0.5*x-2*x*x/3.+ 0.05*x*x*x*x
def df(x): return -1./2 - 4*x/3. + 0.2*x*x*x

x = np.linspace(-5,5,1000)
plt.plot(x,f(x))
plt.axvline(2.753)
plt.show()


