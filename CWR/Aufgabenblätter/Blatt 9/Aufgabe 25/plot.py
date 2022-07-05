import numpy as np
import matplotlib.pyplot as plt
import scipy.stats as stats
from scipy import optimize



inputfile = "plot.dat"
x = np.loadtxt(inputfile, float, usecols=0, delimiter=",") # r
y = np.loadtxt(inputfile, float, usecols=1, delimiter=",") # Dichte
z = np.loadtxt(inputfile, float, usecols=2, delimiter=",") # Masse
t = np.loadtxt(inputfile, float, usecols=3, delimiter=",") # Temp



plt.figure(figsize=(10,8))
#plt.title('Dichte Plot')
plt.scatter(x, y, color='blue')
plt.xlabel(r"$R/R_S$")
plt.ylabel(r"$\rho/g/cm^3$")
plt.grid(which='major', color='black', linestyle='--', alpha=0.75)
plt.grid(which='minor', color='black', linestyle=':', alpha=0.75)
#plt.legend(loc="best",fontsize=10)
plt.savefig("Dichteverteilung", bbox_inches='tight',dpi=120)
plt.show()
