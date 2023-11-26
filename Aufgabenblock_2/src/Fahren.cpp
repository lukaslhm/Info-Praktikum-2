#include "Fahren.h"
#include "Fahrzeug.h"
#include "Weg.h"
#include "Streckenende.h"

Fahren::Fahren(Weg& initWeg)
	: Verhalten(initWeg)
{
}

Fahren::~Fahren()
{
}

double Fahren::dStrecke(Fahrzeug& aFzg, double dZeitIntervall)
{
	double tempStrecke = Verhalten::dStrecke(aFzg, dZeitIntervall);
	if (abs(tempStrecke) < 3 * std::numeric_limits<double>::min()) 
	{ 
		throw Streckenende(aFzg, p_pWeg);
	}
	return tempStrecke;
}
