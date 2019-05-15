#include "pch.h"
#include "gracz.h"
#include "kosci.h"
#include "Pole.h"
#include <windows.h>
#include <time.h>
#include <random>
#include <string>
#include <iostream>
#include <assert.h>

using namespace std;

void setCursor(const int x, const int y)
{
	COORD c;
	c.X = x - 1;
	c.Y = y - 1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
namespace utworz
{
	void utworz_graczy(gracz *&objekt, int &ilosc)
	{
		string nazwa;
		ilosc = 2;
		bool unikalnosc_nazwy;
		cout << "Wybierz ilosc graczy (min 2, max 6): ";
		do
		{
			cin >> ilosc;
			if (ilosc < 2 || ilosc > 6) cout << "Podano zla ilosc graczy, minimalna ilosc to 2 a, maksymalna to 6.\nWybierz ponownie ilosc:";
		} while (ilosc < 2 || ilosc > 6);
		objekt = new gracz[ilosc];
		for (int i = 0; i < ilosc; i++)
		{
			unikalnosc_nazwy = true;
			while (unikalnosc_nazwy == true)
			{
				cout << "Podaj nazwe " << i + 1 << "-ego gracza: ";
				cin >> nazwa;
				unikalnosc_nazwy = objekt[i].sprawdz(objekt, nazwa, i);
			}
			objekt[i] = gracz(nazwa, i + 1);
		}

	}
}
namespace wczytaj
{

}
void przydziel_pola(Pole *&objekt)
{
	objekt = new Pole[40];
	for (int i = 0; i < 40; i++)
	{
		objekt[i] = Pole(i);
	}
}

void ruch(gracz &name, const kosci a, const kosci b)
{
	name.pozycja = (name.pozycja+(a.ilosc_oczek + b.ilosc_oczek)) % 40;
}

void wyswietl_plansze(const gracz *kto, Pole *&p,const int ile_sprawdzic)
{
	string g[6];
	for (int j = 0; j < 40; j++)
	{
		for (int k = 0; k < 6; k++)
		{
			g[k] = " ";
		}
		for (int i = 0; i < ile_sprawdzic; i++)
		{
			if (kto[i].pozycja == p[j].nr_pozycji)
			{
				g[i] = i + 1;
			}
		}
		if (j < 11)
		{
			setCursor(1 + (j * 10), 1);
			cout << "  _______ ";
			setCursor(1 + (j * 10), 2);
			cout << " | " << g[0] << " " << g[1] << " " << g[2] << " | ";
			setCursor(1 + (j * 10), 3);
			cout << " | " << g[3] << " " << g[4] << " " << g[5] << " | ";
			setCursor(1 + (j * 10), 4);
			cout << " |_______| ";
		}
		if (j>10 && j<21)
		{
			int i = 11;
			setCursor(101, 5 + ((j - i) * 4));
			cout << "  _______ ";
			setCursor(101, 6 + ((j - i) * 4));
			cout << " | " << g[0] << " " << g[1] << " " << g[2] << " | ";
			setCursor(101, 7 + ((j - i) * 4));
			cout << " | " << g[3] << " " << g[4] << " " << g[5] << " | ";
			setCursor(101, 8 + ((j - i) * 4));
			cout << " |_______| ";
			i++;
		}
		if (j > 20 && j < 31)
		{
			int i = 21;
			setCursor(91 - (10 * (j - i)), 41);
			cout << "  _______ ";
			setCursor(91 - (10 * (j - i)), 42);
			cout << " | " << g[0] << " " << g[1] << " " << g[2] << " | ";
			setCursor(91 - (10 * (j - i)), 43);
			cout << " | " << g[3] << " " << g[4] << " " << g[5] << " | ";
			setCursor(91 - (10 * (j - i)), 44);
			cout << " |_______| ";
			i++;
		}
		if (j > 30 && j < 40)
		{
			int i = 31;
			setCursor(1, 37 - (4 * (j - i)));
			cout << "  _______ ";
			setCursor(1, 38 - (4 * (j - i)));
			cout << " | " << g[0] << " " << g[1] << " " << g[2] << " | ";
			setCursor(1, 39 - (4 * (j - i)));
			cout << " | " << g[3] << " " << g[4] << " " << g[5] << " | ";
			setCursor(1, 40 - (4 * (j - i)));
			cout << " |_______| ";
			i++;
		}
	}
	setCursor(32, 19);
	cout << "     ___   __          ___   ___   ___           ";
	setCursor(32, 20);
	cout << "|   |   | |    |\\  /| |   | |   | |   | |   \\   /";
	setCursor(32, 21);
	cout << "| / |   | |    | \\/ | |   | |   | |   | |    \\ / ";
	setCursor(32, 22);
	cout << "|/  |   | |__  |    | |   | |___| |   | |     |  ";
	setCursor(32, 23);
	cout << "|\\  |   |    | |    | |   | |     |   | |     |  ";
	setCursor(32, 24);
	cout << "| \\ |___| ___| |    | |___| |     |___| |____ |  ";
	setCursor(1, 46);
}

Pole sprawdz_pozycje(const gracz kto, const Pole *gdzie)
{
	for (int i = 0; i < 40; i++)
	{
		if (kto.pozycja == gdzie[i].nr_pozycji)
		{
			return gdzie[i];
		}
	}
	return 0;
}

void wyswietl_pole(const Pole ktore)
{
	setCursor(115, 4);
	cout << "Pole na ktorym stoisz to: " << ktore.nazwa;
}

void wyswietl_pole(const Pole ktore, const gracz &kto)
{
	int wybor;
	setCursor(115, 7);
	cout << "Pole na ktorym stoisz to: " << ktore.nazwa;
	if (ktore.typ == 1)
	{
		if (ktore.wlasciciel == "brak")
		{
			setCursor(115, 8);
			cout << "Nikt jeszcze nie posiada tego pola wiec mozesz je kupic";
			setCursor(115, 9);
			cout << "Jego cena to: " << ktore.cena << "kosmo$$.";
			setCursor(115, 10);
			cout << "Wprowadz 1 - aby kupic pole.";
			setCursor(115, 11);
			cout << "Wprowadz 2 - aby przejsc dalej.";
			setCursor(115, 12);
			cout << "Twoj wybor:";
			cin >> wybor;
			switch (wybor)
			{
			case 1:
				break;
			case 2:

				break;
			default:
				;
			}

		}
		else
		{
			if (ktore.wlasciciel == kto.nazwa)
			{
				setCursor(115, 8);
				cout << "Jestes wlascicielem tego pola";
			}
			else
			{
				setCursor(115, 8);
				cout << "Jego wlasciciel to: " << ktore.wlasciciel;
			}
		}
	}
}

/*void stworz(Pole ***&pole, const int rozmiar, const int *rozmiar_kol)
{
	pole = new Pole**[rozmiar];
	for (int i = 0; i < rozmiar; i++)
	{
		pole[i] = new Pole*[rozmiar_kol[i]];
		for (int j = 0; j < rozmiar_kol[i]; j++) pole[i][j] = new Pole;
	}
}

void dodaj(Pole ***&pole, int &rozmiar, int *&rozmiar_kol, int ktory)
{

	Pole ***b = new Pole**[rozmiar];
	for (int i = 0; i < rozmiar; i++)
	{
		b[i] = new Pole*[rozmiar_kol[i] + 1];
		for (int j = 0; j < rozmiar + 1; j++)
		{
			b[i][j] = new Pole;
			if (i == rozmiar || j == rozmiar) b[i][j]->ustaw(i);
			else b[i][j] = pole[i][j];
			if (i < rozmiar) delete[] pole[i][j];
		}
		if (i < rozmiar) delete[] pole[i];
	}
	delete[] pole;
	pole = b;
	++rozmiar;
}

void kasuj(Pole ***&pole, int &rozmiar)
{
	if (rozmiar > 0)
	{
		Pole ***b = new Pole**[rozmiar - 1];
		for (int i = 0; i < rozmiar - 1; i++)
		{
			b[i] = new Pole*[rozmiar - 1];
			for (int j = 0; j < rozmiar - 1; j++)
			{
				b[i][j] = new Pole;
				b[i][j] = pole[i][j];
				delete[] pole[i][j];
			}
			delete[] pole[i];
		}
		delete[] pole[rozmiar - 1];
		delete[] pole;
		pole = b;
		--rozmiar;
	}
	else cout << "Tablica zostala usunieta." << endl;
}

void zainicjuj(Pole *const*const*const pole, Pole *const pola, const int rozmiar, const int *rozmiar_kol)
{
	for (int k = 0; k < 40; k++) 
	{
		if (pola[k].zwroc_typ() == 2)
		{
			for (int l = 0; l < rozmiar; l++)
			{
				for (int i = 0; i < rozmiar; i++)
				{
					if (pole[i][0]->zwroc_kolor() == pola[k].zwroc_kolor())
					{
					
					}
					else
					{
						pole[l][0]->kopiuj(pola[k]);
					}
				}
			}
		}
	}
}

void pokaz(Pole *const*const*const pole, const int rozmiar)
{
	int i, j;
	for (i = 0; i < rozmiar; i++)
	{
		for (j = 0; j < rozmiar; j++)
		{
			pole[i][j]->wyswietl();
			cout << "\t";
		}
		cout << endl;
	}
}

void usun(Pole ***&pole, int rozmiar)
{
	for (int i = 0; i < rozmiar; i++)
	{
		for (int j = 0; j < rozmiar; j++) delete[] pole[i][j];
		delete[] pole[i];
	}
	delete[] pole;
	pole = nullptr;
}
*/

void stworz(Pole **&pole, const int rozmiar)
{
	pole = new Pole*[rozmiar];
	for (int i = 0; i < rozmiar; i++)
	{
		pole[i] = new Pole;
	}
}

void zainicjuj(Pole *const*const & pole, Pole *const pola, const int rozmiar)
{
	int i = 0;
	for (int k = 0; k < 40; k++)
	{
			if (pola[k].zwroc_typ() == 1)
			{
				pole[i]->kopiuj(pola[k]);
				i++;
			}
	}
}

void zamien(Pole **&pole, int ktore, const int rozmiar)
{
	Pole *p;
	for (int i = 0; i < rozmiar - 1; i++)
	{

		if (i >= ktore)
		{
			p = pole[i];
			pole[i] = pole[i + 1];
			pole[i + 1] = p;
		}
	}
}

void kasuj(Pole **&pole, int &rozmiar)
{
	if (rozmiar > 0)
	{
		Pole **b = new Pole*[rozmiar - 1];
		for (int i = 0; i < rozmiar - 1; i++)
		{
			b[i] = new Pole;
			b[i] = pole[i];
		}
		delete[] pole;
		pole = b;
		rozmiar--;
	}
	else cout << "Tablica zostala usunieta." << endl;
}

void pokaz(Pole *const*const pole, const int rozmiar)
{
	setCursor(2, 47);
	cout << "Wolne pola:" << endl;
	for (int i = 0; i < rozmiar; i++)
	{
		cout << *pole[i] << endl;
	}
}

void kup(gracz &kto, Pole **&wolne, int &rozmiar)
{
	zamien(wolne, 5, rozmiar);
	kasuj(wolne, rozmiar);
}

short Pole::ilosc_nieruchomosci = 0;
short Pole::ilosc_kart = 0;
short Pole::ilosc_akcji = 0;

ostream& operator << (ostream& out, Pole& p) 
{
	out << p.nazwa << endl;
	out << p.cena << "kosmo$$" << endl;
	out << p.kolor << endl;
	return out;
}

istream& operator >> (istream& in, Pole& p)
{
	in >> p.nazwa;
	in >> p.cena;
	in >> p.kolor;
	return in;
}

bool Pole::operator != (const Pole& p) const
{
	if (nazwa != p.nazwa) return true;
	return false;
}

Pole& Pole::operator = (const Pole& p)
{
	if (&p != this)
	{
		nr_pozycji = p.nr_pozycji;
		nazwa = p.nazwa;
		typ = p.typ;
		cena = p.cena;
		kolor = p.kolor;
	}
	return *this;
}

Pole& Pole::operator [] (int index)
{
	assert(0 <= index && index < Pole::zwroc_sume_pol());
	for (int i = 0; i < Pole::zwroc_sume_pol(); i++)
	{
		if (nr_pozycji == i) return *this;
	}
}

int main()
{
	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
	gracz *gracze;
	kosci kosc1, kosc2;
	Pole *pola, **wolne;

	int rozmiar = 28;
	// int rozmiar_kol[10]{ 1 };
	int wybor;
	int ilosc_graczy;
	bool petla_programu = true;
	bool warunek_zwyciestwa = false;
	srand(time(NULL));
	while (petla_programu == true)
	{
		cout << "MENU GLOWNE:\nWprowadz 1 - Nowa Gra\nWprowadz 2 - Wczytaj Gre\nWprowadz 3 - Wyjscie z programu" << endl;
		cin >> wybor;
		switch (wybor)
		{
		case 1:
			utworz::utworz_graczy(gracze, ilosc_graczy);
			przydziel_pola(pola);
			stworz(wolne, rozmiar);
			zainicjuj(wolne, pola, rozmiar);
			cin.clear();
			cin.ignore(1, '\n');
			while (warunek_zwyciestwa == false)
			{
			for (int i = 0; i < ilosc_graczy; i++)
			{
				system("cls");
				wyswietl_plansze(gracze, pola, ilosc_graczy);
				pokaz(wolne, rozmiar);
				gracze[i].wyswietl_info();
				wyswietl_pole(sprawdz_pozycje(gracze[i], pola));
				setCursor(115, 5);
				cout << "Wcisnij dowolny klawisz aby dokonac rzutu koscmi:";
				cin.get();
				kosc1.rzut();
				kosc2.rzut();
				ruch(gracze[i], kosc1, kosc2);
				system("cls");
				wyswietl_plansze(gracze, pola, ilosc_graczy);
				pokaz(wolne, rozmiar);
				gracze[i].wyswietl_info();
				setCursor(115, 5);
				cout << "Wyrzucona ilosc oczek to " << kosc1.zwroc() << " i " << kosc2.zwroc() << ".";
				wyswietl_pole(sprawdz_pozycje(gracze[i], pola), gracze[i]);
				setCursor(115, 14);
				cout << "Wprowadz 1 - aby wyswietlic posiadane pola.";
				setCursor(115, 15);
				cout << "Wprowadz 2 - aby zakonczyc ture.";
				setCursor(115, 16);
				cout << "Twoj wybor:";
				cin >> wybor;
				switch (wybor)
				{
				case 1:
					break;
				case 2:
					break;
				default:
					;
				}
			}
			}
			system("pause");
			return 0;
			break;
		case 2:
			break;
		case 3:
			petla_programu = false;
			break;
		default:
			system("cls");
			break;
		}
	}
system("pause");
return 0;
}

