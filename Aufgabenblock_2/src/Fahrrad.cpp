#include "Fahrrad.h"
#include "Weg.h"
#include "SimuClient.h"

Fahrrad::Fahrrad()
{
}

Fahrrad::Fahrrad(std::string initName, double initMaxVelo)
	: Fahrzeug(initName, initMaxVelo)
{
}

Fahrrad::~Fahrrad()
{
}

double Fahrrad::dGeschwindigkeit() const
{
	if (p_dMaxGeschwindigkeit < 12) return p_dMaxGeschwindigkeit;

	double result = p_dMaxGeschwindigkeit * std::pow(0.9, p_dGesamtStrecke/20);

	if (result < 12) return 12;
	else return result;
}

void Fahrrad::vAusgeben(std::ostream& out) const
{
	Fahrzeug::vAusgeben(out);
}

void Fahrrad::vZeichnen(const Weg &weg)
{
	bZeichneFahrrad(getName(), weg.getName(), (double) p_dAbschnittStrecke / weg.getLaenge(), dGeschwindigkeit());
}
