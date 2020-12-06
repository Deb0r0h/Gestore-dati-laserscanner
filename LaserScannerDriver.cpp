/*
	Gabriel Taormina
	n° 1219622
*/


#include "LaserScannerDriver.h"
using namespace std;


LaserScannerDriver::LaserScannerDriver(double r)
{

	if (r < 0.1 || r>1)
	{
		cout << "Risoluzione angolare inserita non valida\n";
		throw RisoluzioneNonValida{};
	}

	resolution = r;
	const int n_val = get_n_val();
	buffer = new double* [BUFFER_DIM];
	for (int i = 0; i < BUFFER_DIM; i++)
		buffer[i] = new double[n_val];
}

//costruttore di copia

LaserScannerDriver::LaserScannerDriver(const LaserScannerDriver& arg)
	: index_buffer{ arg.index_buffer }, index_free{ arg.index_free }, n_scan{ arg.n_scan }
{
	double** p = new double* [arg.BUFFER_DIM];
	resolution = arg.resolution;
	for (int i = 0; i < BUFFER_DIM; i++)
	{
		p[i] = new double[get_n_val()];
		for (int j = 0; j < get_n_val(); j++)
		{
			p[i][j] = arg.buffer[i][j];
		}
	}
	buffer = p;
}


//distruttore
LaserScannerDriver::~LaserScannerDriver()
{
	if (buffer == nullptr)
		return;

	for (int i = 0; i < BUFFER_DIM; i++)
	{
		delete[] buffer[i];
		buffer[i] = nullptr;
	}
	delete[] buffer;
}


//costruttore move
LaserScannerDriver::LaserScannerDriver(LaserScannerDriver&& arg)
	:resolution{ arg.resolution }, index_buffer{ arg.index_buffer }, index_free{ arg.index_free }, n_scan{ arg.n_scan }
{
	buffer = arg.buffer;
	arg.buffer = nullptr;
}


//assegnamento copia
LaserScannerDriver& LaserScannerDriver::operator=( LaserScannerDriver& arg)
{
	for (int i = 0; i < BUFFER_DIM; i++)
	{
		for (int j = 0; j < get_n_val(); j++)
		{
			buffer[i][j] = arg.buffer[i][j];
		}
	}
	index_buffer = arg.index_buffer;
	index_free = arg.index_free;
	n_scan = arg.n_scan;
	return *this;
}



//assegnamento move
LaserScannerDriver& LaserScannerDriver::operator=(LaserScannerDriver&& arg)
{
	delete[]buffer;
	index_buffer = arg.index_buffer;
	index_free = arg.index_free;
	n_scan = arg.n_scan;
	buffer = arg.buffer;
	arg.buffer = nullptr;
	arg.index_buffer = 0;
	arg.index_free = 0;
	arg.n_scan = 0;
	arg.resolution = 0;
	return *this;
}




int LaserScannerDriver::get_n_val()const
{
	const int numero_valori = ((int)180 / resolution)+1;
	return numero_valori;
}

void LaserScannerDriver::new_scan(vector<double>&v)
{
	for (int i = 0; i < get_n_val(); i++)
	{
		double l = 0;
		if (v.size() > i)
			l = v[i];
		buffer[index_free][i] = l;
	}
	index_update();
}





void LaserScannerDriver::index_update()
{
	if (n_scan == 10)
	{
		index_buffer = (index_buffer + 1) % BUFFER_DIM;
		index_free = (index_free + 1) % BUFFER_DIM;
		return;
	}
	index_free = (index_free + 1) % BUFFER_DIM;
	n_scan++;


}
void LaserScannerDriver::index_remove()
{
	index_buffer = (index_buffer + 1) % BUFFER_DIM;
	n_scan--;
}


//ritorna la lettura più vecchia del sensore e rimuove dal buffer
vector<double> LaserScannerDriver::get_scan()
{
	if (n_scan == 0)
	{
		cout << "Impossibile ritonare una lettura, il buffer è vuoto\n";
		throw BufferVuoto{};
	}
	vector<double>v;
	for (int i = 0; i < get_n_val(); i++)
	{
		v.push_back(buffer[index_buffer][i]);
	}
	index_remove();
	return v;
}


//elimina tutte le letture salvate
void LaserScannerDriver::clear_buffer()
{
	for (int i = 0; i < BUFFER_DIM; i++)
	{
		delete[] buffer[i];
		buffer[i] = nullptr;
	}
	index_buffer = 0;
	index_free = 0;
	n_scan = 0;
}

//dato un angolo ritorna valore di distanza nella scansione più recente
/*
Nel caso in cui l'angolo non rientri nell'ordine della risoluzione angolare inserita
vado  a confrontare se il primo numero dopo la virgola ottenuto dal rapporto tra l'angolo inserito e la risoluione
è maggiore di 5, in tal caso arrotondo per eccesso all'intero più vicino,altrimenti per difetto
considerando solo la parte intera.

*/
double LaserScannerDriver::get_distance(double a)const
{
	double lettura = 0;
	int index = 0;
	int intero = (int)a;
	double decimale = (a - intero) * 10;

	if (decimale > 5)
		index = (int)((intero / resolution) + 1);
	else
		index = (int)(intero / resolution);
	lettura = buffer[index_free-1][index];
	cout << lettura << endl;
	return lettura;
}


vector<double> LaserScannerDriver::last_scan()const
{
	vector<double>last;
	if (n_scan == 0)
	{
		cout << "Buffer vuoto\n";
		throw BufferVuoto{};
	}
	for (int i = 0; i < get_n_val(); i++)
		last.push_back(buffer[index_free-1][i]);
	return last;
}

ostream& operator<<(std::ostream& os, LaserScannerDriver& scanner)
{
	
	vector<double>last = scanner.last_scan();
	for (int i = 0; i < last.size(); i++)
		os << "Lettura " << i << ":" << " " << last[i] << " " << endl;
	return os;
}
