import numpy as np
import matplotlib.pyplot as plt
import scipy.stats as stats
from scipy import optimize

inputfile = "seir.txt"
t    = np.loadtxt(inputfile, float, usecols=0, delimiter=",")
s    = np.loadtxt(inputfile, float, usecols=1, delimiter=",")
e    = np.loadtxt(inputfile, float, usecols=2, delimiter=",")
i    = np.loadtxt(inputfile, float, usecols=3, delimiter=",")
r    = np.loadtxt(inputfile, float, usecols=4, delimiter=",")

plt.figure(figsize=(10,8))
plt.plot(t, s, label="Nicht betroffen", color='orange')
plt.plot(t, e, label="Inkubationszeit", color='blue')
plt.plot(t, i, label="Ansteckend", color='red')
plt.plot(t, r, label="Geheilt", color='green')



plt.ylabel("Menschen")
plt.xlabel("Zeit")
plt.grid(which='major', color='black', linestyle='--', alpha=0.75)
plt.grid(which='minor', color='black', linestyle=':', alpha=0.75)
plt.legend(loc="best",fontsize=10)
plt.savefig("speed", bbox_inches='tight',dpi=1200)
plt.show()
