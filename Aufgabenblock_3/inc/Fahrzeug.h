/*
 * Fahrzeug.h
 *
 *  Created on: 15.10.2023
 */
#pragma once

#include <string>
#include <iostream>
#include <iomanip>
#include <limits>
#include <memory>

#include "Simulationsobjekt.h"

//Importieren der externen, globalen Zeit
extern double dGlobaleZeit;

class Weg;
class Verhalten;

class Fahrzeug : public Simulationsobjekt {
public:
	///Konstruktor mit Standardeigenschaften
	Fahrzeug(std::string initName = "", double initMaxVelo = 0);
	///Löschen des Copy-Konstruktor
	Fahrzeug(const Fahrzeug&) = delete;
	///Destruktor
	virtual ~Fahrzeug();

	///Ausgabe vom Tabellenkopf für die Ausgabe
	static void vKopf();
	///Ausgabefunktion für die Eigenschaften des Fahrzeugs
	virtual void vAusgeben(std::ostream& out) const override;

	///Simulationsfunktion zum Simulieren vom Verhalten
	virtual void vSimulieren() override;

	///Tankfunktion, muss bei Fahrzeugen mit Tank überschrieben werden
	virtual double dTanken(double dMenge = std::numeric_limits<double>::infinity());

	///Ausgabe der aktuellen Geschwindigkeit. Diese entspricht der maximalen Geschwindigkeit, solange dies nicht überladen wurde
	virtual double dGeschwindigkeit() const;

	///Setzen eines neuen Wegs um das Verhalten vom Fahrzeug ändern zu können
	void vNeueStrecke(Weg& neuerWeg);
	///Setzen eines neuen Wegs um das Verhalten vom parkenden Fahrzeug ändern zu können
	void vNeueStrecke(Weg& neuerWeg, double StartZeit);

	///Zeichnen vom Fahrzeug im GUI, rein virtuell
	virtual void vZeichnen(const Weg& weg) = 0;

	///Rückgabe der zurückgelegten Gesamtstrecke
	double getGesamtStrecke() const;
	///Rückgabe der auf dem Abschnitt zurückgelegten Strecke
	double getAbschnittStrecke() const;

	///Überladen des "kleiner als" Vergeleichoperators zum Vergleich der zurückgelegten Gesamtstrecke
	bool operator<(const Fahrzeug& oprnd);
	///Überladen des copy Operators. Setzt den Namen und Maximale Geschwindigkeit
	Fahrzeug& operator=(const Fahrzeug& oprnd);

protected:
	///Eigenschaften vom Fahrzeug
	double p_dMaxGeschwindigkeit;
	double p_dGesamtStrecke;
	double p_dGesamtZeit;
	std::unique_ptr<Verhalten> p_pVerhalten;
	double p_dAbschnittStrecke;

};
