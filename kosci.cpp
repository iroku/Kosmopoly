#include "pch.h"
#include "kosci.h"
#include <cstdlib>
#include <iostream>
using namespace std;

kosci::kosci()
{
	rzut();
}


kosci::~kosci()
{
}

void kosci::rzut()
{
	ilosc_oczek=(rand() % 6 ) + 1;
}

bool kosci::sprawdz_dublet(kosci a,kosci b)
{
	if (a.ilosc_oczek == b.ilosc_oczek) return true;
	else return false;
}

int kosci::zwroc() const
{
	return ilosc_oczek;
}