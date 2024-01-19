#include <iostream>

#include "Fahrzeug.h"
#include "Weg.h"
#include "Streckenende.h"

/**
 * Konstruktor für die Ausnahme Streckenende, wird benutzt wenn ein Fahrzeug am Ende von einem Weg angekommen ist.
 *
 * @param initFzg Fahrzeug auf das die Ausnahme angewendet werden soll
 * @param initWeg Weg auf dem sich das Fahrzeug befindet
 */
Streckenende::Streckenende(Fahrzeug& initFzg, Weg& initWeg)
	: Fahrausnahme(initFzg, initWeg)
{
}

/**
 * Destruktor für die Ausnahme Streckenende
 */
Streckenende::~Streckenende()
{
}

/**
 * Funktion um das Verhalten vom Fahrzeug beim Auftreten der Ausnahme zu ändern.
 * Wenn das Fahrzeug am Ende vom Weg angekommen ist wird es vom Weg entfernt.
 *
 */
void Streckenende::vBearbeiten()
{
	std::cout << "Streckenende-Ausnahme bei: " << std::endl;
	Fahrzeug::vKopf();
	std::cout << p_pFahrzeug << std::endl;

	p_pWeg.pAbgabe(p_pFahrzeug);
}
