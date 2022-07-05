import numpy as np
import matplotlib.pyplot as plt
import scipy.stats as stats
from scipy import optimize

inputfile = "plot1.txt"
x    = np.loadtxt(inputfile, float, usecols=0, delimiter=",")
y    = np.loadtxt(inputfile, float, usecols=1, delimiter=",")


plt.figure(figsize=(10,8))
plt.scatter(x, y, color='red',label="Volumen")

plt.xlabel("Delta x")
plt.ylabel("Volumen")
plt.grid(which='major', color='black', linestyle='--', alpha=0.75)
plt.grid(which='minor', color='black', linestyle=':', alpha=0.75)
plt.legend(loc="best",fontsize=10)
plt.savefig("Aufgabe1", bbox_inches='tight',dpi=120)
plt.show()
