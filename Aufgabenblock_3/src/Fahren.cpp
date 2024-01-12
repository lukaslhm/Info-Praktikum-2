#include "Fahren.h"
#include "Fahrzeug.h"
#include "Weg.h"
#include "Streckenende.h"

/**
 * Konstruktor für das Verhalten Fahren
 *
 * @param initWeg Weg für das Verhalten
 */
Fahren::Fahren(Weg& initWeg)
	: Verhalten(initWeg)
{
}

/**
 * Destruktor
 */
Fahren::~Fahren()
{
}

/**
 * Strecke die das Fahrzeug simuliert werden soll, das Ende des Wegs soll nicht überschritten werden
 *
 * @param aFzg Fahrzeug das Simuliert werden soll
 * @param dZeitIntervall Zeit für die das Fahrzeug simuliert werden soll
 * @return Strecke die das Fahrzeug zurücklegen soll
 */
double Fahren::dStrecke(Fahrzeug& aFzg, double dZeitIntervall)
{
	double tempStrecke = Verhalten::dStrecke(aFzg, dZeitIntervall);
	if (abs(tempStrecke) < 3 * std::numeric_limits<double>::min()) 
	{ 
		throw Streckenende(aFzg, p_pWeg);
	}
	return tempStrecke;
}
