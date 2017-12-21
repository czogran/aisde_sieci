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
float pasmo_low = 2;

static float time_pasmo = 0;
float time_wrzucanie = 0;
float time_odtwarzanie = 0;





using namespace std;
class Event
{
public:
	Event(float czas, string typ);
	Event(const Event &z);
	float czas;
	string typ;

};

Event::Event(float czas, string typ)
{
	this->czas = czas;
	this->typ = typ;
}

Event::Event(const Event &z)
{
	czas = z.czas;
	typ = z.typ;
}

double normal(const double &mean, const double &std)
{
	static const double pii = 3.1415927;
	static const double r_max = RAND_MAX + 1;
	return std*sqrt(-2 * log((rand() + 1) / r_max))*sin(2 * pii*rand() / r_max) + mean;
}

	


