#include <iostream>

#include "Losfahren.h"

#include "Fahrzeug.h"
#include "Weg.h"

Losfahren::Losfahren(Fahrzeug& initFzg, Weg& initWeg)
	: Fahrausnahme(initFzg, initWeg)
{
}

Losfahren::~Losfahren()
{
}

void Losfahren::vBearbeiten()
{
	std::cout << "Losfahren-Ausnahme bei: " << std::endl;
	Fahrzeug::vKopf();
	std::cout << p_pFahrzeug << std::endl;
	std::cout << "auf dem Weg: " << std::endl;;
	Weg::vKopf();
	std::cout << p_pWeg;
	std::cout << std::endl << std::endl;

	p_pWeg.vAnnahme(p_pWeg.pAbgabe(p_pFahrzeug));
}
