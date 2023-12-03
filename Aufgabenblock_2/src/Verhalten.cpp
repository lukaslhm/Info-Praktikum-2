#include "Verhalten.h"
#include "Weg.h"
#include "Fahrzeug.h"

/**
 * Konstruktor für das Verhalten
 *
 * @param initWeg Weg der das Verhalten vorgibt
 */
Verhalten::Verhalten(Weg& initWeg)
	: p_pWeg(initWeg)
{
}

/**
 * Destruktor
 */
Verhalten::~Verhalten()
{
}

/**
 * Simuliert das Fahrzeug auf der aktuellen Strecke ohne das Ende der Strecke zu überschreiten
 *
 * @param aFzg Fahrzeug zum simulieren
 * @param dZeitIntervall Zeit in der das Fahrzeug simuliert werden soll
 * @return Strecke zum Simulieren
 */
double Verhalten::dStrecke(Fahrzeug& aFzg, double dZeitIntervall)
{
	if (p_pWeg.getLaenge() - aFzg.getAbschnittStrecke() > aFzg.dGeschwindigkeit() * dZeitIntervall)
	{
		return aFzg.dGeschwindigkeit() * dZeitIntervall;
	}
	else
	{
		return p_pWeg.getLaenge() - aFzg.getAbschnittStrecke();
	}
}

/**
 * Gibt das Tempolimit für den Weg zurück
 * @return Tempolimit für den Weg
 */
double Verhalten::getWegTempolimit() const
{
	return p_pWeg.getTempolimit();
}
