#pragma once

extern double dGlobaleZeit;

class Weg;
class Fahrzeug;

class Verhalten
{
public:
	///Konstruktor für die Klasse Verhalten
	Verhalten(Weg& initWeg);
	///Destruktor
	virtual ~Verhalten();

	///Strecke die das Fahrzeug im Simulationsschritt fährt
	virtual double dStrecke(Fahrzeug& aFzg, double dZeitIntervall) = 0;

	///Rückgabe des Tempolimits für den Weg
	double getWegTempolimit() const;

protected:
	Weg& p_pWeg;
};

