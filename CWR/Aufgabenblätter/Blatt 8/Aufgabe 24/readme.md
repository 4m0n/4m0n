### Amon Pönitzsch

### Ausführen
Alles wie immer -> make run und make plot führt das c sowie das python script aus.

### Infos
- Die Werte werden mit den Werten der Sonne nomiert. Um das Rückgängig zu machen, kann man bei den bennanten Konstanten einfach die entsprechenden Werte wieder zu 1 setzen oder noch einfacher, ganz am Anfang, die Werte aus dem fprintf Befehl nehmen. (ganz oben bei #define)

- Ich fprintfe alle 1000 Schritte um einen sauberen Verlauf zu erhalten.


### Bonus
- Die Temperaturrechnung hat leider nicht so ganz funktioniert. Der erste Fehler liegt wohl schon am Startwert, denn dieser ist 0 (oder nahe 0). Aber auch abgesehen davon, gleicht die Kurve nicht der von Wikipedia (nicht das ich dort nachgeguckt hätte).
  - Wenn man sie evlt um 1e7 verschiebt, könnte der Verlauf Sinn ergeben.
- Zur Druckverteilung bin ich deshalb nicht gekommen.
- Bei der Massenberechnung hat die Masse des Sterns am Ende nur 0.5 der (Wikipedia) Masse der Sonne, was merkwürdig ist, da er nur etwas größer ist und so ein großer Unterschied sehr unlogisch ist
