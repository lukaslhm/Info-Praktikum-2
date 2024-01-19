#pragma once

#include <list>
#include <string>
#include <iostream>
#include <memory>

#include "Simulationsobjekt.h"
#include "Tempolimit.h"
#include "vertagt_liste.h"

class Fahrzeug;

class Weg : public Simulationsobjekt
{
public:
	///Default konstruktor
	Weg() = default;
	///Konstruktor mit Name, Länge und Tempolimit. Tempolimit ist ald default unbegrenzt
	Weg(std::string initName, double initLaenge, Tempolimit initTempolimit = Tempolimit::Autobahn, bool ueberholverbot = true);
	///Destruktor
	~Weg();

	///Ausgabe des Tabellenkopfs für die Ausgabe der Wege als Liste im Terminal
	static void vKopf();

	///Simulieren vom Weg und den zugehörigen Fahrzeugen
	void vSimulieren() override;
	///Ausgabe vom Weg und den aktuellen Fahrzeugen
	void vAusgeben(std::ostream& out) const override;
	///Alle Fahrzeuge vom Weg ausgeben
	void vFahrzeugeAusgeben() const;

	///Neues Fahrzeug auf den Weg aufnehmen
	void vAnnahme(std::unique_ptr<Fahrzeug> fzg);
	///Neues parkendes Fahrzeug auf den Weg aufnehmen
	void vAnnahme(std::unique_ptr<Fahrzeug> fzg, double StartZeit);

	///Fahrzeug in der Liste der aktuellen Fahrzeuge suchen, löschen und zurückgeben
	std::unique_ptr<Fahrzeug> pAbgabe(const Fahrzeug& fzg);

	void setVirtuelleSchranke(double newValue);

	///Rückgabe des Tempolimits auf der Straße
	double getTempolimit() const;
	///Rückgabe von der Straßenlänge
	double getLaenge() const;

	double getVirtuelleSchranke() const;

private:
	///Eigenschaften vom Weg
	double p_dLaenge;
	vertagt::VListe<std::unique_ptr<Fahrzeug>> p_pFahrzeuge;
	bool p_bUeberholverbot;
	Tempolimit p_eTempolimit;
	double p_dVirtuelleSchranke;

};

