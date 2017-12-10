#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<iostream>
#include<fstream>
#include<time.h>


using namespace std;

double normal(const double &mean, const double &std)
{
	static const double pii = 3.1415927;
	static const double r_max = RAND_MAX + 1;
	return std*sqrt(-2 * log((rand() + 1) / r_max))*sin(2 * pii*rand() / r_max) + mean;
}

int main()
{
	std::fstream pasmo_dane;
	pasmo_dane.open("pasmo.txt", ios::in | ios::out | ios::trunc);

	
	int czas = 0;
	int iter = 0;
	int pasmo = 5;
	int pasmo_high = 5;
	int pasmo_low = 2;
	srand((unsigned)time(NULL));

	for (int i = 0; i < 560; i++)
	{
		if (iter == 80)
		{
			if (normal(0, 1) > 0.5 || normal(0, 1) < -0.5)
			{
				pasmo = pasmo_high;
			}
			else
				pasmo = pasmo_low;
			
			iter = 0;
		}
		cout << i << "	" << pasmo << "\n";
		pasmo_dane << i << "	" << pasmo << "\n";
		iter++;
	}
	pasmo_dane.close();
	
	system("gnuplot -p -e \"plot 'bufor.txt' with linespoints ls 6 title 'Bufor[s]','pasmo.txt' with linespoints ls 0.6 title 'Pasmo[Mbps]'\"");
	return 0;
}