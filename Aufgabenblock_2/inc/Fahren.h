#pragma once
#include "Verhalten.h"
class Fahren : public Verhalten
{
public:
	Fahren(Weg& initWeg);
	~Fahren();

	double dStrecke(Fahrzeug& aFzg, double dZeitIntervall) override;
};

