#pragma once

extern double dGlobaleZeit;

class Weg;
class Fahrzeug;

class Verhalten
{
public:
	Verhalten(Weg& initWeg);
	virtual ~Verhalten();

	virtual double dStrecke(Fahrzeug& aFzg, double dZeitIntervall) = 0;

	double getWegTempolimit() const;

protected:
	Weg& p_pWeg;
};

