#include "pch.h"
#include "gracz.h"
#include <string>

void setCursor(const int x, const int y);

using namespace std;

gracz::gracz():nr_gracza(0)
{

}

gracz::gracz(string n, int nr, int p)
{
	nazwij(n);
	nr_gracza = nr;
	pozycja = p;
	saldo = Saldo();
}

gracz::~gracz()
{
}

void gracz::nazwij(string n) const
{
	nazwa = n;
}

bool gracz::sprawdz(const gracz *objekt, const string n, const int ilosc)
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

void gracz::Saldo::zwroc_saldo() const
{
	cout << "Twoje saldo jest równe: " << pieniadze + wartosc_pol + wartosc_nieruchomosci << "kosmo$$.";
}

void gracz::Saldo::zwroc_pieniadze() const
{
	cout << "Posiadasz " << pieniadze << "kosmo$$.";
}

void gracz::zwroc_saldo() const
{
	saldo.zwroc_saldo();
}

void gracz::zwroc_pieniadze() const
{
	saldo.zwroc_pieniadze();
}

void gracz::wyswietl_info() const
{
	setCursor(115, 2);
	cout << "Tura gracza " << nazwa << ".";
	setCursor(115, 3);
	zwroc_pieniadze();
}
