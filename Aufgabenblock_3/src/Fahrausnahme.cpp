#include "Fahrausnahme.h"

/**
 * Konstruktor für Fahrausnahmen
 *
 * @param initFzg Fahrzeug für das die Ausnahmen angewandt werden soll
 * @param initWeg Weg für den die Ausnahme angewandt werden soll
 */
Fahrausnahme::Fahrausnahme(Fahrzeug& initFzg, Weg& initWeg)
	: p_pFahrzeug(initFzg), p_pWeg(initWeg)
{
}

/**
 * Destruktor
 */
Fahrausnahme::~Fahrausnahme()
{
}
