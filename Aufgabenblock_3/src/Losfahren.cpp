#include <iostream>

#include "Losfahren.h"

#include "Fahrzeug.h"
#include "Weg.h"

/**
 * Konstruktor für die die Ausnahme Losfahren
 *
 * @param initFzg Fahrzeug auf das die Ausnahme angewendet werden soll
 * @param initWeg Weg auf den die Ausnahme angewendet werden soll
 */
Losfahren::Losfahren(Fahrzeug& initFzg, Weg& initWeg)
	: Fahrausnahme(initFzg, initWeg)
{
}

/**
 * Destruktor
 */
Losfahren::~Losfahren()
{
}
/**
 * Bearbeiten der Eigenschaften vom Fahrzeug beim Aufruf der Ausnahme
 * Fahrzeug fährt nach dem Ausführen
 */
void Losfahren::vBearbeiten()
{
	std::cout << "Losfahren-Ausnahme bei: " << std::endl;
	std::cout << p_pFahrzeug.getName() << std::endl;
	std::cout << "Startzeit: " << dGlobaleZeit << std::endl;
	std::cout << "Startpunkt: " << p_pFahrzeug.getAbschnittStrecke() << std::endl;

	p_pWeg.vAnnahme(p_pWeg.pAbgabe(p_pFahrzeug));
}
