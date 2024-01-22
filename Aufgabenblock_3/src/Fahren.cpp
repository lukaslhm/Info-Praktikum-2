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
		throw Streckenende(aFzg, p_pWeg); //Exception werfen
	}
	else if (aFzg.getAbschnittStrecke() + tempStrecke > p_pWeg.getVirtuelleSchranke()) //Auf dem Streckenabschnitt ist kein vorrausfahrendes Fahrzeug oder das Fahrzeug ist weit genug entfernt
	{
		tempStrecke = p_pWeg.getVirtuelleSchranke() - aFzg.getAbschnittStrecke();
	}
	else //Vor dem Fahrzeug befindet sich ein Fahrzeug das nicht überholt werden darf
	{
		p_pWeg.setVirtuelleSchranke(aFzg.getAbschnittStrecke() + tempStrecke); //Differenzstrecke zu dem Fahreug
	}

	return tempStrecke;
}
