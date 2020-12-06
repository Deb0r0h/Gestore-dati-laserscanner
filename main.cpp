/*
	Gabriel Taormina
	n° 1219622
*/


#include "LaserScannerDriver.h"

using namespace std;

int main()
{
	cout << "primo vettore \n";
	vector<double>v1{ 0.1,0.15,0.13,0.22,0.76,0.99 };
	vector<double>v2{ 1,2,3,4,5,6,7,8,9 };
	LaserScannerDriver laser(0.5);
	cout << "1*****************\n";
	laser.new_scan(v1);
	cout << "prova getdistance()\n";
	laser.get_distance(2);
	cout << "********************\n";
	cout << "prova <<\n";
	cout << laser;
	
	cout << "prova copia\n";
	LaserScannerDriver laser1(1.0);
	laser1 = laser;
	cout << laser1;
	
	cout << "*****************\n";
	LaserScannerDriver laser2 = laser1;
	cout << laser2;
	laser2.clear_buffer();
	cout << "*****************\n";
	vector<double>v0{ 0.1,0.15,0.13,0.22,0.76,0.99 };
	vector<double>v77{ 1,0.1,0.15,0.13,0.22,0.76,0.99 };
	vector<double>v3{2, 0.1,0.15,0.13,0.22,0.76,0.99 };
	vector<double>v4{4, 0.1,0.15,0.13,0.22,0.76,0.99 };
	vector<double>v5{3, 0.1,0.15,0.13,0.22,0.76,0.99 };
	vector<double>v6{2, 0.1,0.15,0.13,0.22,0.76,0.99 };
	vector<double>v7{ 0.1,0.15,0.13,0.22,0.76,0.99 };
	vector<double>v8{1, 0.1,0.15,0.13,0.22,0.76,0.99 };
	vector<double>v9{ 4,0.1,0.15,0.13,0.22,0.76,0.99 };
	vector<double>v10{2, 0.1,0.15,0.13,0.22,0.76,0.99 };
	vector<double>v11{7, 0.1,0.15,0.13,0.22,0.76,0.99 };
	laser1.new_scan(v0);
	laser1.new_scan(v1);
	laser1.new_scan(v2);
	laser1.new_scan(v3);
	laser1.new_scan(v4);
	laser1.new_scan(v5);
	laser1.new_scan(v6);
	laser1.new_scan(v7);
	laser1.new_scan(v8);
	laser1.new_scan(v9);
	laser1.new_scan(v10);
	laser1.new_scan(v0);
	laser1.new_scan(v0);
	laser1.new_scan(v0);
}
