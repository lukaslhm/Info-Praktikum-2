#pragma once

#include <limits>

#include "Fahrzeug.h"

class PKW : public Fahrzeug
{
public:
	///Konstruktor für den PKW mit Name, maximaler Geschwindigkeit, Verbrauch und Tankvolumen
	PKW(std::string initName, double initMaxVelo, double initVerbrauch, double initTankvolumen = 55);
	///Destruktor
	~PKW();

	///Funktion zum Tanken des PKW um eine bestimmte Menge
	double dTanken(double dMenge = std::numeric_limits<double>::infinity()) override;
	///aktuelle Geschwindigkeit vom PKW
	double dGeschwindigkeit() const override;

	///Simulieren des PKW bis zur aktuellen Zeit
	void vSimulieren() override;

	///Ausgeben der Eigenschaften vom PKW
	void vAusgeben(std::ostream& out) const override;

	///Zeichnen vom PKW in der GUI
	void vZeichnen(const Weg& weg) override;

private:
	///Zusätzliche Eigenschaften vom PKW, neben den Eigenschaften von einem Fahrzeug
	double p_dVerbrauch;
	double p_dTankvolumen;
	double p_dTankinhalt;
};

