#pragma once
#include <iostream>
#include <string>
#include "gracz.h"

using namespace std;

class gracz;

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
	static short ilosc_nieruchomosci, ilosc_kart, ilosc_akcji;
	void wyswietl();
	void ustaw(int);
	int zwroc_typ() const;
	void kopiuj(const Pole &pole);
	string zwroc_kolor() const;
	friend Pole sprawdz_pozycje(const gracz kto, const Pole *gdzie);
	friend void wyswietl_pole(const Pole ktore, const gracz &kto);
	friend void wyswietl_pole(const Pole ktore);
	friend void pokaz(Pole *const*const pole, const int rozmiar);
	friend void kup(gracz &kto, Pole ktore, Pole **&wolne, const int rozmiar);
	friend void wyswietl_plansze(const gracz *kto, Pole *&p, const int ile_sprawdzic);
	static int zwroc_ilosc_n() { return ilosc_nieruchomosci; }
	static int zwroc_sume_pol() { return ilosc_nieruchomosci + ilosc_akcji + ilosc_kart; }
	friend ostream& operator << (ostream& out, Pole& p);
	friend istream& operator >> (istream& in, Pole& p);
	bool operator != (const Pole& p) const;
	Pole& operator = (const Pole& p);
	Pole& operator[](int index);
};

