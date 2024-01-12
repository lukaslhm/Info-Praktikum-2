#include "Parken.h"
#include "Fahrzeug.h"
#include "Weg.h"
#include "Losfahren.h"

/**
 * Konstruktor für das Verhalten Parken
 *
 * @param initWeg Weg der das Verhalten vorgibt
 * @param initStartZeit Startzeit für das Verhalten
 */
Parken::Parken(Weg& initWeg, double initStartZeit)
	: Verhalten(initWeg), p_dStartZeit(initStartZeit)
{
}

/**
 * Destruktor
 */
Parken::~Parken()
{
}

/**
 * Strecke die das Fahrzeug simuliert werden soll
 *
 * @param aFzg Fahrzeug das simuliert werden soll
 * @param dZeitIntervall Zeit über die das Fahrzeug simuliert werden soll
 * @return Strecke über die das Fahrzeug simuliert werden soll
 */
double Parken::dStrecke(Fahrzeug& aFzg, double dZeitIntervall)
{
	if (dGlobaleZeit < p_dStartZeit) return 0.0;

	//Ausnahme Losfahren
	throw Losfahren(aFzg, p_pWeg);

	return 0;
}
