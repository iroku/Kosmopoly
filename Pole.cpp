#include "pch.h"
#include "Pole.h"
#include <string>
#include <fstream>
#include "gracz.h"

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

void Pole::kup(gracz &kto, Pole *ktore)
{

}