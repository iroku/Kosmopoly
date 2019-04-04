#pragma once
#include "gracz.h"

using namespace std;

class gracz;

class kosci
{
	int ilosc_oczek;
public:
	kosci();
	~kosci();
	void rzut();
	bool sprawdz_dublet(kosci, kosci);
	int zwroc() const;
	friend void ruch(gracz &name, kosci a, kosci b);
};

