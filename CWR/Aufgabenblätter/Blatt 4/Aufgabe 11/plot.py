import numpy as np
import matplotlib.pyplot as plt
import scipy.stats as stats
from scipy import optimize

inputfile = "plot.txt"
x   = np.loadtxt(inputfile, float, usecols=0, delimiter=",")
y   = np.loadtxt(inputfile, float, usecols=1, delimiter=",")


plt.figure(figsize=(10,8))
plt.bar(x, y, label="Normal", color='blue',width = x[2]-x[1],edgecolor ="k", align = "edge")




plt.ylabel("Anzahl")
plt.xlabel("Wert")
plt.grid(which='major', color='black', linestyle='--', alpha=0.75)
plt.grid(which='minor', color='black', linestyle=':', alpha=0.75)
plt.legend(loc="best",fontsize=10)
plt.savefig("Verteilung", bbox_inches='tight',dpi=1200)
plt.show()
