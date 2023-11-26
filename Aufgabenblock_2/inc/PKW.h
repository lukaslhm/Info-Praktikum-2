#pragma once

#include <limits>

#include "Fahrzeug.h"

class PKW : public Fahrzeug
{
public:
	PKW(std::string initName, double initMaxVelo, double initVerbrauch, double initTankvolumen = 55);
	~PKW();

	double dTanken(double dMenge = std::numeric_limits<double>::infinity()) override;
	double dGeschwindigkeit() const override;

	void vSimulieren() override;

	void vAusgeben(std::ostream& out) const override;

private:
	double p_dVerbrauch;
	double p_dTankvolumen;
	double p_dTankinhalt;
};

