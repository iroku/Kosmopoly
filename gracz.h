#pragma once
#include <iostream>
#include "kosci.h"
#include "Pozycja.h"
#include "Pole.h"

using namespace std;

class Pozycja;
class kosci;
class Karty_akcji;
class Pole;

class gracz
{
	string nazwa;
	int kasa;
	int pozycja;
	int nr_gracza;

public:
	gracz();
	gracz(string, int, int = 15000, int = 0);
	~gracz();
	void nazwij(string n);
	bool sprawdz(gracz *objekt, string n, int ilosc);
	string zwroc() const;
	void wyswietl_info() const;
	friend void ruch(gracz &name, kosci a, kosci b);
	friend void wyswietl_plansze(const gracz *kto, Pozycja *&p,const int ile_sprawdzic);
	friend void kup(gracz **&kto, Pole *ktore);
	friend Pole sprawdz_pozycje(gracz kto, Pole *&gdzie);
	friend void wyswietl_pole(const Pole ktore, const gracz &kto);
};

