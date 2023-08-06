# Gestore dati laserscanner
Modulo C++ per la gestione dei dati provenienti
da un LIDAR. Un LIDAR è un sensore capace di effettuare misurazioni di distanza usando un
fascio laser. Il principio di funzionamento è simile a quello di un metro laser, ma nel caso del lidar
il fascio laser è posto in rotazione e la misurazione è effettuata a intervalli di angolo regolari. Un
LIDAR perciò scandisce un piano nello spazio e riporta le misure di distanza rilevate su quel piano
a intervalli regolari.
Ulteriori dettagli qui:
https://it.wikipedia.org/wiki/Lidar
Tale sensore genera un flusso di dati costituito da un insieme di double che rappresentano le
letture ai vari angoli. L’angolo che separa due letture consecutive prende il nome di risoluzione
angolare è un dato di progetto di ogni LIDAR. Due modelli di LIDAR diversi possono avere
risoluzioni angolari diverse

I LIDAR gestiti hanno un angolo di vista di 180°, quindi un sensore con risoluzione di 
1° fornisce 181 valori per ogni scansione, un sensore con risoluzione di 0.5° fornisce 361 valori 
per ogni scansione, un sensore con risoluzione di 0.25° fornisce 721 valori per ogni scansione, 
ecc. I laserscanner che dovete gestire possono avere una risoluzione compresa tra 1° e 0.1°.
Definiamo lettura il singolo dato, scansione il gruppo di letture consecutive corrispondenti a una 
passata da 0° a 180°.
