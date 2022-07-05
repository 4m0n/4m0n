Amon Pönitzsch
Prüfungsvorleistung2

Die Aufgaben wurden alle in dem File "2dintegral.c" bearbeitet. Um sie aufzurufen muss einfach nur
die entsprechende Funktion aus den Kommentaren genommen werden. Die Plots werden in der Pyhton Datei erstellt.
Der Plot für aufgabe 1 wird mit "make plot1" und der für Aufgabe 3 mit "make plot2" erstellt.


Aufgabe 1)
Ich habe noch 1 weiteren delta_x Wert hinzugefügt um im Plot klarer zu zeigen an welchen Wert sich das Integral annähert.
N (die Schrittanzahl) sollte für x und y unabhängig sein, delta jedoch nicht.
Im Plot wird Delta x nicht mehr richtig angezeigt, kann jedoch in der Konsole (oder im Code) nachgelesen werden.
Auf 2 Nachkommastellen genau war das Ergebnis bei 4 millionen durchläufen (N = 2000, aber da es 2x durchläuft 2k*2k => 4mio, das wurde auch in Aufgabe 3 berücksichtigt).

Aufgab 2)
Die Funktion für Aufgabe 2 (und teils auch 3) habe ich bereits in Aufgabe 13 geschrieben. Das Ergebnis ist Pi (was das Volumen (Flächeninhalt) der Einheitskreis ist).
Das ergibt Sinn, da man mit diesem Verfahren auch genau diese berechnet wird.

Aufgabe 3)
Hier kann man sehen, dass das MC-verfahren wesentlich schlechter ist. Im Plot (wobei Rot das Mittelpunktverfahren und Blau das MC Verfahren darstellt) ist klar zu sehen, wie sich das MP verfahren viel schneller dem richtigen Volumen annähert. Das MC verfahren kann natürlich durch Zufall früher das richtige Volumen anzeigen, allerdings kann man dem natürlich nicht vertrauen.
Das MP verfahren ist sehr viel effizienter und besser wenn es um geringe Dimensionen geht, in höheren ist das MC verfahren besser.

Da ich meine Funktionen aus Aufgabe 13 wiederverwenden wollte, kommt es an manchen Stellen zu code der noch optimiert werden könnte. Dennoch funktioniert alles und ich versuche beim nächsten mal mehr darauf zu achten.



KORREKTUR:
1) Ich lasse die Schleife jetzt von 1 bis einschließlich N laufen.

2)  Ups ja, "mal zwei" und "hoch zwei" sind zwei unterschiedliche Dinge. Ist jetzt behoben und der Plot geht bis 1e7. Man sieht gut, wie auch MP am anfang eine Weile braucht um sich anzunähern, jedoch MC selbst bei 1e7 noch verhältnissmäßig große Abweichungen hat. (Das sieht man am besten bei der Matplot Anwendung bei der man richtig zoomen kann)
Ausserdem haben die Punkte jetzt auch label.

3) ist jetzt auch weg. 
