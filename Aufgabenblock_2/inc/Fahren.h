#pragma once
#include "Verhalten.h"
class Fahren : public Verhalten
{
public:
	///Konstruktor für das Verhalten Fahren
	Fahren(Weg& initWeg);
	///Destruktor
	~Fahren();

	///Strecke die Simuliert werden muss
	double dStrecke(Fahrzeug& aFzg, double dZeitIntervall) override;
};

