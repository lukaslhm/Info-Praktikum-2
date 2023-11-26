#pragma once

#include <list>
#include <string>
#include <iostream>

#include "Simulationsobjekt.h"
#include "Tempolimit.h"

class Fahrzeug;

class Weg : public Simulationsobjekt
{
public:
	Weg() = default;
	Weg(std::string initName, double initLaenge, Tempolimit initTempolimit = Tempolimit::Autobahn);
	~Weg();

	static void vKopf();

	void vSimulieren() override;
	void vAusgeben(std::ostream& out) const override;
	void vFahrzeugeAusgeben() const;

	void vAnnahme(std::unique_ptr<Fahrzeug> fzg);
	void vAnnahme(std::unique_ptr<Fahrzeug> fzg, double StartZeit);

	double getTempolimit() const;
	double getLaenge() const;

private:
	double p_dLaenge;
	std::list<std::unique_ptr<Fahrzeug>> p_pFahrzeuge;
	Tempolimit p_eTempolimit;
};

