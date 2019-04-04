#pragma once
#include <iostream>
#include <string>
#include "gracz.h"

using namespace std;

class Pole
{
	int nr_pozycji;
	string nazwa;
	int typ;
	int cena;
	string kolor;
	int czynsz;
	int ilosc_domkow;
	int ilosc_hoteli;
	string wlasciciel;

public:
	Pole();
	Pole(int, int = 0, int = 0, string = "brak");
	~Pole();
	void wyswietl();
	void ustaw(int);
	void kup(gracz &kto, Pole *ktore);
	friend Pole sprawdz_pozycje(const gracz kto, const Pole *gdzie);
	friend void wyswietl_pole(const Pole ktore, const gracz &kto);
	friend void wyswietl_pole(const Pole ktore);
};

