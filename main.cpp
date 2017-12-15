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







int main()
{
	fstream pasmo_dane;
	fstream bufor_dane;
	pasmo_dane.open("pasmo.txt", ios::in | ios::out | ios::trunc);
	bufor_dane.open("bufor.txt", ios::in | ios::out | ios::trunc);

	for (int i = 0;i <30;i++)
	{
		strumien.push(Segment(1, 2, 2 * i, i));
	}
	
	while (czas < 30)
	{
		//if (czas == 0 || czas-time_pasmo == 80)
		//{
			Zmiana_Pasma();
			
		//}

		if (bufor.size() <max_bufor_size/2 )
		{
			if (pasmo == pasmo_high && czas - time_wrzucanie == 1 || pasmo == pasmo_low && czas - time_wrzucanie == 3 || czas == 0)
			{
				Bufor_Push();
				
			}
		}
		if (czas - time_odtwarzanie == 2)
		{
			Bufor_Pop();
			
			
		}
		bufor_dane << czas << "	" << bufor.size() * 2 << "\n";
		pasmo_dane << czas << "	" << pasmo << "\n";
		czas++;
	}



	bufor_dane.close();
	pasmo_dane.close();

	system("gnuplot -p -e \"plot 'bufor.txt' with linespoints ls 6 title 'Bufor[s]','pasmo.txt' with linespoints ls 0.6 title 'Pasmo[Mbps]'\"");
	return 0;
}