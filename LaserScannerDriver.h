/*
	Gabriel Taormina
	n° 1219622
*/




#include<iostream>
#include<vector>

class LaserScannerDriver
{
public:

	LaserScannerDriver(double r);

	~LaserScannerDriver();

	LaserScannerDriver(const LaserScannerDriver& arg);

	LaserScannerDriver(LaserScannerDriver&&);

	LaserScannerDriver& operator=( LaserScannerDriver& arg);

	LaserScannerDriver& operator=(LaserScannerDriver&& arg);




	void new_scan(std::vector<double>&v);
	std::vector<double> get_scan();
	void clear_buffer();
	double get_distance(double a)const;
	//restituisce il numero di elementi presenti in ogni scansione in base alla 
	//risoluzione angolare inserita
	int get_n_val()const;
	// fa aumentare di uno la posizione dell'indice dell'ultima scansione
	void index_update();
	//fa diminuire l'indice
	void index_remove();
	//funzione che ritorna in un vettore i valori presenti nell'ultima scansione
	//tale vettore servirà nell'uso dell'overloading dell'operatore <<
	std::vector<double>last_scan()const;

	//eccezione che segnala un valore non appartenente al range della risoluzione
	class RisoluzioneNonValida {};

	//eccezione che segnala se il buffer è vuoto
	class BufferVuoto {};


private:

	//risoluzione del lidar
	double resolution;
	//buffer circolare, inteso come puntatore a puntatore
	double** buffer;
	//dimensione del buffer
	const int BUFFER_DIM = 10;
	//indice corrispondente alla prima scansione nel buffer,aumenterà di 1 una volta riempito tutto il buffer
	int index_buffer = 0;
	//indice corrispondente alla prossima cella libera disponibile per effettuare una scansione
	int index_free = 0;
	//numero che riporta se il numero di scansioni inserite, valore massimo pari a BUFFER_DIM
	int n_scan = 0;


};

//overloading operatore <<
std::ostream& operator<<(std::ostream& os, LaserScannerDriver& scanner);
