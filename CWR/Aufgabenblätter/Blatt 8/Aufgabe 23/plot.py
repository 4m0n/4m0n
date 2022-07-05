import numpy as np
import matplotlib.pyplot as plt
import scipy.stats as stats
from scipy import optimize



inputfile = "idk.dat"
x = np.loadtxt(inputfile, float, usecols=0, delimiter=",")
y = np.loadtxt(inputfile, float, usecols=1, delimiter=",")
plt.figure(figsize=(10,8))
plt.plot(x, y, color='red')
plt.xlabel("zeit")
plt.ylabel("Ort")
plt.grid(which='major', color='black', linestyle='--', alpha=0.75)
plt.grid(which='minor', color='black', linestyle=':', alpha=0.75)
plt.legend(loc="best",fontsize=10)
plt.savefig("plot", bbox_inches='tight',dpi=120)
plt.show()


inputfile = "plot.dat"
x = np.loadtxt(inputfile, float, usecols=0, delimiter=",")
y = np.loadtxt(inputfile, float, usecols=1, delimiter=",")
plt.figure(figsize=(10,8))
plt.plot(x, y, color='red')
plt.xlabel("Startgeschwindigkeit")
plt.ylabel("Endposition")
plt.grid(which='major', color='black', linestyle='--', alpha=0.75)
plt.grid(which='minor', color='black', linestyle=':', alpha=0.75)
plt.legend(loc="best",fontsize=10)
plt.savefig("plot", bbox_inches='tight',dpi=120)
plt.show()


for k in range(3):
    inputfile = "plot2_{:d}.txt".format(k+1)
    x = np.loadtxt(inputfile, float, usecols=0, delimiter=",")
    y = np.loadtxt(inputfile, float, usecols=1, delimiter=",")
    plt.figure(figsize=(10,8))
    plt.plot(x,y, label = inputfile)
    plt.xlabel("Startgeschwindigkeit")
    plt.ylabel("Endposition")
    plt.grid(which='major', color='black', linestyle='--', alpha=0.75)
    plt.grid(which='minor', color='black', linestyle=':', alpha=0.75)
    plt.legend(loc="best",fontsize=10)
    plt.savefig("plot2_{:d}".format(k+1),bbox_inches='tight',dpi=120)
    plt.show()
    #plt.clf()
