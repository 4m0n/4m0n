import numpy as np
import matplotlib.pyplot as plt
import scipy.stats as stats
from scipy import optimize

#Info Zeugs
aufgabe = "Aufgabe "
inputfile = "info.txt"
length = int(np.loadtxt(inputfile, float, usecols=0, delimiter=","))
N = int(np.loadtxt(inputfile, float, usecols=1, delimiter=","))
aufgabe+=str(int(np.loadtxt(inputfile, float, usecols=2, delimiter=",")))
print("joooo"+aufgabe)
beschriftung =[];
for i in range(length):
    beschriftung.append(str(np.loadtxt(inputfile, str, usecols=i+3, delimiter=",")))
for i in range(N*length):
    beschriftung.append(None) # auch nur für N>1 wichtig damit nicht jedes pendel ein Label bekommt.
print(beschriftung)

#Plot  Zeugs
inputfile = "plot1.txt"
x =[]
x.append(np.loadtxt(inputfile, float, usecols=0, delimiter=",")) #wird zum erstellen der x-Achsen Skala missbraucht

if length > 1:
    for k in range(length):
        inputfile = "plot{:d}.txt".format(k+1)
        for i in range(N): #Schleife falls die Dimensionen (N) größer als 1 sind
            x.append(np.loadtxt(inputfile, float, usecols=i+1, delimiter=","))
else:
    for i in range(N): #für Dim
        x.append(np.loadtxt(inputfile, float, usecols=i+1, delimiter=","))
t = x[0]
plt.figure(figsize=(10,8))
k = 0
for i in x[1:]:
    plt.plot(t, i, label = beschriftung[k])
    k += 1


plt.xlabel("Zeit")
plt.ylabel("Position")
plt.grid(which='major', color='black', linestyle='--', alpha=0.75)
plt.grid(which='minor', color='black', linestyle=':', alpha=0.75)
plt.legend(loc="best",fontsize=10)
plt.savefig("Bilder/"+aufgabe, bbox_inches='tight',dpi=400)
plt.show()

k = 0
for i in x[1:]:
    plt.clf()
    plt.plot(t, i, label = beschriftung[k])
    plt.xlabel("Zeit")
    plt.ylabel("Position")
    plt.grid(which='major', color='black', linestyle='--', alpha=0.75)
    plt.grid(which='minor', color='black', linestyle=':', alpha=0.75)
    plt.legend(loc="best",fontsize=10)
    plt.savefig("Bilder/"+beschriftung[k], bbox_inches='tight',dpi=400)
    k += 1


# Reibung.c ist auf mehrere Pendel ausgelegt, der Python plot jedoch nicht
