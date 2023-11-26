#pragma once

#include <cmath>

#include "Fahrzeug.h"

class Fahrrad : public Fahrzeug
{
public:
	Fahrrad();
	Fahrrad(std::string initName, double initMaxVelo = 0);
	~Fahrrad();

	double dGeschwindigkeit() const override;

	void vAusgeben(std::ostream& out) const override;

	void vZeichnen(const Weg& weg) override;
};
