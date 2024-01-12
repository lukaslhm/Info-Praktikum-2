#pragma once

#include <cmath>

#include "Fahrzeug.h"

class Fahrrad : public Fahrzeug
{
public:
	///Konstruktor ohne Eigenschaften für das Fahrrad
	Fahrrad();
	///Konstruktor mit Name und maximaler Geschwindigkeit
	Fahrrad(std::string initName, double initMaxVelo = 0);
	///Destruktor
	~Fahrrad();

	///Ausgabe der aktuellen Geschwindigkeit
	double dGeschwindigkeit() const override;

	///Ausgabe der Eigenschaften des Fahrrads
	void vAusgeben(std::ostream& out) const override;

	///Zeichnen des Fahrrads auf der GUI
	void vZeichnen(const Weg& weg) override;
};
