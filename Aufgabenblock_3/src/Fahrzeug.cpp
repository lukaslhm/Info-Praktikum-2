/*
 * Fahrzeug.cpp
 *
 *  Created on: 15.10.2023
 */

#include "Constants.h"
#include "Fahrzeug.h"
#include "Verhalten.h"
#include "Weg.h"
#include "Fahren.h"
#include "Parken.h"
#include <cmath>

/**
 * Konstruktor vom Fahrzeug
 *
 * @param initName Name für das Fahrzeug, standardmäßig leer
 * @param initMaxVelo Maximale Geschwindigkeit für das Fahrzeug, standardmäßig 0
 */
Fahrzeug::Fahrzeug(std::string initName, double initMaxVelo)
	: Simulationsobjekt(initName), p_dMaxGeschwindigkeit(initMaxVelo), p_dGesamtStrecke(0), p_dGesamtZeit(0), p_dAbschnittStrecke(0)
{
}

/**
 * Destruktor für das Fahrzeug
 */
Fahrzeug::~Fahrzeug()
{
}

/**
 * Ausgabe vom Listenkopf für die Eigenschaften des Fahrzeuges im Terminal
 */
void Fahrzeug::vKopf()
{
	//Anpassen an die Breite des Terminals
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

/**
 * Ausgabe der Eigenschaften vom Fahrzeug
 * Ausgabe von maximaler Geschwindigkeit, Gesamtstrecke und die aktuelle Geschwindigkeit
 *
 * @param out Stream für die Ausgabe
 */
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

/**
 * Simulieren des Fahrzeuges bis zur aktuellen globalen Zeit
 */
void Fahrzeug::vSimulieren()
{
	//Berechnen der noch nicht simulierten Zeit
	double dt = dGlobaleZeit - p_dZeit;
	//Schutz vor Doppeltsimulierung
	if (fabs(dt) < 3 * std::numeric_limits<double>::min()) { std::cout << "Fahrzeug doppelt simuliert: (" << p_sName << ", " << p_iID << ')' << std::endl; return; }
	p_dZeit = dGlobaleZeit;
	p_dGesamtZeit += dt;

	double tempStrecke = p_pVerhalten->dStrecke(*this, dt);
	p_dGesamtStrecke += tempStrecke;
	p_dAbschnittStrecke += tempStrecke;
}

/**
 * Tankfunktion für Fahrzeuge. Gibt die tatsächlich getankte Menge zurück. Wenn keine Tankmenge übergeben wird, wird vollgetankt.
 * Muss für Fahrzeuge mit Tank überschrieben werden.
 *
 * @param dMenge Menge in Litern die getankt werden soll, ohne Wert wird vollgetankt
 * @return Tatsächlich getankte Menge in Litern
 */
double Fahrzeug::dTanken(double dMenge)
{
	return 0.0;
}

/**
 * Aktuelle Geschwindigkeit. Entspricht der maximalen Geschwindigkeit, solange die Methode nicht überschrieben wird.
 *
 * @return aktuelle Gescwindigkeit, entspricht der maximalen Geschwindigkeit
 */
double Fahrzeug::dGeschwindigkeit() const
{
	return p_dMaxGeschwindigkeit;
}

/**
 * Setzen eines neuen Wegs um das Verhalten vom Fahrzeug ändern zu können
 *
 * @param neuerWeg Weg der auf das Fahrzeug angewendet werden soll
 */
void Fahrzeug::vNeueStrecke(Weg& neuerWeg)
{
	p_pVerhalten = std::make_unique<Fahren>(neuerWeg);
	p_dAbschnittStrecke = 0;
}

/**
 * Setzen eines neuen Wegs um das Verhalten vom parkende Fahrzeug ändern zu können
 *
 * @param neuerWeg Weg der auf das Fahrzeug angewendet werden soll
 * @param StartZeit Startzeit für das Verhalten
 */
void Fahrzeug::vNeueStrecke(Weg& neuerWeg, double StartZeit)
{
	p_pVerhalten = std::make_unique<Parken>(neuerWeg, StartZeit);
	p_dAbschnittStrecke = 0;
}

/**
 * Gesamtstrecke die das Fahrzeug gefahren ist
 *
 * @return gesamte Strecke des Fahrzeuges
 */
double Fahrzeug::getGesamtStrecke() const
{
	return p_dGesamtStrecke;
}

/**
 * Strecke die das Fahrzeug auf dem Abschnitt gefahren ist
 *
 * @return Strecke auf dem Abschnitt
 */
double Fahrzeug::getAbschnittStrecke() const
{
	return p_dAbschnittStrecke;
}

/**
 * Überladen des "kleiner als" Operators zum Vergleichen der gefahrenen Gesamtstrecke
 *
 * @param oprnd Fahrzeug zum Vergleichen der gefahrenen Gesmatstrecke
 * @return bool welches Fahrzeug eine größere Gesamtstrecke hat
 */
bool Fahrzeug::operator<(const Fahrzeug& oprnd)
{
	return p_dGesamtStrecke < oprnd.getGesamtStrecke();
}

/**
 * Überladung des copy Operators um ein Kopieren zu ermöglichen
 *
 * @param oprnd Fahrzeug, das auf das aktuelle Fahrzeug angewendet werden soll
 * @return Das kopierte Fahrzeug
 */
Fahrzeug& Fahrzeug::operator=(const Fahrzeug& oprnd)
{
	if (this == &oprnd) return *this;
	p_sName = oprnd.p_sName;
	p_dMaxGeschwindigkeit = oprnd.p_dMaxGeschwindigkeit;
	return *this;
}

/**
 * Daten aus Stream (von Datei) in Fahrzeug einlesen um die Eigenschaften zu setzen
 * @param in
 */
void Fahrzeug::vEinlesen(std::istream &in)
{
	Simulationsobjekt::vEinlesen(in); //Nutzen vom Partentobjekt
	in >> p_dMaxGeschwindigkeit; //Zusaätzlich noch die maximale Geschwindigkeit
}
