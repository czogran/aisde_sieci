#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<iostream>
#include<fstream>
#include<time.h>
#include<vector>
#include<queue>

#include"Segment.h"
#include"Event.h"


using namespace std;



double losuj_pasmo(int czas)
{
	return (int)((rand() % 11 + 20) + czas);
}

double losuj_pakiet()
{
	float x = ((rand()%10));
	return x/50;
}

bool sortuj(Event x, Event y)
{
	return x.czas < y.czas;
}


int main()
{
	fstream pasmo_dane;
	fstream bufor_dane;
	vector<Event> zdarzenia;
	queue<Segment> strumien;
	float bufor=0;

	pasmo_dane.open("pasmo.txt", ios::in | ios::out | ios::trunc);
	bufor_dane.open("bufor.txt", ios::in | ios::out | ios::trunc);
	srand((unsigned)time(NULL));
	float czas_rozpoczecia = 0;
	float czas_chwilowy = 0;
	const int packet_size = 2;

	for (int i = 0;i <300;i++)
	{
		strumien.push(Segment(1, 2, 2 * i, i));
	}

	Event zmiana_pasma(losuj_pasmo(czas_chwilowy), "zmiana pasma");
	zdarzenia.push_back(zmiana_pasma);
	
	Event bufor_push(czas_chwilowy + (packet_size / pasmo), "bufor push");
	zdarzenia.push_back(bufor_push);
	
	bufor_dane << czas_chwilowy << "	" << bufor  << "\n";
	pasmo_dane << czas_chwilowy << "	" << pasmo << "\n";

	while (czas_chwilowy < 300)
	{
		sort(zdarzenia.begin(), zdarzenia.end(), sortuj);
		Event event = zdarzenia.front();

		if (event.typ == "bufor push")
			czas_rozpoczecia = czas_chwilowy;

		czas_chwilowy = event.czas;

		if (event.typ == "zmiana pasma")
		{
			if (pasmo == pasmo_high)
			{
				pasmo = pasmo_low;
			}
			else pasmo = pasmo_high;
			Event zmiana_pasma(losuj_pasmo(czas_chwilowy), "zmiana pasma");
			zdarzenia.push_back(zmiana_pasma);
		}
		else if (event.typ == "bufor push")
		{
			Event bufor_push(czas_chwilowy + (packet_size / pasmo) + losuj_pakiet(), "bufor push");
			zdarzenia.push_back(bufor_push);
			if(bufor < 30)		bufor++;
			if (bufor > 0)		bufor = bufor - (czas_chwilowy - czas_rozpoczecia);
				
		}

		bufor_dane << czas_chwilowy << "	" << bufor  << "\n";
		pasmo_dane << czas_chwilowy << "	" << pasmo << "\n";
		zdarzenia.erase(zdarzenia.begin());
		
	}



	bufor_dane.close();
	pasmo_dane.close();

	system("gnuplot -p -e \"plot 'bufor.txt' with linespoints ls 1 title 'Bufor[s]','pasmo.txt' with linespoints ls 0.6 title 'Pasmo[Mbps]'\"");
	return 0;
}