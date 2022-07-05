import numpy as np
import matplotlib.pyplot as plt
import scipy.stats as stats
from scipy import optimize

inputfile = "plot2.txt"
num = 6
x = []
for i in range(num):
    x.append(np.loadtxt(inputfile, float, usecols=i, delimiter=","))

t = x[0]
x_1 =x[1]
k = 0
name = [None, "Monte Carlo", None, None] # MC steht ohne grund an zweiter stelle
plt.figure(figsize=(10,8))
for i in x[2:]:
    print("lol")
    plt.scatter(t, i, color='blue', label = name[k])
    k +=1
plt.scatter(t, x_1, color='red', label = "Midpoint")
plt.xlabel("N")
plt.ylabel("Volumen")
plt.legend(loc="best",fontsize=10)
plt.grid(which='major', color='black', linestyle='--', alpha=0.75)
plt.grid(which='minor', color='black', linestyle=':', alpha=0.75)
plt.savefig("Aufgabe2", bbox_inches='tight',dpi=120)
plt.show()
