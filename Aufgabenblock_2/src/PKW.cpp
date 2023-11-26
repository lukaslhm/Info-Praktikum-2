#include "PKW.h"
#include "Verhalten.h"
#include "AusgabeKonstanten.h"

PKW::PKW(std::string initName, double initMaxVelo, double initVerbrauch, double initTankvolumen)
	: Fahrzeug(initName, initMaxVelo), p_dVerbrauch(initVerbrauch), p_dTankvolumen(initTankvolumen), p_dTankinhalt(p_dTankvolumen/2)
{
}

PKW::~PKW()
{
}

double PKW::dTanken(double dMenge)
{
	if (dMenge < 0) return 0;
	if (dMenge > p_dTankvolumen - p_dTankinhalt)
	{
		double dGetankt = p_dTankvolumen - p_dTankinhalt;
		p_dTankinhalt = p_dTankvolumen;
		return dGetankt;
	}
	
	p_dTankinhalt += dMenge;

	return dMenge;
}

double PKW::dGeschwindigkeit() const
{
	if (p_dMaxGeschwindigkeit < p_pVerhalten->getWegTempolimit()) return Fahrzeug::dGeschwindigkeit();
	else return p_pVerhalten->getWegTempolimit();
}

void PKW::vSimulieren()
{
	if (p_dTankinhalt > 0)
	{
		double ds = p_dGesamtStrecke;
		Fahrzeug::vSimulieren();
		ds = p_dGesamtStrecke - ds;
		p_dTankinhalt -= ds * p_dVerbrauch / 100;
	}
	else
	{
		p_dZeit = dGlobaleZeit;
	}
	if (p_dTankinhalt < 0) p_dTankinhalt = 0;
}

void PKW::vAusgeben(std::ostream& out) const
{
	Fahrzeug::vAusgeben(out);
	out << std::setw(SEPERATOR_WIDTH) << ' ';
	out << std::setw(GESAMTVERBRAUCH_WIDTH) << p_dGesamtStrecke * p_dVerbrauch / 100;
	out << std::setw(SEPERATOR_WIDTH) << ' ';
	out << std::setw(TANKINHALT_WIDTH) << p_dTankinhalt;
}
