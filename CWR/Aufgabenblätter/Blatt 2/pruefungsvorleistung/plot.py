import numpy as np
import matplotlib.pyplot as plt
import scipy.stats as stats
from scipy import optimize

inputfile = "plot1.txt"
x_1    = np.loadtxt(inputfile, float, usecols=0, delimiter=",")
y_1    = np.loadtxt(inputfile, float, usecols=1, delimiter=",")

inputfile = "plot2.txt"
x_2    = np.loadtxt(inputfile, float, usecols=0, delimiter=",")
y_2  = np.loadtxt(inputfile, float, usecols=1, delimiter=",")

inputfile = "plot3.txt"
x_3    = np.loadtxt(inputfile, float, usecols=0, delimiter=",")
y_3  = np.loadtxt(inputfile, float, usecols=1, delimiter=",")




#3 Plots linear, semi Log, doppel Log

fig, ax = plt.subplots(3,figsize=(15,15))
ax[0].set_title("Normaler Plot")
ax[0].scatter(x_1, y_1, label="Bisektion", color='blue')
ax[0].scatter(x_2, y_2, label="Newton Raphson", color='red')

ax[0].grid(which='major', color='black', linestyle='--', alpha=0.75)
ax[0].grid(which='minor', color='black', linestyle=':', alpha=0.75)
ax[0].legend(loc="best",fontsize=10)
ax[0].set_xlabel("Durchläufe")
ax[0].set_ylabel("Abstand der Punkte")

ax[1].set_title("Semilogarithmisch")
ax[1].scatter(x_1, y_1, label="Bisektion", color='blue')
ax[1].scatter(x_2, y_2, label="Newton Raphson", color='red')

ax[1].grid(which='major', color='black', linestyle='--', alpha=0.75)
ax[1].grid(which='minor', color='black', linestyle=':', alpha=0.75)
ax[1].legend(loc="best",fontsize=10)
ax[1].set_yscale('log')
ax[1].set_xlabel("Durchläufe")
ax[1].set_ylabel("Abstand der Punkte")

ax[2].set_title("Doppellogarithmisch")
ax[2].scatter(x_1, y_1, label="Bisektion", color='blue')
ax[2].scatter(x_2, y_2, label="Newton Raphson", color='red')

ax[2].grid(which='major', color='black', linestyle='--', alpha=0.75)
ax[2].grid(which='minor', color='black', linestyle=':', alpha=0.75)
ax[2].legend(loc="best",fontsize=10)
ax[2].set_yscale('log')
ax[2].set_xscale('log')
ax[2].set_xlabel("Durchläufe")
ax[2].set_ylabel("Abstand der Punkte")
#Plot von Aufgabe 4
plt.savefig("Annaeherung.jpg", bbox_inches='tight',dpi=1200)
plt.clf()
plt.title("Aufgabe 7.4 - Abbildung x(t)")
plt.figure(figsize=(10,8))
plt.scatter(x_3, y_3, label="Abbildung", color='blue')
plt.xlabel("t-Wert")
plt.ylabel("Nullstelle")
plt.grid(which='major', color='black', linestyle='--', alpha=0.75)
plt.grid(which='minor', color='black', linestyle=':', alpha=0.75)
plt.legend(loc="best",fontsize=10)
plt.savefig("Abbildung.jpg", bbox_inches='tight',dpi=1200)

print("\n\n\n\n ==DONE== \n\n\n\n")
