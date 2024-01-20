#include <Constants.h>
#include "PKW.h"
#include "Verhalten.h"
#include "SimuClient.h"
#include "Weg.h"

/**
 * Konstruktor für den PKW
 *
 * @param initName Name für den PKW
 * @param initMaxVelo Maximale Geschwindigkeit vom PKW
 * @param initVerbrauch Verbrauch des PKWs auf 100km in Litern
 * @param initTankvolumen Tankvolumen vom PKW in Litern
 */
PKW::PKW(std::string initName, double initMaxVelo, double initVerbrauch, double initTankvolumen)
	: Fahrzeug(initName, initMaxVelo), p_dVerbrauch(initVerbrauch), p_dTankvolumen(initTankvolumen), p_dTankinhalt(p_dTankvolumen/2)
{
}

/**
 * Destruktor vom PKW
 */
PKW::~PKW()
{
}

/**
 * Tanken des PKW
 * Wird keine Menge angegeben wird der PKW vollgetankt
 *
 * @param dMenge Menge in Litern die der PKW getankt werden soll, wenn keine Menge übergeben wird, wird vollgetankt
 * @return Menge die Tatsächlich getankt wurde in Litern
 */
double PKW::dTanken(double dMenge)
{
	//Weiteres ausleeren des Tanks ausschließen
	if (dMenge < 0) return 0;
	//Wenn mehr getankt werden als in den Tank passen, wird berechnet was wirklich getankt wird.
	if (dMenge > p_dTankvolumen - p_dTankinhalt)
	{
		double dGetankt = p_dTankvolumen - p_dTankinhalt;
		p_dTankinhalt = p_dTankvolumen;
		return dGetankt;
	}
	
	//normales tanken, wenn die Menge kleiner als das freie Volumen ist.
	p_dTankinhalt += dMenge;

	return dMenge;
}

/**
 * Ausgabe der aktuellen Geschwindigkeit.
 * Diese entspricht nicht der maximalen Geschwindigkeit vom PKW, wenn auf der aktuellen Straße eine Geschwindigkeitsbegrenzung gilt.
 * Wenn eine Geschwindigkeitsbegrenzung gilt, fährt der PKW mit dieser Geschwindigkeit
 *
 * @return aktuelle Geschwindigkeit vom PKW
 */
double PKW::dGeschwindigkeit() const
{
	if (p_dMaxGeschwindigkeit < p_pVerhalten->getWegTempolimit()) return Fahrzeug::dGeschwindigkeit();
	else return p_pVerhalten->getWegTempolimit();
}

/**
 * Simulieren vom PKW
 */
void PKW::vSimulieren()
{
	//Wenn der Tank nicht leer ist fahrt der PKW weiter. Ansonsten bleibt der PKW stehen und die Zeit wird aktualisiert
	if (p_dTankinhalt > 0)
	{
		double ds = p_dGesamtStrecke;
		Fahrzeug::vSimulieren();
		ds = p_dGesamtStrecke - ds;	//Berechnen der gefahrenen Strecke
		p_dTankinhalt -= ds * p_dVerbrauch / 100; //Berechnen des Kraftstoffverbrauchs und aktualisierung vom Tankinhalt
	}
	else
	{
		p_dZeit = dGlobaleZeit;
	}
	if (p_dTankinhalt < 0) p_dTankinhalt = 0;
}

/**
 * Ausgabe der Eigenschaften vom PKW. Zusätzlich zu den allgemeinen Eigenschaften vom Fahrzeug wird noch der Gesamtverbrauch und der aktuelle Tankinhalt ausgegeben.
 * @param out Stream für die Ausgabe
 */
void PKW::vAusgeben(std::ostream& out) const
{
	Fahrzeug::vAusgeben(out);
	out << std::setw(SEPERATOR_WIDTH) << ' ';
	out << std::setw(GESAMTVERBRAUCH_WIDTH) << p_dGesamtStrecke * p_dVerbrauch / 100;
	out << std::setw(SEPERATOR_WIDTH) << ' ';
	out << std::setw(TANKINHALT_WIDTH) << p_dTankinhalt;
}

/**
 * Zeichnen des PKW auf dem GUI
 * @param weg Weg auf dem sich der PKW aktuell befindet
 */
void PKW::vZeichnen(const Weg &weg)
{
	bZeichnePKW(getName(), weg.getName(), (double) p_dAbschnittStrecke / weg.getLaenge(), dGeschwindigkeit(), p_dTankinhalt);
}

void PKW::vEinlesen(std::istream &in)
{
	Fahrzeug::vEinlesen(in);
	in >> p_dVerbrauch >> p_dTankvolumen;
}
