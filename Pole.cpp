#include "pch.h"
#include "Pole.h"
#include "gracz.h"
#include <string>
#include <fstream>
#include <assert.h>

using namespace std;

Pole::Pole()
{
}

Pole::Pole(int nr, int d, int h, string w)
{
	this->nr_pozycji = nr;
	this->wlasciciel = w;
	fstream plik;
	plik.open("pola.txt", ios::in);

	if (plik.good() == false)
	{
		cout << "Nie uda³o siê otworzyæ pliku." << endl;
	}
	string::size_type sz;
	int nr_linii = (nr) * 4 + 1;
	int aktualny_numer = 1;
	string linia;
	while (getline(plik, linia))
	{
		if (aktualny_numer == nr_linii) nazwa = linia;
		if (aktualny_numer == nr_linii + 1) typ = stoi(linia, &sz);
		if (aktualny_numer == nr_linii + 2) cena = stoi(linia, &sz);
		if (aktualny_numer == nr_linii + 3) kolor = linia;
		aktualny_numer++;
	}
	plik.close();
	switch (typ)
	{
	case 1:
		ilosc_nieruchomosci++;
		break;
	case 2:
		ilosc_kart++;
		break;
	case 3:
		ilosc_akcji++;
		break;
	default:
		assert(!"kod nie powinien tu dojsc");
		system("pause");
	}
}

void Pole::ustaw(int n)
{
	nr_pozycji = n;
}

void Pole::wyswietl()
{
	cout << nazwa;
}

Pole::~Pole()
{
}

int Pole::zwroc_typ() const
{
	return typ;
}

string Pole::zwroc_kolor() const
{
	return kolor;
}

void Pole::kopiuj(const Pole &pole)
{
	nr_pozycji = pole.nr_pozycji;
	nazwa = pole.nazwa;
	typ = pole.typ;
	cena = pole.cena;
	kolor = pole.kolor;
	wlasciciel = pole.wlasciciel;
}