#include "pch.h"
#include "gracz.h"
#include <string>

void setCursor(const int x, const int y);

using namespace std;

gracz::gracz():nr_gracza(0)
{

}

gracz::gracz(string n, int nr, int k, int p)
{
	nazwij(n);
	this->nr_gracza = nr;
	this->kasa = k;
	this->pozycja = p;
}


gracz::~gracz()
{
}

void gracz::nazwij(string n)
{
	nazwa = n;
}

bool gracz::sprawdz(gracz *objekt, string n, int ilosc)
{
	for (int i = ilosc-1; i >= 0; i--)
	{
		if (n != objekt[i].nazwa);
		else
		{
			cout << "Podana nazwa gracza jest juz zajeta. Wybierz inna nazwe." << endl;
			return true;
		}
	}
	return false;
}

string gracz::zwroc() const
{
	return nazwa;
}

void gracz::wyswietl_info() const
{
	setCursor(115, 2);
	cout << "Tura gracza " << nazwa << ".";
	setCursor(115, 3);
	cout << "Posiadasz " << kasa << " kosmo$$.";
}
