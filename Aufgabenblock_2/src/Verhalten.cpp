#include "Verhalten.h"
#include "Weg.h"
#include "Fahrzeug.h"

Verhalten::Verhalten(Weg& initWeg)
	: p_pWeg(initWeg)
{
}

Verhalten::~Verhalten()
{
}

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

double Verhalten::getWegTempolimit() const
{
	return p_pWeg.getTempolimit();
}
