#include "Parken.h"
#include "Fahrzeug.h"
#include "Weg.h"
#include "Losfahren.h"

Parken::Parken(Weg& initWeg, double initStartZeit)
	: Verhalten(initWeg), p_dStartZeit(initStartZeit)
{
}

Parken::~Parken()
{
}

double Parken::dStrecke(Fahrzeug& aFzg, double dZeitIntervall)
{
	if (dGlobaleZeit < p_dStartZeit) return 0.0;

	throw Losfahren(aFzg, p_pWeg);

	return 0;
}
