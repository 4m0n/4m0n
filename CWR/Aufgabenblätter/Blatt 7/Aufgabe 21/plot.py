import numpy as np
import matplotlib.pyplot as plt
import scipy.stats as stats
from scipy import optimize

inputfile = "position.dat"
x =[]
num = 30#len(inputfile[0])
for i in range(num):
    x.append(np.loadtxt(inputfile, float, usecols=i, delimiter=","))


t = x[0]
plt.figure(figsize=(10,8))
for i in x[1:]:
    plt.plot(t, i, color='red')

inputfile = "energy.dat"
x_1=np.loadtxt(inputfile, float, usecols=0, delimiter=",")
x_2=np.loadtxt(inputfile, float, usecols=1, delimiter=",") #E_kin
x_3=np.loadtxt(inputfile, float, usecols=2, delimiter=",") #E_pot
x_5=[]
for i in range(len(x_1)):
    x_5.append(x_2[i]+x_3[i])

plt.figure(figsize=(10,8))
plt.plot(x_1, x_2, color='red',label = "E_kin")
plt.plot(x_1, x_3, color='blue',label = "E_pot")
plt.plot(x_1, x_5, color='orange',label = "E_Gesamt")

plt.xlabel("Zeit")
plt.ylabel("Position?")
plt.grid(which='major', color='black', linestyle='--', alpha=0.75)
plt.grid(which='minor', color='black', linestyle=':', alpha=0.75)
plt.legend(loc="best",fontsize=10)
plt.savefig("plot", bbox_inches='tight',dpi=120)
plt.show()
