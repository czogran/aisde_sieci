#pragma once
#include <iostream>
#include<time.h>
#include<math.h>
#include "Segment.h"




queue<Segment> strumien;
queue<Segment>bufor;
float czas = 0;

int max_bufor_size = 30;
float pasmo = 5;
float pasmo_high = 5;
float pasmo_low = 1;

static float time_pasmo = 0;
float time_wrzucanie = 0;
float time_odtwarzanie = 0;





using namespace std;
class Event
{
public:
	enum typ : int
	{
		zmiana_pasma = 0,
		bufor_push = 1,
		bufor_pop=2
	};



};

class Zmiana_Pasma :public Event
{
public:
	double normal(const double &mean, const double &std)
	{
		srand((unsigned)time(NULL));
		static const double pii = 3.1415927;
		static const double r_max = RAND_MAX + 1;
		return std*sqrt(-2 * log((rand() + 1) / r_max))*sin(2 * pii*rand() / r_max) + mean;
	}
	Zmiana_Pasma()
	{
		
		time_pasmo = czas;
	if (czas == 0)
			{
				pasmo = pasmo_high;
			}
		if (normal(0, 1) > 0.5 || normal(0, 1) < -0.5)
		{
			pasmo = pasmo_high;
		}
		else
			pasmo = pasmo_low;

		
	}
};

class Bufor_Push :public Event
{
public:
		Bufor_Push()
	{
			time_wrzucanie = czas;
			
		if (!strumien.empty())
		{
			bufor.push(strumien.front());
			strumien.pop();
		}
	}
};




class Bufor_Pop : public Event
{
public:
	Bufor_Pop()
	{
		time_odtwarzanie = czas;
		if (!bufor.empty())
		{
			bufor.pop();
		}
	}


};