import numpy as np
import matplotlib.pyplot as plt
import scipy.stats as stats
from scipy import optimize

inputfile = "plot.txt"
x_1    = np.loadtxt(inputfile, float, usecols=0, delimiter=",")
y_1   = np.loadtxt(inputfile, float, usecols=1, delimiter=",")
y_2   = np.loadtxt(inputfile, float, usecols=2, delimiter=",")
y_3   = np.loadtxt(inputfile, float, usecols=3, delimiter=",")

plt.figure(figsize=(10,8))
plt.plot(x_1, y_1, label="Normal", color='blue')
plt.plot(x_1, y_2, label="Midpoint", color='red')
plt.plot(x_1, y_3, label="Simpson", color='green')



plt.ylabel("Wert")
plt.xlabel("Durchgang")
plt.grid(which='major', color='black', linestyle='--', alpha=0.75)
plt.grid(which='minor', color='black', linestyle=':', alpha=0.75)
plt.legend(loc="best",fontsize=10)
plt.savefig("speed", bbox_inches='tight',dpi=1200)
plt.show()
