import numpy as np
import matplotlib.pyplot as plt
import scipy.stats as stats
from scipy import optimize

inputfile = "plot.dat"
x =[]
num = 2#len(inputfile[0])
for i in range(num):
    x.append(np.loadtxt(inputfile, float, usecols=i, delimiter=","))


t = x[0]
plt.figure(figsize=(10,8))
for i in x[1:]:
    plt.plot(t, i, color='red')

plt.xlabel("Delta_t")
plt.ylabel("Y Wert")
plt.yscale("log")
plt.xscale("log")
plt.grid(which='major', color='black', linestyle='--', alpha=0.75)
plt.grid(which='minor', color='black', linestyle=':', alpha=0.75)
plt.legend(loc="best",fontsize=10)
plt.savefig("Konvergenz Plot", bbox_inches='tight',dpi=400)
plt.show()
