#pragma once
#include "Verhalten.h"
class Parken : public Verhalten
{
public:
	///Konstruktor für das Verhalten Parken
	Parken(Weg& initWeg, double initStartZeit);
	///Destruktor
	~Parken();

	///Strecke die das Fahrzeug simuliert werden soll
	double dStrecke(Fahrzeug& aFzg, double dZeitIntervall) override;

private:
	double p_dStartZeit;
};

