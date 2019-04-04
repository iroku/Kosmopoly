#pragma once
#include "gracz.h"

using namespace std;

class gracz;

class Pozycja
{
	int nr_pozycji;

public:
	Pozycja();
	Pozycja(int);
	~Pozycja();
	friend void wyswietl_plansze(const gracz *kto, Pozycja *&p,const int ile_sprawdzic);
};

