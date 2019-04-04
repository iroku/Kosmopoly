#include "pch.h"
#include "gracz.h"
#include "kosci.h"
#include "Pozycja.h"
#include "Pole.h"
#include <windows.h>
#include <time.h>
#include <random>
#include <string>
#include <iostream>

using namespace std;

void setCursor(const int x, const int y)
{
	COORD c;
	c.X = x - 1;
	c.Y = y - 1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

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
		objekt[i] = gracz(nazwa, i+1);
	}
	
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

void wyswietl_plansze(const gracz *kto, Pozycja *&p,const int ile_sprawdzic)
{
	p = new Pozycja[40];
	string g[6];
	for (int j = 0; j < 40; j++)
	{
		p[j] = Pozycja(j);
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
	delete[] p;
}

Pole sprawdz_pozycje(const gracz kto,const Pole *gdzie)
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

void stworz(Pole ***&pole, const int rozmiar)
{
	pole = new Pole**[rozmiar];
	for (int i = 0; i < rozmiar; i++)
	{
		pole[i] = new Pole*[rozmiar];
		for (int j = 0; j < rozmiar; j++) pole[i][j] = new Pole;
	}
}

void dodaj(Pole ***&pole, int &rozmiar)
{

	Pole ***b = new Pole**[rozmiar + 1];
	for (int i = 0; i < rozmiar + 1; i++)
	{
		b[i] = new Pole*[rozmiar + 1];
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

void zainicjuj(Pole *const*const*const pole, const int rozmiar)
{
	for (int i = 0; i < rozmiar; i++)
		for (int j = 0; j < rozmiar; j++) pole[i][j]->ustaw(i);
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

int main()
{
	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
	gracz *gracze;
	kosci kosc1, kosc2;
	Pozycja *plansza;
	Pole *pola, ***wolne;
	int rozmiar = 6;
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
			utworz_graczy(gracze, ilosc_graczy);
			przydziel_pola(pola);
			cin.clear();
			cin.ignore(1, '\n');
			while (warunek_zwyciestwa == false)
			{
			for (int i = 0; i < ilosc_graczy; i++)
			{
				system("cls");
				wyswietl_plansze(gracze, plansza, ilosc_graczy);
				gracze[i].wyswietl_info();
				wyswietl_pole(sprawdz_pozycje(gracze[i], pola));
				setCursor(115, 5);
				cout << "Wcisnij dowolny klawisz aby dokonac rzutu koscmi:";
				cin.get();
				kosc1.rzut();
				kosc2.rzut();
				ruch(gracze[i], kosc1, kosc2);
				system("cls");
				wyswietl_plansze(gracze, plansza, ilosc_graczy);
				gracze[i].wyswietl_info();
				setCursor(115, 5);
				cout << "Wyrzucona ilosc oczek to " << kosc1.zwroc() << " i " << kosc2.zwroc() << ".";
				wyswietl_pole(sprawdz_pozycje(gracze[i], pola), gracze[i]);
				setCursor(115, 11);
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

