#pragma once
#include "Verhalten.h"
class Parken : public Verhalten
{
public:
	Parken(Weg& initWeg, double initStartZeit);
	~Parken();

	double dStrecke(Fahrzeug& aFzg, double dZeitIntervall) override;

private:
	double p_dStartZeit;
};

