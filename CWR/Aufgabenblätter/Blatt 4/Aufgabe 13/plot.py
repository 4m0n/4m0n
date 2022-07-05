import numpy as np
import matplotlib.pyplot as plt
import scipy.stats as stats
from scipy import optimize

inputfile = "plot.txt"
x    = np.loadtxt(inputfile, float, usecols=0, delimiter=",")
y    = np.loadtxt(inputfile, float, usecols=1, delimiter=",")


plt.figure(figsize=(10,8))
plt.scatter(x, y, color='red',label="Hyperkugel")


plt.xlabel("Dimensionen")
plt.ylabel("Volumen")
plt.grid(which='major', color='black', linestyle='--', alpha=0.75)
plt.grid(which='minor', color='black', linestyle=':', alpha=0.75)
plt.legend(loc="best",fontsize=10)
plt.savefig("Volumen Hyperkugel2", bbox_inches='tight',dpi=1200)
plt.show()
