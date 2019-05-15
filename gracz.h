#pragma once
#include <iostream>
#include "kosci.h"
#include "Pole.h"

using namespace std;

class Pozycja;
class kosci;
class Karty_akcji;
class Pole;

class gracz
{
	mutable string nazwa;
	class Saldo
	{
		int pieniadze;
		int wartosc_pol;
		int wartosc_nieruchomosci;
	public:
		Saldo(int p = 15000, int wp = 0, int wn = 0) : pieniadze(p), wartosc_pol(wp), wartosc_nieruchomosci(wn) {}
		void zwroc_saldo() const;
		void zwroc_pieniadze() const;
	};
	Saldo saldo;
	int pozycja;
	int nr_gracza;
	Pole **posiadane_pola;

public:
	gracz();
	gracz(string, int, int = 0);
	~gracz();
	void nazwij(string n) const;
	bool sprawdz(const gracz *objekt, const string n, const int ilosc);
	string zwroc() const;
	void wyswietl_info() const;
	friend void ruch(gracz &name, const kosci a, const kosci b);
	friend void wyswietl_plansze(const gracz *kto, Pole *&p,const int ile_sprawdzic);
	friend Pole sprawdz_pozycje(const gracz kto, const Pole *gdzie);
	friend void wyswietl_pole(const Pole ktore, const gracz &kto);
	friend void kup(gracz &kto, Pole ktore, Pole **&wolne, const int rozmiar);
	void zwroc_saldo() const;
	void zwroc_pieniadze() const;
};

