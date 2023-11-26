/*
 * Fahrzeug.cpp
 *
 *  Created on: 15.10.2023
 *      Author: llohm
 */

#include "Fahrzeug.h"
#include "AusgabeKonstanten.h"
#include "Verhalten.h"
#include "Weg.h"
#include "Fahren.h"
#include "Parken.h"

Fahrzeug::Fahrzeug(std::string initName, double initMaxVelo)
	: Simulationsobjekt(initName), p_dMaxGeschwindigkeit(initMaxVelo), p_dGesamtStrecke(0), p_dGesamtZeit(0), p_dAbschnittStrecke(0)
{
}

Fahrzeug::~Fahrzeug()
{
}

void Fahrzeug::vKopf()
{
	auto oldWidth = std::cout.width();
	auto oldFill = std::cout.fill();

	std::cout << std::setiosflags(std::ios::left);

	std::cout << std::setw(ID_WIDTH) << "ID";
	std::cout << std::setw(SEPERATOR_WIDTH) << ' ';
	std::cout << std::setw(NAME_WIDTH) << "Name";
	std::cout << std::setw(SEPERATOR_WIDTH) << ' ';
	std::cout << std::setw(MAX_VELO_WIDTH) << "MaxGeschwindigkeit";
	std::cout << std::setw(SEPERATOR_WIDTH) << ' ';
	std::cout << std::setw(GESAMTSTRECKE_WIDTH) << "GesamtStrecke";
	std::cout << std::setw(SEPERATOR_WIDTH) << ' ';
	std::cout << std::setw(GESCHWINDIGKEIT_WIDTH) << "Geschwindigkeit";
	std::cout << std::setw(SEPERATOR_WIDTH) << ' ';
	std::cout << std::setw(GESAMTVERBRAUCH_WIDTH) << "GesamtVerbrauch";
	std::cout << std::setw(SEPERATOR_WIDTH) << ' ';
	std::cout << std::setw(TANKINHALT_WIDTH) << "Tankinhalt";
	std::cout << std::endl;
	std::cout << std::setfill('-') << std::setw(FAHRZEUG_WIDTH) << '-';
	std::cout << std::endl;

	std::cout << std::resetiosflags(std::ios::left);
	std::cout << std::setw(oldWidth) << std::setfill(oldFill);
}

void Fahrzeug::vAusgeben(std::ostream& out) const
{
	auto oldWidth = out.width();
	auto oldPrec = out.precision();

	Simulationsobjekt::vAusgeben(out);

	out << std::setw(SEPERATOR_WIDTH) << ' ';
	out << std::setw(MAX_VELO_WIDTH) << std::setprecision(2) << std::setiosflags(std::ios::fixed) << p_dMaxGeschwindigkeit;
	out << std::setw(SEPERATOR_WIDTH) << ' ';
	out << std::setw(GESAMTSTRECKE_WIDTH) << p_dGesamtStrecke;
	out << std::setw(SEPERATOR_WIDTH) << ' ';
	out << std::setw(GESCHWINDIGKEIT_WIDTH) << dGeschwindigkeit() << std::resetiosflags(std::ios::fixed);

	out << std::setw(oldWidth) << std::setprecision(oldPrec);
}

void Fahrzeug::vSimulieren()
{
	double dt = dGlobaleZeit - p_dZeit;
	if (abs(dt) < 3 * std::numeric_limits<double>::min()) { std::cout << "Fahrzeug doppelt simuliert: (" << p_sName << ", " << p_iID << ')' << std::endl; return; }
	p_dZeit = dGlobaleZeit;
	p_dGesamtZeit += dt;

	double tempStrecke = p_pVerhalten->dStrecke(*this, dt);
	p_dGesamtStrecke += tempStrecke;
	p_dAbschnittStrecke += tempStrecke;
}

double Fahrzeug::dTanken(double dMenge)
{
	return 0.0;
}

double Fahrzeug::dGeschwindigkeit() const
{
	return p_dMaxGeschwindigkeit;
}

void Fahrzeug::vNeueStrecke(Weg& neuerWeg)
{
	p_pVerhalten = std::make_unique<Fahren>(neuerWeg);
	p_dAbschnittStrecke = 0;
}

void Fahrzeug::vNeueStrecke(Weg& neuerWeg, double StartZeit)
{
	p_pVerhalten = std::make_unique<Parken>(neuerWeg, StartZeit);
	p_dAbschnittStrecke = 0;
}

double Fahrzeug::getGesamtStrecke() const
{
	return p_dGesamtStrecke;
}

double Fahrzeug::getAbschnittStrecke() const
{
	return p_dAbschnittStrecke;
}

bool Fahrzeug::operator<(const Fahrzeug& oprnd)
{
	return p_dGesamtStrecke < oprnd.getGesamtStrecke();
}

Fahrzeug& Fahrzeug::operator=(const Fahrzeug& oprnd)
{
	if (this == &oprnd) return *this;
	p_sName = oprnd.p_sName;
	p_dMaxGeschwindigkeit = oprnd.p_dMaxGeschwindigkeit;
	return *this;
}
