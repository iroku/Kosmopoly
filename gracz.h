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
	mutable string nazwa;
	int kasa;
	int pozycja;
	int nr_gracza;

public:
	gracz();
	gracz(string, int, int = 15000, int = 0);
	~gracz();
	void nazwij(string n) const;
	bool sprawdz(const gracz *objekt, const string n, const int ilosc);
	string zwroc() const;
	void wyswietl_info() const;
	friend void ruch(gracz &name, const kosci a, const kosci b);
	friend void wyswietl_plansze(const gracz *kto, Pozycja *&p,const int ile_sprawdzic);
	friend void kup(gracz **&kto, Pole *ktore);
	friend Pole sprawdz_pozycje(const gracz kto, const Pole *gdzie);
	friend void wyswietl_pole(const Pole ktore, const gracz &kto);
};

