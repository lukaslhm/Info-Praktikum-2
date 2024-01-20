#pragma once

#include <list>
#include <string>
#include <iostream>
#include <memory>

#include "Simulationsobjekt.h"
#include "Tempolimit.h"
#include "vertagt_liste.h"

class Fahrzeug;
class Kreuzung;

class Weg : public Simulationsobjekt
{
public:
	///Default konstruktor
	Weg() = default;
	///Konstruktor mit Name, Länge und Tempolimit. Tempolimit ist ald default unbegrenzt
	Weg(std::string initName, double initLaenge, Tempolimit initTempolimit = Tempolimit::Autobahn, bool ueberholverbot = true, std::weak_ptr<Kreuzung> zielKreuzung = std::weak_ptr<Kreuzung>());
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

	void setRueckWeg(std::weak_ptr<Weg> rueckWeg);
	///Rückgabe des Tempolimits auf der Straße
	double getTempolimit() const;
	///Rückgabe von der Straßenlänge
	double getLaenge() const;

	double getVirtuelleSchranke() const;

	std::shared_ptr<Kreuzung> getZielKreuzung() const;
	std::shared_ptr<Weg> getRuckWeg() const;

private:
	///Eigenschaften vom Weg
	double p_dLaenge = 0;
	vertagt::VListe<std::unique_ptr<Fahrzeug>> p_pFahrzeuge;
	bool p_bUeberholverbot = true;
	Tempolimit p_eTempolimit = Tempolimit::Autobahn;
	double p_dVirtuelleSchranke = 0;

	std::weak_ptr<Weg> p_pRueckWeg;
	const std::weak_ptr<Kreuzung> p_pZielKreuzung = std::weak_ptr<Kreuzung>();

};

