import numpy as np
import matplotlib.pyplot as plt
import scipy.stats as stats
from scipy import optimize



inputfile = "plot.dat"
x = np.loadtxt(inputfile, float, usecols=0, delimiter=",")
y = np.loadtxt(inputfile, float, usecols=1, delimiter=",") 




plt.figure(figsize=(10,8))
#plt.title('Dichte Plot')
plt.scatter(x, y, color='blue')
plt.xlabel(r"Sekunden")
plt.ylabel(r"Dimension")
plt.grid(which='major', color='black', linestyle='--', alpha=0.75)
plt.grid(which='minor', color='black', linestyle=':', alpha=0.75)
#plt.legend(loc="best",fontsize=10)
plt.savefig("CPU-zeit", bbox_inches='tight',dpi=120)
plt.show()
