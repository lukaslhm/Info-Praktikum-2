#include <iostream>

#include "Fahrzeug.h"
#include "Weg.h"
#include "Streckenende.h"

Streckenende::Streckenende(Fahrzeug& initFzg, Weg& initWeg)
	: Fahrausnahme(initFzg, initWeg)
{
}

Streckenende::~Streckenende()
{
}

void Streckenende::vBearbeiten()
{
	std::cout << "Streckenende-Ausnahme bei: " << std::endl;
	Fahrzeug::vKopf();
	std::cout << p_pFahrzeug << std::endl;
	std::cout << "auf dem Weg: " << std::endl;
	Weg::vKopf();
	std::cout << p_pWeg;
	std::cout << std::endl << std::endl;

	p_pWeg.pAbgabe(p_pFahrzeug);
}
